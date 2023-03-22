#include "format.h"

#include <string>

using std::string;

string Format::ElapsedTime(long seconds) {
  long hour = seconds / 3600;
  long min = (seconds % 3600) / 60;
  long sec = (seconds % 3600) % 60;

  return std::to_string(hour) + ':' + std::to_string(min) + ':' +
         std::to_string(sec);
}