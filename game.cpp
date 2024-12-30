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

// �}�X�ɋL�����ꂽ����Ǘ�����
char board[NUM][NUM] = {
	{'1', '2', '3'},
	{'4', '5', '6'},
	{'7', '8', '9'}
};


void DrawScreen() {
	//3�~3�̃}�X��\��
	for (int x = 0; x < NUM; x++) {
		for (int y = 0; y < NUM; y++)
			printf("%c ", board[x][y]); //�����l�^�̒l��\������
		printf("\n");
	}
}

void decidePlayerPosition(int* x, int* y) {
	int ChoiceNum;
	bool blank = true;

	do {
		printf("�ǂ̃}�X�ɋL�����܂����H(1�`9)\n");
		do {
			scanf_s("%d", &ChoiceNum);
			if (ChoiceNum < 1 || ChoiceNum > 9) {
				printf("�����ȓ��͂ł��B1�`9�͈̔͂œ��͂��Ă��������B\n");
				blank = false;
			}
			else
				blank = true;
		} while (!blank);

		//�z��̍��W���v�Z
		*x = (ChoiceNum - 1) / NUM; // ��ԍ� (������)
		*y = (ChoiceNum - 1) % NUM; // �s�ԍ� (�c����)

		if (board[*x][*y] == 'o' || board[*x][*y] == 'x') {
			printf("���̃}�X�͂��łɖ��܂��ă}�X...\n");
			printf("--------\n");
			blank = false;
		}
		else {
			printf("--------\n");
			blank = true;
		}
	} while (!blank);
}

//CPU�́��~�I��
void decideComPosition(int* x, int* y) {
	do {
		*x = rand() % NUM;
		*y = rand() % NUM;
	} while (board[*x][*y] == 'o' || board[*x][*y] == 'x');

}

//�^�[���̐l�̃}�[�N�ɍ��킹�đI��
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

//�v���C���[��CPU���ŁZ�~��ς��ē��͂���
void writeMark(int x, int y, TURN turn) {

	if (turn == TURN_PLAYER) {
		board[x][y] = 'o';
	}
	else {
		board[x][y] = 'x';
	}
}

//�}�X�����܂��Ă��邩�ǂ���
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

//���s����
RESULT judgeResult(TURN turn) {
	int count = 0;
	char mark;

	//�L�����ꂽ�}�[�N���擾
	if (turn == TURN_PLAYER) {
		mark = 'o';
	}
	else {
		mark = 'x';
	}

	//�������m�F
	for (int y = 0; y < NUM; y++) {
		count = 0;
		for (int x = 0; x < NUM; x++) {
			if (board[y][x] == mark) {
				count++;
			}
		}
		if (count == TARGET) {
			return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
		}
	}

	//�c�����m�F
	for (int x = 0; x < NUM; x++) {
		count = 0;
		for (int y = 0; y < NUM; y++) {
			if (board[y][x] == mark) {
				count++;
			}
		}
		if (count == TARGET) {
			return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
		}
	}

	//�E�΂ߊm�F
	count = 0;
	for (int k = 0; k < NUM; k++) {
		if (board[k][k] == mark) {
			count++;
		}
	}
	if (count == TARGET) {
		return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
	}

	//���΂ߊm�F
	count = 0;
	for (int k = 0; k < NUM; k++) {
		if (board[NUM - 1 - k][k] == mark) {
			count++;
		}
	}
	if (count == TARGET) {
		return turn == TURN_PLAYER ? RESULT_WIN : RESULT_LOSE;
	}

	// �}�X���S�Ė��܂������ǂ������m�F
	if (judgeFull()) {
		return RESULT_DRAW;
	}

	// �܂����s�����肵�Ă��Ȃ�
	return RESULT_NONE;

}

//�^�[����i�߂�
TURN nextTurn(TURN now) {
	return now == TURN_PLAYER ? TURN_COM : TURN_PLAYER;
}

//���s����
void printResult(RESULT result) {

	if (result == RESULT_WIN) {
		printf("���Ȃ��̏����ł�!!!\n");
	}
	else if (result == RESULT_LOSE) {
		printf("���Ȃ��̕����ł�!!!\n");
	}
	else if (result == RESULT_DRAW) {
		printf("���������ł�\n");
	}
}

//������
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

	//�}�X�̏�����
	srand(time(NULL));
	/*init();*/

	//�}�X�̕\��
	DrawScreen();

	do {
		printf("--------\n");
		if (turn == TURN_PLAYER)
			printf("���Ȃ��̃^�[���I\n");
		else
			printf("CPU�̃^�[���I\n");
		printf("--------\n");

		//���~���L������ʒu����͂���
		decidePosition(&x, &y, turn);

		//���~���L������
		writeMark(x, y, turn);
		/*board[x][y] = 'o';*/

		//�ēx�}�X��\������
		DrawScreen();

		//�����̌��ʂ𔻒f����
		result = judgeResult(turn);

		//�^�[����i�߂�
		turn = nextTurn(turn);

		//�����̌��ʂ����܂��Ă��Ȃ���΍ēxdo���̏������J��Ԃ�
	} while (result == RESULT_NONE);

	//�����̌��ʂ�\������
	printResult(result);

}