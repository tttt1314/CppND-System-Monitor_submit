#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

// using namespace std;

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  int MemTotal;
  int MemFree;
  int MemAvaliable;
  int Buffers;
  string text;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    filestream >> text >> MemTotal >> text;
    filestream >> text >> MemFree >> text;
    filestream >> text >> MemAvaliable >> text;
    filestream >> text >> Buffers >> text;
    return 1.0 - (static_cast<float>(MemFree) / (MemTotal - Buffers));
  } else {
    return -1;
  }
}

// Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  long uptime;
  if (filestream.is_open()) {
    filestream >> uptime;
    return uptime;
  } else {
    return -1;
  }
}

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  long user, nice, system, idle, iowait, irg, softirg, steal, guest, guest_nice;
  string cpu;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (!filestream.is_open()) {
    return -1;
  } else {
    filestream >> cpu >> user >> nice >> system >> idle >> iowait >> irg >>
        softirg >> steal >> guest >> guest_nice;
  }

  return user + nice + system + irg + softirg + steal + guest + guest_nice;
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  long user, nice, system, idle, iowait, irg, softirg, steal, guest, guest_nice;
  string cpu;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (!filestream.is_open()) {
    return -1;
  } else {
    filestream >> cpu >> user >> nice >> system >> idle >> iowait >> irg >>
        softirg >> steal >> guest >> guest_nice;
  }

  return idle + iowait;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::ifstream filestream(kProcDirectory + kStatFilename);
  string x;
  int TotalProcess;

  if (!filestream.is_open()) {
    return -1;
  } else {
    while (filestream >> x) {
      if (x == "processes") {
        filestream >> TotalProcess;
        break;
      }
    }
    return TotalProcess;
  }
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::ifstream filestream(kProcDirectory + kStatFilename);
  string x;
  int RunningProcess;
  if (!filestream.is_open()) {
    return -1;
  } else {
    while (filestream >> x) {
      if (x == "procs_running") {
        filestream >> RunningProcess;
        break;
      }
    }
    return RunningProcess;
  }
}

// TODO: Read and return the command associated with a process
string LinuxParser::Command(int pid) {
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  string line;
  if (!filestream.is_open()) {
    return "fail";
  } else {
    getline(filestream, line);
  }
  return line;
}

// TODO: Read and return the memory used by a process
string LinuxParser::Ram(int pid) {
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  string x;
  int ram = 0;
  if (!filestream.is_open()) {
    return "fail";
  } else {
    while (filestream >> x) {
      if (x == "VmSize:") {
        filestream >> ram;
        break;
      }
    }
    return to_string(ram / 1000);
  }
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) {
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  string target;
  string uid;

  if (!filestream.is_open()) {
    return "fail";
  } else {
    while (filestream >> target) {
      if (target == "Uid:") {
        filestream >> uid;
        return uid;
      }
    }
    return "no exist";
  }
}

// TODO: Read and return the user associated with a process
string LinuxParser::User(int pid) {
  string uid = LinuxParser::Uid(pid);
  std::ifstream filestream(kPasswordPath);
  string line;

  if (!filestream.is_open()) {
    return "fail";
  } else {
    while (getline(filestream, line)) {
      if (line.find(":x:") + 3 == line.find(uid)) {
        return line.substr(0, line.find(":x:") - 0);
      }
    }
    return "fail";
  }
}
