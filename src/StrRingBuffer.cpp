#include <Arduino.h>
#include "StrRingBuffer.h"

StrRingBuffer::StrRingBuffer(size_t len)
{
    this->len = len;
    this->buffer = new char[len];
    this->start = this->end = 0;
}

StrRingBuffer::~StrRingBuffer()
{
    delete this->buffer;
}

void StrRingBuffer::reset()
{
    this->start = this->end = 0;
}

size_t StrRingBuffer::buflen()
{
    return this->len;
}

size_t StrRingBuffer::strlen()
{
    if(this->start <= this->end)
        return (this->end - this->start);
    else
        return (this->len + this->end - this->start);
}

void StrRingBuffer::push(char c)
{
    this->buffer[this->end] = c;
    this->end = (this->end + 1) % this->len;
}

char StrRingBuffer::pop()
{
    char c = this->buffer[this->start];
    this->start = (this->start + 1) % this->len;
    return c;
}

char StrRingBuffer::peek()
{
    return this->buffer[this->start];
}

void StrRingBuffer::getstr(char *target)
{
    size_t c = this->start;
    char *p = target;

    while(c != this->end) {
        *p++ = this->buffer[c];
        c = (c + 1) % this->len;
    }
    *p = '\0';
}

void StrRingBuffer::getnstr(char *target, size_t len)
{
    size_t c = this->start;
    size_t written = 0;
    char *p = target;

    while((c != this->end) && (written < len - 1)) {
        *p++ = this->buffer[c];
        c = (c + 1) % this->len;
        written++;
    }
    *p = '\0';
}

void StrRingBuffer::pushstr(char *s)
{
    char *p = s;

    while(*p != '\0') {
        this->buffer[this->end] = *p++;
        this->end = (this->end + 1) % this->len;
    }
}

void StrRingBuffer::pushnstr(char *s, size_t len)
{
    size_t written = 0;
    char *p = s;

    while((*p != '\0') && (written < len)) {
        this->buffer[this->end] = *p++;
        this->end = (this->end + 1) % this->len;
        written++;
    }
}

int StrRingBuffer::strcmp(char *str)
{
    size_t c = this->start;
    char *p = str;

    while((c != this->end) && (*p != '\0')) {
        if(this->buffer[c] < *p)
            return -1;
        if(this->buffer[c] > *p)
            return 1;
        p++;
        c = (c + 1) % this->len;
    }

    if((c == this->end) && (*p == '\0'))
        return 0;
    if(*p == '\0')
        return 1;
    else
        return -1;
}

int StrRingBuffer::strncmp(char *str, size_t len)
{
    size_t c = this->start;
    size_t compared = 0;
    char *p = str;

    while((c != this->end) && (*p != '\0') && (compared != len)) {
        if(this->buffer[c] < *p)
            return -1;
        if(this->buffer[c] > *p)
            return 1;
        p++;
        c = (c + 1) % this->len;
        compared++;
    }

    if(compared == len)
        return 0;
    if((c == this->end) && (*p == '\0'))
        return 0;
    if(*p == '\0')
        return 1;
    else
        return -1;
}

bool StrRingBuffer::endswith(char *str)
{
    return this->endsnwith(str, ::strlen(str));
}

bool StrRingBuffer::endsnwith(char *str, size_t len)
{
    size_t c;
    char *p = str;

    if(this->strlen() < len)
        return false;

    if(end < len)
        c = end - len + this->len;
    else
        c = end - len;

    while(c != this->end) {
        if(this->buffer[c] != *p)
            return false;
        p++;
        c = (c + 1) % this->len;
    }

    return true;
}

