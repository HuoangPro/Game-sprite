#include <SFML/Graphics.hpp>
#include <algorithm>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include "background.h"
#include "hero.h"
#include "colum.h"
#include "bridge.h"
#include "rock.h"
#include "nutplay.h"
#include "smoke.h"
/*
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 600
#define MOC_MEP_PHAI_COT_MOT 50
#define MIN_WIDTH_COLUM 40
#define MAX_WIDTH_COLUM 100
#define MIN_DISTANDT_WITH_TWO_COLUM 5
#define HEIGHT_COLUM 100
#define PHUONG_THANG_DUNG 0
#define BRIDGE_WIDTH 3
*/
using namespace std;
using namespace sf;

double speedAhii = SPEED_INIT;
Clock dongho;
Time thoigian_Max_Wait = seconds(2);
RenderWindow window(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"hoangdz",Style::Close);
//Background background(&window,"pic/bg32.jpg",0,250,400,600);
RectangleShape ochuadiem;
Background background(&window,"pic/bgr0.png",10,8,0.01);
//Background background(&window,"pic/screen.png",24,3,0.01);
//Background background(&window,"pic/5146.png",1,3,0.01);
Smoke smoke(&window,"pic/smoke.png",11,1.5);
Hero hero(&window,"pic/giun001.png",186,445,6,1,1,1,6);
NutPlay nutPlay(&window,"pic/play01.png",SCREEN_WIDTH/2,SCREEN_HEIGHT*2/5);
Colum colum1(&window,"pic/002.png",SCREEN_WIDTH/2-100/2,SCREEN_HEIGHT-HEIGHT_COLUM,100,HEIGHT_COLUM);
Colum colum2(&window,"pic/002.png",SCREEN_WIDTH/2-100/2,SCREEN_HEIGHT-HEIGHT_COLUM,100,HEIGHT_COLUM);
Colum colum3(&window,"pic/002.png",SCREEN_WIDTH,SCREEN_HEIGHT-HEIGHT_COLUM,50,HEIGHT_COLUM);
Bridge bridge(&window,"pic/bridge.jpg",MOC_MEP_PHAI_COT_MOT-1,SCREEN_HEIGHT-HEIGHT_COLUM,BRIDGE_WIDTH,0,PHUONG_THANG_DUNG);
Bridge bridge1(&window,"pic/bridge.jpg",MOC_MEP_PHAI_COT_MOT-1,SCREEN_HEIGHT-HEIGHT_COLUM,BRIDGE_WIDTH,0,PHUONG_THANG_DUNG);
Rock rock(&window,"pic/rock.png",40,-100);
int diemInt = 0;
//int diemCaoNhat = 0;
Text diemText;

string diemString;
void itoa(int i,string &s, int cs) {
    s = "";
    while(i) {
        s +=i%cs+48;
        i/=cs;
    }
    reverse(s.begin(),s.begin()+s.size());
}

