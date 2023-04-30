/*
    Fiz tudo e passou em todos os testes
    Fiz sozinho
    Como foi a primeira vez que fiz do zero quebrei bastante a cabeça, mas no fim aprendi bastante sobre as funções str(). 
    Levei 6h

*/

#include <fn.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

class Slot {
  std::string name;
  float price;
  int quantity;

public:
  Slot(std::string name, float price, int quantity) {
    setName(name);
    setPrice(price);
    setQuantity(quantity);
  };

  std::string getName() { return name; }

  float getPrice() { return price; }

  int getQuantity() { return quantity; }

  void setName(std::string name) { this->name = name; }

  void setPrice(float price) { this->price = price; }

  void setQuantity(int quantity) { this->quantity = quantity; }

  std::string str() const {
    std::stringstream ss;
    ss << "[";
    if (name == "empty")
      ss << "   ";
    else
      ss << " ";
    ss << name << " : " << quantity << " U : " << std::fixed
       << std::setprecision(2) << price << " RS]";
    return ss.str();
  }
};
std::ostream &operator<<(std::ostream &os, const Slot &slot) {
  return os << slot.str();
}
class Machine {
  std::vector<Slot> slots;
  float profit, cash;
  int capacity;

public:
  Machine(int capacity = 0)
      : capacity(capacity), slots(capacity, Slot("empty", 0.00, 0)) {}

  Slot getSlot(int index) { return slots[index]; };

  void setSlot(int index, Slot slot) {
    if (index > capacity || index < 0) {
      fn::write("fail: indice nao existe");
      return;
    }
    slots[index] = slot;
  }

  void clearSlot(int index) { slots[index] = Slot("empty", 0.00, 0); };

  void insertCash(float cash) { this->cash += cash; };

  void withdrawCash() {
    auto tempCash = cash;
    cash = 0.0;
    fn::write(fn::format("voce recebeu {%.2f} RS", tempCash));
  }

  float getCash() { return cash; }

  float getProfit() { return profit; }

  void buyItem(int index) {
    auto qtyItems = slots[index].getQuantity();
    auto priceOfItem = slots[index].getPrice();
    
    if (index > capacity || index < 0) {
      fn::write("fail: indice nao existe");
      return;
    }
    if (qtyItems == 0) {
      fn::write("fail: espiral sem produtos");
      return;
    }
    if (cash - priceOfItem < 0) {
      fn::write("fail: saldo insuficiente");
      return;
    }
    slots[index].setQuantity(qtyItems - 1);
    profit += priceOfItem;
    cash -= priceOfItem;
    fn::write(fn::format("voce comprou um {}", slots[index].getName()));
  }

  std::string str() const {
    std::stringstream ss;
    ss << "saldo: " << std::fixed << std::setprecision(2) << cash;
    for (int i = 0; i < slots.size(); i++) {
      ss << "\n" << i << " " << slots[i].str();
    }
    return ss.str();
  }
};

std::ostream &operator<<(std::ostream &os, const Machine &machine) {
  return os << machine.str();
}

int main() {
  Machine machine;

  while (true) {

    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line);

    if (args[0] == "end") {
      break;
    } else if (args[0] == "init") {
      machine = Machine(+args[1]);
    } else if (args[0] == "show") {
      fn::write(machine);
    } else if (args[0] == "set") {
      machine.setSlot(+args[1], Slot(fn::tostr(args[2]), +args[4], +args[3]));
    } else if (args[0] == "limpar") {
      machine.clearSlot(+args[1]);
    } else if (args[0] == "dinheiro") {
      machine.insertCash(+args[1]);
    } else if (args[0] == "troco") {
      machine.withdrawCash();
    } else if (args[0] == "comprar") {
      machine.buyItem(+args[1]);
    }
    else {
      fn::write("fail: comando invalido!");
    }
  }
  return 0;
}