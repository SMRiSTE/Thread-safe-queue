#include <iostream>
#include<thread>
#include"thread_pool.h"

void print_name() {
    std::cout << __func__ << std::endl;
}

int main()
{
    std::cout << std::thread::hardware_concurrency() <<std::endl;

    thread_pool tp;
    tp.submit(print_name);
}