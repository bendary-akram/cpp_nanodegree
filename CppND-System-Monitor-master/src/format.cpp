#include "format.h"

#include <string>

using std::string;

string Format::ElapsedTime(long seconds) {
  long hours = seconds / 3600;
  long minutes = (seconds % 3600) / 60;
  long secs = (seconds % 3600) % 60;

  string sec = std::to_string(secs);
  sec.insert(0, 2 - sec.length(), '0');

  string mins = std::to_string(minutes);
  mins.insert(0, 2 - mins.length(), '0');

  string hrs = std::to_string(hours);
  hrs.insert(0, 2 - hrs.length(), '0');

  return hrs + ':' + mins + ':' + sec;
}