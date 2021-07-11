#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>


#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return Process::pid_;}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    std::ifstream filestream("/proc/" + to_string(pid_) + "/stat");
    vector<string> stat = {};
    string x; 
    int utime, stime, cutime, cstime;
    long totaltime;
    long SystemUpTime = LinuxParser::UpTime();
    int seconds;

    if(!filestream.is_open()) {
        return -1;
    } else {
        for(int i = 0 ; i < 22 ; i++) {
            filestream >> x;
            stat.push_back(x);
        }
    }

    utime = stoi(stat[13]);
    stime = stoi(stat[14]);
    cutime = stoi(stat[15]);
    cstime = stoi(stat[16]);
    starttime_ = stoi(stat[21]);

    totaltime = utime + stime + cutime + cstime;
    seconds = (int) SystemUpTime  - (starttime_ / sysconf(_SC_CLK_TCK) );
    Process::cpu_ = (totaltime + 0.0) / sysconf(_SC_CLK_TCK) / (seconds + 0.0);
    return cpu_;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Process::pid_); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Process::pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::pid_); }

// TODO: Return the age of tc

long int Process::UpTime() { return starttime_ / sysconf(_SC_CLK_TCK); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
  if( cpu_ * 100 > a.cpu_ * 100) {
    return true;
  }
  else {
    return false;
  }
}