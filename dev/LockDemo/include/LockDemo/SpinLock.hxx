#include <atomic>

namespace LockDemo
{
class SpinLock
{
public:
    SpinLock():lockFlag_(false)
    {}

    void lock();

    void unlock();

private:
    std::atomic_flag lockFlag_;
};

}