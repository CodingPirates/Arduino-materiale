#ifndef BufferedKeypad_H
#define BufferedKeypad_H

#include "Arduino.h"
#include "Keypad.h"

class BufferedKeypad : public Keypad
{
public:
    BufferedKeypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols);

    char getKey();

    const char * getBuffer() const { return buffer_; }

    void clearBuffer();

private:
    size_t size_;
    char buffer_[33];
};

#endif // BufferedKeypad_H
