#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>


struct Entity {
    int x {0}, y {0}, step {0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture){
        this->x = x;
        this->y = y;
        this->step = step;
        this->sprite.setTexture(texture);
    }
    void draw(sf:: RenderWindow& window) {
        this->sprite.setPosition(x * step, y * step);
        setSize();
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Wolf and Rabbit");
    sf::Texture wolf_texture;
    
    bool wolfImgWasLoad = wolf_texture.loadFromFile("wolf.png");
    if(!wolfImgWasLoad){
        std::cout << "Error loading texture" << '\n';
        exit(1);
    }
    sf::Sprite wolf(wolf_texture);
    wolf.setPosition(100, 100);
    auto rect = wolf.getLocalBounds();
    wolf.setScale(100 / rect.width, 100 / rect.height);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // shape.setPosition(300, 150);
        window.clear();
        window.draw(wolf);
        window.display();
    }

    return 0;
}