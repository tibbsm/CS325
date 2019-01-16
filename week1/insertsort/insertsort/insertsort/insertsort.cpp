// Author: Marc Tibbs (tibbsm@oregonstate.edu)
// Date: January 14, 2018
// Description: This program takes a text file and sorts the numbers listed in the file using insertion sort

#include <iostream>
#include <fstream>

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
    
    std::ifstream infile("data.txt");
    std::ofstream outfile("insert.out");
    
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
            insertSort(myArray, arrSize);
            
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
