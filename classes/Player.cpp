#include <iostream>
#include <string>


using namespace std;

#pragma once

class Player {
    private:
        string playerName;
        int score;

    public:
        Player(string playerName){
            this->playerName = playerName;
            this->score = 0;
        }

        string getName(){
            return this->playerName;
        }

        void setName(string name){
            this->playerName = name;
        }

        int getScore(){
            return this->score;
        }

        void increaseScore(){
            this->score += 10;
        }

        void setScore(int score){
            this->score = score;
        }


};