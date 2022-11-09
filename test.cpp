//
// Created by shriller44 on 10/10/22.
//
#include <cstring>
#include <cstdlib>
#include <vector>
#include <iostream>

struct cum {
    int x;
    int y;
    int z;
};

struct test {

    int operator[](cum c){

        std::cout << "test" << std::endl;
        return test[1];
    }

private:
    std::vector<int> test{1,2,3};
};

int main(){
    test t;
    auto val = t[{1,2,3}];

    std::cout << "test" <<val << std::endl;
}
