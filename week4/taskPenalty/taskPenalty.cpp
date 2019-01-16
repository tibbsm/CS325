
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm> 

struct task{
    int d;
    int p;
} t0, t1, t2, t3, t4, t5, t6, t7;

int main(int argc, const char * argv[]) {
    
    // ai 1 2 3 4 5 6 7
    // di 4 2 4 3 1 4 6
    // wi 70 60 50 40 30 20 10

    std::vector<struct task> v;
    t0.d = 0;   t0.p = 0;
    t1.d = 4;   t1.p = 70;
    t2.d = 2;   t2.p = 60;
    t3.d = 4;   t3.p = 50;
    t4.d = 3;   t4.p = 40;
    t5.d = 1;   t5.p = 30;
    t6.d = 4;   t6.p = 20;
    t7.d = 6;   t7.p = 10;


    v.push_back(t7);
    v.push_back(t6);
    v.push_back(t5);
    v.push_back(t4);
    v.push_back(t3);
    v.push_back(t2);
    v.push_back(t1);
    // for (int i = 0; i < v.size(); i++)
    //     std::cout << i + 1 << " " << v[i].d << " " << v[i].p << std::endl;

    task arr[v.size()];

    for (int i = 0; i < v.size(); i++){
        arr[i] = t0;
    }

    int sumP;

    while(!v.empty()){
        task cur = v.back();
        v.pop_back();

        int k = cur.d;

        while(k > 0){
            if (arr[cur.d-1].d == 0){
                arr[cur.d-1] = cur;
            }
        }

    }

    for (int i = 0; i < 7; i++){
        std::cout << i + 1 << " " << arr[i].d << " " << arr[i].p << std::endl;
    }

    
    return 0;
}
