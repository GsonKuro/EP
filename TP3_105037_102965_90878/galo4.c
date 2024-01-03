//-----------------------------//
//         Libraries
//-----------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-----------------------------//
//         Macros
//-----------------------------//

#define BOARD_SIZE 3
#define NUM_POSITIONS (BOARD_SIZE * BOARD_SIZE)

//----------------------------------//
//  Print recent state of the board
//----------------------------------//

void printBoard(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

//-----------------------------//
//  Check if there is a winner
//-----------------------------//

int isWinner(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return 1;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return 1;
    }

    return 0;
}

//-----------------------------//
//  Check if the board is full
//-----------------------------//

int isBoardFull(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0; // Board is not full
            }
        }
    }
    return 1; // Board is full
}

//-----------------------------//
//  Evaluate move possibility
//-----------------------------//

int evaluateMove(char board[BOARD_SIZE][BOARD_SIZE], int move, char player) {
    int row = move / BOARD_SIZE;
    int col = move % BOARD_SIZE;

    char opponent = (player == 'X') ? 'O' : 'X';

    // Evaluate the move based on potential wins for both players
    board[row][col] = player;
    if (isWinner(board, player)) {
        board[row][col] = ' '; // Undo the move
        return 10; // High score for a winning move
    }
    board[row][col] = ' '; // Undo the move

    board[row][col] = opponent;
    if (isWinner(board, opponent)) {
        board[row][col] = ' '; // Undo the move
        return 9; // High score for blocking opponent's win
    }
    board[row][col] = ' '; // Undo the move

    // Default score for other moves
    return 0;
}

//-----------------------------//
//        Find best move
//-----------------------------//

