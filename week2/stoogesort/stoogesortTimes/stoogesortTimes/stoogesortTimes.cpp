// Author: Marc Tibbs (tibbsm@oregonstate.edu)
// Date: January 21, 2018
// Description: This program takes a text file and sorts the numbers listed in the file using STOOGESORT

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

void stoogeSort(int A[], int lo, int hi) {
    
    int size = (hi - lo + 1);
    
    if(lo>=hi)
        return;
    
    //Base case
    if (size == 2 && A[lo]>A[hi]) {
        std::swap(A[lo],A[hi]);
    }
    //Recurse
    else if (size > 2){
        int m = std::ceil(double(2*size)/3);
        stoogeSort(A, lo, lo+m-1);          //Sort lower array
        stoogeSort(A, hi-m+1, hi);         //Sort higher array
        stoogeSort(A, lo, lo+m-1);          //Sort lower array
    }
}

int main(int argc, const char * argv[]) {
    
    std::ofstream outfile("stoogeTimesMatch.txt");
    const int arrSize = 1000002;
    int array[arrSize];
    
    for (int k = 0; k <= 10000; k=k+500){
        
        float total = 0, average = 0;
        
        outfile << k << ", " ;
        std::cout << k << ", ";
        
        
        for (int i = 1; i <= 3; i++){
            
            //Create array with random ints
            srand(time_t(NULL));
            
            for (int j = 0; j < k; j++){
                array[j] = rand() % 1000;
            }
            
            clock_t t1, t2;
            t1 = clock();
            
            stoogeSort(array, 0, k-1);
            
            t2 = clock();
            
            float diff ((float)t2 - (float)t1);     //Total time
            float seconds = diff/CLOCKS_PER_SEC;
            total = total + seconds;
            outfile << seconds << ", ";
            std::cout << seconds << ", ";
        }
        average = total / 3;
        outfile << average << std::endl;
        std::cout << average << std::endl;
    }
    
    outfile.close();
    
    return 0;
}
