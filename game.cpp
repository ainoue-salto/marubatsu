#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define NUM 3 // マス数
#define TARGET NUM // 並べたら勝ちとなる印の数

int MathNum; //各マスの数字

typedef enum {
	RESULT_WIN, // プレイヤーの勝ち
	RESULT_LOSE, // プレイヤーの負け
	RESULT_DRAW, // 引き分け
	RESULT_NONE // 結果が決まっていない
} RESULT;

typedef enum {
	TURN_PLAYER, // プレイヤーのターン
	TURN_COM, // コンピューターのターン
} TURN;

char board[NUM][NUM]; // マスに記入された印を管理する配列

int  DrawNum(int x, int y) {

	MathNum = x * 3;

	switch (y)
	{
	case 0:
		MathNum += 1;
		break;
	case 1:
		MathNum += 2;
		break;
	case 2:
		MathNum += 3;
		break;
	default:
		break;
	}
	return MathNum;
}

void DrawScreen() {
	//3×3のマスを表示
	for (int y = 0; y < NUM; y++) {
		for (int x = 0; x < NUM; x++)
			printf("%d ", DrawNum(x, y)); //整数値型の値を表示する
		printf("\n");
	}
}

int main() {
	//マスを表示
	DrawScreen();

}