/*
    Fiz tudo e passou em todos os testes
    Fiz sozinho
    Aprendi usar ponteitos compartilhados
    Levei 2h
*/

#include <iostream>
#include <sstream>
#include <memory>  //sharedptr
#include <iomanip> //setprecision
#include <utility> //exchange
#include <fn.hpp>

class Lead {
    float thickness;
    std::string hardness;
    int size;

  public:
      Lead(float thickness, std::string hardness, int size) {
        this->thickness = thickness;
        this->hardness = hardness;
        this->size = size;
      }

      int usagePerSheet() const {
          return hardness == "HB" ? 1 : hardness == "2B" ? 2 : hardness == "4B" ? 4 : 6;
      }
  
      float getThickness() const {
          return thickness;
      }
  
      std::string getHardness() const {
          return hardness;
      }
  
      int getSize() const {
          return size;
      }
  
      void setSize(int size) {
        this->size = size;
      }
      std::string str() const {
          std::stringstream ss;
          ss << std::fixed << std::setprecision(1) 
             << thickness << ":" << hardness << ":" << size;
          return ss.str();
      }
};

std::ostream& operator<<(std::ostream& ss, Lead gr) {
    return ss << gr.str();
}

struct Pencil {
    float thickness {0.f};
    std::shared_ptr<Lead> tip {nullptr};

    Pencil(float thickness = 0.0) {
      this->thickness = thickness;
    }

    bool hasGrafite() {
        return tip ? true : false;
    }

    bool insert(std::shared_ptr<Lead> grafite) {

      if(hasGrafite()) {
        fn::write("fail: ja existe grafite");
        return false;
      }
      if(this->thickness != grafite->getThickness()) {
          fn::write("fail: calibre incompativel");
          return false;
        }
      tip = std::make_shared<Lead>(grafite->getThickness(), grafite->getHardness(), grafite->getSize());
        return true;
    }

    std::shared_ptr<Lead> remove() {
        tip = { nullptr };
        return tip;
    }

    void writePage() {
      if(!hasGrafite()) {
        fn::write("fail: nao existe grafite");
        return;
      }
      if(tip->getSize() <= 10) {
        fn::write("fail: tamanho insuficiente");
        return;
      }
      if(tip->getSize() - tip->usagePerSheet() < 10) {
        int total_writed = tip->getSize() - 10;
        tip->setSize(tip->getSize() - total_writed);

        fn::write("fail: folha incompleta");
        return;
      }
      tip->setSize(tip->getSize() - tip->usagePerSheet());
    }

    std::string str() {
        std::stringstream ss;
        ss << "calibre: " << thickness << ", grafite: ";
        if (tip != nullptr)
            ss << "[" << *tip << "]";
        else
            ss << "null";
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Pencil l) {
    return os << l.str();
}

using namespace fn;

int main() {
    Pencil pencil;

    while (true) {
        auto line = input();
        write("$" + line);
        auto args = split(line);

        if      (args[0] == "end"   ) { break;                                                                                  }
        else if (args[0] == "show"  ) { write(pencil);                                                                    }
        else if (args[0] == "init"  ) { pencil = Pencil(number(args[1]));                                                       }
        else if (args[0] == "insert") { pencil.insert(std::make_shared<Lead>(number(args[1]), args[2], (int) number(args[3])));}
        else if (args[0] == "remove") { pencil.remove();                                                                        }
        else if (args[0] == "write" ) { pencil.writePage();                                                                     }
    }
}
