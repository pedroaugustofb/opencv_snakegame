#include <iostream>
#include <string>
#include <vector>
#include "Player.cpp"
using namespace std;

#pragma once

class Menu {
    public:

        void print(){
            system("CLS");
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            cout << "|                                      JOGO DA COBRINHA                                            |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|                                   [0] - Fechar sistema.                                          |" << endl;
            cout << "|                                   [1] - Iniciar novo jogo.                                       |" << endl;
            cout << "|                                   [2] - Consultar ranking.                                       |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
        }

        void endGame(Player player){
            system("CLS");
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            cout << "|                                        FIM DE JOGO                                               |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|                                   Jogador: " << player.getName() << endl;
            cout << "|                                   Pontuação: "<< player.getScore() << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            system("pause");
        }

        void printRanking(vector<Player> Players){

            system("CLS");
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            cout << "|                                        FIM DE JOGO                                               |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            for(Player player : Players){
            cout << "              Jogador: " << player.getName() << "      | Pontuacao: "<< player.getScore() << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            }
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            system("pause");
        }


        void invalidName(){
            system("CLS");
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|                                  Nome de jogador ja existente.                                   |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            system("pause");
        }
        
        void startingGame(){
            system("CLS");

            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            cout << "|                                                                                                  |" << endl;                                                                                                                                                                              
            cout << "|                                  Seu jogo vai comecar em 3 segundos...                           |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            Sleep(1000);
            system("CLS");

            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            cout << "|                                                                                                  |" << endl;                                                                                                                                                                              
            cout << "|                                  Seu jogo vai comecar em 2 segundos...                           |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;            
            Sleep(1000);
            system("CLS");

                        cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            cout << "|                                                                                                  |" << endl;                                                                                                                                                                              
            cout << "|                                  Seu jogo vai comecar em 1 segundos...                           |" << endl;
            cout << "|                                                                                                  |" << endl;
            cout << "|--------------------------------------------------------------------------------------------------|" << endl;
            Sleep(1000);
            system("CLS");
        }

};