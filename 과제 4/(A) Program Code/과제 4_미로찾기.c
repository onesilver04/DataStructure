// 인공지능공학부 2311613 한은정 (A) Program Code_미로찾기 24.05.20~24

#include <stdio.h>
#include <stdlib.h>

#define MAZE_SIZE 10 // 미로 크기
#define EMTPY '0' // 갈 수 있는 길
#define FILLED '1' // 벽으로 막힌 길
#define VISITED '.' // 이미 지나간 길

// 위치 표현 위한 구조체 정의
typedef struct {
	int r; // 행
	int c; // 열
} element;

// 스택을 나타내는 구조체 정의
typedef struct stack {
	element* data;
	int capacity; // 스택 용량
	int top; // 스택의 최상위 원소
} Stack;

// 상하좌우 이동을 위한 방향 벡터
const int DIR[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };

element entry = { 1,0 }; // 미로 입구 위치
char maze[MAZE_SIZE][MAZE_SIZE] = { // 미로 설정
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

// 스택 초기화 함수
void initStack(Stack* s) {
	s->capacity = 1; // 초기 용량 설정
	s->top = -1; // 초기 top 설정
	s->data = (element*)malloc(s->capacity * sizeof(element)); // malloc이용한 동적 메모리 할당
}

// 스택이 비었는지 확인하는 함수
int empty(Stack* s) {
	return s->top == -1;
}

// 스택이 가득 찼는지 확인하는 함수
int full(Stack* s) {
	return s->top == s->capacity - 1;
}

// 스택에 요소를 추가하는 함수
void push(Stack* s, element value) {
	if (full(s)) {
		s->capacity *= 2; // 스택 용량 넉넉히 증가
		void* tmp = realloc(s->data, s->capacity * sizeof(element)); // 재할당
		if (tmp != NULL)
			s->data = (element*)tmp; // 재할당 성공 시 포인터 업데이트
	}
	if (s->data != NULL)
		s->data[++s->top] = value; // top 증가시키고 새로운 요소 추가

	printf("push element(s): ");
	for (int i = 0; i <= s->top; ++i) {
		printf("(%d,%d) ", s->data[i].r, s->data[i].c); // 추가된 요소 출력
	}
	printf("\n");
}

// 스택이 비었을 때 오류 출력
void empty_error() {
	printf("Stack is empty...\n");
	exit(1);
}

// 스택에서 요소를 꺼내는 함수
element pop(Stack* s) {
	if (empty(s))
		empty_error(); // 스택이 비었을 때 오류로 처리
	element popped = s->data[s->top--]; // top 감소시키고 원소 반환

	printf("Stack after pop: ");
	for (int i = 0; i <= s->top; ++i) {
		printf("(%d,%d) ", s->data[i].r, s->data[i].c); // 스택 내용을 확인하기 위한 출력문
	}
	printf("\n");

	return popped;
}

// 스택의 최상위 원소 확인
element peek(Stack* s) {
	if (empty(s))
		empty_error(); // 스택이 비었을 때 오류로 처리
	return s->data[s->top];
}

// 미로 출력 함수
void print_maze(const char(*maze)[MAZE_SIZE]) {
	// 2차원 배열로, 이중 for문 실행
	for (int i = 0; i < MAZE_SIZE; ++i) { // 행 순회
		for (int j = 0; j < MAZE_SIZE; ++j) // 열 순회
			printf("%c", maze[i][j]);
		printf("\n");
	}
	printf("\n");
}

// 특정 위치를 스택에 추가하는 함수
int push_loc(Stack* s, int r, int c) {
	if (r < 0 || c < 0 || maze[r][c] == VISITED || maze[r][c] == FILLED) // 유효하지 않은 범위인지 확인
		return 0; // 유효하지 않은 경우 추가하지 않음

	push(s, (element) { r, c }); // 유효한 위치는 스택에 추가 가능
	return 1;
}

// 두 위치가 서로 인접해 있는지 확인하는 함수
int is_beside(element here, element top) {
	for (int i = 0; i < 4; ++i)
		if (here.r + DIR[i][0] == top.r && here.c + DIR[i][1] == top.c)
			return 1; // 인접해 있다면 1 반환
	return 0; // 아니라면 0 반환
}

void escapeMaze() {
	int r, c, i;
	Stack possible; // 후보 저장 스택
	Stack route; // 이동한 경로 저장 스택
	element here = entry; // 입구에서 시작

	initStack(&possible); // 후보 경로 스택 초기화
	initStack(&route); // 이동한 경로 스택 초기화
	while (maze[here.r][here.c] != 'x') { // 출구(x) 찾을 때까지 반복
		r = here.r;
		c = here.c;
		maze[r][c] = VISITED; // 현재 위치를 방문한 것으로 표시
		print_maze(maze); // 현재 미로 상태 출력

		int branch = 0;
		for (i = 0; i < 4; ++i)
			if (push_loc(&possible, r + DIR[i][0], c + DIR[i][1]))
				branch++; // 후보 경로 스택에 추가

		// 잘못 들어간 길은 삭제
		if (branch == 0) {
			while (!is_beside(peek(&possible), peek(&route))) {
				element tmp = pop(&route); // 경로 스택에서 pop
				maze[tmp.r][tmp.c] = EMTPY; // 미로에서 해당 위치를 empty로 다시 표시
			}
		}

		if (empty(&possible)) {
			printf("실패\n"); // 후보 경로가 더 이상 없을 경우 실패 처리
			return;
		}
		else {
			here = pop(&possible); // 다음 후보 경로 pop
			push(&route, here); // 경로 스택에 추가
		}

		printf("Remaining route: ");
		for (int i = 0; i <= possible.top; ++i) {
			printf("(%d,%d) ", possible.data[i].r, possible.data[i].c); // 스택의 내용 확인 위한 출력문
		}
		printf("\n");

	}
	printf("성공\n"); // 출구 찾으면 탈출 성공
}

int main()
{
	escapeMaze(); // 미로 탈출 함수 실행
	return 0;
}