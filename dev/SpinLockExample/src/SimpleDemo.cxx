#include "LockDemo/SpinLock.hxx"
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>

#include <limits>

int main()
{
    std::uint32_t counter=0;
    LockDemo::SpinLock lock;
    // std::mutex lock;
    auto demoTask = [&counter,&lock](){
        for(int i=0;i<1000000;i++)
        {
            //lock.lock();
            std::lock_guard<decltype(lock)> lc(lock);
            // std::cout<<"locked"<<std::endl;
            for (int j=0;j<10;j++)
            {
                counter++;
            }
 /*           if (!(counter%100000000))
            {
                std::cout<<counter<<std::endl; 
            }*/
            //lock.unlock();
            // std::cout<<"unlocked"<<std::endl;
        }
    };
    std::thread t1(demoTask);
    std::thread t2(demoTask);
    t1.join();
    t2.join();

    std::cout<<"counter = "<<counter<<std::endl;

}