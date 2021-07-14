#include <iomanip>
#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  int hour;
  int min;
  int sec;
  std::stringstream OutStr;

  sec = seconds % 60;
  seconds /= 60;
  min = seconds % 60;
  seconds /= 60;
  hour = seconds % 24;
  OutStr << std::setfill('0') << std::setw(2) << std::to_string(hour);
  OutStr << ":";
  OutStr << std::setfill('0') << std::setw(2) << std::to_string(min);
  OutStr << ":";
  OutStr << std::setfill('0') << std::setw(2) << std::to_string(sec);

  return OutStr.str();
}