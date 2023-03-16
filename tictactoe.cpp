// g++ -std=c++11 tictactoe.cpp -o tictactoe
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

string board{"123456789"};
bool gameover = false;
int counter = 0;
int player = 1;

void clear_screen()
{
#ifdef WINDOWS
    system("cls");
#else
    // Assume POSIX
    system ("clear");
#endif
}

void printBoard() {
    clear_screen();

    cout << "***************************" << endl;
    cout << "******* TIC TAC TOE *******" << endl;
    cout << endl;

    cout << "\t" << board[0] << "  | " << board[1] << " |  " << board[2] << endl;
    cout << "\t" << "---|---|---" << endl;
    cout << "\t" << board[3] << "  | " << board[4] << " |  " << board[5] << endl;
    cout << "\t" << "---|---|---" << endl;
    cout << "\t" << board[6] << "  | " << board[7] << " |  " << board[8] << endl;
    cout << endl;

    cout << "***************************" << endl;
}

void getInput() {
    int pos = 0;
    do {
        cout << "Player " << player << "(1-9): ";
        cin >> pos;

        if (pos < 0) {
            gameover = true;
            return;
        } else if((pos > 9) || (pos == 0)) {
            cout << "Invalid Input" << endl;
        } else if(board[pos-1] != ' ') {
            cout << "Space Filled Already" << endl;
        }
    } while((pos > 9) || (pos == 0) || (board[pos-1] != ' '));

    if(player == 1) {
        board[pos-1] = 'X';
        player++;
    } else {
        board[pos-1] = 'O';
        player--;
    }
    counter++;
}

void winner() {
    clear_screen();
    printBoard();
    cout << "PLAYER " << player << " WINS" << endl;
}

bool isWin() {
    if(counter >= 9) {
        clear_screen();
        printBoard();
        cout << "DRAW" << endl;
        return true;
    }
    int xWin = 'X' + 'X' + 'X';
    int oWin = 'O' + 'O' + 'O';
    for(int i{0}; i < 3; i++) {
        int row = board[i*3] + board[1+i*3] + board[2+i*3];
        if(row == xWin) {
            player = 1;
            winner();
            return true;
        }
        if(row == oWin) {
            player = 2;
            winner();
            return true;
        }
    }
    for(int i{0}; i < 3; i++) {
        int column = board[i] + board[3+i] + board[6+i];
        if(column == xWin) {
            player = 1;
            winner();
            return true;
        }
        if(column == oWin) {
            player = 2;
            winner();
            return true;
        }
    }
    int lB = board[0] + board[4] + board[8];
    int rU = board[6] + board[4] + board[2];
    if(lB == xWin) {
        player = 1;
        winner();
        return true;
    }
    if(lB == oWin) {
        player = 2;
        winner();
        return true;
    }
    if(rU == xWin) {
        player = 1;
        winner();
        return true;
    }
    if(rU == oWin) {
        player = 2;
        winner();
        return true;
    }
    return false;
}

void initialize() {
    board = string(9, ' ');
    gameover = false;
    counter = 0;
    player = 1;
}

void gameLoop() {
    while(!gameover) {
        printBoard();
        getInput();
        if(!gameover) {
            gameover = isWin();
        }
    }
}

int main() {
    string start;
    printBoard();
    while(true) {
        cout << "Start Game (y/n)? ";
        cin >> start;

        if((start[0] == 'y') || (start[0] == 'Y')) {
            initialize();
            gameLoop();
        } else {
            cout << "KILLING TIC TAC TOE" << endl;
            break;
        }
    }

    return 0;
}