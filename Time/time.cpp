/*
Fiz tudo e passou em todos os testes
Fiz sozinho
Levei 1.5h
*/

#include "fn.hpp"
#include <iostream>

using namespace fn;
using namespace std;

class Time {
  int hour{0};
  int minute{0};
  int second{0};

public:
  Time(int hour = 0, int minute = 0, int second = 0) {
    setHour(hour);
    setMinute(minute);
    setSecond(second);
  }
  void toString() {
    write(format("{%02d}:{%02d}:{%02d}", hour, minute, second));
  }
  void setHour(int hour) {
    if (hour >= 24) {
      write("fail: hora invalida");
      return;
    }
    this->hour = hour;
  }
  void setMinute(int minute) {
    if (minute >= 60) {
      write("fail: minuto invalido");
      return;
    }
    this->minute = minute;
  }
  void setSecond(int second) {
    if (second >= 60) {
      write("fail: segundo invalido");
      return;
    }
    this->second = second;
  }
  int getHour() { return hour; }
  int getMinute() { return minute; }
  int getSecond() { return second; }

  void nextSecond() {
    second++;
    if (second >= 60) {
      second = 0;
      minute++;
    }
    if (minute >= 60) {
      minute = 0;
      hour++;
    }
    if (hour == 24) {
      hour = 0;
    }
  }
};

int main() {
  Time time(0, 0, 0);
  while (true) {
    
    auto line = input();
    write("$" + line);
    auto args = split(line);
    
    if (args[0] == "init") {
      time = Time(+args[1], +args[2], +args[3]);
    }
    else if (args[0] == "show") {
      time.toString();
    }
    else if (args[0] == "set") {
      time.setHour(+args[1]);
      time.setMinute(+args[2]);
      time.setSecond(+args[3]);
    }
    else if (args[0] == "next") {
      time.nextSecond();
    }
    else if (args[0] == "end") {
      break;
    }
  }
  return 0;
}