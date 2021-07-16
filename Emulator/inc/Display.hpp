#ifndef _Display_hpp
#define _Display_hpp

#include <mutex>
#include <condition_variable>

#include "Thread.hpp"

class Display: public Thread{

protected:
    std::mutex mutexWait;
    std::unique_lock<std::mutex> lock;

    std::condition_variable lowByte;
    bool lowByteCondition = false;

    std::condition_variable highByte;
    bool highByteCondition = false;

    bool end = false;
    bool lowByteSet = false;
    bool highByteSet = false;
    std::mutex mutex;

    short value;

protected:
    virtual void run();

public:
    Display();
    virtual ~Display();

    void setLowByte(char value);
    void setHighByte(char value);
    char getLowByte();
    char getHighByte();

    int stop();
};

#endif
