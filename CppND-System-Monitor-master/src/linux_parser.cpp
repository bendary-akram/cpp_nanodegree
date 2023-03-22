#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//#include <linux/jiffies.h>
#include <exception>

using std::ifstream;
using std::istringstream;
using std::stof;
using std::string;
using std::to_string;
using std::vector;

#define utime_index (14)
#define stime_index (15)
#define cutime_index (16)
#define cstime_index (17)
#define starttime_index (22)

// DONE: An example of how to read data from the filesystem
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

// DONE: An example of how to read data from the filesystem
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

float LinuxParser::MemoryUtilization() {
  std::ifstream file_stream(kProcDirectory + kMeminfoFilename);
  string line_str;
  string key;
  int value;
  float memoryValue;
  int MTotal;
  int MFree;
  if (file_stream.is_open()) {
    while (std::getline(file_stream, line_str)) {
      std::istringstream linestream(line_str);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          MTotal = value;
        } else if (key == "MemFree:") {
          MFree = value;
        }
      }
    }
  }
  memoryValue = (MTotal - MFree) / float(MTotal);
  return memoryValue;
}

long LinuxParser::UpTime() {
  ifstream file_stream(kProcDirectory + kUptimeFilename);
  string line;
  string uptime;
  if (file_stream.is_open()) {
    getline(file_stream, line);
    std::istringstream linestream(line);
    linestream >> uptime;
  }
  try {
    return (stol(uptime));
  }

  catch (std::exception& e) {
    return (std::stol("1"));
  }
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  ifstream file_stream(kProcDirectory + kStatFilename);
  string key;
  string value;
  string line_str;
  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      istringstream line_stream(line_str);
      while (line_stream >> key >> value) {
        if (key == "cpu") break;
      }
      if (key == "cpu") break;
    }
  }
  // std::cout << "Jiffies" << value << std::endl;
  try {
    return (stoi(value));
  } catch (std::exception& e) {
    return (1);
  }
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
  ifstream file_stream(kProcDirectory + to_string(pid) + kStatFilename);
  string key;
  string value;
  string line_str;
  string user;
  string nice;
  string system;
  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      istringstream line_stream(line_str);
      while (line_stream >> key >> user >> nice >> system >> value) {
        if (key == "cpu") break;
      }
      if (key == "cpu") break;
    }
  }
  // std::cout << "Active Jiffies pid " << value << std::endl;
  try {
    return (stoi(user) + stoi(nice) + stoi(system));
  } catch (std::exception& e) {
    return (1);
  }
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
  ifstream file_stream(kProcDirectory + kStatFilename);
  string key;
  string value;
  string line_str;
  string user;
  string nice;
  string system;
  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      istringstream line_stream(line_str);
      while (line_stream >> key >> user >> nice >> system >> value) {
        if (key == "cpu") break;
      }
      if (key == "cpu") break;
    }
  }
  // std::cout << "Active Jiffies" << value << std::endl;
  try {
    return (stoi(user) + stoi(nice) + stoi(system));
  } catch (std::exception& e) {
    return (1);
  }
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  ifstream file_stream(kProcDirectory + kStatFilename);
  string key;
  string value;
  string line_str;
  string user;
  string nice;
  string system;
  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      istringstream line_stream(line_str);
      while (line_stream >> key >> user >> nice >> system >> value) {
        if (key == "cpu") break;
      }
      if (key == "cpu") break;
    }
  }
  // std::cout << "Idle Jiffies" << value << std::endl;
  try {
    return (stoi(value));
  } catch (std::exception& e) {
    return (1);
  }
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  string line{"1"};
  string utime{"1"};
  string stime{"1"};
  string cutime{"1"};
  string cstime{"1"};
  string starttime{"1"};
  string temp{"1"};
  long total_time = 0;
  long seconds = 0;
  long herz = sysconf(_SC_CLK_TCK);
  vector<int> pids = LinuxParser::Pids();
  long cpu_usage = 0;
  std::vector<string> result;
  try {
    for (int pid : pids) {
      ifstream file_stream(kProcDirectory + to_string(pid) + kStatFilename);
      long uptime = LinuxParser::UpTime(pid);
      int i = 0;
      if (file_stream.is_open()) {
        getline(file_stream, line);
        std::istringstream linestream(line);

        while (i < starttime_index) {
          if (i == utime_index - 1)
            linestream >> utime >> stime >> cutime >> cstime;
          else if (i == starttime_index - 4)
            linestream >> starttime;
          else
            linestream >> temp;

          i++;
        }
        total_time = stol(cutime) + stol(cstime) + stol(stime) + stol(utime);
        seconds = abs(uptime - (stol(starttime) / herz));
        if (seconds <= 0) seconds =1;
        cpu_usage = 100 * ((total_time / herz) / seconds);
      }
      result.emplace_back(to_string(cpu_usage));
    }
  } catch (std::exception& e) {
    std::cout << "Standard exception: " << e.what() << std::endl;
  }
  return result;
}

