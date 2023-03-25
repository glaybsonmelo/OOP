/*
Fiz tudo e passou em todos os testes
Fiz sozinho
Melhorei meu conhecimento sobre conversão de tipos
Levei 1 hora
*/

#include <fn.hpp>
#include <iostream>

using namespace fn;
using namespace std;

struct Car {
  int pass{0}, passMax{2}, gas{0}, gasMax{100}, km{0};
  string show() {
    return "pass: " + tostr(pass) + ", gas: " + tostr(gas) +
           ", km: " + tostr(km);
  }
  void enter() {
    if (pass == passMax) {
      write("fail: limite de pessoas atingido");
      return;
    }
    pass++;
  }
  void leave() {
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
      return;
    }
    pass--;
  }

  void fuel(int qty_fuel) {
    if (qty_fuel >= gasMax) {
      gas = gasMax;
      return;
    }
    gas += qty_fuel;
  }

  void drive(int qty_km) {
    if (pass == 0) {
      write("fail: nao ha ninguem no carro");
      return;
    }
    if (gas == 0) {
      write("fail: tanque vazio");
      return;
    }
    if (qty_km > gas) {
      write("fail: tanque vazio apos andar " + tostr(gas) + " km");
      km += gas;
      gas = 0;
      return;
    }
    gas -= qty_km;
    km += qty_km;
  }
};

int main() {
  Car car;

  while (true) {

    auto line = input();
    write("$" + line);
    auto args = split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "show") {
      write(car.show());
    } else if (args[0] == "enter") {
      car.enter();
    } else if (args[0] == "leave") {
      car.leave();
    } else if (args[0] == "fuel") {
      car.fuel(stoi(args[1]));
    } else if (args[0] == "drive") {
      car.drive(stoi(args[1]));
    };
  }
  return 0;
}