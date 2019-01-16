// Author: Marc Tibbs (tibbsm@oregonstate.edu)
// Date: January 14, 2018
// Description: This program takes a text file and sorts the numbers listed in the file using insertion sort

#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <stdlib.h>

void insertSort(int array[], int size) {
    
    for (int i = 0; i < size; i++) {
        int j = i;
        //Move elements of array that are > 'up' the list
        while (j > 0 && array[j - 1] > array[j]) {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
            j--;
        }
    }
}



int main(int argc, const char * argv[]) {
    
    std::ofstream outfile("insertTimesMatch.txt");
    const int arrSize = 1000002;
    int array[arrSize];
    
    for (int k = 0; k <= 5000; k=k+500){
        
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
            
            insertSort(array, k);
            
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
