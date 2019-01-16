// Author: Marc Tibbs (tibbsm@oregonstate.edu)
// Date: Feb. 4, 2018
// Description: This program takes a text file 'act.txt' and reads the activity id, start and finish times. 
//  It the finds an optimal solution for the maximum number of compatiable acitivities based on their times
//  and outputs the results to the console. 

#include <iostream>
#include <fstream>
#include <vector>

struct activity{
	//activity id, start and finish times
	int id, s, f;
};

void merge(activity array[], int lowIndex1, int highIndex1, int lowIndex2, int highIndex2);

void mergeSort(activity array[], int lowIndex, int highIndex) {
    
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

void merge(activity array[], int lowIndex1, int highIndex1, int lowIndex2, int highIndex2)
{   //Calculate the new array size
    int size = (highIndex2 - lowIndex1) + 1;
    
    //Generate new array to stored merged arrays
    activity newArr[size];
    
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
        else if (array[top1].f >= array[top2].f){
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

void lastToStart(activity arr[], int n)
{
    // Sort jobs according to finish time, descending
    mergeSort(arr, 0, n-1);
 
    int i = 0;

    //Initialize vector for storing results
    std::vector<activity> result;

    //first activity is alwasy selected
    result.push_back(arr[i]);

    //Loop to find all compatible activities
    for (int j = 1; j < n; j++){
        if (arr[j].f <= arr[i].s){
            result.push_back(arr[j]);
            i = j;
        }
    }

	//Print number of activities selected
    std::cout << "Number of activities selected = " << result.size() << std::endl;

	//Print activity id numbers 
    std::cout << "Activities: ";
    while (!result.empty()){
        std::cout << result.back().id << " ";
        result.pop_back(); 
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {

    std::ifstream infile("act.txt");
    
    if(infile.is_open()){
    	//Set number initialized
    	int set = 0;
        //Begin loop to go through all rows of text file
        while(infile.good()){
            int size;
            
            //Get first value of each row as size of the array
            infile >> size;
            
            //Initialize array to take incoming integers
            std::vector<activity> vActivities;
            
            //activity struct
            activity init;

            std::cout << "Set " << ++set << std::endl;

            // Put activity ID, start & finish time into new struct
			for(int i = 0; i < size; i++){
				infile >> init.id;
	        	infile >> init.s;
	        	infile >> init.f;
	        	vActivities.push_back(init);
			}
            
			lastToStart(&vActivities[0], size);
    	}
    }
    else {
        std::cout << "File could not be opened." << std::endl;
    }
    
    return 0;
}
