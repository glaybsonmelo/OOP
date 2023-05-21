/*
  Fiz tudo e passou em todos os testes
  Fiz sozinho
  Lwvei 3h distribuidas em 3 dias
  Fiquei com duvida se usei o Label corretamente.
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fn.hpp>
#include <list>

enum Label {
  Edeposit,
  Efee,
  Eopening,
  Ereverse,
  Ewithdraw
};

class Operation {
  int index;
  Label label;
  int value;
  int balance;
  public:
    Operation(int index, Label label, int value, int balance): index(index), label(label), value(value), balance(balance){};
  int getBalance(){
    return balance;
  }
  int getIndex(){
    return index;
  }
  Label getLabel(){
    return label;
  }
  int getValue(){
    return value;
  }
  std::string str() const {
    std::stringstream ss;
    std::string labelStr = label == Edeposit ? "deposit" :
                         label == Efee ? "fee" :
                         label == Eopening ? "opening" :
                         label == Ereverse ? "reverse" :
                         label == Ewithdraw ? "withdraw" :
                         "unknown";

  ss << std::setw(2) << index << ":" << std::setw(9) << labelStr << ":" << std::setw(5) << value << ":" << std::setw(5) << balance + value;
    return ss.str();
  }
};
std::ostream &operator<<(std::ostream &os, const Operation &operation) {
  return os << operation.str();
}
class BalanceManager {
  int balance {0};
  std::list<Operation> extract;
  int nextId {0};
  public:
    BalanceManager(){};
    void addOperation(Label label, int value){
      if(label == 0){
        if(value < 0){
          fn::write("fail: invalid value");
          return;
        }
        extract.push_back(Operation(nextId, label, value, balance));
        balance += value;
        nextId ++;
      }
      else if(label == 4) {
        if(balance - value < 0){
          fn::write("fail: insufficient balance");
          return;
        }
        extract.push_back(Operation(nextId, label, value*-1, balance));
        balance -= value;
        nextId ++;
      }
      else if(label == 1) {
        extract.push_back(Operation(nextId, label, value*-1, balance));
        balance -= value;
        nextId ++;
      }
      else if(label == 2) {
        extract.push_back(Operation(nextId, label, value, balance));
        nextId ++;
      }
      else if(label == 3) {
        extract.push_back(Operation(nextId, label, value, balance));
        balance += value;
        nextId ++;
      }
    };
    std::list<Operation> getExtract(int qtdOp){
      std::list<Operation> auxListExtract;
      for(auto ext : extract) {
        if(qtdOp == 0){
          auxListExtract.push_back(ext);
        }
        else if(extract.size() - qtdOp <= ext.getIndex())
          auxListExtract.push_back(ext);
      }
      return auxListExtract;
    }
    int getBalance() const {
      return balance;
    }
    std::string str() const {
      std::stringstream ss;
      for(auto ext : extract){
        ss << ext << std::setw(5) << balance;
      }
      return ss.str();
    };

};
std::ostream &operator<<(std::ostream &os, const BalanceManager &balanceMnger) {
  return os << balanceMnger.str();
}
class Account{
  BalanceManager balanceManager;
  int id;
  public:
    Account(int id = 0): id(id){balanceManager.addOperation(Eopening, 0);};
    void deposit(int value){
      balanceManager.addOperation(Edeposit, value);
    }
    void withdraw(int value){
      balanceManager.addOperation(Ewithdraw, value);
    }
    void fee(int value) {
      balanceManager.addOperation(Efee, value);
    }
    void reverse(int index) {
      int lengthExtract = balanceManager.getExtract(0).size();
      int value = 0;
      auto extracts = balanceManager.getExtract(0);
      for(auto ext : extracts){
          if(ext.getIndex() == index){
            if(ext.getLabel() != 1){
              fn::write(fn::format("fail: index {} is not a fee", index));
              continue;
            }
            value = ext.getValue()*-1;
            break;
          }
      }
      if (index > lengthExtract){
        fn::write(fn::format("fail: index {} invalid", index));
        return;
      };
      if(value > 0){
        balanceManager.addOperation(Ereverse, value);
          return;
        
      }
    }
    BalanceManager getBalanceManager(){
      return balanceManager;
    }
    std::string str() const {
      std::stringstream ss;
      ss << fn::format("account:{} balance:{}", id, balanceManager.getBalance());
      return ss.str();
  }
};

std::ostream &operator<<(std::ostream &os, const Account &account) {
  return os << account.str();
}

int main(){
  Account account;
  while(true) {
    
    auto line = fn::input();
    fn::write("$" + line);
    auto args = fn::split(line);
    
    if(args[0] == "end")
      break;
      
    else if(args[0] == "init")
      account = Account(stoi(args[1]));
    
    else if(args[0] == "show")
      fn::write(account);
    
    else if(args[0] == "deposit")
      account.deposit(stoi(args[1]));
    
    else if(args[0] == "withdraw")
      account.withdraw(stoi(args[1]));
      
    else if(args[0] == "fee")
      account.fee(stoi(args[1])); 
      
    else if (args[0] == "extract") {
        auto extracts = account.getBalanceManager().getExtract(stoi(args[1]));
        for (auto extract : extracts) {
          fn::write(extract);
        }
    }
    else if (args[0] == "reverse"){
      account.reverse(stoi(args[1]));
      account.reverse(stoi(args[2]));
      account.reverse(stoi(args[3]));
      account.reverse(stoi(args[4]));
    }
    else 
      fn::write("fail: invalid command!");
  };
  
}
