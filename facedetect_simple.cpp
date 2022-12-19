#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include <string>
#include <typeinfo>
#include <Windows.h>
#include <iostream>

#include "classes/GameController.cpp"
#include "classes/Menu.cpp"
#include "classes/Repository.cpp"

using namespace std;
using namespace cv;

void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip);

string cascadeName;
const float Max_x = 639;
const float Max_y = 479;

void newGame(VideoCapture capture, Mat frame, CascadeClassifier cascade, double scale, bool tryflip, Menu menu, GameController game){

        menu.startingGame();

        if(!game.gameOver)
            for(;;)
            {
                capture >> frame;
                if( frame.empty() ){
                    break;
                }

                    system("CLS");
                    double t = 0;
                    vector<Rect> faces;
                    Mat gray, smallImg;
                    Scalar color = Scalar(255,0,0);

                    if( tryflip ) {
                        flip(frame, frame, 1);
                    }

                    cvtColor( frame, gray, COLOR_BGR2GRAY );
                    double fx = 1 / scale;
                    resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
                    equalizeHist( smallImg, smallImg );

                    t = (double)getTickCount();

                    cascade.detectMultiScale( smallImg, faces,
                        1.3, 2, 0
                        //|CASCADE_FIND_BIGGEST_OBJECT
                        //|CASCADE_DO_ROUGH_SEARCH
                        |CASCADE_SCALE_IMAGE,
                        Size(40, 40) );
                    t = (double)getTickCount() - t;
                    // PERCORRE AS FACES ENCONTRADAS
                    for ( size_t i = 0; i < faces.size(); i++ )
                    {
                        Rect r = faces[i];
                        rectangle( frame, Point(cvRound(r.x*scale), cvRound(r.y*scale)),
                                    Point(cvRound((r.x + r.width-1)*scale), cvRound((r.y + r.height-1)*scale)),
                                    color, 3);
                    }
                    

                    Point Fruit = game.getFruitPosition();

                    Mat image = imread("F:\\UFPB\\LP1\\SnakeGame_\\faceDetect\\orange.png");
                    resize(image, image, Size(21,21));

                    Mat roi = frame(Rect( (Fruit.x - 10), (Fruit.y - 10), image.cols, image.rows));
                    addWeighted(roi, 0, image, 1, 0, roi);

                    String infos = "Score: " + to_string(game.getPlayer().getScore()) + "           Tempo Restante: " + to_string(game.getTime()); 

                    imshow( "result", frame );
                    
                    if(faces.size() > 0 && !game.gameOver){
                        Rect r = faces[0];
                        Point playerPosition = Point( 
                            ( (cvRound(r.x*scale) + cvRound((r.x + r.width-1)*scale)) / 2), 
                            ( (cvRound(r.y*scale) + cvRound((r.y + r.height-1)*scale)) / 2)
                            );


                        game.loop(playerPosition);
                        imshow( "result", frame );
                        displayOverlay("result", infos); 
                    }

                    else if(game.gameOver) {
                        menu.endGame(game.getPlayer());
                        
                        break;
                    }

                char c = (char)waitKey(10);
                if( c == 27 || c == 'q' || c == 'Q' )
                    break;
            }
        


        
}

int main()
{   
    //opencv vars
    VideoCapture capture;
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;

    cascadeName = "haarcascade_frontalface_default.xml";
    cascadeName = "haarcascade_frontalface_alt2.xml";
    scale = 1;
    if (scale < 1)
        scale = 1;
    tryflip = true;

    if (!cascade.load(cascadeName)) {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return -1;
    }

//    if(!capture.open("video.mp4")) // para testar com um video
    if(!capture.open(0))
    {
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    if( capture.isOpened() )
    {
        /* menu inicial*/
        Menu menu;
        Repository repository;
        string playerName;
        bool closeSystem = false;

        for(;;){
            if(!closeSystem){
                menu.print();

                int code = (cin >> (cout << "|----------------> Digite o codigo correspondente a operacao que deseja: ",code), code);

                if(code == 0) 
                    closeSystem = true;

                else if(code == 1){
                    getchar();
                    cout << "|----------------> Digite o nome do Jogador:";
                    getline(cin, playerName);


                    GameController game = GameController(Max_y, Max_x, playerName);
                    newGame(capture, frame, cascade, scale, tryflip, menu, game);

                    if(!repository.verifyNewPlayer(game.getPlayer().getName())){
                        
                        if(repository.getPlayerScore(game.getPlayer().getName()) < game.getPlayer().getScore()){
                            repository.ReplacePlayer(game.getPlayer());
                        }

                        

                    }else repository.addPlayer(game.getPlayer());
                    

                }

                else if(code == 2){
                  menu.printRanking(repository.getAllPlayers());  
                } 

            }

            else break;
        }
    }

    return 0;
}
