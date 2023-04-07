/*
    Fiz tudo e passou em todos os testes
    Fiz sozinho
    Aprendi mais sobre operador ternário
    levei 30m para concluir
*/
#include <iostream>
#include <vector>

int count(std::vector<int> vet, int x) {
  int qty {0};
  for(int item : vet)
    if(item == x) qty ++;
  return qty;
}

int sum(std::vector<int> vet) {
  int total {0};
  for(int item : vet){
      total += abs(item);
  }
  return total;
}

double average(const std::vector<int>& vet) {
  int total {0};
  double average {0.0};
  for(int item : vet){
      total += abs(item);
  }
  average = (double) total / vet.size();
  return average;
}

std::string more_men(const std::vector<int>& vet) {
  int qty_women {0}, qty_men {0};
  for(int item : vet){
    if(item > 0) qty_men ++;
    else qty_women ++;
  }
  return qty_men > qty_women ? "men" : qty_women > qty_men ? "women" : "draw";
}

std::string half_compare(const std::vector<int>& vet) {
  int qty_stress_first_half {0}, qty_stress_second_half {0};
  for(int i = 0; i < vet.size(); i++){
    if(i < vet.size()/2)
      qty_stress_first_half += abs(vet[i]);
    else 
      qty_stress_second_half += abs(vet[i]);
  }
  return qty_stress_first_half > qty_stress_second_half ? "first" : qty_stress_second_half > qty_stress_first_half ? "second" : "draw";
}

std::string sex_battle(const std::vector<int>& vet) {
  int qty_stress_men {0}, qty_stress_women {0};
  for(int item : vet) {
    if(item > 0) qty_stress_men += abs(item);
    else qty_stress_women += abs(item);
  }
  return qty_stress_men > qty_stress_women ? "men" : qty_stress_women > qty_stress_men ? "women" : "draw";
}

#include <fn.hpp>
using namespace fn;

int main() {

    auto str2vet = [](auto s) { return s.substr(1, s.size() - 2) | SPLIT(',') | MAP(FNT(x, (int)+x)); };

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"              ) { break;                                              }
        else if (args[0] == "count"            ) { count(str2vet(args[1]), +args[2])         | WRITE();}
        else if (args[0] == "sum"              ) { sum(str2vet(args[1]))                     | WRITE();}
        else if (args[0] == "more_men"         ) { more_men(str2vet(args[1]))                | WRITE();} 
        else if (args[0] == "half_compare"     ) { half_compare(str2vet(args[1]))            | WRITE();}
        else if (args[0] == "more_men_or_women") { more_men(str2vet(args[1]))                | WRITE();}
        else if (args[0] == "sex_battle"       ) { sex_battle(str2vet(args[1]))              | WRITE();}
        else if (args[0] == "average"          ) { average(str2vet(args[1])) | TOSTR("%.2f") | WRITE();}
        else                                     { "fail: unknown command"                   | WRITE();}
    }     
}
