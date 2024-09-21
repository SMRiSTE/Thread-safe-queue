#include <iostream>
#include<thread>
#include<chrono>
#include"thread_pool.h"

void func1() {
    std::cout << __func__ << "is working" << std::endl;
}

void func2() {
    std::cout << __func__ << "is working" << std::endl;
}

int main()
{
    std::cout << std::thread::hardware_concurrency() <<std::endl;

    thread_pool tp;
    while (true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        tp.submit(func1);
        tp.submit(func2);
    }

}