#include "LockDemo/SpinLock.hxx"

#include <iostream>

namespace LockDemo{

    void SpinLock::lock()
    {
    //    std::cout<<"Locking"<<std::endl;
        while (lockFlag_.test_and_set())
        {}
    //    std::cout<<"Locked"<<std::endl;
    }

    void SpinLock::unlock()
    {
        lockFlag_.clear();
    }
}