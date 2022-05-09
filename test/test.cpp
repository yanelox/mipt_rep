#include <thread>
#include <iostream>

void test_func ()
{
    std::cout << "jopa\n";
}

int main ()
{
    std::thread thr (test_func);

    thr.detach();

    std::this_thread::sleep_for(std::chrono::seconds(5));

    return 0;
}