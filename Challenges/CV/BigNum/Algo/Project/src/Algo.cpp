#include "Algo.h"

int Algo::TargetNumSize = 0;
xstring Algo::AllNumbers;
xstring Algo::DisplayStr;

Segment Algo::FindWithThreads(bool UseEightNums)
{
    xvector<std::string_view> numStrs;
    std::string_view view = Algo::AllNumbers;
    numStrs.resize(Nexus<>::Thread_Count());

    int loc = 0;
    const int UpSize = view.size() / Nexus<>::Thread_Count();
    for (int i = 0; i < Nexus<>::Thread_Count(); i++)
    {
        numStrs[i] = view.substr(loc, static_cast<size_t>(loc) + UpSize + Algo::TargetNumSize);
        loc += UpSize;
    }

    xvector<Segment> segs = numStrs.xrender<Segment>([&UseEightNums](const std::string_view& numStr)
    {
        return Algo::FindWithStream(
            UseEightNums,
            numStr
        );
    });

    int biggest = 0;
    for (const auto& seg : segs)
    {
        if (seg.Total() > biggest)
            biggest = seg.Total();
    }
    for (const auto& seg : segs)
    {
        if (seg.Total() == biggest)
            return seg;
    }
    std::cout << "Error: Could not find Seg! (Algo::FindWithThreads)" << endl;
    return Segment();
}

Segment Algo::FindWithStream(bool UseEightNums, const std::string_view& numbers)
{
    Segment seg(UseEightNums);
    for (std::string_view::const_iterator it = numbers.begin(); it != numbers.end(); it++)
        seg << ((*it) - 48);

    return seg;
}


unsigned int Algo::FindDisplayStr(bool UseThreading, bool UseEightNums)
{
    Algo::TargetNumSize = (UseEightNums) ? 8 : 4;
    Segment seg;
    if (UseThreading)
        seg = Algo::FindWithThreads(UseEightNums);
    else
        seg = Algo::FindWithStream(UseEightNums, Algo::AllNumbers);


    std::stringstream stream;
    stream << "[ ";
    xstring target;
    for (int* ptr = seg.BigVars(); ptr < &seg.BigVars()[seg.Size()]; ptr++)
        stream << *ptr;

    target = stream.str().substr(2, static_cast<size_t>(seg.Size()) + Algo::TargetNumSize);
    stream << " >> " << seg.Total() << " ]";
    
    Algo::DisplayStr = stream.str();

    return static_cast<unsigned int>(Algo::AllNumbers.find(target));
}

void Algo::SetAllNumbers(const xstring& nums){
    Algo::AllNumbers = nums;
}

xstring Algo::GetAllNumbers(){
    return Algo::AllNumbers;
}

void Algo::SetDisplayStr(const xstring& nums){
    Algo::AllNumbers;
}

xstring Algo::GetDisplayStr(){
    return Algo::DisplayStr;
}
