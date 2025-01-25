#ifndef marubatsu_H
#define marubatsu_H

#include <stdbool.h>

#define NUM 3 // �}�X��
#define TARGET NUM // ���ׂ��珟���ƂȂ��̐�

typedef enum {
	RESULT_WIN, // �v���C���[�̏���
	RESULT_LOSE, // �v���C���[�̕���
	RESULT_DRAW, // ��������
	RESULT_NONE // ���ʂ����܂��Ă��Ȃ�
} RESULT;

typedef enum {
	TURN_PLAYER, // �v���C���[�̃^�[��
	TURN_COM, // �R���s���[�^�[�̃^�[��
} TURN

char board[NUM][NUM];

//�֐��̃v���g�^�C�v�錾
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