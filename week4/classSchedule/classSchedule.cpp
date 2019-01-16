
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> 

int main(int argc, const char * argv[]) {
    
    std::priority_queue<int> lHall;
    std::vector<int> start, finish;
    
    start.push_back(1);
    start.push_back(1);
    start.push_back(2);
    start.push_back(3);
    start.push_back(4);
    start.push_back(6);
    start.push_back(7);

    finish.push_back(4);
    finish.push_back(3);
    finish.push_back(5);
    finish.push_back(7);
    finish.push_back(7);
    finish.push_back(7);
    finish.push_back(8);
    
    for (int i = 0; i < start.size(); i++){
        if (lHall.empty()){
            lHall.push(finish[i]);
            std::cout << "Class " << i + 1<< " should use lecture hall " << lHall.size() << std::endl;
        }
        else {
            int ender = lHall.top();
            lHall.pop();

            if (start[i] < 8-ender){
                lHall.push(finish[i]);
                std::cout << "Class " << i + 1<< " should use lecture hall " << lHall.size() + 1 << std::endl;
            }
            else {
                ender = finish[i];
                std::cout << "Class " << i + 1<< " should use lecture hall " << lHall.size() - 1 << std::endl;
            }
            lHall.push(ender); 
            
        }
        
    }
    std::cout << "Min number of lecture halls needed: " << lHall.size() << std::endl;
    
    return 0;
}
