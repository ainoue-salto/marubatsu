#include <marubatsu.h>
#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int MathNum; //各マスの数字

//// マスに記入された印を管理する
char board[NUM][NUM] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};


void DrawScreen() {
	//3×3のマスを表示
	for (int x = 0; x < NUM; x++) {
		for (int y = 0; y < NUM; y++)
			printf("%c ", board[x][y]); //整数値型の値を表示する
		printf("\n");
	}
}

void decidePlayerPosition(int* x, int* y) {
	int ChoiceNum;
	bool blank = true;

	do {
		printf("どのマスに記入しますか？(1〜9)\n");
		do {
			scanf_s("%d", &ChoiceNum);
			if (ChoiceNum < 1 || ChoiceNum > 9) {
				printf("無効な入力です。1〜9の範囲で入力してください。\n");
				blank = false;
			}
			else
				blank = true;
		} while (!blank);

		//配列の座標を計算
		*x = (ChoiceNum - 1) / NUM; // 列番号 (横方向)
		*y = (ChoiceNum - 1) % NUM; // 行番号 (縦方向)

		if (board[*x][*y] == 'o' || board[*x][*y] == 'x') {
			printf("そのマスはすでに埋まってマス...\n");
			printf("--------\n");
			blank = false;
		}
		else {
			printf("--------\n");
			blank = true;
		}
	} while (!blank);
}

//CPUの●×選択
void decideComPosition(int* x, int* y) {
	do {
		*x = rand() % NUM;
		*y = rand() % NUM;
	} while (board[*x][*y] == 'o' || board[*x][*y] == 'x');

}

//ターンの人のマークに合わせて選択
void decidePosition(int* x, int* y, TURN turn) {

	while (true) {
		if (turn == TURN_PLAYER) {
			decidePlayerPosition(x, y);
		}
		else {
			decideComPosition(x, y);
		}
		break;
	}

}

//プレイヤーかCPUかで〇×を変えて入力する
void writeMark(int x, int y, TURN turn) {

	if (turn == TURN_PLAYER) {
		board[x][y] = 'o';
	}
	else {
		board[x][y] = 'x';
	}
}

//マスが埋まっているかどうか
bool judgeFull(void) {
	int count = 0;
	for (int x = 0; x < NUM; x++) {
		for (int y = 0; y < NUM; y++) {
			if (board[x][y] == 'o' || board[x][y] == 'x')
				count++;
			if (count == 9) {
				return true;
			}
		}
	}

	return false;
}

//勝敗判定
// 横方向の勝敗を判定する
bool checkHorizontal(char mark) {
	for (int y = 0; y < NUM; y++) {
		int count = 0;
		for (int x = 0; x < NUM; x++) {
			if (board[y][x] == mark) {
				count++;
			}
		}
		if (count == TARGET) {
			return true;
		}
	}
	return false;
}

// 縦方向の勝敗を判定する
bool checkVertical(char mark) {
	for (int x = 0; x < NUM; x++) {
		int count = 0;
		for (int y = 0; y < NUM; y++) {
			if (board[y][x] == mark) {
				count++;
			}
		}
		if (count == TARGET) {
			return true;
		}
	}
	return false;
}

// 右斜め方向の勝敗を判定する
bool checkDiagonalRight(char mark) {
	int count = 0;
	for (int k = 0; k < NUM; k++) {
		if (board[k][k] == mark) {
			count++;
		}
	}
	return count == TARGET;
}

// 左斜め方向の勝敗を判定する
bool checkDiagonalLeft(char mark) {
	int count = 0;
	for (int k = 0; k < NUM; k++) {
		if (board[NUM - 1 - k][k] == mark) {
			count++;
		}
	}
	return count == TARGET;
}

// 全体の勝敗を判定する
RESULT judgeResult(TURN turn) {
	char mark = (turn == TURN_PLAYER) ? 'o' : 'x';

	// 各方向の判定
	if (checkHorizontal(mark) || checkVertical(mark) ||
		checkDiagonalRight(mark) || checkDiagonalLeft(mark)) {
		return (turn == TURN_PLAYER) ? RESULT_WIN : RESULT_LOSE;
	}

	// マスが埋まっているかの確認
	if (judgeFull()) {
		return RESULT_DRAW;
	}

	// まだ勝敗が決まっていない
	return RESULT_NONE;
}


//ターンを進める
TURN nextTurn(TURN now) {
	return now == TURN_PLAYER ? TURN_COM : TURN_PLAYER;
}

//勝敗結果
void printResult(RESULT result) {

	if (result == RESULT_WIN) {
		printf("あなたの勝ちです!!!\n");
	}
	else if (result == RESULT_LOSE) {
		printf("あなたの負けです!!!\n");
	}
	else if (result == RESULT_DRAW) {
		printf("引き分けです\n");
	}
}

//初期化
void init(void) {
	srand(time(NULL));

	for (int x = 0; x < NUM; x++) {
		for (int y = 0; y < NUM; y++) {
			printf("%c ", board[x][y]);
		}
	}
}

int main() {

	int x, y;
	RESULT result = RESULT_NONE;
	TURN turn = TURN_PLAYER;

	//マスの初期化
	srand(time(NULL));
	/*init();*/

	//マスの表示
	DrawScreen();

	do {
		printf("--------\n");
		if (turn == TURN_PLAYER)
			printf("あなたのターン！\n");
		else
			printf("CPUのターン！\n");
		printf("--------\n");

		//○×を記入する位置を入力する
		decidePosition(&x, &y, turn);

		//○×を記入する
		writeMark(x, y, turn);
		/*board[x][y] = 'o';*/

		//再度マスを表示する
		DrawScreen();

		//勝負の結果を判断する
		result = judgeResult(turn);

		//ターンを進める
		turn = nextTurn(turn);

		//勝負の結果が決まっていなければ再度do内の処理を繰り返す
	} while (result == RESULT_NONE);

	//勝負の結果を表示する
	printResult(result);

}