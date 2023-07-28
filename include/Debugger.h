#ifndef  DEBUGGER_H
#define DEBUGGER_H

#include <utility>
#include <string>
#include <linux/types.h>
#include <unordered_map>

// #include "breakpoint.hpp"
#include "dwarf/dwarf++.hh"
#include "elf/elf++.hh"

#include <iostream>

    
enum class symbol_type 
{
    notype,            // No type (e.g., absolute symbol)
    object,            // Data object
    func,              // Function entry point
    section,           // Symbol is associated with a section
    file,              // Source file associated with the
};   

struct symbol {
    symbol_type type;
    std::string name;
    std::uintptr_t addr;
};


class Debugger
{
private:
    std::string m_prog_name;
    pid_t m_pid;
private:
    void wait_for_signal();
    auto get_signal_info() -> siginfo_t;
public:
    Debugger(std::string prog_name, pid_t pid) : m_prog_name{std::move(prog_name)}, m_pid{pid} 
    {
        
    }

    ~Debugger();

    void run();
    std::string to_string (symbol_type st);


};



    








#endif