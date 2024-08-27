// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_1-A 24.05.08~13

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

typedef char element;

// ����ü ����
typedef struct {
    element data[MAX_SIZE];
    int top;
} Stack;

// stack �ʱ�ȭ func.
void init(Stack* s) {
    s->top = -1;
}

// stack ���� func.
int isEmpty(Stack* s) {
    return s->top == -1;
}

// stack ��ȭ Ȯ�� func.
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

// ���� �� �켱����
int PIS(char ch) {
    switch (ch) {
    case '(':
    case '[':
    case '{':
        return 0; // ��ȣ���� ������
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

// ���� �� ������ �켱����(���� ǥ��� ��ȯ ��)
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

// infix -> postfix�� ��ȯ�ϴ� �Լ�
void infix_to_postfix(const char exp[], char postfix[]) {
    char ch, top_op;
    int len = strlen(exp);
    Stack stack;
    init(&stack, len); // ���� �ʱ�ȭ
    int j = 0; // postfix�� array
    for (int i = 0; i < len; i++) { // infix�� ����(len)��ŭ �ݺ�
        ch = exp[i];
        switch (ch) {
        case '+': case '-': case '*': case '/': // �������� ��츦 case���� �̿�
            while (!isEmpty(&stack) && PIS(peek(&stack)) >= PIE(ch)) { // ���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
                postfix[j++] = ' '; // �������� ���� ���� �߰�
                postfix[j++] = pop(&stack); // ���ÿ��� pop�� ���� j�� �߰�
            }
            push(&stack, ch); // ���ÿ� ������ push
            postfix[j++] = ' '; // �������� ���� ���� �߰�
            break;
        
        // ���� ��ȣ�� �� ���ÿ� ������ push
        case'(':case'{':case'[':
            push(&stack, ch);
            break;

        // �ݴ� ��ȣ�� ��(��ȣ ¦���� �������)
        case ')': case '}': case ']':
            if (ch == ')') { // �Ұ�ȣ
                top_op = pop(&stack);
                while (top_op != '(') {
                    postfix[j++] = ' ';
                    postfix[j++] = top_op;
                    top_op = pop(&stack);
                }
            }
            else if (ch == '}') { // �߰�ȣ
                top_op = pop(&stack);
                while (top_op != '{') {
                    postfix[j++] = ' ';
                    postfix[j++] = top_op;
                    top_op = pop(&stack);
                }
            }
            else if (ch == ']') { // ���ȣ
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
    while (!isEmpty(&stack)) { // ���ÿ� ���� �ִ� ��ҵ� ��� ���
        postfix[j++] = ' ';
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
    return postfix;
}

// ���� ǥ�� ������ ����ϴ� �Լ�
int evaluatePostfix(char postfix_exp[]) {
    Stack e;
    int op1, op2, i = 0;
    int len = strlen(postfix_exp);
    init(&e, len); // ���� e �ʱ�ȭ
    while (i < len) { // ���� ǥ��� ���̸�ŭ �ݺ�
        if (isdigit(postfix_exp[i])) {
            int value = 0;
            while (isdigit(postfix_exp[i])) {
                value = value * 10 + (postfix_exp[i] - '0'); // 10�� ���ؼ� value�� �ڸ��� �ø���, '0'���� �ƽ�Ű�ڵ� �̿�
                                                             // �ش� ���ڿ� �����ϴ� ���� ����
                i++; // ���� ���� �б�
            }
            push(&e, value); // ������ ���� value�� ���ÿ� push
        }

        else if (postfix_exp[i] != ' ') { // ���ڰ� �ƴϸ鼭 ���鵵 �ƴ� ��� (=������) �ǿ����� �ΰ� pop�ϰ� ������ ��� �� ���ÿ� push
            op2 = pop(&e); // �ǿ����� 2
            op1 = pop(&e); // �ǿ����� 1
            switch (postfix_exp[i]) { // �����ڿ� �°� ���� ���� �� �� ����� ���� e�� �ٽ� push
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
        
        i++; // ���� ���� �б�
    }
    return pop(&e); // ���� ��� ��ȯ
}

int main() {
    char infix_exp[] = "[3*(20+10)]-{20/5+[4*2]/2}+8";
    char postfix_exp[100]; // ���� ǥ����� �˳��� ���ڷ� ũ�� ���س���
    printf("Postfix Expression: ");
    infix_to_postfix(infix_exp, postfix_exp);
    printf("%s\n", postfix_exp);
    printf("��, ��� ����� %d\n", evaluatePostfix(postfix_exp));
    return 0;
}