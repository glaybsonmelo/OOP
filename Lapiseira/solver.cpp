/*
    Fiz tudo e passou em todos os testes
    Fiz sozinho
    Melhorei meu conhecimento sobre ponteiros
    Levei 1h
*/

#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <utility>
#include <iomanip> //setprecision
#include <fn.hpp>
using namespace fn;

class Grafite{
    float calibre;
    std::string dureza;
    int tamanho;
public:
    Grafite(float calibre, std::string dureza, int tamanho) {
        this->calibre = calibre;
        this->dureza = dureza;
        this->tamanho = tamanho;
    }
    int desgastePorFolha() {
        if (dureza == "HB")
            return 1;
        if (dureza == "2B")
            return 2;
        if (dureza == "4B")
            return 4;
        return 6;
    }
    float getCalibre() {
        return calibre;
    }
    std::string getDureza() {
        return dureza;
    }
    int getTamanho() {
        return tamanho;
    }
    void setTamanho(int tamanho) {
        this->tamanho = tamanho;
    }
    std::string str() const {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1) << calibre << ":" << dureza << ":" << tamanho;
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, Grafite g) {
    return os << g.str();
}

using PGrafite = std::shared_ptr<Grafite>;

struct Lapiseira{
    float calibre {0.f};
    PGrafite grafite {nullptr};
    std::list<PGrafite> tambor;

    Lapiseira(float calibre = 0.0) {
      this->calibre = calibre;
    }

    bool inserir(PGrafite grafite) {
      if(calibre != grafite->getCalibre()) {
        fn::write("fail: calibre incompatível");
        return false;
      }
      PGrafite novoGrafite = std::make_shared<Grafite>(grafite->getCalibre(), grafite->getDureza(), grafite->getTamanho());
      tambor.push_back(novoGrafite);
      return true;
    }

    PGrafite remover() {
      if(!this->grafite) {
        fn::write("fail: nao existe grafite no bico");
        return {nullptr};
      }
      PGrafite temp = this->grafite;
      this->grafite = {nullptr};
      return temp;
    }

    void write() {
      if(!this->grafite) {
        fn::write("fail: nao existe grafite no bico");
        return;
      }
      if(grafite->getTamanho() == 10) {
        fn::write("fail: tamanho insuficiente");
        return;
      }
      if(grafite->getTamanho() - grafite->desgastePorFolha() < 10) {
        int total_escrito = grafite->getTamanho() - 10;
        grafite->setTamanho(grafite->getTamanho() - total_escrito);
        fn::write("fail: folha incompleta");
        return;
      }

      grafite->setTamanho(grafite->getTamanho() - grafite->desgastePorFolha());
    }
    void puxar() {
      if(grafite) {
        fn::write("fail: ja existe grafite no bico");
        return;
      }
      PGrafite grafite2insert = this->tambor.front();
      this->tambor.pop_front();
      grafite = grafite2insert;
    }
    std::string str() const {
        auto fngr = [](PGrafite g) { return "[" + (g == nullptr ? "" : g->str()) + "]"; };
        std::ostringstream os;
        os << "calibre: " << calibre 
           << ", bico: " << fngr(grafite)
           << ", tambor: {" << (tambor | MAP(fngr) | JOIN("")) << "}";
        return os.str();
    }
};

std::ostream& operator<<(std::ostream& os, const Lapiseira& l) {
    return os << l.str();
}

int main() {
    Lapiseira lapiseira;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "show") {
            fn::write(lapiseira.str());
        } else if (args[0] == "init") {
            lapiseira = Lapiseira((float) +args[1]);
        } else if (args[0] == "insert") {
            lapiseira.inserir(std::make_shared<Grafite>((float) +args[1], args[2], +args[3]));
        } else if (args[0] == "remove") {
            lapiseira.remover();
        } else if (args[0] == "pull") {
            lapiseira.puxar();
        } else if (args[0] == "write") {
            lapiseira.write();
        } else {
            fn::write("fail: comando invalido");
        }
    }
}
