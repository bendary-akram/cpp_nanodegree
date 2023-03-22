#include "processor.h"
#include "process.h"
#include "linux_parser.h"

float Processor::Utilization() { 
    std::vector<std::string> cpu_usage = LinuxParser::CpuUtilization();
    float total_cpu_usage=0;

    for(std::string x : cpu_usage){
        total_cpu_usage=total_cpu_usage+ stof(x);

    }
    return total_cpu_usage;
}