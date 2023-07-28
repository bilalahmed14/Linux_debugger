#include <iostream>
#include <vector>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/personality.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <iomanip>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Debugger.h"

using namespace std;


void execute_debugee (const std::string& prog_name) 
{
    if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
        std::cerr << "Error in ptrace\n";
        return;
    }
    execl(prog_name.c_str(), prog_name.c_str(), nullptr);
}


int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Program name not specfied\n";
        return -1;
    }

    auto prog = argv[1];
    auto pid = fork();

    if (pid == 0)
    {
        // we are in the child process
        personality(ADDR_NO_RANDOMIZE);
        execute_debugee(prog);
    }
    else if (pid >= 1)
    {
        // we are in the parent process
        cout << "Debugging process started" << endl;

        Debugger dbg(prog, pid);
        dbg.run();

    }

    std::cout << "Program end\n";
    return 0;
}