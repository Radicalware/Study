// Copyright[2020][Joel Leagues aka Scourge] under the Apache V2 Licence

#include <iostream>
#include <ctime>
#include <sstream>

#include "Nexus.h"
#include "xvector.h"
#include "xstring.h"
#include "xmap.h"
#include "Timer.h"
#include "SYS.h"
#include "OS.h"

#include "Algo.h"
#include "Args.h"

using std::cout;
using std::endl;

using ull = unsigned long long;

int help(int retErr)
{
    cout << R"(
   
    ------------------------------------------------------------------------
      USUAL ARGUMENTS
    ------------------------------------------------------------------------
      -t     |  --threads   |  (int)    Number of Threads (Default All)
      -e     |  --eightNums |  (int)    Eight Num Segment (Default is 4)
      -n     |  --numSize   |  (int)    Number Size (Default 1000)
      -f     |  --file      |  (string) Test nums from a file
      -s     |  --stopwatch |  (bool)   Stopwatch
      -d     |  --defaults  |  (bool)   Use All Defaults
      -h     |  --help      |  (bool)   Help which you are looking at
    ------------------------------------------------------------------------
)";
    Nexus<>::Stop();
    return retErr;
}

int main(int argc, char** argv)
{
    Nexus<>::Start(); 
    Timer t;
    SYS sys;
    Args args;

    sys.alias('t', "--threads");
    sys.alias('e', "--eightNums");
    sys.alias('n', "--numSize");
    sys.alias('f', "--file");
    sys.alias('d', "--defaults");
    sys.set_args(argc, argv);
    
    if (sys.help()) return help(0);

    if (sys('t')) {
        if (sys['t'].size() && sys['t'][0]->match(R"(^\d*$)") && sys['t'][0]->to_int() > 0)
        {
            args.Threads = sys['t'][0]->to_int();
            Nexus<>::Set_Thread_Count(args.Threads);
        }
    }

    args.UseEightNums = sys('e');


    if (sys('n')) {
        if (sys['n'].size() && sys['n'][0]->match(R"(^\d*$)"))
            args.AllNumberSize = sys['n'][0]->to_int();
    }

    if (sys('f'))
    {
        if (OS::Has_File(*sys['f'][0]))
            args.File = *sys['f'][0];
        else {
            cout << "File Not Found: " << *sys['f'][0] << endl;
            Nexus<>::Stop();
            return 0;
        }

        Algo::SetAllNumbers(OS::Fast_Read(args.File).sub(R"(([^\d]))", ""));
    }

    if (!Algo::GetAllNumbers().size())
    {
        std::srand(std::time(nullptr));
        int random_variable = std::rand();
        xvector<int> nums;
        for(int i = 0; i < args.AllNumberSize; i++)
            nums << std::rand() / ((RAND_MAX + 1u) / 10);

        std::stringstream stream;
        for (auto num : nums)
            stream << num;

        Algo::SetAllNumbers(stream.str());
    }

    if (args.Threads > 1)
        Algo::FindDisplayStr(true, args.UseEightNums);
    else
        Algo::FindDisplayStr(false, args.UseEightNums);
        

    cout << "------------------------------------\n";
    cout << "Thread Count: " << args.Threads << endl;
    cout << "UseEightNums: " << args.UseEightNums << endl;
    cout << "Number Size : " << args.AllNumberSize << endl;
    cout << Algo::GetDisplayStr() << endl;
    cout << "------------------------------------\n";
    xstring(OS::Console_Size()[0], '=').print();
    if (sys('s'))
        cout << "Time: " << t.elapsed() << endl;
    else
        Algo::GetAllNumbers().inclusive_split(Algo::GetDisplayStr().search(R"(^[^\d]+(\d+))")[0]).join('\n').print();

    xstring(OS::Console_Size()[0], '=').print(2);


    return Nexus<>::Stop();
}
