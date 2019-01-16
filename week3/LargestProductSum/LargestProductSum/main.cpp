//
//  main.cpp
//  LargestProductSum
//
//  Created by Marc Tibbs on 2018/01/24.
//  Copyright © 2018 Marc Tibbs. All rights reserved.
//

#include <iostream>
#include <vector>

//int proSum(int arr[], int floor, int ceil){
//    
//    if (floor == ceil)
//        return 0;
//    
//    return 0;
//}

int proSumAux(int arr[], std::vector<int> vector, int floor, int ceil){

    std::vector<int> vec4(arr, arr+sizeof(arr)/sizeof(arr[0]));
    
    if (floor == ceil)
        return 0;
    

    return 0;
}

int main(int argc, const char * argv[]) {
    int test4[4] = {3, 2, 4, 2};
//
//    std::cout << proSum(test, 0, 1);
//    std::cout << std::endl;
//    std::cout << proSum(test2, 0, 2);
//    std::cout << std::endl;
//    std::cout << proSum(test3, 0, 3);
//    std::cout << std::endl;
//    std::cout << proSum(test4, 0, 4);
//    std::cout << std::endl;
    
//    std::vector<int> vec4(test4, test4+sizeof(test4)/sizeof(test4[0]));
    
//    std::cout << *std::max_element(vec4.begin(),vec4.end()) << std::endl;
    
    return 0;
}
