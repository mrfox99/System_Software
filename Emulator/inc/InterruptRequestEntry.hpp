#ifndef _InterruptRequestEntry_hpp
#define _InterruptRequestEntry_hpp

enum InterruptRequestEntry:unsigned char{
    RESET_PROCESSOR_REQUEST_ENTRY,
    BAD_INSTRUCTION_REQUEST_ENTRY,
    TIMER_REQUEST_ENTRY,
    TERMINAL_REQUEST_ENTRY,
    UNDF_REQUEST_ENTRY
};

#endif
