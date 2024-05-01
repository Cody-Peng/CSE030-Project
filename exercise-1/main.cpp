#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cctype>
#include <string>
#include "GameState.h"

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

int getSingleDigitInput(const string& prompt) {
    string line;
    int number = 0;
    while (true) {
        cout << prompt;
        getline(cin, line);

        if (line.size() == 1 && isdigit(line[0])) {
            number = line[0] - '0';
            break;
        } else {
            cout << "Invalid input. Please enter exactly one digit.\n";
        }
    }
    return number;
}

int mainMenu() {
    cout << "\033[2J\033[1;1H";  // Clear screen and move cursor to home position
    cout << R"(
    _______ _        _______           _______         
   |__   __(_)      |__   __|         |__   __|        
      | |   _  ___     | | __ _  ___     | | ___   ___ 
      | |  | |/ __|    | |/ _` |/ __|    | |/ _ \ / _ \
      | |  | | (__     | | (_| | (__     | | (_) |  __/
      |_|  |_|\___|    |_|\__,_|\___|    |_|\___/ \___|
    )" << endl;
    cout << "\n1. Start new game\n";
    cout << "2. Exit\n";
    cout << "\nSelect an option: ";
    return getSingleDigitInput("");
}

void playGame() {
    cout << "\033[2J\033[1;1H";  // Clear screen and move cursor to home position
    int size = getSingleDigitInput("Enter the size of the board (e.g., 3 for a 3x3 board): ");
    while (size > 3) {
        cout << "Not implemented yet. \n";
        size = getSingleDigitInput("Invalid size. Please enter a number equal to or less than 3: ");
    }

    GameState game(size);
    int gameMode = getSingleDigitInput("Select game mode:\n1. Play against easy computer\n2. Play against hard computer\n3. Play against another player\nEnter your choice: ");
    while (gameMode < 1 || gameMode > 3) {
        gameMode = getSingleDigitInput("Invalid choice. Please enter a number between 1 and 3: ");
    }

    Timer timer;
    double elapsed = 0;

    while (!game.done) {
        cout << "\033[2J\033[1;1H";
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
            x = getSingleDigitInput("");
            y = getSingleDigitInput("");

            while (x >= size || y >= size || x < 0 || y < 0 || !game.play(x, y)) {
                cout << "Invalid position or move. Try again.\n";
                x = getSingleDigitInput("Enter row: ");
                y = getSingleDigitInput("Enter column: ");
            }
            elapsed += timer.elapsed_seconds();
        }
    }

    cout << "\033[2J\033[1;1H";
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
