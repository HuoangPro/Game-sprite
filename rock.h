#include <SFML/Graphics.hpp>

class Rock{
private:
    sf::RenderWindow* window;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Rock(sf::RenderWindow* _window,std::string filename,double x,double y) {
        window = _window;
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        sprite.setPosition(x,y);
        sprite.setScale(0.1,0.1);
        sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
    }
    double getSizeY() {
        return texture.getSize().y;
    }
    double getY() {
        return sprite.getPosition().y;
    }
    void setXY(double x,double y) {
        sprite.setPosition(x,y);
    }
    void updateXY(double x,double y) {
        sprite.move(x,y);
    }
    void updateScale(double scale) {
        sprite.setScale(scale,scale);
    }
    void updateRotation(double deltaRotation) {
        sprite.setRotation(sprite.getRotation()+deltaRotation);
    }
    void draw() {
        window->draw(sprite);
    }
};
