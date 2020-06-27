#pragma once

#include <iostream>
#include <string>

#include "xstring.h"
#include "xmap.h"

#include "Segment.h"

using std::cout;
using std::endl;

class Algo
{
    static int TargetNumSize;

    static Segment FindWithThreads(bool UseEightNums);
    static Segment FindWithStream(bool UseEightNums, const std::string_view& numbers);

public:
    static xstring AllNumbers;
    static xstring DisplayStr;

    static unsigned int FindDisplayStr(bool UseThreading, bool UseEightNums);

    static void SetAllNumbers(const xstring& nums);
    static xstring GetAllNumbers();
    
    static void SetDisplayStr(const xstring& nums);
    static xstring GetDisplayStr();

};