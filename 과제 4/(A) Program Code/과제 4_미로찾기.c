// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_�̷�ã�� 24.05.20~24

#include <stdio.h>
#include <stdlib.h>

#define MAZE_SIZE 10 // �̷� ũ��
#define EMTPY '0' // �� �� �ִ� ��
#define FILLED '1' // ������ ���� ��
#define VISITED '.' // �̹� ������ ��

// ��ġ ǥ�� ���� ����ü ����
typedef struct {
	int r; // ��
	int c; // ��
} element;

// ������ ��Ÿ���� ����ü ����
typedef struct stack {
	element* data;
	int capacity; // ���� �뷮
	int top; // ������ �ֻ��� ����
} Stack;

// �����¿� �̵��� ���� ���� ����
const int DIR[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };

element entry = { 1,0 }; // �̷� �Ա� ��ġ
char maze[MAZE_SIZE][MAZE_SIZE] = { // �̷� ����
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
	{ 'm', '0', '0', '0', '1', '1', '1', '1', '1', '1' },
	{ '1', '1', '1', '0', '0', '0', '0', '1', '1', '1' },
	{ '1', '1', '0', '0', '1', '1', '1', '1', '1', '1' },
	{ '1', '1', '0', '1', '1', '1', '1', '0', '1', '1' },
	{ '1', '1', '0', '0', '0', '0', '1', '0', '1', '1' },
	{ '1', '1', '0', '1', '1', '0', '0', '0', '0', '1' },
	{ '1', '1', '0', '1', '1', '1', '1', '1', '0', '1' },
	{ '1', '1', '1', '1', '1', '1', '1', '1', '0', 'x' },
	{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
};

// ���� �ʱ�ȭ �Լ�
void initStack(Stack* s) {
	s->capacity = 1; // �ʱ� �뷮 ����
	s->top = -1; // �ʱ� top ����
	s->data = (element*)malloc(s->capacity * sizeof(element)); // malloc�̿��� ���� �޸� �Ҵ�
}

// ������ ������� Ȯ���ϴ� �Լ�
int empty(Stack* s) {
	return s->top == -1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int full(Stack* s) {
	return s->top == s->capacity - 1;
}

// ���ÿ� ��Ҹ� �߰��ϴ� �Լ�
void push(Stack* s, element value) {
	if (full(s)) {
		s->capacity *= 2; // ���� �뷮 �˳��� ����
		void* tmp = realloc(s->data, s->capacity * sizeof(element)); // ���Ҵ�
		if (tmp != NULL)
			s->data = (element*)tmp; // ���Ҵ� ���� �� ������ ������Ʈ
	}
	if (s->data != NULL)
		s->data[++s->top] = value; // top ������Ű�� ���ο� ��� �߰�

	printf("push element(s): ");
	for (int i = 0; i <= s->top; ++i) {
		printf("(%d,%d) ", s->data[i].r, s->data[i].c); // �߰��� ��� ���
	}
	printf("\n");
}

// ������ ����� �� ���� ���
void empty_error() {
	printf("Stack is empty...\n");
	exit(1);
}

// ���ÿ��� ��Ҹ� ������ �Լ�
element pop(Stack* s) {
	if (empty(s))
		empty_error(); // ������ ����� �� ������ ó��
	element popped = s->data[s->top--]; // top ���ҽ�Ű�� ���� ��ȯ

	printf("Stack after pop: ");
	for (int i = 0; i <= s->top; ++i) {
		printf("(%d,%d) ", s->data[i].r, s->data[i].c); // ���� ������ Ȯ���ϱ� ���� ��¹�
	}
	printf("\n");

	return popped;
}

// ������ �ֻ��� ���� Ȯ��
element peek(Stack* s) {
	if (empty(s))
		empty_error(); // ������ ����� �� ������ ó��
	return s->data[s->top];
}

// �̷� ��� �Լ�
void print_maze(const char(*maze)[MAZE_SIZE]) {
	// 2���� �迭��, ���� for�� ����
	for (int i = 0; i < MAZE_SIZE; ++i) { // �� ��ȸ
		for (int j = 0; j < MAZE_SIZE; ++j) // �� ��ȸ
			printf("%c", maze[i][j]);
		printf("\n");
	}
	printf("\n");
}

// Ư�� ��ġ�� ���ÿ� �߰��ϴ� �Լ�
int push_loc(Stack* s, int r, int c) {
	if (r < 0 || c < 0 || maze[r][c] == VISITED || maze[r][c] == FILLED) // ��ȿ���� ���� �������� Ȯ��
		return 0; // ��ȿ���� ���� ��� �߰����� ����

	push(s, (element) { r, c }); // ��ȿ�� ��ġ�� ���ÿ� �߰� ����
	return 1;
}

// �� ��ġ�� ���� ������ �ִ��� Ȯ���ϴ� �Լ�
int is_beside(element here, element top) {
	for (int i = 0; i < 4; ++i)
		if (here.r + DIR[i][0] == top.r && here.c + DIR[i][1] == top.c)
			return 1; // ������ �ִٸ� 1 ��ȯ
	return 0; // �ƴ϶�� 0 ��ȯ
}

void escapeMaze() {
	int r, c, i;
	Stack possible; // �ĺ� ���� ����
	Stack route; // �̵��� ��� ���� ����
	element here = entry; // �Ա����� ����

	initStack(&possible); // �ĺ� ��� ���� �ʱ�ȭ
	initStack(&route); // �̵��� ��� ���� �ʱ�ȭ
	while (maze[here.r][here.c] != 'x') { // �ⱸ(x) ã�� ������ �ݺ�
		r = here.r;
		c = here.c;
		maze[r][c] = VISITED; // ���� ��ġ�� �湮�� ������ ǥ��
		print_maze(maze); // ���� �̷� ���� ���

		int branch = 0;
		for (i = 0; i < 4; ++i)
			if (push_loc(&possible, r + DIR[i][0], c + DIR[i][1]))
				branch++; // �ĺ� ��� ���ÿ� �߰�

		// �߸� �� ���� ����
		if (branch == 0) {
			while (!is_beside(peek(&possible), peek(&route))) {
				element tmp = pop(&route); // ��� ���ÿ��� pop
				maze[tmp.r][tmp.c] = EMTPY; // �̷ο��� �ش� ��ġ�� empty�� �ٽ� ǥ��
			}
		}

		if (empty(&possible)) {
			printf("����\n"); // �ĺ� ��ΰ� �� �̻� ���� ��� ���� ó��
			return;
		}
		else {
			here = pop(&possible); // ���� �ĺ� ��� pop
			push(&route, here); // ��� ���ÿ� �߰�
		}

		printf("Remaining route: ");
		for (int i = 0; i <= possible.top; ++i) {
			printf("(%d,%d) ", possible.data[i].r, possible.data[i].c); // ������ ���� Ȯ�� ���� ��¹�
		}
		printf("\n");

	}
	printf("����\n"); // �ⱸ ã���� Ż�� ����
}

int main()
{
	escapeMaze(); // �̷� Ż�� �Լ� ����
	return 0;
}