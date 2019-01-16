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
    
    std::ofstream outfile("mergeTimes.txt");
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
            
            mergeSort(array, 0, k-1);
            
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
}
