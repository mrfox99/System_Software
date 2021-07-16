#include "../inc/Thread.hpp"

Thread::Thread(){
}

Thread::~Thread(){
}

int Thread::start(){
    if(thread)
        delete thread;
    thread = new std::thread([this](){run();});
    return 0;
}

int Thread::join(){
    thread->join();
    return 0;
}

int Thread::stop(){
    pthread_cancel(thread->native_handle());
    return 0;
}