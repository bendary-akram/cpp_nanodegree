#include "processor.h"

#include "linux_parser.h"
#include "process.h"

float Processor::Utilization() {
  std::vector<std::string> cpu_usage = LinuxParser::CpuUtilization();
  float total_cpu_usage = 0;

  int idled = stoi(cpu_usage[3]) + stoi(cpu_usage[4]);

  int nonIdle = stoi(cpu_usage[0]) + stoi(cpu_usage[1]) + stoi(cpu_usage[2]) +
                stoi(cpu_usage[5]) + stoi(cpu_usage[6]) + stoi(cpu_usage[7]);
  int totald = idled + nonIdle;

  try {
    total_cpu_usage = (float)(totald - idled) / (float)totald;

  } catch (std::exception& e) {
    total_cpu_usage = 1.1;
  }

  return (total_cpu_usage);
}