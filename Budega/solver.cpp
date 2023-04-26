#include <fn.hpp>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Pessoa {
  std::string nome;

public:
  Pessoa(std::string nome) {
    this->nome = nome;
  }
  std::string getNome() const {
    return nome;
  }
  std::string str() const {
    return fn::format("{}", getNome());
  }
};
std::ostream &operator<<(std::ostream &os, const Pessoa &p) {
  return (os << p.str());
}

class Mercantil {
  std::vector<std::shared_ptr<Pessoa>> caixas;  // caixas do supermercado
  std::list<std::shared_ptr<Pessoa>> esperando; // lista de clientes esperando

  bool validarIndice(int indice) {
    return (indice >= 0 && indice < caixas.size());
  }

public:

  Mercantil(int qtd_caixas) : caixas(qtd_caixas, nullptr) {}

  void chegar(const std::shared_ptr<Pessoa> &person) {
    esperando.push_back(person);
  }

bool chamarNoCaixa(int indice) {

    if (esperando.empty())
        return fn::write("fail: sem clientes");

    if(caixas[indice] != nullptr) return fn::write("fail: caixa ocupado");
    
    caixas[indice] = esperando.front();
    esperando.pop_front();
    
    return true;
}

  std::shared_ptr<Pessoa> finalizar(int indice) {
    if (validarIndice(indice) && caixas[indice] != nullptr) {
      auto pessoa = caixas[indice];
      caixas[indice] = nullptr;
    if (!esperando.empty()) {
      auto next = esperando.front();
    }

    return pessoa;
    }
    if(!validarIndice(indice))
      fn::write("fail: caixa inexistente");
    else 
      fn::write("fail: caixa vazio");
    
      return nullptr;
  
  }

  std::string str() const {
    auto caixas_str =
        caixas | fn::MAP(FNT(c, c == nullptr ? "-----" : c->getNome()));
    return "Caixas: " + fn::tostr(caixas_str) + "\n" +
           "Espera: " + fn::tostr(esperando);
  }
};

std::ostream &operator<<(std::ostream &os, const Mercantil &b) {
  return (os << b.str());
}

int main() {
  Mercantil bank(0);
  while (true) {
    auto line = fn::input();
    auto args = fn::split(line, ' ');
    fn::write("$" + line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "init") {
      bank = Mercantil(+args[1]);
    } else if (args[0] == "call") {
      bank.chamarNoCaixa(+args[1]);
    } else if (args[0] == "finish") {
      bank.finalizar(+args[1]);
    } else if (args[0] == "arrive") {
      bank.chegar(std::make_shared<Pessoa>(args[1]));
    } else if (args[0] == "show") {
      fn::write(bank);
    } else {
      fn::write("fail: comando invalido");
    }
  }
}
