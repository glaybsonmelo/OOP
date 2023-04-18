/*
  - Fiz tudo e passou em todos os teste
  - Fiz sozinho
  - Tive dificulade na ultima função (repeated),
    pesquisando no youtube achei uma estrutura que facilitava a resolução, unordered_map
    usei para armazenar a frequência que cada elemento aparece no vetor.
  - Levei 1.5h distribuidas em 3 dias
*/
#include <iostream>
#include <vector>
#include <fn.hpp>

using namespace fn;

std::vector<int> get_men(std::vector<int> vet) {
  std::vector<int> mens;
  for(int person : vet) {
    if (person > 0) {
      mens.push_back(person);
    }
  }
   return mens;
}

std::vector<int> get_calm_women(std::vector<int> vet) {
  std::vector<int> womens;
  for(int person : vet) {
    if (person < 0 && person > - 10) {
      womens.push_back(person);
    }
  }
   return womens;
}

std::vector<int> sort(std::vector<int> vet) {
  int temp {0};
  for(int i  = 0; i < vet.size() - 1; i++) {
    for(int k = i; k < vet.size(); k++){
      if(vet[k] < vet[i]){
        temp = vet[i];
        vet[i] = vet[k];
        vet[k] = temp;
      }
    };
  }
    return vet;
}

std::vector<int> sort_stress(std::vector<int> vet) {
  int temp {0};
  for(int i  = 0; i < vet.size() - 1; i++) {
    for(int k = i; k < vet.size(); k++){
      if(abs(vet[k]) < abs(vet[i])){
        temp = vet[i];
        vet[i] = vet[k];
        vet[k] = temp;
      }
    };
  }
    return vet;
}

std::vector<int> reverse(std::vector<int> vet) {
  int temp {0};
  for(int i  = 0, currentLast = vet.size() - 1; i  < vet.size()/2; i++, currentLast --) {
    temp = vet[i];
    vet[i] = vet[currentLast];
    vet[currentLast] = temp;
  }
    return vet;
}

std::vector<int> unique(std::vector<int> vet) {
  for(int i = 0; i < vet.size(); i++)
      for(int k = i + 1; k < vet.size();){
          if(vet[i] == vet[k])
              vet.erase(vet.begin() + k);
          else 
              k++;
      }
  return vet;
}

std::vector<int> repeated(std::vector<int> vet) {

    std::unordered_map<int, int> freq;
    std::vector<int> vet_copy;
    for (int i = 0; i < vet.size(); i++) {
        freq[vet[i]]++;
        if (freq[vet[i]] > 1) {
            vet_copy.push_back(vet[i]);
        }
    }
    return vet_copy;
}


int main() {
    auto strToVet = [](auto s) { return s.substr(1, s.size() - 2) | SPLIT(',') | MAP(FNT(x, (int)+x)); };

    while(true) {
        std::string line = input();
        auto args = split(line, ' ');
        write('$' + line);

        if     (args[0] == "get_men"        ) { write(get_men(strToVet(args[1])));        }
        else if(args[0] == "get_calm_women" ) { write(get_calm_women(strToVet(args[1]))); }
        else if(args[0] == "sort"           ) { write(sort(strToVet(args[1])));           }
        else if(args[0] == "sort_stress"    ) { write(sort_stress(strToVet(args[1])));    }
        else if(args[0] == "reverse"        ) { write(reverse(strToVet(args[1])));        }
        else if(args[0] == "unique"         ) { write(unique(strToVet(args[1])));         }
        else if(args[0] == "repeated"       ) { write(repeated(strToVet(args[1])));       }
        else if(args[0] == "end"            ) { break;                                    }
    }
}

