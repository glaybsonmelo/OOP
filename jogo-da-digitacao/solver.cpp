#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <string>

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

class Game {
  private:
    sf::RenderWindow window;
  public:
    Game(): window(sf::VideoMode(800, 600), "Bubbles"){
      window.setFramerateLimit(60);
    };

    void process_events() {
      sf::Event event;
      while (window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
          window.close(); 
      }
    };

    void draw(){
      // Background color
      window.clear(sf::Color::Black);

      static Bubble bubble(200, 100, 'B', 2);
      bubble.update();
      bubble.draw(window);
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
