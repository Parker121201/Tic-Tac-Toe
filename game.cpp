#include <string>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <algorithm>

/*

X O _       1 2 3   (0 1 2)
O _ _       4 5 6   (3 4 5)
_ X _       7 8 9   (6 7 8)

*/

//g++ -std=c++1z -Wconversion -Wall -Werror -Wextra -pedantic game.cpp -o tictactoe

using namespace std;

/* Don't need

//DONE
* Returns true if the board is full of X and O
bool board_full(char board[9]) {
    //Goes through each board space, if it is still blank, return false
    for (size_t i = 0; i < 9; ++i) {
        if (board[i] == '_') {return false;}
    }
    return true;
}

*/

//DONE
//* Returns true and the character {X, O} of the winner if a win is achieved
//Looks at one space on the board, checks adjacent spaces to see if there are 3 in a row
pair<bool, char> winner(char board[9]) {
    //* Starts looking at the upper left corner
    char upper_left = board[0];

    //Check for _ space
    if (upper_left == '_') {return {false, '_'};}

    //Check horizontal
    if (board[1] == upper_left) {
        if (board[2] == upper_left) {return {true, upper_left};}
    }
    //Check diagional
    if (board[4] == upper_left) {
        if (board[8] == upper_left) {return {true, upper_left};}
    }
    //Check vertical
    if (board[3] == upper_left) {
        if (board[6] == upper_left) {return {true, upper_left};}
    }


    //* Next look at middle space
    char middle = board[4];

    //Check for _ space
    if (middle == '_') {return {false, '_'};}

    //Check horizontal
    if (board[3] == middle) {
        if (board[5] == middle) {return {true, middle};}
    }
    //Check diagional
    if (board[6] == middle) {
        if (board[2] == middle) {return {true, middle};}
    }
    //Check vertical
    if (board[1] == middle) {
        if (board[7] == middle) {return {true, middle};}
    }


    //* Lastly look at bottom right spacce
    char bottom_right = board[8];

    //Check for _ space
    if (bottom_right == '_') {return {false, '_'};}

    //Check horizontal
    if (board[6] == bottom_right) {
        if (board[7] == bottom_right) {return {true, bottom_right};}
    }
    //Check vertical
    if (board[2] == bottom_right) {
        if (board[5] == bottom_right) {return {true, bottom_right};}
    }

    return {false, '_'};
}

//DONE
//* Prints the board and a corresponding board with numbers for the user
void print_board(char board[9]) {
    cout << board[0] << " " << board[1] << " " << board[2] << "\t\t1 2 3\n";
    cout << board[3] << " " << board[4] << " " << board[5] << "\t\t4 5 6\n";
    cout << board[6] << " " << board[7] << " " << board[8] << "\t\t7 8 9\n\n";
}

//DONE
//* Returns true if the given move is valid ([1-9] and not already taken)
bool valid_move(char board[9], int move) {
    if ((move < 1) || (move > 9)) {return false;}
    //Translates 1-9 board to 0-8 array indexing
    if (board[--move] != '_') {return false;}
    return true;
}

int main() {
    int num_moves = 0;
    while (true) {
        char board[9] = {'_', '_', '_', '_', '_', '_', '_', '_', '_'};

        cout << "\n\n\t\tTic Tac Toe\n\n\n\n";

        char p1_choice;
        char p2_choice;

        //While loop validates input
        while (true) {
            cout << "Player 1 select 'X' or 'O' : ";
            cin >> p1_choice;
            if ((p1_choice == 'X') || (p1_choice == 'O')) {break;}
            else {
                cout << "Invalid selection! Try again\n";
            }
        }

        //Assigns p2_choice based on player 1 input
        p1_choice == 'X' ? p2_choice = 'O' : p2_choice = 'X';

        cout << "\nPlayer 1 is " << p1_choice << "\n";
        cout << "Player 2 is " << p2_choice << "\n\n";
        cout << "Player one moves first!\n\n\n";
        bool p1_move = true;

        //Strings to shorten ? operator code
        string p1 = "Player 1";
        string p2 = "Player 2";
        string enter = ", enter the number of your move: ";
        string wins = " you have won!\n\n";
        
        int move;

        //While loop for the game, plays until winner or tie
        while (true) {
            print_board(board);

            //While loop validates move input
            while (true) {
                //If it is P1's move, prompts them. Otherwise, prompts P2
                p1_move == true ? cout << p1 << enter : cout << p2 << enter;
                cin >> move;
                cout << "\n";
                if (valid_move(board, move)) {break;}
                else {
                    cout << "Invalid move! Try again\n";
                }
            }

            //If it is P1's move, replace the _ on the board with their symbol.
            //Otherwise, replace it with P2's symbol
            p1_move == true ? board[--move] = p1_choice : board[--move] = p2_choice;
            num_moves++;

            //Changes turns
            p1_move = !p1_move;

            //First check if there is a winner, only after 5 moves
            if (num_moves >= 5) {
                auto win_report = winner(board);
                //If there is a winner, congratulate them and print the board
                if (win_report.first) {
                    cout << "Congratulations ";
                    win_report.second == p1_choice ? cout << p1 << wins : cout << p2 << wins;
                    print_board(board);
                    break;
                }
            }

            //If this is the 9th move and no winner, it must be a tie
            if (num_moves == 9) {
                cout << "The game has ended in a tie!\n\n";
                print_board(board);
                break;
            }
        }

        //Prompt the user to play again, while loop validates user input
        char play_again;
        while (true) {
            cout << "\n\nWould you like to play again? (Y, N): ";
            cin >> play_again;

            if ((play_again == 'Y') || (play_again == 'N')) {
                break;
            }
            else {
                cout << "Invalid selection! Try again\n";
            }
        }
        
        if (play_again == 'Y') {
            cout << "\n\n\n";
        }
        else if (play_again == 'N') {
            cout << "Thanks for playing!\n";
            return 0;
        }
    }
}