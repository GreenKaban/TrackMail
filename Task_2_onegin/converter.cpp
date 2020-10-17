#include "converter.h"
#include <stdlib.h>
#include <stdio.h>
#include <clocale>
#include <sys/stat.h>
#include <fcntl.h>
#include <io.h>

/**
 * @file converter.cpp
 *
 * @brief Contains definitions of functions StrLen, ToWchar for utf-8
 *
 * @author Igor Kochetkov, DCAM MIPT (System Programming Base Chair) Student
 *
 * @date 10/17/2020
 */

int utf8StrLen(const char* src)
{
    int length = 0;
    Assert_c(src != NULL);
    if (!src)
        return -1;
    const char* ptr = src;
    while (*ptr)
    {
        length++;
        char v = (*ptr);
        if (v >= 0)
        {
            ptr++;
            continue;
        }
        int shiftCount = 0;
        if ((v & 0xE0) == 0xC0)
            shiftCount = 1;
        if ((v & 0xF0) == 0xE0)
            shiftCount = 2;
        ptr+= shiftCount+1;
    }
    return length;
}



int utf8ToWchar(wchar_t* dest, const char* src)
{
    Assert_c(src != NULL);
    if (!src)
        return -1;
    Assert_c(dest != NULL);
    if (!dest)
        return -1;
    wchar_t* resultStr = dest;
    wchar_t c;
    const char* ptr = src;
    while (*ptr)
    {
        char v = (*ptr);
        if (v >= 0)
        {
            c = v;
            *resultStr = c;
            resultStr++;
            ptr++;
            continue;
        }
        int shiftCount = 0;
        if ((v & 0xE0) == 0xC0)
        {
            shiftCount = 1;
            c = v & 0x1F;
        }
        else if ((v & 0xF0) == 0xE0)
        {
            shiftCount = 2;
            c = v & 0xF;
        }
        else
            return -1;
        ptr++;

        while (shiftCount)
        {
            v = *ptr;
            ptr++;
            c <<= 6;
            c |= (v & 0x3F);
            shiftCount--;
        }
        *resultStr = c;
        resultStr++;
    }
    return 0;
}
