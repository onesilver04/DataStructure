// 인공지능공학부 2311613 한은정 (A) Program Code_1-A 24.05.08~13

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

typedef char element;

// 구조체 정의
typedef struct {
    element data[MAX_SIZE];
    int top;
} Stack;

// stack 초기화 func.
void init(Stack* s) {
    s->top = -1;
}

// stack 공백 func.
int isEmpty(Stack* s) {
    return s->top == -1;
}

// stack 포화 확인 func.
int is_full(Stack* s) {
    return (s->top == (MAX_SIZE - 1));
}

// push func.
void push(Stack* s, element value) {
    if (is_full(s)) {
        return;
    }
    else s->data[++s->top] = value;
}

// pop func.
element pop(Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }
    else return s->data[(s->top)--];
}

// peek func.
element peek(Stack* s) {
    if (isEmpty(s)) {
        return -1;
    }
    else return s->data[s->top];
}

// 스택 내 우선순위
int PIS(char ch) {
    switch (ch) {
    case '(':
    case '[':
    case '{':
        return 0; // 괄호들은 최하위
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

// 수식 내 연산자 우선순위(후위 표기식 변환 전)
int PIE(char ch) {
    switch (ch) {
    case '(':
    case '[':
    case '{':
        return 3;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

// infix -> postfix로 변환하는 함수
void infix_to_postfix(const char exp[], char postfix[]) {
    char ch, top_op;
    int len = strlen(exp);
    Stack stack;
    init(&stack, len); // 스택 초기화
    int j = 0; // postfix의 array
    for (int i = 0; i < len; i++) { // infix의 길이(len)만큼 반복
        ch = exp[i];
        switch (ch) {
        case '+': case '-': case '*': case '/': // 연산자인 경우를 case문을 이용
            while (!isEmpty(&stack) && PIS(peek(&stack)) >= PIE(ch)) { // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
                postfix[j++] = ' '; // 가독성을 위해 공백 추가
                postfix[j++] = pop(&stack); // 스택에서 pop한 것을 j에 추가
            }
            push(&stack, ch); // 스택에 연산자 push
            postfix[j++] = ' '; // 가독성을 위해 공백 추가
            break;
        
        // 여는 괄호일 때 스택에 무조건 push
        case'(':case'{':case'[':
            push(&stack, ch);
            break;

        // 닫는 괄호일 때(괄호 짝마다 맞춰야함)
        case ')': case '}': case ']':
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
    while (!isEmpty(&stack)) { // 스택에 남아 있는 요소들 모두 출력
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
    init(&e, len); // 스택 e 초기화
    while (i < len) { // 후위 표기식 길이만큼 반복
        if (isdigit(postfix_exp[i])) {
            int value = 0;
            while (isdigit(postfix_exp[i])) {
                value = value * 10 + (postfix_exp[i] - '0'); // 10을 곱해서 value의 자릿수 올리고, '0'으로 아스키코드 이용
                                                             // 해당 문자에 대응하는 숫자 얻음
                i++; // 다음 문자 읽기
            }
            push(&e, value); // 위에서 얻은 value를 스택에 push
        }

        else if (postfix_exp[i] != ' ') { // 숫자가 아니면서 공백도 아닌 경우 (=연산자) 피연산자 두개 pop하고 연산자 계산 후 스택에 push
            op2 = pop(&e); // 피연산자 2
            op1 = pop(&e); // 피연산자 1
            switch (postfix_exp[i]) { // 연산자에 맞게 연산 실행 후 그 결과를 스택 e에 다시 push
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
        
        i++; // 다음 문자 읽기
    }
    return pop(&e); // 최종 결과 반환
}

int main() {
    char infix_exp[] = "[3*(20+10)]-{20/5+[4*2]/2}+8";
    char postfix_exp[100]; // 후위 표기식은 넉넉한 숫자로 크기 정해놓음
    printf("Postfix Expression: ");
    infix_to_postfix(infix_exp, postfix_exp);
    printf("%s\n", postfix_exp);
    printf("즉, 계산 결과는 %d\n", evaluatePostfix(postfix_exp));
    return 0;
}