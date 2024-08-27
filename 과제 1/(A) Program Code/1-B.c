// 인공지능공학부 2311613 한은정 (A) Program Code_1-B 24.05.09~13

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100;

// 연결 리스트 노드 정의
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 구조체 정의
typedef struct {
    Node* top;
} Stack;

// 스택 초기화 함수
void initializeStack(Stack* stack) {
    stack->top = NULL;
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// 스택에 원소를 추가하는 함수
void push(Stack* stack, int num) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // malloc이용하여 필요할 때마다 새로운 노드 생성
    newNode->data = num;
    newNode->next = stack->top;
    stack->top = newNode;
}

// 스택에서 원소를 제거하고 반환하는 함수
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack underflow\n"); // 빈 스택일 경우 에러문 출력
        exit(EXIT_FAILURE);
    }
    int data = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp); // free를 해줌으로써 데이터상 미아가 되지 않도록 함
    return data;
}

// 스택의 top 값을 반환하는 함수
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack underflow\n"); // 빈 스택일 경우 에러문 출력
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// 스택 들어가기 전
int PIE(char ch) {
    switch (ch) {
    case '(':
    case '[':
    case '{':
        return 3; // 괄호는 최우선
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

// 스택 들어간 후
int PIS(char ch) {
    switch (ch) {
    case '(':
    case '[':
    case '{':
        return 0; // 괄호는 최하위
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}


// 중위 표기법 수식을 후위 표기법으로 변환하는 함수
char* infixToPostfix(char infix[]) {
    int i = 0;
    char ch, top_op;
    int len = strlen(infix);
    char* postfix = (char*)malloc(sizeof(char) * (len * 2 + 1));
    Stack stack;
    initializeStack(&stack); // 스택 초기화
    int j = 0; // 후위표기식 담을 배열을 위해 j 정의

    for (i = 0; i < len; i++) { // 식의 길이만큼 반복
        ch = infix[i];
        switch (ch) {
        case'+': case'-': case'*':case'/': // 연산자
            while (!isEmpty(&stack) && PIS(peek(&stack)) >= PIE(ch)) { // 연산자일 경우 ISP와 ICP를 사용하여 우선순위를 비교하여 처리
                postfix[j++] = ' '; // 가독성을 위해 공백 추가
                postfix[j++] = pop(&stack); // 스택에서 pop한 원소를 j에 넣음
            }
            push(&stack, ch); // 
            postfix[j++] = ' ';
            break;

        case'(':case'{':case'[': // 여는 괄호일 경우
            push(&stack, ch); // 스택에 push
            break;
        case ')': case '}': case ']': // 닫는 괄호일 경우(괄호마다 짝을 맞춰주기)
            if (ch == ')') { // 소괄호
                top_op = pop(&stack);
                while (top_op != '(') {
                    postfix[j++] = ' ';
                    postfix[j++] = top_op;
                    top_op = pop(&stack);
                }
            }
            else if (ch == '}') { // 중괄호
                top_op = pop(&stack);
                while (top_op != '{') {
                    postfix[j++] = ' ';
                    postfix[j++] = top_op;
                    top_op = pop(&stack);
                }
            }
            else if (ch == ']') { // 대괄호
                top_op = pop(&stack);
                while (top_op != '[') {
                    postfix[j++] = ' ';
                    postfix[j++] = top_op;
                    top_op = pop(&stack);
                }
            }
            break;
        default:
            postfix[j++] = ch;
            break;

        }
    }

    while (!isEmpty(&stack)) { // 스택에 남은 원소들을 스택이 빌 때까지 꺼냄
        postfix[j++] = ' ';
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
    return postfix;
}

// 후위 표기 수식을 계산하는 함수
int evaluatePostfix(char postfix_exp[]) {
    Stack e;
    int op1, op2, i = 0;
    int len = strlen(postfix_exp);
    initializeStack(&e, len); // 스택 초기화

    while (i < len) { // 후위 표기식 길이만큼 반복
        if (isdigit(postfix_exp[i])) { // 숫자일 때
            int value = 0;
            while (isdigit(postfix_exp[i])) {
                value = value * 10 + (postfix_exp[i] - '0'); // 10을 곱해서 value 자릿수 올리고, '0'으로 아스키코드 이용
                                                             // 해당 문자에 대응하는 숫자 얻음
                i++; // 다음 문자로 이동
            }
            push(&e, value); // 위에서 얻은 value를 스택에 push
        }
        else if (postfix_exp[i] != ' ') { // 숫자가 아니면서 공백도 아닌 경우 (연산자)
            op2 = pop(&e); // 피연산자2
            op1 = pop(&e); // 피연산자1
            switch (postfix_exp[i]) { // 연산자에 맞는 연산 실행 후 해당 결과를 스택에 다시 push
            case '+':
                push(&e, op1 + op2);
                break;
            case '-':
                push(&e, op1 - op2);
                break;
            case '*':
                push(&e, op1 * op2);
                break;
            case '/':
                push(&e, op1 / op2);
                break;
            }
        }
        i++; // 다음 문자로 이동
    }
    return pop(&e); // 최종 결과 반환
}

int main() {
    char* infix_expression = "2*(10+15*3-5)+{[30/3-(4/2)*3]+8}+6";
    char* postfix_expression = infixToPostfix(infix_expression);
    printf("Postfix expression: %s\n", postfix_expression);
    int result = evaluatePostfix(postfix_expression);
    printf("즉, 계산 결과는 %d\n", result);
    free(postfix_expression);
    return 0;
}
