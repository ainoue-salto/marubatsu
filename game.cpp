#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define NUM 3 // �}�X��
#define TARGET NUM // ���ׂ��珟���ƂȂ��̐�

int MathNum; //�e�}�X�̐���

typedef enum {
	RESULT_WIN, // �v���C���[�̏���
	RESULT_LOSE, // �v���C���[�̕���
	RESULT_DRAW, // ��������
	RESULT_NONE // ���ʂ����܂��Ă��Ȃ�
} RESULT;

typedef enum {
	TURN_PLAYER, // �v���C���[�̃^�[��
	TURN_COM, // �R���s���[�^�[�̃^�[��
} TURN;

char board[NUM][NUM]; // �}�X�ɋL�����ꂽ����Ǘ�����z��

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
	//3�~3�̃}�X��\��
	for (int y = 0; y < NUM; y++) {
		for (int x = 0; x < NUM; x++)
			printf("%d ", DrawNum(x, y)); //�����l�^�̒l��\������
		printf("\n");
	}
}

int main() {
	//�}�X��\��
	DrawScreen();

}