int findBestMove(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    int bestMove = -1;
    int bestScore = -1;

    for (int i = 0; i < NUM_POSITIONS; i++) {
        int row = i / BOARD_SIZE;
        int col = i % BOARD_SIZE;

        if (board[row][col] == ' ') {
            int score = evaluateMove(board, i, player);
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    return bestMove;
}

//------------------------------------//
//  Function to simulate random moves
//------------------------------------//

int makeRandomMove(char board[BOARD_SIZE][BOARD_SIZE]) {
    int availableMoves[NUM_POSITIONS];
    int numAvailableMoves = 0;

    // Find available moves
    for (int i = 0; i < NUM_POSITIONS; i++) {
        int row = i / BOARD_SIZE;
        int col = i % BOARD_SIZE;

        if (board[row][col] == ' ') {
            availableMoves[numAvailableMoves++] = i;
        }
    }

    if (numAvailableMoves == 0) {
        return -1; // No available moves
    }

    // Choose a random move
    int randomIndex = rand() % numAvailableMoves;
    return availableMoves[randomIndex];
}

//-----------------------------//
//    Function that permit pvp
//-----------------------------//

void playerVsPlayer(char board[BOARD_SIZE][BOARD_SIZE]) {
    int currentPlayer = 1; // 1 for player X, -1 for player O

    do {
        // Print the current board
        printf("Current Board:\n");
        printBoard(board);

        int row, col;

        // Player's turn
        printf("Player %c's move (enter row and column): ", (currentPlayer == 1) ? 'X' : 'O');
        scanf("%d %d", &row, &col);

        // Check if the move is valid
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make the move
        board[row][col] = (currentPlayer == 1) ? 'X' : 'O';

        // Check if the current player wins
        if (isWinner(board, (currentPlayer == 1) ? 'X' : 'O')) {
            printf("Player %c wins!\n", (currentPlayer == 1) ? 'X' : 'O');
            break;
        }

        // Switch to the other player's turn
        currentPlayer *= -1;

    } while (!isBoardFull(board));

    // Print the final board
    printf("Final Board:\n");
    printBoard(board);
}

//-------------------------------------------------------//
//  Function that permits play versus a tained computer
//-------------------------------------------------------//

void playerVsComputer(char board[BOARD_SIZE][BOARD_SIZE]) {
    int currentPlayer = 1; // 1 for player X, -1 for computer O

    do {
        // Print the current board
        printf("Current Board:\n");
        printBoard(board);

        int row, col;

        if (currentPlayer == 1) {
            // Player's turn
            printf("Player X's move (enter row and column): ");
            scanf("%d %d", &row, &col);
        } else {
            // Computer's turn
            int bestMove = findBestMove(board, 'O');
            if (bestMove == -1) {
                printf("It's a tie!\n");
                break;
            }
            row = bestMove / BOARD_SIZE;
            col = bestMove % BOARD_SIZE;
            printf("Computer (O) plays at: %d %d\n", row, col);
        }

        // Check if the move is valid
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make the move
        board[row][col] = (currentPlayer == 1) ? 'X' : 'O';

        // Check if the current player wins
        if (isWinner(board, (currentPlayer == 1) ? 'X' : 'O')) {
            printf("Player %c wins!\n", (currentPlayer == 1) ? 'X' : 'O');
            break;
        }

        // Switch to the other player's turn
        currentPlayer *= -1;

    } while (!isBoardFull(board));

    // Print the final board
    printf("Final Board:\n");
    printBoard(board);
}

//--------------------------------------------------------------//
//  Function that permits see random moves from both players
//--------------------------------------------------------------//

void randomVsRandom(char board[BOARD_SIZE][BOARD_SIZE]) {
    int currentPlayer = (rand() % 2 == 0) ? 1 : -1; // Randomly decide who plays first

    do {
        // Print the current board
        printf("Current Board:\n");
        printBoard(board);

        int row, col;

        // Random player's turn
        int randomMove = makeRandomMove(board);
        if (randomMove == -1) {
            printf("It's a tie!\n");
            break;
        }
        row = randomMove / BOARD_SIZE;
        col = randomMove % BOARD_SIZE;
        printf("Random player plays at: %d %d\n", row, col);

        // Check if the move is valid
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make the move
        board[row][col] = (currentPlayer == 1) ? 'X' : 'O';

        // Check if the current player wins
        if (isWinner(board, (currentPlayer == 1) ? 'X' : 'O')) {
            printf("Player %c wins!\n", (currentPlayer == 1) ? 'X' : 'O');
            break;
        }

        // Switch to the other player's turn
        currentPlayer *= -1;

    } while (!isBoardFull(board));

    // Print the final board
    printf("Final Board:\n");
    printBoard(board);
}

//----------------------------------------------------------------------//
//   Function that permit play versus a computer that plays randomly
//----------------------------------------------------------------------//

void playerVsRandom(char board[BOARD_SIZE][BOARD_SIZE]) {
    int currentPlayer = 1; // 1 for player X, -1 for random O

    do {
        // Print the current board
        printf("Current Board:\n");
        printBoard(board);

        int row, col;

        if (currentPlayer == 1) {
            // Player's turn
            printf("Player X's move (enter row and column): ");
            scanf("%d %d", &row, &col);
        } else {
            // Random player's turn
            int randomMove = makeRandomMove(board);
            if (randomMove == -1) {
                printf("It's a tie!\n");
                break;
            }
            row = randomMove / BOARD_SIZE;
            col = randomMove % BOARD_SIZE;
            printf("Random player plays at: %d %d\n", row, col);
        }

        // Check if the move is valid
        if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
            printf("Invalid move! Try again.\n");
            continue;
        }

        // Make the move
        board[row][col] = (currentPlayer == 1) ? 'X' : 'O';

        // Check if the current player wins
        if (isWinner(board, (currentPlayer == 1) ? 'X' : 'O')) {
            printf("Player %c wins!\n", (currentPlayer == 1) ? 'X' : 'O');
            break;
        }

        // Switch to the other player's turn
        currentPlayer *= -1;

    } while (!isBoardFull(board));

    // Print the final board
    printf("Final Board:\n");
    printBoard(board);
}

//-----------------------------//
//         Main Function
//-----------------------------//

int main(void) {

    //-----------------------------//
    //       Initialization
    //-----------------------------//

    srand(time(NULL));

    do {
        char board[BOARD_SIZE][BOARD_SIZE] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };

        //-----------------------------//
        //         Execution
        //-----------------------------//

        printf("Choose mode:\n1. Player vs Player\n2. Player vs Computer\n3. Random vs Random\n4. Player vs Random\n5. Exit\n");
        int mode;
        scanf("%d", &mode);

        switch (mode) {
            case 1:
                playerVsPlayer(board);
                break;
            case 2:
                playerVsComputer(board);
                break;
            case 3:
                randomVsRandom(board);
                break;
            case 4:
                playerVsRandom(board);
                break;
            case 5:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid mode selected.\n");
                break;
        }

        // Ask if the user wants to play again
        printf("Do you want to play again? (1 for yes, 0 for no): ");
        int playAgain;
        scanf("%d", &playAgain);

        if (!playAgain) {
            printf("Goodbye!\n");
            break;
        }

    } while (1);

    return 0;
}
