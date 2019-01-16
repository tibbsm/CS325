//  SIMULATED ANNEALING ALGORITHM 
//  Filename: 	TSP_SA.cpp
//  Author:     Marc Tibbs

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "nrutil.h"
#include <time.h>
#include <string.h>

// Distance calculation
#define ALEN(a,b,c,d) round(sqrt(((b-a)*(b-a))+((d-c)*(d-c))))

// 
#define MBIG 1000000000

// 
#define MSEED 161803398

// 
#define MZ 0

// 
#define FAC (1.0/MBIG)


// Calculates the tour length of an array of city locations
int tourDistance(float x[], float y[], int iorder[], int ncity){
    int start, destination, path = 0;

    // Calculate initial path length.
    for (int i = 1; i < ncity; i++){
        start = iorder[i];
        destination = iorder[i+1];
        path += ALEN(x[start], x[destination], y[start], y[destination]);
    }
    
    // Close the loop by tying path ends together.
    start = iorder[ncity];
    destination = iorder[1];
    path += ALEN(x[start], x[destination], y[start], y[start]);

	return path;
}


// CITED FROM: "Numerical Recipes" by W. Press & S. Teukolsky
// Returns a uniform random deviate btwn 0.0 and 1.0. 
// Set idum to any negative value to initialize or reinitialize the sequence.
float ran3(long *idum){
    static int inext, inextp;
    static long ma[56]; // The value 56 (range ma[1..55] is special and should not be modified; see Knuth.)
    static int iff=0;
    long mj, mk;
    int i, ii, k;

    // Initialization.
    if (*idum < 0 || iff == 0){
        iff = 1;
        mj = labs(MSEED-labs(*idum)); // Initialize ma[55] using the seed idum and the large number MSEED.
        mj %= MBIG;
        ma[55] = mj;
        mk = 1;

        // Now initialize the rest of the table, in slightly random order, with numbers that are not especially random.
        for (i = 1; i < 54; i++){
            ii = (21*i) % 55;
            ma[ii] = mk;
            mk = mj - mk;
            if (mk < MZ)
                mk += MBIG;
            mj = ma[ii];
        }
        // We randomize them by "warming up the generator"
        for (k = 1; k<=4; k++){
            for (i = 1; i <=55; i++){
                ma[i] -= ma[1+(i+30) % 55];
                if (ma[i] < MZ)
                    ma[i] += MBIG;
            }
        }
        inext = 0;
        inextp = 31;
        *idum = 1;
    }
    // Here is where we start, except on initialization.
    if (++inext == 56) inext = 1;       // Increment inext & inextp, wrapping around 56 to 1
    if (++inextp == 56) inextp = 1;
    mj = ma[inext]-ma[inextp];          // Generate a new random number subtractively.
    if (mj < MZ) mj += MBIG;            // Be sure that it is in range.
    ma[inext] = mj;                     // Store it
    return mj * FAC;                    // and output the derived uniform deviate

}

#define IB1 1           //Powers of 2.
#define IB2 2
#define IB5 16
#define IB18 131072
#define MASK (IB1+IB2+IB5)

// CITED FROM: "Numerical Recipes" by W. Press & S. Teukolsky
// Returns as an integer a random bit, based on the 18 low-significance bits in iseed (which is modified for the next call).
int irbit1(unsigned long *iseed){
    if (*iseed & IB18) {                          // Change all masked bits, shift, and put 1 into bit 1.
        *iseed = ((*iseed ^ MASK) << 1) | IB1;
        return 1;
    } else {                                      // Shift and put 0 into bit 1.
        *iseed <<= 1;
        return 0;
    }
}


//Annealing schedule: Reduce t by this factor on each step.
#define TFACTOR 0.992

