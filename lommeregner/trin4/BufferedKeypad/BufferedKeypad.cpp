#include "BufferedKeypad.h"

BufferedKeypad::BufferedKeypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols)
: Keypad(userKeymap, row, col, numRows, numCols)
, size_(0)
, buffer_()
{
    clearBuffer();
}

void BufferedKeypad::clearBuffer()
{
    size_ = 0;
    strcpy(buffer_, "");
}

char BufferedKeypad::getKey()
{
    char const key = Keypad::getKey();

    if (key == NO_KEY || size_ >= 32)
    {
        return key;
    }

    buffer_[size_] = key;
    buffer_[size_ + 1] = '\0';
    ++size_;

    return key;
}
