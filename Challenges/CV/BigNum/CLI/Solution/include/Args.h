
#include "Nexus.h"
#include "xstring.h"

struct Args
{
    int Threads = Nexus<>::Thread_Count();
    bool UseEightNums = false;
    int AllNumberSize = 1000;
    xstring File;
};