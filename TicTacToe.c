#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_DIMENSION 3

#define TIC 1 // X
#define TAC 2 // O
#define EMPTY 3

const char *input[2] = {
	"TIC: Enter the position where you want to make your move: ",
	"TAC: Enter the position where you want to make your move: "
};

const char *boardElements[3] = {
	"X",
	"O",
	"_"
};

#define DRAW_GAME 4
#define TIC_WON 5
#define TAC_WON 6
#define GAME_NOT_FINISHED 7

int enterDimensionOfTheTable() {
	int n;

	while (1) {
		printf("Enter dimension of the table: ");
		scanf("%d", &n);

		if (n >= MIN_DIMENSION) {
			break;
		}
		else {
			printf("Incorrect dimension! Dimension must be >= %d\n", MIN_DIMENSION);
		}
	}

	return n;
}

void initializeRandomNumberGenerator() {
	srand(time(NULL));
}

int **createBoard(int n) {
	int **board = malloc(n * sizeof(int *));

	for (int i = 0; i < n; i++) {
		board[i] = malloc(n * sizeof(int));

		for (int j = 0; j < n; j++) {
			board[i][j] = EMPTY;
		}
	}

	return board;
}

int checkIfPlayerWon(int **board, int n, int player) {
	for (int i = 0; i < n; i++) {
		int j;
		for (j = 0; j < n; j++) {
			if (board[i][j] != player) {
				break;
			}
		}

		if (j == n) {
			return 1;
		}
	}

	for (int j = 0; j < n; j++) {
		int i;
		for (i = 0; i < n; i++) {
			if (board[i][j] != player) {
				break;
			}
		}

		if (i == n) {
			return 1;
		}
	}

	int i, j;
	for (i = 0, j = 0; i < n; i++, j++) {
		if (board[i][j] != player) {
			break;
		}
	}

	if (i == n) {
		return 1;
	}

	for (i = n - 1, j = 0; j < n; i--, j++) {
		if (board[i][j] != player) {
			break;
		}
	}

	if (j == n) {
		return 1;
	}

	return 0;
}

int gameFinshed(int **board, int n, int currentPlayer) {

	int gameFinished = DRAW_GAME;

	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
		if (board[i][j] == EMPTY) {
			gameFinished = GAME_NOT_FINISHED;
			i = n;
			break;
		}
	}

	// here gameFinished has the value of GAME_NOT_FINISHED

	if (checkIfPlayerWon(board, n, currentPlayer) == 1) {
		return (currentPlayer == TIC ? TIC_WON : TAC_WON);
	}

	return gameFinished;
}

int inputIsValid(int **board, int n, int row, int col) {
	if (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == EMPTY) {
		return 1;
	}

	return 0;
}

void makeAMove(int **board, int n, int currentPlayer) {
	int row, col;

	while (1) {
		printf("\n%s", input[currentPlayer - 1]);
		scanf("%d %d", &row, &col);

		if (inputIsValid(board, n, row, col)) {
			break;
		}
		else {
			printf("Invalid input! Try again!\n");
		}
	}

	board[row][col] = currentPlayer;
}

void printBoard(int **board, int n) {
	putchar('\n');

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%s ", boardElements[board[i][j] - 1]);
		}

		putchar('\n');
	}
}

void deleteBoard(int **board, int n) {
	for (int i = 0; i < n; i++) {
		free(board[i]);
	}

	free(board);
}

int main() {
	initializeRandomNumberGenerator();

	int n = enterDimensionOfTheTable();
	int **board = createBoard(n);
	int currentPlayer = ((rand() % 101) > 51) ? TIC : TAC;

	printBoard(board, n);

	while (1) {
		makeAMove(board, n, currentPlayer);
		printBoard(board, n);

		if (gameFinished(board, n, currentPlayer) != GAME_NOT_FINISHED) {
			break;
		}

		currentPlayer = (currentPlayer == TIC) ? TAC : TIC;
	}

	deleteBoard(board, n);

	putchar('\n');

	return EXIT_SUCCESS;
}