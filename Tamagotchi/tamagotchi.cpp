/*
  Fiz tudo e passou em todos os casos de testes 
  Fiz sozinho
  Levei 1h
*/

#include <fn.hpp>

class Pet{
private:
    int energy {0}, energyMax {0}, hungry {0}, hungryMax {0}, clean {0}, cleanMax{0};
    int diamonds {0}, age {0};
    bool alive;

    bool testAlive() {
        if (alive)
            return true;
        fn::write("fail: pet esta morto");
        return false;
    }

    void setHungry(int value) {
        if (value <= 0) {
            hungry = 0;
            fn::write("fail: pet morreu de fome");
            alive = false;
        } else if (value > hungryMax) {
            hungry = hungryMax;
        } else {
            hungry = value;
        }
    }
    void setEnergy(int value) {
      if(value <= 0){
        energy = 0;
        fn::write("fail: pet morreu de fraqueza");
        alive = false;
      }
      else {
        energy = value;  
        }
    }

    void setClean(int value) {
      if (value <= 0){
        clean = 0;
        fn::write("fail: pet morreu de sujeira");
        alive = false;
      }
      else {
        clean = value;
      }
    }

public:
    Pet(int energy = 0, int hungry = 0, int clean = 0) {
      this->energy = energy;
      this->hungry = hungry;
      this->clean = clean;
      energyMax = energy;
      hungryMax = hungry;
      cleanMax = clean;
      alive = true;
    }

    void play() {
        if (!testAlive())
            return;
        setEnergy(getEnergy() - 2);
        setHungry(getHungry() - 1);
        setClean(getClean() - 3);
        diamonds += 1;
        age += 1;
    }

    void shower() {
      if(!testAlive())
        return;
      setEnergy(getEnergy() - 3);
      setHungry(getHungry() - 1);
      setClean(cleanMax);
      age += 2;
    }

    void eat() {
      if(!testAlive())
        return;
      setEnergy(getEnergy() - 1);
      setHungry(getHungry() + 4);
      setClean(getClean() - 2);
      age += 1;
    }

    void sleep() {
      if(!testAlive())
        return;
      if(energy > energyMax - 5){
        fn::write("fail: nao esta com sono");
        return;
      }
      energy = energyMax;
      setHungry(getHungry() - 1);
      age += 5;
    }

    int getClean() {
        return clean;
    }
    int getHungry() {
        return hungry;
    }
    int getEnergy() {
        return energy;
    }
    int getEnergyMax() {
        return energyMax;
    }
    int getCleanMax() {
        return cleanMax;
    }
    int getHungryMax() {
        return hungryMax;
    }

    std::string toString() {
        return fn::format("E:{}/{}, S:{}/{}, L:{}/{}, D:{}, I:{}", 
            energy, energyMax, hungry, hungryMax, clean, cleanMax, diamonds, age);
    }

};

int main() {
    Pet pet;
    while (true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');

        fn::write("$" + line);

        if (args[0] == "end") {
            break;
        } else if (args[0] == "init") {
            pet = Pet(+args[1], +args[2], +args[3]);
        } else if (args[0] == "show") {
            fn::write(pet.toString());
        } else if (args[0] == "play") {
            pet.play();
        } else if (args[0] == "eat") {
            pet.eat();
        } else if (args[0] == "sleep") {
            pet.sleep();
        } else if (args[0] == "shower") {
            pet.shower();
        } else {
            fn::write("fail: comando invalido");
        }
    }
}
