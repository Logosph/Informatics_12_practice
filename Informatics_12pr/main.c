#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>


/*
Exit codes:
-2 : stoi got not a digit string
*/

int power(int num, int pow_to) {
	/*
	Input: number and it's power
	Output: number in this power
	*/
	int result = 1;
	while (pow_to > 0) {
		result *= num;
		pow_to--;
	}
	return result;
}

int isDigit(char str[]) {
	/*
	Input: C-Style string
	Output: 1 if string consists only of digits and 0 if not
	*/
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] > '9' || str[i] < '0') {
			return 0;
		}
	}
	return 1;
}

int stoi(char str[]) {
	/*
	Input: C-Style string
	Output: Integer, got from string. 
	If string consists not only of digits, programme crashes with code -2
	*/
	int result = 0, maxDigit = strlen(str) - 1, currentDigit = maxDigit;
	for (int i = 0; i <= maxDigit; i++) {
		if (str[i] - '0' >= 0 && str[i] - '0' <= 9) {
			result += power(10, currentDigit) * (str[i] - '0');
			currentDigit--;
		}
		else {
			exit(-2);
		}
	}
	return result;
}

void fillRandomly(int** arr, int M) {
	/*
	Input: 2D square array and it's size
	Output: No output
	This procedure fills array with random values
	*/
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			arr[i][j] = rand() % 99 + 1;
		}
	}
}

void fillManually(int** arr, int M) {
	/*
	Input: array to fill and it's size
	Output: No output
	This procedure fills array manually, using keyboard input
	*/
	char tmp[1000] = "\0";
	int number = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			while (1) {
				printf("Enter element (from 1 to 100) with coordinates (%d, %d): ", i, j);
				gets(tmp);
				if (isDigit(tmp)) {
					number = stoi(tmp);
					if (number >= 1 && number <= 100) {
						arr[i][j] = number;
						break;
					}
				}
			}
		}
	}
}

void inversedBubbleSort(int* arr, int M) {
	/*
	
	*/
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M - i - 1; j++) {
			if (arr[j] < arr[j + 1]){
				// Swiping numbers without using additional variables
				arr[j] += arr[j + 1];
				arr[j + 1] = arr[j] - arr[j + 1];
				arr[j] -= arr[j + 1];
			}
		}
	}
}

void displayMatrix(int** arr, int M) {
	/*
	Input: 2D square array and it's size
	Output: No output
	This procedure displays this array to console
	*/
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (arr[i][j] < 10 && arr[i][j] > 0) {
				printf("  ");
			}
			else if (arr[i][j] < 100 && arr[i][j] >= 10 || arr[i][j] < 0 && arr[i][j] > -10) {
				printf(" ");
			}
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main() {
	// Some presets to disable Ctrl+C, Ctrl+Z and to set random really random with time
	signal(SIGINT, SIG_IGN);
	srand(time(NULL));

	int M = 0, tmp = 0, rnd = rand();
	char str[1000] = "", randomOrManuallyFlag[1000] = "";

	// Input size of matrix
	while (1) {
		printf("Enter size of matrix (integer from 2 to 5): ");
		gets(str);
		if (isDigit(str)) {
			tmp = stoi(str);
			if (tmp <= 5 && tmp >= 2) {
				M = tmp;
				break;
			}
		}
	}
	
	printf("Yiii you passed first step! Now choose: do you want to fill matrix randomly or manually? (r/m): ");

	// Input type of filling matrix
	while (1) {
		gets(randomOrManuallyFlag);
		if (!strcmp(randomOrManuallyFlag, "r") || !	strcmp(randomOrManuallyFlag, "m")) {
			break;
		}
		printf("Pls enter \"r\" or \"m\": ");
	}

	// Needed to use dynamic array because it's size is not a constant :(
	int** matrix = (int**)calloc(M, sizeof(*matrix));
	for (int i = 0; i < M; i++) {
		matrix[i] = (int*)calloc(M, sizeof(int));
	}
	
	// Choosing method of filling matrix
	if (!strcmp(randomOrManuallyFlag, "r")) {
		fillRandomly(matrix, M);
	}
	else {
		fillManually(matrix, M);
	}

	system("cls");
	printf("Source matrix: \n");
	displayMatrix(matrix, M);
	printf("\n");

	// (M * M - M) / 2 + M = M * (M + 1) / 2
	int* toSort = (int*)calloc(M * (M + 1) / 2, sizeof(int));
	int c = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i < j) {
				matrix[i][j] *= -1;
			}
			else {
				toSort[c] = matrix[i][j];
				c++;
			}
		}
	}

	inversedBubbleSort(toSort, M * (M + 1) / 2);

	c = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i >= j) {
				matrix[i][j] = toSort[c];
				c++;
			}
		}
	}

	printf("\nTransformed matrix: \n");
	displayMatrix(matrix, M);

	free(matrix);
	free(toSort);

	gets();
}
