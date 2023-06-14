#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

class Pencil {
  private:
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;
  public:
    Pencil(sf::RenderWindow& window): window(window) {
      if(!font.loadFromFile("./fonts/FiraCode-Bold.ttf")) 
        std::cout << "Font not loaded" << '\n';

      text.setFont(font);
    }

    void write(std::string str, int x, int y, int size, sf::Color color) {
      text.setString(str);
      text.setPosition(x, y);
      text.setCharacterSize(size);
      text.setFillColor(color);
      window.draw(text);
    }
    
};

class Bubble {
  private:
    int x, y;
    char letter;
    int speed;
    static const int radius { 10 };
    bool alive { true };
  public:
    Bubble(int x, int y, char letter, int speed): x(x), y(y), letter(letter), speed(speed) {};
    
    void update() {
      y += speed;
    }

    void draw(sf::RenderWindow& window) {
      static Pencil pencil(window);
      sf::CircleShape bubble (Bubble::radius);
      bubble.setPosition(x, y);
      bubble.setFillColor(sf::Color::White);
      window.draw(bubble);
      pencil.write(std::string(1, letter), x + 0.2 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::Blue);
    }
};

class Board {
  private:
    sf::RenderWindow& window; 
    std::vector<Bubble> bubbles;
    int new_bubble_timeout { 30 };
    int new_bubble_timer { 0 };
    int hits { 0 };
    int misses { 0 };
  public:
    Board(sf::RenderWindow& window): window(window) {
      bubbles.push_back(Bubble(100, 100, 'A', 1));
      bubbles.push_back(Bubble(200, 100, 'B', 2));
      bubbles.push_back(Bubble(300, 100, 'C', 3));
    };

    void update() {
      for(auto& bubble : bubbles) {
        bubble.update();
      }
    }

    void draw() {
      for(auto& bubble : bubbles) {
        bubble.draw(window);
      }
    }
};

class Game {
  private:
    sf::RenderWindow window;
    Board board;
  public:
    Game(): window(sf::VideoMode(800, 600), "Bubbles"), board(window){
      window.setFramerateLimit(30);
    };

    void process_events() {
      sf::Event event;
      while (window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
          window.close(); 
      }
    };

    void draw(){
      board.update();
      // Background color
      window.clear(sf::Color::Black);

      board.draw();
      window.display();
    };

    void main_loop() {
      while (window.isOpen()) {
        process_events();
        draw();
      }
    }
};

int main(){
  Game game;
  game.main_loop();
  return 0;
}
