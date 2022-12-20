#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
#include "Player.cpp"
#include <Mmsystem.h>

using namespace std;
using namespace cv;


#pragma once

class GameController {
    private:

        Point fruitPosition;

        int height;
        int width;

        Player *player;

        float time;


    public:
        bool gameOver = false;
        

        GameController(int height, int width, string playerName){
            gameOver = false; //start the gameOver with false value

            this->height = height;
            this->width = width;

            this->createNewFruit();

            this->time = 60;

            player = new Player(playerName);

        };

        void createNewFruit(){
            this->fruitPosition.x = rand() %this->width;
            this->fruitPosition.y = rand() %this->height;

            if(this->fruitPosition.x < 50)
                this->fruitPosition.x += 50;
            if(this->fruitPosition.x > (this->width - 50) )
                this->fruitPosition.x -= 50;

            if(this->fruitPosition.y < 50)
                this->fruitPosition.y += 50;
            if(this->fruitPosition.y > (this->height - 50))
                this->fruitPosition.y -= 50;
        }

        Point getFruitPosition(){
            return fruitPosition;
        }

        int getTime(){
            return this->time;
        }

        Player getPlayer(){
            return *this->player;
        }

        void loop(Point playerPosition){

            // um quadrado que começa em [ 0, 0 ] e termina em [ 10, 10 ], 
            //como saber se um ponto esta dentro dele

            // ponto [ 5, 5 ]

            if( playerPosition.x >= (fruitPosition.x - 10) && playerPosition.x <= (fruitPosition.x + 10))
                if( playerPosition.y >= (fruitPosition.y - 10) && playerPosition.y <= (fruitPosition.y + 10)){
                    //comeu a fruta
                    player->increaseScore();
                    this->createNewFruit();
                    fstream audio;
                    bool played = PlaySound(TEXT("sound.wav"),  NULL, SND_ASYNC);
                    cout << "COMEU?" << played; 
                }

            this->time = time -0.1;

            if(this->time <= 0){
                this->gameOver = true;
            }
        }

};