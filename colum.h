#include <SFML/Graphics.hpp>

class Colum{
private:
    sf::RenderWindow* window;
    sf::Texture texture;
    sf::Sprite sprite;
    double wColum;
    double hColum;
public:
    Colum(sf::RenderWindow* _window,std::string filename,double x_Colum,double y_Colum,double w_Colum,double h_Colum) {
        window = _window;
        wColum = w_Colum;
        hColum = h_Colum;
        texture.loadFromFile(filename);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setPosition(x_Colum,y_Colum);
        sprite.setTextureRect(sf::IntRect(0,0,w_Colum,h_Colum));
        //sprite.setColor(Color::White);
    }
    double getZ() {
        return wColum;
    }
    double getX() {
        return sprite.getPosition().x;
    }
    void updateXY(double speedX,double speedY) {
        sprite.move(speedX,speedY);
    }
    void updateZ(double newZ) {
        wColum = newZ;
        sprite.setTextureRect(sf::IntRect(0,0,wColum,hColum));
    }
    void updateX(double newX) {
        sprite.setPosition(newX,sprite.getPosition().y);
    }
    void swapColum(Colum &B) {
        double xA = sprite.getPosition().x , xB = B.sprite.getPosition().x;
        double yA = sprite.getPosition().y , yB = B.sprite.getPosition().y;
        double wA = wColum , wB = B.wColum;
        B.wColum = wA , wColum = wB;
        sprite.setPosition(xB,yB);
        B.sprite.setPosition(xA,yA);
        sprite.setTextureRect(sf::IntRect(0,0,wColum,hColum));
        B.sprite.setTextureRect(sf::IntRect(0,0,B.wColum,B.hColum));
    }
    void draw() {
        //window->clear();
        window->draw(sprite);
    }
};
