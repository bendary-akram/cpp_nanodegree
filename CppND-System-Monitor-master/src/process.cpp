#include "process.h"

#include <unistd.h>

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid, string user, string cmd, string ram, long int uptime)
    : pid_(pid), user_(user), command_(cmd), ram_(ram), uptime_(uptime) {}
int Process::Pid() { return pid_; }

float Process::CpuUtilization() {
  long seconds = LinuxParser::UpTime(pid_);
  long totaltime = LinuxParser::ActiveJiffies(pid_);
  // cpu_usage_ = LinuxParser::CpuUtilization(pid_);
  cpu_usage_ = float(totaltime) / float(seconds);
  return cpu_usage_;
}

string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

string Process::User() { return user_; }

long int Process::UpTime() { return uptime_; }

bool Process::operator<(Process const& a) const {
  bool result;
  try {
    result = (a.cpu_usage_ < cpu_usage_);
  }

  catch (std::exception& e) {
    std::cout << "Standard exception: " << e.what() << std::endl;
  }

  return (result);
}