//This algorithm finds the shortest round-trip path to ncity cities whose coordinates are in x[1...ncity], y[1...ncity].
//The array iorder[1...ncity] specifies the order in which the cities are visited.
//On input, the elements of iOrder may be set to any permutation of numbers 1 to ncity.
//This routine will return the best alternative path it can find.
void anneal(float x[], float y[], int iorder[], int ncity){
    int irbit1(unsigned long *iseed);
    int metrop(float de, float t);
    float ran3(long *idum);
    float revcst(float x[], float y[], int iorder[], int ncity, int n[]);
    void reverse(int iorder[], int ncity, int n[]);
    float trncst(float x[], float y[], int iorder[], int ncity, int n[]);
    void trnspt(int iorder[], int ncity, int n[]);
    int ans, nover, nlimit, i1, i2;
    int i, j, k, nsucc, nnsucc = 0, nn, idec, zz;
    static int n[7];
    long idum;
    unsigned long iseed;
    float path, de, t;
    int best_distance;
    int *best_tour = malloc(ncity*sizeof(int));

    // Max number of paths tried at any temperature.
    nover = 180 * ncity;
    // Max number of successful path changes before continuing.
    nlimit = 10 * ncity;
    path = 0.0;
    t =   30.0;
   
    // Calculate initial path length.
    for (i = 1; i < ncity; i++){
        i1 = iorder[i];
        i2 = iorder[i+1];
        path += ALEN(x[i1], x[i2], y[i1], y[i2]);
    }
    
    // Close the loop by tying path ends together.
    i1 = iorder[ncity];
    i2 = iorder[1];
    path += ALEN(x[i1], x[i2], y[i1], y[i2]);
    idum = -1;
    iseed = 111;
    best_distance = path;

    // Try up to j temperatures
    for (j = 1; j <= 605; j++){
        nsucc = 0;
        for (k = 1; k <= nover; k++) {
            
            do {
                // Choose beginning and end of segment.
                n[1] = 1 + (int)(ncity * ran3(&idum));
                n[2] = 1 + (int)((ncity-1) * ran3(&idum));
                
                if (n[2] >= n[1]){
                    ++n[2];
                }
                // nn is the number of cities not on the segment.
                nn = 1 + ((n[1] - n[2] + ncity - 1) % ncity);
            } while (nn < 3);
            idec = irbit1(&iseed);
            // Decide whether to do a segment reversal or transport.
            // Do a transport.
            if (idec == 0) {
                n[3] = n[2]+(int) (abs(nn-2)*ran3(&idum))+1;
                n[3] = 1 + ((n[3]-1) % ncity);
                
                // Transport to a location not on the path.
                de = trncst(x, y, iorder, ncity, n);    // Calculate cost.

                ans = metrop(de, t);                    // Consult the oracle.

                if(ans) {
                    ++nsucc;
                    path += de;
                    trnspt(iorder, ncity, n);           // Carry out the transport.
                }
                // Do a path reversal.
                } else {
                de = revcst(x, y, iorder, ncity, n);    // Calculate cost.
               
                ans = metrop(de, t);                    // Consult the oracle.
                 
                if (ans){
                    ++nsucc;

                    path += de;
                    reverse(iorder, ncity, n);          // Carry out the reversal.
                }
            }
            // Finish early if we have enough successful changes.
            if (nsucc >= nlimit) break;
        }
        // printf("T: %10.6f", t);
        // printf(" - Path: %12.6f ", path);
        // printf(" - Moves: %6d\n", nsucc);

    // Annealing Schedule
        t *= TFACTOR;
        // If no successes, we are done.
        if (nsucc == 0){
           if(nnsucc == 5){    
            return;
           }
           nnsucc++; 
        }
    }
}

