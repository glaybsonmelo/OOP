#include <SFML/Graphics.hpp>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <functional>

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
    bool alive { true };
    static const int radius { 10 };
  public:
    Bubble(int x, int y, char letter, int speed): x(x), y(y), letter(letter), speed(speed) {};
    
    int get_x() {
      return x;
    }

    int get_y() {
      return y;
    }

    bool get_status(){
      return alive;
    }

    char get_letter(){
      return letter;
    }

    void set_status(bool status) {
        alive = status;
    }
    void update() {
      y += speed;
    }
    static const int get_radius() {
      return radius;
    }
    void draw(sf::RenderWindow& window) {
      static Pencil pencil(window);
      sf::CircleShape bubble (Bubble::radius);
      bubble.setPosition(x, y);
      bubble.setFillColor(sf::Color::White);
      window.draw(bubble);
      pencil.write(std::string(1, letter), x + 0.2 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::White);
    }
};

class Board {
  private:
    sf::RenderWindow& window; 
    std::vector<Bubble> bubbles;
    Pencil pencil;
    int hits { 0 };
    int misses { 0 };
  public:
    Board(sf::RenderWindow& window): window(window), pencil(window) {
      bubbles.push_back(Bubble(100, 100, 'A', 1));
      bubbles.push_back(Bubble(200, 100, 'B', 2));
      bubbles.push_back(Bubble(300, 100, 'C', 3));
    };

    void update() {
      if (check_new_bubble()){
        add_new_bubble();
      }
      for(auto& bubble : bubbles) {
        bubble.update();
      }
      mark_outside_bubbles();
      remove_dead_bubbles();
      
    }
    int get_misses(){
      return misses;
    }
    void remove_dead_bubbles() {
      std::vector<Bubble> aliveBubbles;
      for(Bubble& bubble : bubbles) {
        if (bubble.get_status()) {
          aliveBubbles.push_back(bubble);
        }
      }
      bubbles = aliveBubbles;
    }

    void mark_by_hit(char letter) {
      for (Bubble& bubble : bubbles) {
        if (bubble.get_letter() == letter) {
          bubble.set_status(false);
          hits++;
          break;
        }
      }
    }

    bool check_new_bubble() {
      static const int new_bubble_timeout { 30 };
      static int new_bubble_timer { 0 };
      new_bubble_timer --;
      if(new_bubble_timer <= 0) {
        new_bubble_timer = new_bubble_timeout;
        return true;
      }
      return false;
    }

    void add_new_bubble() {
      int x = rand() % ((int) this->window.getSize().x - 2 * Bubble::get_radius());
      int y = - 2 * Bubble::get_radius();
      int speed = rand() % 12 + 1;
      char letter = rand() % 26 + 'A';
      bubbles.push_back(Bubble(x, y, letter, speed));
    }

    void mark_outside_bubbles() {
      for(Bubble& bubble : bubbles) {
        if(bubble.get_y() + 2 * bubble.get_radius() > (int) window.getSize().y) {
          if(bubble.get_status()){
            bubble.set_status(false);
            misses++;
          }
        }
      }
    }

    void draw() {
      pencil.write("Hits: " + std::to_string(hits) + " Misses: " + std::to_string(misses), 10, 10, 20, sf::Color::White);
      pencil.write("Size: " + std::to_string(bubbles.size()), 10, 30, 20, sf::Color::White);
      for(auto& bubble : bubbles) {
        bubble.draw(window);
      }
    }
};

class Game {
  private:
    sf::RenderWindow window;
    Board board;
    sf::Sprite sprite;
    sf::Texture background_tex;
    Pencil pencil;
    std::function<void()> on_update;

  public:
    Game(): window(sf::VideoMode(800, 500), "Bubbles"), board(window), pencil(window), background_tex { loadTexture("sky-background.png") }{
      on_update = [&]() {
        gameplay();
      };
      window.setFramerateLimit(30);
    };

    void process_events() {
      sf::Event event;
      while (window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
          window.close(); 
        else if (event.type == sf::Event::TextEntered) {
          char code = static_cast<char>(event.text.unicode);
          code = std::toupper(code);
          board.mark_by_hit(code);
        }
      }
    };

    void gameplay(){
      board.update();
      window.draw(sprite);
      board.draw();
      window.display();
    };

    sf::Texture loadTexture(std::string path) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cout << "Error loading texture" << std::endl;
            exit(1);
        }
        return texture;
    }
    
    void setTexture() {
      sprite.setTexture(background_tex);
    }

    void gameover(){
      window.clear(sf::Color::Red);
      pencil.write("Game Over", 250, 200, 50, sf::Color::White);
      board.draw();
      window.display();
    };

    void main_loop() {
      setTexture();
      while (window.isOpen()) {
        if(board.get_misses() >= 4){
          on_update = [&]() {
          gameover();
          };
        }
        process_events();
        on_update();
      }
    }
};

int main(){
  Game game;
  game.main_loop();
  return 0;
}