int LinuxParser::TotalProcesses() {
  ifstream stat_stream(kProcDirectory + kStatFilename);
  string key;
  string value;
  string line_str;

  if (stat_stream.is_open()) {
    while (getline(stat_stream, line_str)) {
      std::istringstream line_stream(line_str);

      while (line_stream >> key >> value) {
        if (key == "processes") break;
      }
      if (key == "processes") break;
    }
  }
  try {
    return (stoi(value));
  } catch (std::exception& e) {
    return (1);
  }
}

int LinuxParser::RunningProcesses() {
  ifstream file_stream(kProcDirectory + kStatFilename);
  string key;
  string value;
  string line_str;

  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      std::istringstream line_stream(line_str);
      while (line_stream >> key >> value) {
        if (key == "procs_running") break;
      }
      if (key == "procs_running") break;
    }

  } else {
  }
  try {
    return (stoi(value));
  } catch (std::exception& e) {
    return (1);
  }
}

string LinuxParser::Command(int pid) {
  ifstream file_stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  string line_str;

  if (file_stream.is_open()) {
    getline(file_stream, line_str);
  }

  else {
  }
  // std::cout << "Cmd is " << line_str << std::endl;

  return line_str;
}

string LinuxParser::Ram(int pid) {
  ifstream file_stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string key;
  string value;
  string line_str;

  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      std::istringstream line_stream(line_str);
      line_stream >> key >> value;
      if (key == "VmSize:") break;
    }

  } else {
  }
  try {
    return to_string(stoi(value) / 1024);
  } catch (std::exception& e) {
    return ("1");
  }
}

string LinuxParser::Uid(int pid) {
  ifstream file_stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string key;
  string value;
  string line_str;

  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      std::istringstream line_stream(line_str);
      line_stream >> key >> value;
      if (key == "Uid:") break;
    }

  } else {
  }

  return value;
}

string LinuxParser::User(int pid) {
  ifstream file_stream(kPasswordPath);
  string name;
  string x;
  string Uid;
  string line_str;
  string Uid_str;
  Uid = LinuxParser::Uid(pid);

  if (file_stream.is_open()) {
    while (getline(file_stream, line_str)) {
      std::replace(line_str.begin(), line_str.end(), ':', ' ');

      std::istringstream line_stream(line_str);
      line_stream >> name >> x >> Uid_str;

      if (Uid_str == Uid) break;
    }

  } else {
  }
  return name;
}

long LinuxParser::UpTime(int pid) {
  ifstream file_stream(kProcDirectory + to_string(pid) + kStatFilename);
  string line;
  string uptime;
  int i = 0;

  if (file_stream.is_open()) {
    {
      getline(file_stream, line);
      std::istringstream linestream(line);
      while (i++ < starttime_index) {
        linestream >> uptime;
      }
    }
  }

  try {
    return (stol(uptime) / sysconf(_SC_CLK_TCK));
  }

  catch (std::exception& e) {
    return (std::stol("1"));
  }
}
float LinuxParser::CpuUtilization(int pid) {
  string line{"1"};
  string utime{"1"};
  string stime{"1"};
  string cutime{"1"};
  string cstime{"1"};
  string starttime{"1"};
  string temp{"1"};
  long total_time = 0;
  long seconds = 0;
  long herz = sysconf(_SC_CLK_TCK);
  float cpu_usage = 0;
  try {
    ifstream file_stream(kProcDirectory + to_string(pid) + kStatFilename);
    long uptime = LinuxParser::UpTime(pid);
    int i = 0;
    if (file_stream.is_open()) {
      getline(file_stream, line);
      std::istringstream linestream(line);

      while (i <= starttime_index) {
        if (i == utime_index - 1)
          linestream >> utime >> stime >> cutime >> cstime;
        else if (i == starttime_index - 4)
          linestream >> starttime;
        else
          linestream >> temp;

        i++;
      }
      total_time = stol(cutime) + stol(cstime) + stol(stime) + stol(utime);
      seconds = abs(uptime - (stol(starttime) / herz));
      if (seconds <= 0) seconds =1;
      cpu_usage = 100 * ((total_time / herz) / seconds);
    }
  } catch (std::exception& e) {
    std::cout << "Standard exception: " << e.what() << std::endl;
  }
  return cpu_usage;
}
