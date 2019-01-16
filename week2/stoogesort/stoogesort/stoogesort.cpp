// Author: Marc Tibbs (tibbsm@oregonstate.edu)
// Date: January 21, 2018
// Description: This program takes a text file and sorts the numbers listed in the file using STOOGESORT

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

void stoogeSort(int A[], int lo, int hi) {
    
    int size = (hi - lo + 1);
    
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
    
    std::ifstream infile("data.txt");
    std::ofstream outfile("stooge.out");
    
    if(infile.is_open())
    {
        //Begin loop to go through all rows of text file
        while(infile.good()){
            int arrSize;
            
            //Get first value of each row as size of the array
            infile >> arrSize;
            
            //Initialize array to take incoming integers
            int myArray[arrSize];
            
            //Get all integers from row into array
            for(int i = 0; i < arrSize; i++){
                infile >> myArray[i];
            }
            
            //Sort array
            stoogeSort(myArray, 0, arrSize-1);
            
            //Save sorted array into merge.out
            for(int i = 0; i < arrSize; i++){
                outfile << myArray[i] << " " ;
            }
            outfile << std::endl;
        }
        outfile.close();
    }
    else {
        std::cout << "File could not be opened." << std::endl;
    }
    
    return 0;
}
