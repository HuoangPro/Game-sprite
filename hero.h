#include <SFML/Graphics.hpp>

class Hero{
private :
    sf::RenderWindow* window;
    std::vector<sf::IntRect> frame;
    double frameRecent = 0;
    sf::Texture texture;
    sf::Sprite sprite;
public :
    // Image must convert chuan of Hoangdz
    Hero(sf::RenderWindow* _window,std::string filename,double x_hero,double y_hero,int soCot,int soHang,int cotStart,int hangStart,int _soLuongFrames) {
        window = _window;
        texture.loadFromFile(filename);
        texture.setSmooth(true);
        double w_oneFrame = texture.getSize().x/soCot;
        double h_oneFrame = texture.getSize().y/soHang;
        //std::cout<<w_oneFrame<<" "<<h_oneFrame<<"\n";
        //int _soLuongFrames= soCot*soHang;
        for(int i=0; i<_soLuongFrames; i++) {
            frame.push_back(sf::IntRect((cotStart-1)*w_oneFrame,(hangStart-1)*h_oneFrame,w_oneFrame,h_oneFrame));
            cotStart++;
            if(cotStart>soCot) {
                cotStart = 1;
                hangStart++;
                if(hangStart>soHang) hangStart = 1;
            }
        }
        sprite.setTexture(texture);
        sprite.setScale(0.5,0.5);
        sprite.setPosition(x_hero,y_hero);
        sprite.setTextureRect(frame[0]);
    }
    void updateX(double x) {
        sprite.setPosition(x,sprite.getPosition().y);
    }
     void updateY(double y) {
        sprite.setPosition(sprite.getPosition().x,y);
    }
    double getX() {
        return sprite.getPosition().x;
    }
    double getY() {
        return sprite.getPosition().y;
    }
    void updateXY(double speedHeroRunX,double speedHeroRunY) {
        sprite.move(speedHeroRunX,speedHeroRunY);
        //if(sprite.getPosition().x>window->getSize().x) sprite.setPosition(-20,sprite.getPosition().y);
    }
    void updateFrame(double speedLoadImage) {
        frameRecent += speedLoadImage;
        if(frameRecent>frame.size()) frameRecent = 0;
        sprite.setTextureRect(frame[(int)frameRecent]);
    }
    void draw() {
        //window->clear();
        window->draw(sprite);
    }
};
