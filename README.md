# String Ring Buffer

[![License](https://img.shields.io/badge/license-BSD%203--Clause-green.svg)](https://raw.githubusercontent.com/fotisl/strringbuffer/master/LICENSE)
[![Build Status](https://travis-ci.org/fotisl/strringbuffer.svg?branch=master)](https://travis-ci.org/fotisl/strringbuffer)

An arduino library implementing a ring buffer especially designed for strings.

# Usage

To use the library, you must first construct an object of type StrRingBuffer.
Then you can use any of the methods displayed below.

## Methods

### StrRingBuffer(size\_t len = STRRINGBUFFER\_DEF\_SIZE)

The constructor takes an optional single argument which is the size of the
ring buffer. By default, the size will be ```STRRINGBUFFER_DEF_SIZE```, which is
a define in ```strringbuffer.h```. The default value is equal to 16, but if you
want to change it, you can define it to a different value before including the
header file.

### ~StrRingBuffer()

The destructor just frees up the allocated memory.

### void reset()

The ```reset``` method resets all internal pointers and provides a fresh ring
buffer.

### size\_t buflen()

The ```buflen``` method returns the length of the buffer.

### size\_t strlen()

The ```strlen``` method returns the length of the string stored inside the
buffer.

### void push(char c)

The ```push``` method appends the character ```c``` to the buffer.

### char pop()

The ```pop``` method returns the first character from the buffer. Since it is
a ring buffer, it is a FIFO and not a LIFO queue. The character will be deleted
from the buffer.

### char peek()

The ```peek``` method returns the first character from the buffer, without
removing it.

### void getstr(char \*target)

The ```getstr``` method copies the string stored in the buffer to ```target```.
It is up to the user to provide a large enough string to hold all the contents
of the buffer. At the end of the string, a ```\0``` will be appended.

### void getnstr(char \*target, size\_t len)

Similar to ```getstr```, ```getnstr``` copies the string stored in the buffer
to ```target```, but will store a maximum of ```len``` characters, including
the final ```\0```.

### void pushstr(char \*s)

The ```pushstr``` method will append all characters from ```s``` to the buffer.

### void pushnstr(char \*s, size\_t len)

The ```pushnstr``` method will append at most ```len``` characters from ```s```
to the buffer. If the string stored in ```s``` is less than ```len``` characters
then the whole string will be appended.

### int strcmp(char \*str)

The ```strcmp``` method compares the string from the buffer with ```str```. The
return value is similar to the result of using the standard ```strcmp```
function to compare the string stored in the buffer and ```str```.

### int strncmp(char \*str, size\_t len)

Similar to ```strcmp```, but compares at most ```len``` characters. Similar to
using the standard ```strncmp``` function.

### bool endswith(char \*str)

The ```endswith``` method returns true if the buffer ends with ```str```,
otherwise false.

### bool endsnwith(char \*str, size\_t len)

The ```endsnwith``` method returns true if the buffer ends with at most
```len``` characters from ```str```, otherwise false.

## Example

You can find sample code in the examples/ directory.

# Notes

It is important to note that since the library was designed to be small and
fast, there are several things that are missing.

The most important thing is that there is no buffer overflow detection and
protection. Thus, if you have a buffer which can hold a maximum of 16
characters, the library will not stop you from inserting 20 characters or a
20 character string. It is up to you to reserve the appropriate buffer.

Futhermore, a buffer with a size equal to n can hold up to n - 1 characters.
This was a design decision, since adding the necessary checks would require a
more memory and more code.

# License

The code is licensed under the BSD 3-clause "New" or "Revised" License.
