#include <SFML/Graphics.hpp>

class Bridge{
private:
    sf::RenderWindow* window;
    sf::Sprite sprite;
    sf::Texture texture;
    double alpha;
    double hBridge;
    double wBridge;
public:
    Bridge(sf::RenderWindow* _window,std::string filename,double x,double y,double _wBridge,double _hBridge,double _alpha) {
        window = _window;
        wBridge = _wBridge;
        hBridge = _hBridge;
        alpha = _alpha;
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        //std::cout<< "texture.getSize().y-hBridge "<<texture.getSize().y-hBridge<<"\n";
        sprite.setTextureRect(sf::IntRect(0,0,wBridge,hBridge));
        sprite.setOrigin(0,hBridge);
        sprite.setPosition(x,y);
        sprite.setRotation(_alpha);
        //sprite.setColor(Color::Black);
    }
    void swapBridge(Bridge &B) {
        double hB = B.hBridge;
        double alB = B.alpha;
        double xB = B.getX();

        B.setAlpha(alpha);
        B.setH(hBridge);
        B.updateX(sprite.getPosition().x);

        alpha = alB;
        hBridge = hB;
        sprite.setPosition(xB,sprite.getPosition().y);
        sprite.setTextureRect(sf::IntRect(0,0,wBridge,hBridge));
        sprite.setOrigin(0,hBridge);
        sprite.setRotation(alpha);
    }

    double getX() {
        return sprite.getPosition().x;
    }
    double getH() {

        //cout<<"hBridge "<<hBridge<<"\n";
        return hBridge;
    }
    void updateX(double X) {
        sprite.setPosition(X,sprite.getPosition().y);
    }
    void updateH(double deltaH) {
        hBridge += deltaH;
        sprite.setTextureRect(sf::IntRect(0,0,wBridge,hBridge));
        sprite.setOrigin(0,hBridge);
    }
    void updateXY(double deltaX, double deltaY) {
        sprite.move(deltaX,deltaY);
    }
    void updateAlpha(double deltaAlpha) {
        alpha += deltaAlpha;
        sprite.setRotation(alpha);
    }
    void setH(double H) {
        hBridge = H;
        sprite.setTextureRect(sf::IntRect(0,0,wBridge,hBridge));
        sprite.setOrigin(0,hBridge);
    }
    void setAlpha(double A) {
        alpha = A;
        sprite.setRotation(alpha);
    }
    void draw() {
        window->draw(sprite);
    }
};
