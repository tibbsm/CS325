//
//  main.cpp
//  randGen
//
//  Created by Marc Tibbs on 2018/01/27.
//  Copyright © 2018 Marc Tibbs. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, const char * argv[]) {

    std::ofstream outfile("changeRand.txt");
    
    for (int i = 10000000; i <= 40000000; i = i + 10000000){
        
        int fftn = 0, k = 2;
        
        while (fftn < 5){
            
            std::vector<int> vec;
            srand(time_t(NULL));
            
            for (int m = 0; m < 3; m++){
                vec.push_back(1);
                for(int j = 0; j < k - 1; j++){
                    vec.push_back(rand()%100);
                }
                
                std::sort(vec.begin(), vec.end());
                std::reverse(vec.begin(), vec.end());
                
                for (int l = 0; l < k; l++){
                    outfile << vec.back() << " ";
                    vec.pop_back();
                }
                outfile << std::endl;
                outfile << i << std::endl;
                
                vec.clear();
            }
            
            k += 2;
            fftn++;
        }
        
    }
    
    return 0;
}
