#include <iostream>
#include <string>
#include <vector>
#include "Player.cpp"
#include <sstream>
#include <fstream>

using namespace std;

#pragma once

class Repository {
    private:
        vector<Player> Players;
        fstream fs; 

    public:
        
        Repository(){
             this->fs.open("repository.txt", fstream::in); // open file to read
                
                string line;
                vector<string> lines;

                while(getline(fs, line)){
                    lines.push_back(line);
                }

                int lineSize = lines.size();

                for(int lineIndex = 0; lineIndex < lineSize; lineIndex++){
                    
                    if(lines[lineIndex] == "player"){
                        Player newPlayer = Player(lines[lineIndex + 1]);
                        newPlayer.setScore(stoi(lines[lineIndex + 2]));

                        Players.push_back(newPlayer);
                    }
                }
 
             this->fs.close();
        }

        void saveRepository(){ //methos responsible to rewrite the repository (txt) basesed in the Players vector

            this->fs.open("repository.txt", fstream::out); //open file to write

            for(Player player : Players){
                this->fs << "player" << endl << player.getName() << endl << player.getScore() << endl;
            }
        
            this->fs.close();
        }

        void addPlayer(Player player){ //to add and save a new Player in the repository
        
            Players.push_back(player);
            this->saveRepository();
 
        };

        vector<Player> getAllPlayers(){
            this->orderPlayers();
            return this->Players;
        }

        bool verifyNewPlayer(string playerName){
            bool valid = true;
            for(Player player : Players){
                if(player.getName() == playerName)
                    valid = false;
            }

            return valid;
        }

        int getPlayerScore(string playerName){
            int score;
            for(Player player : Players){
                if(player.getName() == playerName)
                    score = player.getScore();
            }

            return score;
        }

        void orderPlayers(){
            
            int aux = 0;
            string auxstr = "";

            int playersSize = Players.size();
            
            for(int i = 0; i < playersSize; i++){
                for(int j = 0; j < playersSize; j++){
                    
                    if(Players[i].getScore() < Players[j].getScore()){
                        
                        aux = Players[i].getScore();
                        auxstr = Players[i].getName();

                        Players[i].setScore(Players[j].getScore());
                        Players[i].setName(Players[j].getName());

                        Players[j].setScore(aux);
                        Players[j].setName(auxstr);
                        
                    }
                }
            }

            reverse(Players.begin(), Players.end());

        }

        void ReplacePlayer(Player replacedPLayer){

            int PersonIndex = 0;

            for( Player player : this->Players)
                if(player.getName() == replacedPLayer.getName())
                    break;
                else PersonIndex++;
            
            this->Players.erase(this->Players.begin() + PersonIndex);
            this->addPlayer(replacedPLayer);

            this->saveRepository();

        }
};