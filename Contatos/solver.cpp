/*
  Fiz tudo e passou em tods os testes
  Fiz sozinho
  Levei 1h distribuida em 2d
*/
#include <iostream>
#include <fn.hpp>

class Fone {
  std::string id;
  std::string number;

public:
  Fone(std::string id = "", std::string number = "") : id(id), number(number) {}
  std::string getId() { return id; }
  std::string getNumber() { return number; }
  bool isValid() { return {}; }
  std::string str() {
    std::stringstream ss;
    ss << id << ":" << number;
    return ss.str();
  }
};
std::ostream &operator<<(std::ostream &out, Fone fone) {
  return out << fone.str();
}

class Contact {
  std::string name;
  bool favorited;
  std::vector<Fone> fones;
  

public:
  Contact(std::string name = "") : name(name) {}

  std::string getName() { return name; }

  std::vector<Fone> getFones() { return fones; }

  void addFone(std::string id, std::string number) {
    this->name = name;
    for (int i = 0; i < number.size(); i++) {
      if ((number[i] < '0' || number[i] > '9') && number[i] != '(' &&
          number[i] != ')' && number[i] != '.') {
        fn::write("fail: invalid number");
        return;
      }
    }
    fones.push_back(Fone(id, number));
  }

  void rmFone(int index) {
    int acc = 0;
    for (auto fone : fones) {
      if (acc == index)
        fones.erase(fones.begin() + acc);
      acc++;
    }
  }

  void toogleFavorited() {
    if (isFavorited())
      favorited = false;
    else
      favorited = true;
  }

  bool isFavorited() { return favorited; }

  std::string str() {
    std::stringstream ss;
    int cont = 0;

    ss << (favorited == true ? "@ " : "- ") << name << " [";
    for (auto fone : fones) {
      ss << fone << (cont != fones.size() - 1 ? ", " : "");
      cont++;
    }
    ss << "]";
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &out, Contact contato) {
  return out << contato.str();
}

int main() {
  Contact contato;
  while (true) {
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line, ' ');

    if (args[0] == "end") {
      break;
    } else if (args[0] == "init") {
      contato = Contact(args[1]);
    } else if (args[0] == "add") {
      contato.addFone(args[1], args[2]);
    } else if (args[0] == "rm") {
      contato.rmFone(+args[1]);
    } else if (args[0] == "tfav") {
      contato.toogleFavorited();
    } else if (args[0] == "show") {
      fn::write(contato);
    } else {
      fn::write("fail: comando invalido");
    }
  }
}
