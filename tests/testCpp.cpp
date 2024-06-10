#include <string>
#include <iostream>

int main(){
    std::string str = "Hello, C++17!";
    if(str.ends_with("C++17!")){
        std::cout << "C++17 is supported!" << std::endl;
    }
    return 0;
}