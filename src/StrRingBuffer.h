#ifndef StrRingBuffer_h
#define StrRingBuffer_h

#include <Arduino.h>

#ifndef STRRINGBUFFER_DEF_SIZE
#define STRRINGBUFFER_DEF_SIZE  16
#endif

class StrRingBuffer {
    //private:
    public:
        char *buffer;
        size_t len, start, end;

    public:
        StrRingBuffer(size_t len = STRRINGBUFFER_DEF_SIZE);
        ~StrRingBuffer();

        void reset();
        size_t buflen();
        size_t strlen();
        void push(char c);
        char pop();
        char peek();
        void getstr(char *target);
        void getnstr(char *target, size_t len);
        void pushstr(char *s);
        void pushnstr(char *s, size_t len);
        int strcmp(char *str);
        int strncmp(char *str, size_t len);
        bool endswith(char *str);
        bool endsnwith(char *str, size_t len);
};

#endif
