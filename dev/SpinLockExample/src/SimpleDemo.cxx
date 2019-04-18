#include "LockDemo/SpinLock.hxx"

#include <boost/core/demangle.hpp>
#include <boost/timer/timer.hpp>

#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include <limits>

template <typename LckType>
auto doTest(uint16_t numOfThreads)
{
    std::uint32_t ctr=0;
    LckType lock;
    std::vector<std::unique_ptr<std::thread>> threads(numOfThreads);
    std::cout<<"\nTesting with "<<numOfThreads<<" threads using "
        <<boost::core::demangle(typeid(LckType).name())<<std::endl;
    
    boost::timer::cpu_timer timer;
    for (std::unique_ptr<std::thread> &pThread : threads)
    {
        pThread = std::make_unique<std::thread>([&ctr,&lock](){
            for(int i=0;i<1000000;i++)
            {
                std::lock_guard<decltype(lock)> lc(lock);
                for (int j=0;j<10;j++)
                {
                    ctr++;
                }
            }
        });
    }
    for (std::unique_ptr<std::thread> &pThread : threads)
    {
        pThread->join();
    }
    timer.stop();
    
    std::cout<<timer.format()<<std::endl;
    std::cout<<"Counter : "<<ctr<<std::endl;
    return ctr;
}

int main()
{
    const uint16_t noOfThreads=2;

    std::uint32_t counter=0;
    LockDemo::SpinLock lock;    
    doTest<LockDemo::SpinLock>(noOfThreads);
    doTest<std::mutex>(noOfThreads);
}