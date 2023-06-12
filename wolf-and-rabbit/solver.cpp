#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <vector>

void setSize(sf::Sprite& sprite, int width, int height) {
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

int WIDTH = 700;
int HEIGHT = 500;

struct Entity {
    int x {0};
    int y {0};
    int step {0};
    sf::Sprite sprite;
    sf::Texture& rightTexture;
    sf::Texture& leftTexture;
    bool isFacingRight {true};

    Entity(int x, int y, int step, sf::Texture& rightTexture, sf::Texture& leftTexture):
        x {x}, y {y}, step {step}, sprite(rightTexture), rightTexture(rightTexture), leftTexture(leftTexture) {
    }

    void setTexture() {
        if (isFacingRight) {
            sprite.setTexture(rightTexture);
        } else {
            sprite.setTexture(leftTexture);
        }
    }

    void draw(sf::RenderWindow& window) {
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        setTexture();
        window.draw(this->sprite);
    }
};

struct Board {
    int nc {0};
    int nl {0};
    int step {0};
    sf::Sprite sprite;
    sf::RectangleShape rect;
    
    Board(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);
        
        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(2);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);
        for (int i = 0; i < nc; i++) {
            for (int j = 0; j < nl; j++) {
                rect.setPosition(i * step, j * step);
                window.draw(rect);
            }
        }
    }
};

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys, Entity& stone) {

    int nextX = entity.x;
    int nextY = entity.y;

    if (key == move_keys[0]) { 
        nextX--;
    }
    else if (key == move_keys[1]){ 
        nextY--;
    }
    else if (key == move_keys[2]){ 
        nextX++;
    }
    else if (key == move_keys[3]){ 
        nextY++;
    }

    if (nextX != stone.x || nextY != stone.y) {
        entity.x = nextX;
        entity.y = nextY;
    if (key == move_keys[0]) { 
        entity.isFacingRight = false;
    }
    else if (key == move_keys[2]){ 
        entity.isFacingRight = true;
    }
}
}

sf::Texture loadTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    return texture;
}

int main() {

    sf::Texture wolf_right_tex { loadTexture("wolf_right.png") };
    sf::Texture wolf_left_tex { loadTexture("wolf_left.png") };
    sf::Texture rabbit_right_tex { loadTexture("rabbit_right.png") };
    sf::Texture rabbit_left_tex { loadTexture("coelho.png") };
    sf::Texture rock_tex { loadTexture("rock.png") };
    sf::Texture grass_tex { loadTexture("grama.jpg") };

    const int STEP {100};

    Entity wolf(1, 1, STEP, wolf_right_tex, wolf_left_tex);
    Entity rabbit(3, 3, STEP, rabbit_right_tex, rabbit_left_tex);
    Entity rock(5, 3, STEP, rock_tex, rock_tex);
    Board board(7, 5, STEP, grass_tex);

    sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "Wolf & Rabbit");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                moveEntity(event.key.code, wolf, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down}, rock);
                moveEntity(event.key.code, rabbit, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S}, rock);
            }
        }

        window.clear();
        board.draw(window);
        rock.draw(window);
        wolf.draw(window);
        rabbit.draw(window);
        window.display(); 
    }

    return 0;
}
