#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "background.h"
#include "colum.h"

#define SCREEN_WIDTH 400
#define SCREEN_HEIGH 600
#define MOC_MEP_PHAI_COT_MOT 50
#define MIN_WIDTH_COLUM 10
#define MAX_WIDTH_COLUM 100
#define MIN_DISTANDT_WITH_TWO_COLUM 2
#define HEIGH_COLUM 100
#define PHUONG_THANG_DUNG -180
#define BRIDGE_WIDTH 3
#define WIDTH_DEFAULT_COLUM 100

using namespace std;
using namespace sf;

void choseBgr(Background &background,RenderWindow* window,Texture &tBgr01,Texture &tBgr02) {

    const int nFramesBgr01 = 10, nFramesBgr02 = 24;
    const double speedFrameBgr = 3;
    const double speedMoveBgr = 0.01;


    int numberRand = rand()%2;
    background.create(window,numberRand==0?tBgr01:tBgr02,numberRand==0?nFramesBgr01:nFramesBgr02,speedFrameBgr,speedMoveBgr);
}
void createColum(Colum &colum1,Colum &colum2,Colum &colum3,RenderWindow* window,Texture &tColum) {
    colum1.create(window,tColum,SCREEN_WIDTH/2-WIDTH_DEFAULT_COLUM/2,SCREEN_HEIGH-HEIGH_COLUM,WIDTH_DEFAULT_COLUM);
    colum2.create(window,tColum,SCREEN_WIDTH/2-WIDTH_DEFAULT_COLUM/2,SCREEN_HEIGH-HEIGH_COLUM,WIDTH_DEFAULT_COLUM);
    colum3.create(window,tColum,SCREEN_WIDTH/2-WIDTH_DEFAULT_COLUM/2,SCREEN_HEIGH-HEIGH_COLUM,WIDTH_DEFAULT_COLUM);

}
int main() {
    //data
    srand(time(NULL));
    RenderWindow window;
    Background background;
    Colum colum1,colum2,colum3;
    // texture
    Texture tBgr01,tBgr02,tColum;

    //Create window 400x600
    window.create(VideoMode(SCREEN_WIDTH,SCREEN_HEIGH),"key is hoangpro",Style::Close);
    //load data
    tBgr01.loadFromFile("D:/huoang/SFML/pic/bgr0.png");
    tBgr02.loadFromFile("D:/huoang/SFML/pic/screen.png");
    tColum.loadFromFile("D:/huoang/SFML/pic/002.png");
    //don't say anythings
    choseBgr(background,&window,tBgr01,tBgr02);
    createColum(colum1,colum2,colum3,&window,tColum);
    //
    while(window.isOpen()) {
        Event E;
        while(window.pollEvent(E)) {
            if(E.type == Event::Closed) window.close();
        }
        //Update Status Game
        background.updateFrame();
        background.moveX();

        //Render Status Game
        window.clear();
        background.draw();
        colum1.draw();
        colum2.draw();
        colum3.draw();
        window.display();
    }
    return 0;
}
