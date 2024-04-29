#include <iostream>
#include <cstdlib> 
#include "GameState.h"

using namespace std;

Vec validMove(GameState game) {
    for (int i = 0; i < game.size; i++) {
        for (int j = 0; j < game.size; j++) {
            if (game.grid[i][j] == -1) {
                return Vec(i, j);
            }
        }
    }
    return Vec(-1, -1);  
}

int main() {
    system("clear");
    int size;
    cout << "Enter the size of the board (e.g., 3 for a 3x3 board): ";
    cin >> size;

    while (cin.fail() || size != 3) {
        cout << "Not implemented yet. \n";
        cout << "Invalid size. Please enter a number equal to 3: ";
        cin.clear();
        while(cin.get() != '\n'){
            continue;
        }
        cin >> size;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    GameState game(size); 
    int gameMode;
    cout << "Select game mode:\n";
    cout << "1. Play against easy computer\n";
    cout << "2. Play against hard computer\n";
    cout << "3. Play against another player\n";
    cout << "4. Cancel\n";
    cin >> gameMode;

    while (gameMode < 1 || gameMode > 4) {
        cout << "Invalid choice. Please enter 1, 2, 3, or 4: ";
        cin >> gameMode;
    }

    if(gameMode != 3) {
        system("clear");
        if (gameMode == 4){
            cout << "Thanks for Playing!" << endl;
            return 0;
        }
        int firstPlayer;
        cout << "Who should start first?\n";
        cout << "1. Player\n";
        cout << "2. Computer\n";
        cin >> firstPlayer;

        while (firstPlayer < 1 || firstPlayer > 2) {
            cout << "Invalid choice. Please enter 1 for Player or 2 for Computer: ";
            cin >> firstPlayer;
        }

        if (gameMode == 1 && firstPlayer == 2 || gameMode == 2 && firstPlayer == 2) {
            game.currentTurn = 1;  
        } else {
            game.currentTurn = 0;  
        }
    }
    
    while (!game.done) {
        system("clear");
        cout << game << endl;

        int x, y;
        if ((gameMode == 1 || gameMode == 2) && game.currentTurn) {
            Vec move = (gameMode == 1 ? validMove(game) : game.findBestMove(game));
            x = move.x;
            y = move.y;
            cout << (gameMode == 1 ? "Easy Computer" : "Hard Computer") << " played (" << x << ", " << y << ")\n";
            game.play(x, y);
        } else if (gameMode == 3 || !game.currentTurn) {
            cout << "Player " << (game.currentTurn ? "O" : "X") << "'s turn. Enter move (row column): ";
            cin >> x >> y;
            while (!game.play(x, y)) {
                cout << "Invalid move. Try again. Player " << (game.currentTurn ? "O" : "X") << ": ";
                cin >> x >> y;
            }
        }
    }

    system("clear");
    cout << game << endl;
    if (game.hasWon(0)) {
        cout << "Player X has won!" << endl;
    } else if (game.hasWon(1)) {
        cout << "Player O has won!" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }

    return 0;
}
