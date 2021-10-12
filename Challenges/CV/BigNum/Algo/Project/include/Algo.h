#pragma once

#include <iostream>
#include <string>

#include "Macros.h"
#include "xstring.h"

#include "Segment.h"

using std::cout;
using std::endl;

class __declspec(dllexport) Algo
{
    inline static int TargetNumSize = 0;

    static Segment FindWithThreads(bool UseEightNums);
    static Segment FindWithStream(bool UseEightNums, const std::string_view& numbers);

public:
    inline static xstring AllNumbers;
    inline static xstring DisplayStr;

    static pint FindDisplayStr(bool UseThreading, bool UseEightNums);

    static void SetAllNumbers(const xstring& nums);
    static xstring GetAllNumbers();
    
    static void SetDisplayStr(const xstring& nums);
    static xstring GetDisplayStr();

};