void rendergame() {
    window.clear();
    background.draw();
    colum1.draw();
    colum2.draw();
    bridge.draw();
    bridge1.draw();
    smoke.updateFrame();
    smoke.draw();
    hero.draw();
    rock.draw();
    nutPlay.draw();
    window.draw(ochuadiem);
    window.draw(diemText);
    window.display();
}
void checkGame(bool &endGame,int &loai) {
    double H = bridge.getH();
    if(bridge.getX()+H<colum2.getX()) {
        cout<<"end Game\n";
        loai =1;
        endGame = true;
    } else if(bridge.getX()+H>colum2.getX()+colum2.getZ()) {
        cout<<"end Game\n";
        loai = 2;
        endGame = true;
    }
}
void rotRock() {
    while(rock.getY()<SCREEN_HEIGHT + rock.getSizeY()/2) {
        (rock.getY()>hero.getY())?hero.updateXY(0,1):hero.updateXY(0,0);
        rock.updateXY(0,2);
        rock.updateRotation(3);
        background.updateFrame();
        rendergame();
    }
}
void updateGame(bool &endGame) {
    bool isPress = false;
    while(Mouse::isButtonPressed(Mouse::Left)) {
        //cout<<"Press\n";
        isPress = true;
        bridge.updateH(speedAhii);
        background.updateFrame();
        rendergame();
    }
    /*
    //Pause
            bool IsPressH = false;
            while(Keyboard::isKeyPressed(Keyboard::H)) {
                IsPressH = true;
            }
            if(!IsPressH) return;
    //End pause
    */
    if(isPress) {

        int loai = 0;
        checkGame(endGame,loai);
        if(loai==0) smoke.setX(MOC_MEP_PHAI_COT_MOT+bridge.getH());
        int const deltaAlpha = 90;
        for(int i=0; i<deltaAlpha; i++) {
            bridge.updateAlpha(1);
            background.updateFrame();
            if(loai==0) {
                if(i==75) smoke.setFrame(1);
                smoke.updateFrame();
            }
            rendergame();
        }
        if(loai == 1) { // bridge khong toi noi

            for(int i=0; i<deltaAlpha; i++) {
                bridge.updateAlpha(1);
                background.updateFrame();
                rendergame();
            }
            rotRock();
        }
        else if(loai == 0) {//run hero

            // 40 is chieu rong real hero
            diemInt++;
            if(diemInt%10 == 9) speedAhii += 0.2;
            itoa(diemInt,diemString,10);
            cout<<diemString<<"\n";
            diemText.setString(diemString);
            // 50 la do dai 1 chu so
            diemText.setOrigin(diemString.size()*50/2,50);
            while(hero.getX()+40<colum2.getX()+colum2.getZ()) {
                background.moveX();
                background.updateFrame();
                hero.updateFrame(0.025);
                hero.updateXY(0.2,0);
                rendergame();
            }
        }
        else {// loai = 2 :: chet -> roi xuong

            while(hero.getX()<bridge.getH()+bridge.getX()) {
                background.moveX();
                background.updateFrame();
                hero.updateFrame(0.025);
                hero.updateXY(0.2,0);
                rendergame();
            }
            while(hero.getY()<SCREEN_HEIGHT) {
                hero.updateXY(0,0.5);
                background.updateFrame();
                rendergame();
            }
        }




        //next move
        if(!endGame) {

                double z3 = rand()%MAX_WIDTH_COLUM+MIN_WIDTH_COLUM;
                double x3 = rand()%(SCREEN_WIDTH-MIN_DISTANDT_WITH_TWO_COLUM-MOC_MEP_PHAI_COT_MOT-(int)z3)+MOC_MEP_PHAI_COT_MOT+MIN_DISTANDT_WITH_TWO_COLUM;
                colum3.updateZ(z3);

                const double step  = 200;
                double v = (colum2.getX()+colum2.getZ()-MOC_MEP_PHAI_COT_MOT)/step;
                double v3 = (colum3.getX()-x3)/step;
                for(int i=0; i<step; i++) {
                    bridge.updateXY(-v,0);
                    colum1.updateXY(-v,0);
                    colum2.updateXY(-v,0);
                    colum3.updateXY(-v3,0);
                    hero.updateXY(-v,0);
                    background.updateFrame();
                    rendergame();
                }
                colum1.swapColum(colum2);
                colum2.swapColum(colum3);
                colum3.updateX(SCREEN_HEIGHT);

                bridge1.swapBridge(bridge);
                bridge.setAlpha(PHUONG_THANG_DUNG);
                bridge.setH(0);
                bridge.updateX(MOC_MEP_PHAI_COT_MOT);
                background.updateFrame();

                rendergame();
                dongho.restart();
        } else {
            //replay
            nutPlay.updatePlay(1);
        }

    }

    else {
        // mai khong press
        //cout<<dongho.getElapsedTime().asSeconds()<<endl;
        if(dongho.getElapsedTime()>=thoigian_Max_Wait) {
            endGame = true;
            rotRock();
            //replay
            nutPlay.updatePlay(1);
        }
    }

}
bool isStart() {
    bool start = false;
    //bool an = false;
    while(Mouse::isButtonPressed(Mouse::Left)) {
        //an = true;
        //cout<<Mouse::getPosition().x<<" "<<Mouse::getPosition().y<<"\n";
        if(nutPlay.getX()-nutPlay.getW()/2 <= Mouse::getPosition(window).x && Mouse::getPosition(window).x <= nutPlay.getX()+nutPlay.getW()/2
           && nutPlay.getY()-nutPlay.getH()/2 <= Mouse::getPosition(window).y && Mouse::getPosition(window).y <= nutPlay.getY()+nutPlay.getH()/2) {

            start = true;
        }
    }
    /*
    an is press
    if(an) {
        cout<<"-   -    -    -\n";
        cout<<nutPlay.getX()-nutPlay.getW()/2<<" "<<nutPlay.getX()+nutPlay.getW()/2<<"\n";
        cout<<nutPlay.getY()-nutPlay.getH()/2<<" "<<nutPlay.getY()+nutPlay.getH()/2<<"\n";
        cout<<"______________________________\n";
    }
    */
    // empty
    if(start) {
        nutPlay.updatePlay(2);
        itoa(diemInt,diemString,10);
        diemString = "0";
        diemText.setString(diemString);
        diemText.setOrigin(diemString.size()*50/2,50);
        ochuadiem.setSize(Vector2f(200,100));
        ochuadiem.setOrigin(100,50);
        ochuadiem.setPosition(SCREEN_WIDTH/2,65);
        ochuadiem.setFillColor(Color(224, 224, 210,100));
    }
    return start;
}
void resetAll() {
    speedAhii = SPEED_INIT;
    diemInt = 0;
    background.setX(0);
    // 7 is moc_mep_phai - chieu rong con sau
    hero.updateX(7);
    // 444 is screen_height - width_colum - chieu cao con sau
    hero.updateY(445);
    rock.setXY(MOC_MEP_PHAI_COT_MOT-10,0-100); // -100 de rock hoan toan bi an
    bridge.setAlpha(PHUONG_THANG_DUNG);
    bridge.setH(0);
    bridge.updateX(MOC_MEP_PHAI_COT_MOT);
    bridge1.setAlpha(PHUONG_THANG_DUNG);
    bridge1.setH(0);
    bridge1.updateX(MOC_MEP_PHAI_COT_MOT);

    double z1 = rand()%MAX_WIDTH_COLUM+MIN_WIDTH_COLUM;
    double x1 = MOC_MEP_PHAI_COT_MOT - z1;
    colum1.updateX(x1);
    colum1.updateZ(z1);
    double z2 = rand()%MAX_WIDTH_COLUM+MIN_WIDTH_COLUM;
    double x2 = rand()%(SCREEN_WIDTH-MIN_DISTANDT_WITH_TWO_COLUM-MOC_MEP_PHAI_COT_MOT-(int)z2)+MOC_MEP_PHAI_COT_MOT+MIN_DISTANDT_WITH_TWO_COLUM;

    colum2.updateX(x2);
    colum2.updateZ(z2);
    double z3 = rand()%MAX_WIDTH_COLUM+MIN_WIDTH_COLUM;
    double x3 = SCREEN_WIDTH;
    colum3.updateX(x3);
    colum3.updateZ(z3);
    rendergame();
}
int main() {
    srand(time(NULL));
    ////


    ////
    Font font;
    font.loadFromFile("tahoma.ttf");
    diemText.setFont(font);
    diemText.setCharacterSize(100);
    diemText.setOrigin(diemString.size()/2,50);
    diemText.setPosition(SCREEN_WIDTH/2,50);
    diemText.setFillColor(Color::Black);
    smoke.setFrame(11);
    while(window.isOpen()) {
        Event E;
        while(window.pollEvent(E)) {
            if(E.type==Event::Closed) window.close();
        }

        if(isStart()) {
            dongho.restart();
            resetAll();
            cout<<"Start Play\n";
            bool endGame = false;
            while(!endGame) {
                while(window.pollEvent(E)) {
                    if(E.type==Event::Closed) window.close();
                }
                updateGame(endGame);

                //background.updateXY(-0.01,0);
                //hero.updateFrame();
                background.updateFrame();
                rendergame();
            }
        }

        //background.updateXY(-0.01,0);
        // nutplay di chuyen len xuong
        if(nutPlay.getY()>=SCREEN_HEIGHT*2/5+5||nutPlay.getY()<=SCREEN_HEIGHT*2/5-5) nutPlay.huong *= -1;
        nutPlay.updateY(nutPlay.huong*0.005);

        background.updateFrame();
        rendergame();
    }

}



