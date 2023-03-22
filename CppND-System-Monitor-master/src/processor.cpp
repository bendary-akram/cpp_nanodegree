#include "processor.h"

#include "linux_parser.h"
#include "process.h"

float Processor::Utilization() {
  std::vector<std::string> cpu_usage = LinuxParser::CpuUtilization();
  float total_cpu_usage = 0;

  try {
    for (std::string x : cpu_usage) {
    total_cpu_usage = total_cpu_usage + stof(x);
  }

  } catch (std::exception& e) {
    total_cpu_usage=1.1;
  }

    return total_cpu_usage;
}