#include <iostream>

#define self (*this)

class Segment
{
    int* mVars = nullptr;
    int* mBigVars = nullptr;
    int  mSize = 0;
    int  mTotal = 0;

    void clean();
    void Copy(const Segment& seg);
    void Move(Segment& seg);

    void UpdateBigVars();

public:
    Segment();
    Segment(bool eightNums);
    Segment(size_t size);
    ~Segment();

    Segment(const Segment& seg);
    Segment(Segment&& seg) noexcept;

    void operator=(const Segment& seg);
    void operator=(Segment&& seg) noexcept;

    int  operator[](int idx);
    void operator<<(int val);

    int   Size() const;
    int*  Vars() const;
    int*  BigVars() const;
    int   CurrentTotal();
    int   Total() const;
};