#include "Debugger.h"


Debugger::Debugger(std::string prog_name, pid_t pid) : m_prog_name{std::move(prog_name)}, m_pid{pid} 
{
    auto fd = open(m_prog_name.c_str(), O_RDONLY);

    m_elf = elf::elf{elf::create_mmap_loader(fd)};
    m_dwarf = dwarf::dwarf{dwarf::elf::create_loader(m_elf)};
}

Debugger::~Debugger()
{
}


void Debugger::run()
{
    wait_for_signal();
    std::cout << "start\n";
}

std::string Debugger::to_string (symbol_type st) {
    switch (st) {
    case symbol_type::notype: return "notype";
    case symbol_type::object: return "object";
    case symbol_type::func: return "func";
    case symbol_type::section: return "section";
    case symbol_type::file: return "file";
    default: return "Unknown";
    }  
}


void Debugger::wait_for_signal()
{
    int wait_status;
    auto option = 0;

    waitpid(m_pid, &wait_status, option);

    auto siginfo = get_signal_info();
    switch (siginfo.si_signo)
    {
    case SIGTRAP:
        handle_sigtrap(siginfo);
        break;
    case SIGSEGV:
        std::cout << "Yay, segfault. Reason: " << siginfo.si_code << std::endl;
        break;
    default:
        std::cout << "Got signal " << strsignal(siginfo.si_signo) << std::endl;
    }
}

auto Debugger::get_signal_info() -> siginfo_t
{
    siginfo_t info;
    ptrace(PTRACE_GETSIGINFO, m_pid, nullptr, &info);
    return info;
}
