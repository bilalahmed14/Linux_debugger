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

using namespace std;

int main (int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Program name not specfied";
        return -1;
    }

    auto progv = argv[1];
    auto pid = fork();

    if (pid == 0)
    {
        // we are in the child process
    }
    else if (pid >= 1)
    {
        // we are in the parent process
    }
}