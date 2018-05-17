#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 600
#define MOC_MEP_PHAI_COT_MOT 50
#define MIN_WIDTH_COLUM 40
#define MAX_WIDTH_COLUM 100
#define MIN_DISTANDT_WITH_TWO_COLUM 5
#define HEIGHT_COLUM 100
#define PHUONG_THANG_DUNG 0
#define BRIDGE_WIDTH 3
#define SPEED_INIT 0.2

class Smoke {
private :
    sf::RenderWindow* _window;
    double _speedFrame ;
    sf::Sprite _sprite;
    sf::Texture _texture;
    double _x; //
    double _y; //
    double _weigh; // weigh per frame
    double _heigh; // heigh per frame
public :
    //Background();
    Smoke(sf::RenderWindow* window,std::string filename,int nFrames,double speedFrame) {
        _window = window;
        _speedFrame = speedFrame;
        _texture.loadFromFile(filename);
        _heigh = _texture.getSize().y;
        _weigh = _texture.getSize().x/nFrames;
        //std::cout<<"_heigh "<<_heigh<<"\n";
        //std::cout<<"_weigh "<<_weigh<<"\n";
        _sprite.setTexture(_texture);
        _sprite.setOrigin(_weigh/2,_heigh);
        _sprite.scale(0.5,0.5);
        _x = 0;
        _y = 0;
    }
    void setX(double x) {
        _sprite.setPosition(x,SCREEN_HEIGHT-HEIGHT_COLUM);
    }
    void setFrame(int iFrame) {
        _x = (iFrame-1)*_weigh;
        _sprite.setTextureRect(sf::IntRect(int(_x/_weigh)*_weigh,_y,_weigh,_heigh));
    }
    void updateFrame() {
        _x += _speedFrame;
        if(_x >= _texture.getSize().x)  setFrame(11);//11?
        _sprite.setTextureRect(sf::IntRect(int(_x/_weigh)*_weigh,_y,_weigh,_heigh));
    }
    void draw() {
        _window->draw(_sprite);
    }
};