// This function returns the value of the cost function for proposed path reversal.
// ncity is the number of cities, and arrays x[1...ncity], y[1...ncity] give the coordinates of these cities.
// iorder[1...ncity] holds the present itinerary.
// The first two values n[1] and n[2] of array n give the starting and ending cities along the path segment which is to be reversed.
// On output, de is the cost of making the reversal. The actual reversal is not preformed by this routine.
float revcst(float x[], float y[], int iorder[], int ncity, int n[]){
    float xx[5], yy[5], de;
    int j, ii;
    
    // Find the city before n[1] and the city after n[2].
    n[3] = 1 + ((n[1] + ncity - 2) % ncity);
    n[4] = 1 + (n[2] % ncity);
    
    // Find the coordinates for the four cities involved.
    for (j = 1; j <= 4; j++){
        ii = iorder[n[j]];
        xx[j] = x[ii];
        yy[j] = y[ii];
    }

    // Calculate cost of disconnecting the segment at both ends and reconnecting in the opposite order.
    de = -ALEN(xx[1], xx[3], yy[1], yy[3]);
    de -= ALEN(xx[2], xx[4], yy[2], yy[4]);
    de += ALEN(xx[1], xx[4], yy[1], yy[4]);
    de += ALEN(xx[2], xx[3], yy[2], yy[3]);

    return de;
}

// This routine performs a path segment reversal.
// iorder[1...ncity] is an input array giving the present itinerary.
// The vector n has as its first four elements the first and last cities n[1], n[2] of the path segment to be reversed, and the two cities n[3] & n[4] that immediately precede and follow this segment.
// n[3] and n[4] are found by function revcst. On output, iorder[1...ncity] contains the segment from n[1] to n[2] in reversed order.
void reverse(int iorder[], int ncity, int n[]){
    int nn, j, k, l, itmp;
    
    // This many cities must be swapped to effect the reversal.
    nn = (1 + ((n[2] - n[1] + ncity) % ncity)) / 2;
    
    // Start at the ends of the segment and swap pairs of cities, moving toward the center.
    for (j = 1; j <=nn; j++){
        k = 1 + ((n[1] + j - 2) % ncity);
        l = 1 + ((n[2] - j + ncity) % ncity);
        itmp = iorder[k];
        iorder[k] = iorder[l];
        iorder[l] = itmp;
    }
}

// This routine returns the value of the cost function for a proposed path segment transport.
// ncity is the number of cities, and arrays x[1...ncity] and y[1...ncity] give the city coordinates.
// iorder[1...ncity] is an array giving the present itinerary.
// The first three elements of array n give the starting and ending cities of the path to be transported, and the point among the remaining cities after which it is to be inserted.
// On output, de is the cost of the change. The actual transport is not performed by this routine.
float trncst(float x[], float y[], int iorder[], int ncity, int n[]){
    float xx[7], yy[7], de;
    int j, ii;
    
    n[4] = 1 + (n[3] % ncity);                  // Find the city following n[3]
    n[5] = 1 + ((n[1] + ncity - 2) % ncity);    // Find the city preceding n[1]
    n[6] = 1 + (n[2] % ncity);                  // Find the city following n[2]
    
    // Determine coordinates for the six cities involved.
    for (j = 1; j <= 6; j++){
        ii = iorder[n[j]];
        xx[j] = x[ii];
        yy[j] = y[ii];
    }
    
    // Calculate the cost of disconnecting the path segment form n[1] to n[1], opening a space btwn n[3] and n[4], connecting the segment in the space, and connecting n[5] to n[6].
    de = -ALEN(xx[2], xx[6], yy[2], yy[6]);
    de -= ALEN(xx[1], xx[5], yy[1], yy[5]);
    de -= ALEN(xx[3], xx[4], yy[3], yy[4]);
    de += ALEN(xx[1], xx[3], yy[1], yy[3]);
    de += ALEN(xx[2], xx[4], yy[2], yy[4]);
    de += ALEN(xx[5], xx[6], yy[5], yy[6]);
    return de;
}

