// Author: Marc Tibbs (tibbsm@oregonstate.edu)
// Date: January 14, 2018
// Description: This program takes a text file and sorts the numbers listed in the file using mergesort

#include <iostream>
#include <fstream>

void merge(int a[], int lowIndex1, int highIndex1, int lowIndex2, int highIndex2);

void mergeSort(int array[], int lowIndex, int highIndex) {

    //Base case
    if (lowIndex >= highIndex) {
        return;
    }
    //Recurse
    else {
        int mid = (lowIndex + highIndex)/2;
        mergeSort(array, lowIndex, mid);               //Sort lower array
        mergeSort(array, mid+1, highIndex);            //Sort higher array
        merge(array, lowIndex, mid, mid+1, highIndex);  //Merge array back together
    }
}

void merge(int array[], int lowIndex1, int highIndex1, int lowIndex2, int highIndex2)
{   //Calculate the new array size
    int size = (highIndex2 - lowIndex1) + 1;
    
    //Generate new array to stored merged arrays
    int newArr[size];
    
    //Set the lowest values indexes up for comparison
    int top1 = lowIndex1, top2 = lowIndex2;
    
    for (int i = 0; i < size; i++) {
        //If lower array is 'empty' place top2 in next spot
        if (top1 == highIndex1 + 1){
            newArr[i] = array[top2];
            top2++;
        }
        //If upper array is 'empty' place top1 in next spot
        else if (top2 == highIndex2 + 1){
            newArr[i] = array[top1];
            top1++;
        }
        //If the top1 value is lower place in next spot
        else if (array[top1] <= array[top2]){
            newArr[i] = array[top1];
            top1++;
        }
        //If the top2 value is lower place in next spot
        else{
            newArr[i] = array[top2];
            top2++;
        }
    }
    
    //Copy the sorted list to appropriate position in original array
    for (int i = 0; i < size; i++){
        array[lowIndex1] = newArr[i];
        lowIndex1++;
    }
}




int main(int argc, const char * argv[]) {

    std::ifstream infile("data.txt");
    std::ofstream outfile("merge.out");
    
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
            mergeSort(myArray, 0, arrSize-1);
            
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
