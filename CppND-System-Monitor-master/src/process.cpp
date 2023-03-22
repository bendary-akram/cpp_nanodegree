#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid,string user,string cmd,string ram, long int uptime) : pid_(pid),user_(user),command_(cmd),ram_(ram),uptime_(uptime){}
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
  cpu_usage_= LinuxParser::CpuUtilization(pid_);
  return cpu_usage_;
  /* 
  vector<string> cpu_usage = LinuxParser::CpuUtilization();
  float total_cpu_usage=0;
  for(string i : cpu_usage)
  {
    total_cpu_usage = total_cpu_usage + stof(i);
  }
  
  return total_cpu_usage;
  */ }

string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

string Process::User() { return user_; }

long int Process::UpTime() { return uptime_; }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a ) const{
  bool result;
  try{
    result = (a.cpu_usage_  < cpu_usage_);
  }

  catch (std::exception& e)
  {
    std::cout << "Standard exception: " << e.what() << std::endl;
  }

  return ( result );
}