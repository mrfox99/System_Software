#ifndef _Thread_hpp
#define _Thread_hpp

#include <thread>

class Thread{

protected:
    std::thread *thread = nullptr;
    
public:
    Thread();
    ~Thread();

    int start();
    int join();
    int stop();

protected:
    virtual void run() = 0;
    
};

#endif

