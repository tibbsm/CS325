// Author: Marc Tibbs (tibbsm@oregonstate.edu)
// Date: January 28, 2018
// Description: This program takes a text file 'amount.txt' reads the odd lines of coin denominations and the even lines of
//  the amount to make change of. The program will return the minimum number of coins to make the amount. It will output a
//  file 'change.txt' with (line 1) the coin denominations (line 2) the amount (line 3) the amount of each coins needed
//  (line 4) the minimum number of coins to make change.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<int> makeChange(int vals[], int size, int A){
    
    //return vector
    std::vector<int> final(size);
    
    //vector to track coin amts
    std::vector<int> track(A + 1);
    
    //array to store results
    std::vector<int> arr(A + 1);
    
    //base case
    arr[0] = 0;
    
    //arr[i] = inf
    for (int i = 1; i <= A; i++) {
        arr[i] = std::numeric_limits<int>::max();;
    }
    
    //for i = 1 to A
    for (int i = 1; i <= A; i++){
        
        //test vals < i
        for (int j = 0; j < size; j++){
            
            if (vals[j] <= i){
                int change = arr[i-vals[j]];
                
                //store result in arr
                if (change + 1 < arr[i] && change < std::numeric_limits<int>::max()){
                    arr[i] = change + 1;
                    track[i] = j;
                    
                }
            }
        }
    }
    
    int cnt = A;
    while(cnt > 0){
        final.at(track[cnt])++;
        cnt = cnt - vals[track[cnt]];
    }
    
    final.push_back(arr[A]);
    
    return final;
}


int main(int argc, const char * argv[]) {
    
    std::ifstream infile("amount.txt");
    std::ofstream outfile("change.txt");
    std::ofstream timefile("times.txt");
    int lineCounter = 0, amount = 0; 
    std::vector<int> vArr;
    std::vector<int> vFin;
    float total = 0, average = 0;
    float trial = 0;
    int tryCount = 0;
    
    if(infile){
        
        std::string str;
        while(getline(infile, str)){
            
            std::istringstream ss(str);
            int num;
            
            if (lineCounter % 2 == 0){
                while(ss >> num){
                    vArr.push_back(num);
                }
                lineCounter++;
            }
            else{
                while(ss >> num){
                    amount = num;
                    
                    //save coin denominations
                    for (std::vector<int>::const_iterator i = vArr.begin(); i != vArr.end(); ++i)
                        outfile << *i << ' ';
                    outfile << std::endl;
                    
                    //save amount
                    outfile << amount << std::endl;
                    
//
                    clock_t t1, t2;
                    t1 = clock();
                    
                    vFin = makeChange(&vArr[0], int(vArr.size()), amount);
                    
                    t2 = clock();
                    
                    float diff ((float)t2 - (float)t1);     //Total time
                    float seconds = diff/CLOCKS_PER_SEC;
                    total = /*total +*/ seconds;
                    timefile << seconds << ", ";
                    std::cout << seconds << ", ";
//                    
                    int noc = vFin.back();
                    vFin.pop_back();
                    
                    //save coin amounts
                    for (std::vector<int>::const_iterator i = vFin.begin(); i != vFin.end(); ++i)
                        outfile << *i << ' ';
                    outfile << std::endl;
                    
                    //save min amount of coins
                    outfile << noc << std::endl;
                    
                    vArr.clear();
                    vFin.clear();
                }
                lineCounter++;
                
                if(tryCount < 2){
                    trial += total;
                    tryCount++;
                }
                else if(tryCount==2){
                    trial += total;
                    average = trial / 3;
                    timefile << average << std::endl;
                    std::cout << average << std::endl;
                    trial = 0;
                    tryCount = 0;
                }
                
            }
            
        }
        
        timefile.close();
        outfile.close();
    }
    else
        std::cout << "File could not be opened." << std::endl;
    
    return 0;
}
