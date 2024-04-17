#include <iostream>
#include <system_error>
#include "GameState.h"

using namespace std;


Vec validMove(GameState game){
    for (int i = 0; i < game.size; i++){
        for (int j = 0; j < game.size; j++){
            if (game.grid[i][j] == -1){
                return Vec(i, j);
            }
        }
    }
    return Vec(0,0);
}

int main(){
    system("clear");
    GameState game;
    int option = -1;
    
    while(option != 0 || option == -1){
        cout << "Would you like to play Tic-Tac-Toe: " << endl << "1. Against another person" << endl << "2. Against a weak AI" << endl << "3. Against an advanced AI" << endl << "Type \"1\", \"2\", or \"3\" to select! You can also type \"0\" to stop." << endl;
        cin >> option;
        if(option == 2){
            cout << "would you like to play x or o?" << endl;
            bool PlayerType;
            string answer;
            cin >> answer;
            while(!game.done){
                system("clear");
                cout << game << endl;
                
                int x, y;
                
                if(answer == "x"){
                    if (game.currentTurn){
                        Vec move = validMove(game);
                        x = move.x;
                        y = move.y;
                    }
                    else{
                        cout << endl;
                        cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                        cin >> x >> y;
                    }

                    game.play(x, y);
                    }
                    else{
                        if (!game.currentTurn){
                        Vec move = validMove(game);
                        x = move.x;
                        y = move.y;
                    }
                    else{
                        cout << endl;
                        cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                        cin >> x >> y;
                    }

                    game.play(x, y);
                    }
            }

            system("clear");
            cout << game << endl;
            cout << endl;
            if (game.hasWon(0)){
                cout << "Player X has won" << endl;
            }
            else if (game.hasWon(1)){
                cout << "Player O has won" << endl;
            }
            else {
                cout << "It's a tie" << endl;
            }
        } else if (option == 1){
            //play against human function
            //Current plan:
            //while !game.done:
            //First player is x, and makes a move using cin
            //valid move func used to test, if fails call above again
            //Second player is o, and makes a move using cin
            //valid move func used to test, if fails call above again
            while(!game.done){
                system("clear");
                int x, y;
                
            }
            cout << "This hasn't been implemented yet!" << endl;
        } else if(option == 3){
            //play against hard AI function
                cout << "This hasn't been implemented yet!" << endl;
        } else if(option == 0){
            system("clear");
            cout << "Thanks for playing!" << endl;
            break;
        }else{
            system("clear");
            cout << "Please enter a valid option!" << endl << endl << endl;
        }
    }
    return 0;
}
