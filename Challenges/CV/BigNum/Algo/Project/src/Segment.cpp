#include "Segment.h"


void Segment::clean()
{
    if (mVars)
        delete[] mVars;

    if (mBigVars)
        delete[] mBigVars;

    mVars = nullptr;
    mBigVars = nullptr;
}

void Segment::Copy(const Segment& seg)
{
    self.clean();

    mSize = seg.mSize;
    mTotal = seg.mTotal;
    mVars = new int[mSize];
    mBigVars = new int[mSize];

    for (int i = 0; i < mSize; i++)
        mVars[i] = seg.mVars[i];

    for (int i = 0; i < mSize; i++)
        mBigVars[i] = seg.mBigVars[i];
}

void Segment::Move(Segment& seg)
{
    self.clean();

    mSize  = seg.mSize;
    mTotal = seg.mTotal;

    mVars  = seg.mVars;
    mBigVars = seg.mBigVars;

    seg.mVars = nullptr; // avoid duplicate delete
    seg.mBigVars = nullptr;
}

void Segment::UpdateBigVars()
{
    for (int i = 0; i < mSize; i++)
        mBigVars[i] = mVars[i];
}

Segment::Segment()
{
}

Segment::Segment(bool eightNums)
{
    if (eightNums)
        mSize = 8;
    else 
        mSize = 4;
    
    mVars    = new int[static_cast<size_t>(mSize) + 1];
    mBigVars = new int[static_cast<size_t>(mSize) + 1];


    auto zero = [this](int* array) -> void
    {
        for (int i = 0; i < mSize; i++)
            array[i] = 0;
    };

    zero(mVars);
    zero(mBigVars);
}

Segment::Segment(size_t size): mSize(size){
    mVars = new int[static_cast<size_t>(mSize) + 1];
}

Segment::~Segment(){
    self.clean();
}

Segment::Segment(const Segment& seg){
    self.Copy(seg);
}

Segment::Segment(Segment&& seg) noexcept {
    self.Move(seg);
}

void Segment::operator=(const Segment& seg){
    self.Copy(seg);
}

void Segment::operator=(Segment&& seg) noexcept {
    self.Move(seg);
}


int Segment::operator[](int idx){
    return mVars[idx];
}

void Segment::operator<<(int val)
{
    for(int* ptr = mVars; ptr < &mVars[mSize - 1]; ptr++)
        *ptr = *(ptr+1);

    mVars[mSize - 1] = val;

    int NewTotal = self.CurrentTotal();
    if (mTotal < NewTotal) 
    {
        mTotal = NewTotal;
        self.UpdateBigVars();
    }
}

int Segment::Size() const {
    return mSize;
}

int* Segment::Vars() const {
    return mVars;
}

int* Segment::BigVars() const {
    return mBigVars;
}

int Segment::CurrentTotal()
{
    int total = 1;
    for (int* ptr = mVars; ptr < &mVars[mSize]; ptr++)
    {
        //std::cout << *ptr << " ";
        total *= *ptr;
    }
    //std::cout << total << std::endl;
    return total;
}

int Segment::Total() const {
    return mTotal;
}
