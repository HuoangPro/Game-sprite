#include <SFML/Graphics.hpp>

class Background {
private :
    sf::RenderWindow* _window;
    double _speedFrame ;
    double _speedMoveBgr ;
    sf::Sprite _sprite;
    sf::Texture _texture;
    double _x = 0; // x of frame
    double _y = 0; // y of frame
    double _weigh; // weigh per frame
    double _heigh; // heigh per frame
public :
    //Background();
    Background(sf::RenderWindow* window,std::string filename,int nFrames,double speedFrame,double speedMoveBgr) {
        _window = window;
        _speedFrame = speedFrame;
        _speedMoveBgr = speedMoveBgr;
        _texture.loadFromFile(filename);
        _heigh = _texture.getSize().y/nFrames;
        _weigh = _texture.getSize().x;
        _sprite.setTexture(_texture);
    }
    void setX(double x) {
        _x = x;
        _y = 0;
        _sprite.setTextureRect(sf::IntRect(_x,_y,_weigh,_heigh));
    }
    void moveX() {
        _x += _speedMoveBgr;
        int a = _texture.getSize().x;
        int b = _window->getSize().x;
        if(_x >= a-b) _x = 0;
        _sprite.setTextureRect(sf::IntRect(_x,int(_y/_heigh)*_heigh,_weigh,_heigh));
    }
    void updateFrame() {
        _y += _speedFrame;
        if(_y >= _texture.getSize().y) _y= 0;
        _sprite.setTextureRect(sf::IntRect(_x,int(_y/_heigh)*_heigh,_weigh,_heigh));
    }
    void draw() {
        _window->draw(_sprite);
    }
};
