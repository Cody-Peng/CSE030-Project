#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
// #include <algorithm>

struct Vec{
    int x;
    int y;

    Vec(){
        x = 0;
        y = 0;
    }

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }
};

std::ostream& operator<<(std::ostream& os, const Vec& v){
    os << "(" << v.x << ", " << v.y << ")";

    return os;
}

struct GameState;
std::ostream& operator<<(std::ostream& os, const GameState& state);

struct GameState{
    int** grid;
    bool currentTurn;
    int size;
    int turnCount;

    bool done;
    Vec lastMove;

    GameState(){
        size = 3;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
    }

    GameState(int size){
        this->size = size;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
    }

    GameState(const GameState& other){
        size = other.size;
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    bool operator==(const GameState& other){
        bool sizeMatch = size == other.size;
        bool currentTurnMatch = currentTurn == other.currentTurn;
        bool turnCountMatch = turnCount == other.turnCount;
        bool doneMatch = done == other.done;
        bool lastMoveMatch = lastMove.x == other.lastMove.x && lastMove.y == other.lastMove.y;
        if (sizeMatch && currentTurnMatch && turnCountMatch && doneMatch && lastMoveMatch){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (grid[i][j] != other.grid[i][j]){
                        return false;
                    }
                }
            }
            
            return true;
        }
        else{
            return false;
        }
    }

    GameState& operator=(const GameState& other){
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        if (size == other.size){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }
        else{
            for (int i = 0; i < size; i++){
                delete[] grid[i];
            }
            delete[] grid;

            size = other.size;

            grid = new int*[size];

            for (int i = 0; i < size; i++){
                grid[i] = new int[size];
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }

        return *this;
    }

    bool hasWon(int player){
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[i][j] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[j][i] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }
        int mainDiagCount = 0;

        for (int i = 0; i < size; i++){
            if (grid[i][i] == player){
                mainDiagCount++;
            }
        }
        if (mainDiagCount == size){
            return true;
        }

        int secondaryDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (grid[i][size-1-i] == player){
                secondaryDiagCount++;
            }
        }
        if (secondaryDiagCount == size){
            return true;
        }
        
        return false;
    }

    bool play(int x, int y){
        if (grid[x][y] != -1){
            return false;
        }

        grid[x][y] = currentTurn;
        currentTurn = !currentTurn;
        turnCount++;
        lastMove.set(x, y);

        if (turnCount == size * size){
            done = true;
        }
        else if (hasWon(0) || hasWon(1)){
            done = true;
        }

        return true;
    }

    int evaluate(GameState& game){
        for (int row = 0; row < game.size; ++row) {
            bool rowWin = true;
            for (int col = 1; col < game.size; ++col) {
                if (game.grid[row][col] != game.grid[row][col - 1] || game.grid[row][col] == -1) {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin) {
                return (game.grid[row][0] == 1) ? 10 : -10;
            }
        }

        for (int col = 0; col < game.size; ++col) {
            bool colWin = true;
            for (int row = 1; row < game.size; ++row) {
                if (game.grid[row][col] != game.grid[row - 1][col] || game.grid[row][col] == -1) {
                    colWin = false;
                    break;
                }
            }
            if (colWin) {
                return (game.grid[0][col] == 1) ? 10 : -10;
            }
        }

        bool mainDiagWin = true;
        for (int i = 1; i < game.size; i++) {
            if (game.grid[i][i] != game.grid[i - 1][i - 1] || game.grid[i][i] == -1) {
                mainDiagWin = false;
                break;
            }
        }
        if (mainDiagWin) {
            return (game.grid[0][0] == 1) ? 10 : -10;
        }

        bool secDiagWin = true;
        for (int i = 1; i < game.size; i++) {
            if (game.grid[i][game.size - i - 1] != game.grid[i - 1][game.size - i] || game.grid[i][game.size - i - 1] == -1) {
                secDiagWin = false;
                break;
            }
        }
        if (secDiagWin) {
            return (game.grid[0][game.size - 1] == 1) ? 10 : -10;
        }

        return 0;
    }

    bool hasEmptyCell() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == -1) {
                    return true;
                }
            }
        }
        return false;
    }

    int minimax(GameState& game, int depth, bool isMax) {
        int score = evaluate(game);

        if (score == 10) return score;

        if (score == -10) return score;

        if (!game.hasEmptyCell()) return 0;

        if (isMax) {
            int best = -1000;

            for (int i = 0; i < game.size; i++) {
                for (int j = 0; j < game.size; j++) {
                    if (game.grid[i][j] == -1) {
                        game.grid[i][j] = 1;

                        best = std::max(best, minimax(game, depth + 1, !isMax));

                        game.grid[i][j] = -1;
                    }
                }
            }
            return best;
        } else {
            int best = 1000;

            for (int i = 0; i < game.size; i++) {
                for (int j = 0; j < game.size; j++) {
                    if (game.grid[i][j] == -1) {
                        game.grid[i][j] = 0;

                        best = std::min(best, minimax(game, depth + 1, !isMax));

                        game.grid[i][j] = -1;
                    }
                }
            }
            return best;
        }
    }

    Vec findBestMove(GameState& game) {
        int bestVal = -1000;
        Vec bestMove(-1, -1);

        for (int i = 0; i < game.size; i++) {
            for (int j = 0; j < game.size; j++) {
                if (game.grid[i][j] == -1) {
                    game.grid[i][j] = 1;

                    int moveVal = minimax(game, 0, false);

                    game.grid[i][j] = -1;

                    if (moveVal > bestVal) {
                        bestMove.x = i;
                        bestMove.y = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    ~GameState(){
        for (int i = 0; i < size; i++){
            delete[] grid[i];
        }
        delete[] grid;
    }
};

std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << " " << j << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << "--- ";
    }
    os << std::endl;
    for (int i = 0; i < state.size; i++){
        os << i << " ";
        for (int j = 0; j < state.size; j++){
            char c = ' ';
            if (state.grid[i][j] == 0){
                c = 'X';
            }
            else if (state.grid[i][j] == 1){
                c = 'O';
            }
            os << "| " << c << " ";
            if (j == state.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < state.size; j++){
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif
