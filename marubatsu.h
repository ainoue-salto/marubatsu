#ifndef marubatsu_H
#define marubatsu_H

#include <stdbool.h>

#define NUM 3 // マス数
#define TARGET NUM // 並べたら勝ちとなる印の数

typedef enum {
	RESULT_WIN, // プレイヤーの勝ち
	RESULT_LOSE, // プレイヤーの負け
	RESULT_DRAW, // 引き分け
	RESULT_NONE // 結果が決まっていない
} RESULT;

typedef enum {
	TURN_PLAYER, // プレイヤーのターン
	TURN_COM, // コンピューターのターン
} TURN

char board[NUM][NUM];

//関数のプロトタイプ宣言
void DrawScreen(void);
void decidePlayerPosition(int* x, int* y);
void decideComPosition(int* x, int* y);
void decidePosition(int* x, int* y, TURN turn);
void writeMark(int x, int y, TURN turn);
bool judgeFull(void);
RESULT judgeResult(TURN turn);
TURN nextTurn(TURN now);
void printResult(RESULT result);
void init(void);

#endif // !marubatsu_H