// This routine does the actual path transport, once metrop has approved.
// iorder[1..ncity] is an input array giving the present itinerary.
// The array n has as its six elements the beginning n[1] and end n[2] of the path to be transported, the adjacent cities n[3] and n[4] btwn which the path is to be placed, and the cities n[5] and n[6] that preced and follow the path.
// n[4], n[5], n[6] are calculated by function trncst.
// On output, iorder is modified to reflect the movement of the path segment.
void trnspt (int iorder[], int ncity, int n[]){
    int m1, m2, m3, nn, j, jj, *jorder;
    
    jorder = ivector(1, ncity);
    m1 = 1 + ((n[2] - n[1] + ncity) % ncity);   // Find number of cities from n[1] to n[2]
    m2 = 1 + ((n[5] - n[4] + ncity) % ncity);   // Find number of cities from n[4] to n[5]
    m3 = 1 + ((n[3] - n[6] + ncity) % ncity);   // Find number of cities from n[6] to n[3]
    
    nn = 1;
    
    // Copy the chosen segment
    for (j = 1; j <= m1; j++){
        jj = 1 + ((j + n[1] - 2) % ncity);
        jorder[nn++] = iorder[jj];
    }
    
    // Copy the segment from n[4] to n[5]
    for (j = 1; j <= m2; j++){
        jj = 1 + ((j + n[4] - 2) % ncity);
        jorder[nn++] = iorder[jj];
    }
    
    // Copy the segment from n[6] to n[3]
    for (j = 1; j <= m3; j++){
        jj = 1 + ((j + n[6] - 2) % ncity);
        jorder[nn++] = iorder[jj];
    }
    // Copy jorder back into iorder
    for (j = 1; j <= ncity; j++){
        iorder[j] = jorder[j];
    }
    
    free_ivector(jorder, 1, ncity);
}


// Metropolis algorithm returns a boolean variable that issues a verdict on whether  to accept a reconfiguration that leads to a change de in the objective function e.
// If de < 0, metrop = 1 (true), while if de > 0, metrop is only true with probability exp(-de/t), where t is a temperature determined by the annealing schedule.
int metrop(float de, float t){
    float ran3(long *idum);
    static long gljdum = 1;
    
    return de < 0.0 || ran3(&gljdum) < exp(-de/t);
}



int main( int argc, char** argv ) {

    FILE *infile;
    int size = 0;
    int i = 0;

    infile = fopen(argv[1],"r");
    if (!infile){
    	printf("File could not be found/opened.\n");
        return 1;
    }

	// Get number of cities
    while(!feof(infile)) {
        fscanf(infile,"%d%*[^\n]", &size);   
    } 
    fclose(infile);
    size++;
 
    int tmp = 0;
    float ftmp = 0;

    // Create arrays for holding city data
    int *iorder = malloc(size*sizeof(int));
    float *x = malloc(size*sizeof(float));
    float *y = malloc(size*sizeof(float));

    infile =fopen(argv[1],"r");

    // Copy city data to arrays
    for (i = 1; i <= size; i++) {
        fscanf(infile," %d", &tmp);
        iorder[i] = tmp+1;
        
        fscanf(infile," %f", &ftmp);
        x[i] = ftmp;

        fscanf(infile," %f", &ftmp);
        y[i] = ftmp;
    } 

    // 
    clock_t begin, end;
    double time_spent = 0.0;
    int best_distance = tourDistance(x, y, iorder, size); 
    int *best_tour = malloc(size*sizeof(int));

    begin = clock();

    // Run SA algorithm within time frame
    while (time_spent < 120.0){

        anneal(x, y, iorder, size);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        int distance =  tourDistance(x, y, iorder, size);

        if (distance < best_distance){
            best_distance = distance;
            memcpy(best_tour, iorder, sizeof(iorder)*size) ;
           // printf("distance: %d\n", distance);
        }
    }

    printf("Best Distance: %d - ", best_distance);
    printf("Time: %3.2f seconds \n\n ", time_spent);

	//Write to output file
	char outfile[100];
	strcpy(outfile, argv[1]);
	strcat(outfile, ".tour");

	FILE *output = fopen(outfile, "w");
	fprintf(output, "%d\n", best_distance);

    for (i = 1; i <= size; i++) {
        fprintf(output, "%d ", best_tour[i]-1);
        fprintf(output,"%10.0f ", x[best_tour[i]]);
        fprintf(output, "%10.0f \n", y[best_tour[i]]);
    }
	    
	fclose(output);
    return 0;
}
