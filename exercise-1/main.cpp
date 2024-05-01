#include <iostream>
#include <cstdlib> 
#include "GameState.h"
#include <chrono>

using namespace std;

class Timer {
private:
    chrono::time_point<chrono::steady_clock> start_time;

public:
    Timer() : start_time(chrono::steady_clock::now()) {}

    void reset() {
        start_time = chrono::steady_clock::now();
    }

    double elapsed_seconds() const {
        auto end_time = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = end_time - start_time;
        return elapsed_seconds.count();
    }
};

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

int mainMenu() {
    //system("clear");
    cout << "Main Menu\n";
    cout << "1. Start new game\n";
    cout << "2. Exit\n";
    int choice;
    cin >> choice;
    return choice;
}

void playGame() {
    int size;
    cout << "Enter the size of the board (e.g., 3 for a 3x3 board): ";
    cin >> size;

    while (cin.fail() || size > 3) {
        cout << "Not implemented yet. \n";
        cout << "Invalid size. Please enter a number equal to or less than 3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> size;
    }

    GameState game(size); 
    int gameMode;
    cout << "Select game mode:\n";
    cout << "1. Play against easy computer\n";
    cout << "2. Play against hard computer\n";
    cout << "3. Play against another player\n";
    cin >> gameMode;

    Timer timer;
    double elapsed = 0;

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
        } else {
            cout << "Player " << (game.currentTurn ? "O" : "X") << "'s turn. Enter move (row column): ";
            timer.reset();
            cin >> x >> y;

            // Validate the move
            while (x >= size || y >= size || x < 0 || y < 0 || !game.play(x, y)) {
                if (x >= size || y >= size || x < 0 || y < 0) {
                    cout << "Invalid position. The board is " << size << "x" << size << ". Enter move (row column): ";
                } else {
                    cout << "Invalid move. Cell already occupied. Try again. Player " << (game.currentTurn ? "O" : "X") << ": ";
                }
                cin >> x >> y;
            }
            elapsed += timer.elapsed_seconds();
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

    cout << "Elapsed time: " << elapsed << " seconds" << endl;
}

int main() {
    while (true) {
        int choice = mainMenu();

        if (choice == 1) {
            playGame();
        } else if (choice == 2) {
            cout << "Thanks for Playing!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please select 1 or 2." << endl;
        }
    }
    return 0;
}
