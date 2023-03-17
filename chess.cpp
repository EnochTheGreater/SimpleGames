// g++ -std=c++11 chess.cpp -o chess
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

#define BOARD_SIZE 64

vector<int> board = {
     2, 3, 4, 5, 6, 4, 3, 2,
     1, 1, 1, 1, 1, 1, 1, 1,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
    -1,-1,-1,-1,-1,-1,-1,-1,
    -2,-3,-4,-6,-5,-4,-3,-2,
};

list<vector<int> > previous = list<vector<int> >(5, board);

vector<int> graveyard;
int player = 0;

void clear_screen()
{
#ifdef WINDOWS
    system("cls");
#else
    // Assume POSIX
    system ("clear");
#endif
}

void initialize() {
    board.clear();
    board = {
     2, 3, 4, 5, 6, 4, 3, 2,
     1, 1, 1, 1, 1, 1, 1, 1,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0,
    -1,-1,-1,-1,-1,-1,-1,-1,
    -2,-3,-4,-5,-6,-4,-3,-2,
    };
    previous.clear();
    previous = list<vector<int> >(5, graveyard);
    graveyard.clear();
    player = 0;
}

void writeBoard() {

}

string getChar(int n) {
    switch(n) {
        case 1:
            return "\u2659";
        case 2:
            return "\u2656";
        case 3:
            return "\u2658";
        case 4:
            return "\u2657";
        case 5:
            return "\u2654";
        case 6:
            return "\u2655";
        case -1:
            return "\u265F";
        case -2:
            return "\u265C";
        case -3:
            return "\u265E";
        case -4:
            return "\u265D";
        case -5:
            return "\u265A";
        case -6:
            return "\u265B";
    }
    return "?";
}

void printBoard() {
    cout << "a b c d e f g h" << endl;
    for(int i{0}; i < BOARD_SIZE; i++) {
        if(board[i] == 0) {
            cout << "\u2022 ";
        } else {
            cout << getChar(board[i]) << " ";
        }
        if((i+1) % 8 == 0) {
            cout << (i+1) / 8 << endl;
        }
    }
}

int getPos(string pos) {
    return (pos[0]-97)+(pos[1]-49)*8;
}

int move(string a, string b) {
    int apos = getPos(a);
    int bpos = getPos(b);
    int bnum = board[bpos];
    previous.pop_back();
    previous.push_back(board);
    board[bpos] = board[apos];
    board[apos] = 0;
    return bnum;
}

bool isValid(string a, string b) {
    int apos = getPos(a);
    int bpos = getPos(b);
    if((board[apos]>0) && (player!=0)) return false;
    if((board[apos]<0) && (player!=1)) return false;
    return true;
}

bool input() {
    string a, b;
    do {
        cout << "(ex: a1, q for quit, r for reset, p for undo)" << endl;
        cout << "move: ";
        cin >> a;
        if(a == "q") return false;
        if(a == "r") {
            initialize();
            return true;
        }
        if((a == "p") && !previous.empty()) {
            board = previous.front();
            previous.pop_front();
            player = abs(player-1)%2;
            if(!graveyard.empty()) {
                graveyard.pop_back();
            }
            return true;
        }
    } while((a[0]<97) || (a[0]>104) || (a[1]<49) || (a[1]>56) || (board[getPos(a)] == 0) || !isValid(a, b));

    do {
        cout << "to: ";
        cin >> b;
        if(b == "q") return false;
        if(a == "r") {
            initialize();
            return true;
        }
    } while((b[0]<97) || (b[0]>104) || (b[1]<49) || (b[1]>56));

    graveyard.push_back(move(a, b));
    player = (player+1)%2;
    return true;
}

int main() {
    do {
        clear_screen();
        cout << "player: " << player + 1 << endl;
        cout << "graveyard: ";
        for(int n : graveyard) {
            if(n != 0) {
                cout << getChar(n) << " ";
            }
        }
        cout << endl;
        cout << endl;
        printBoard();
    } while(input());

    return 0;
}