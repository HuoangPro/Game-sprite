#include <SFML/Graphics.hpp>

class NutPlay{
private:
    sf::RenderWindow* window;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    double huong = 1;
    NutPlay(sf::RenderWindow* _window,std::string filename,double x,double y) {
        window = _window;
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0,0,texture.getSize().x,texture.getSize().y/3));
        sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/3/2);
        sprite.setPosition(x,y);
        sprite.setScale(0.5,0.5);
    }
    void updatePlay(int loai) {
        if(loai == 0) {
            //play
            sprite.setTextureRect(sf::IntRect(0,0,texture.getSize().x,texture.getSize().y/3));
        } else if(loai == 1) {
            //replay
            sprite.setTextureRect(sf::IntRect(0,texture.getSize().y/3,texture.getSize().x,texture.getSize().y/3));
        } else if(loai == 2) {
            //empty
            sprite.setTextureRect(sf::IntRect(0,texture.getSize().y*2/3,texture.getSize().x,texture.getSize().y/3));
        }
    }
    double getX() {
        return sprite.getPosition().x;
    }
    double getY() {
        return sprite.getPosition().y;
    }
    double getW() {
        return texture.getSize().x;
    }
    double getH() {
        return texture.getSize().y/3;
    }
    void updateY(double deltaY) {
        sprite.move(0,deltaY);
    }
    void draw() {
        window->draw(sprite);
    }
    void setXY(double x, double y) {
        sprite.setPosition(x,y);
    }
};
