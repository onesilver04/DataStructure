// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_1-B 24.05.09~13

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100;

// ���� ����Ʈ ��� ����
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// ����ü ����
typedef struct {
    Node* top;
} Stack;

// ���� �ʱ�ȭ �Լ�
void initializeStack(Stack* stack) {
    stack->top = NULL;
}

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

// ���ÿ� ���Ҹ� �߰��ϴ� �Լ�
void push(Stack* stack, int num) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // malloc�̿��Ͽ� �ʿ��� ������ ���ο� ��� ����
    newNode->data = num;
    newNode->next = stack->top;
    stack->top = newNode;
}

// ���ÿ��� ���Ҹ� �����ϰ� ��ȯ�ϴ� �Լ�
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack underflow\n"); // �� ������ ��� ������ ���
        exit(EXIT_FAILURE);
    }
    int data = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp); // free�� �������ν� �����ͻ� �̾ư� ���� �ʵ��� ��
    return data;
}

// ������ top ���� ��ȯ�ϴ� �Լ�
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack underflow\n"); // �� ������ ��� ������ ���
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// ���� ���� ��
int PIE(char ch) {
    switch (ch) {
    case '(':
    case '[':
    case '{':
        return 3; // ��ȣ�� �ֿ켱
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}

// ���� �� ��
int PIS(char ch) {
    switch (ch) {
    case '(':
    case '[':
    case '{':
        return 0; // ��ȣ�� ������
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    }
    return -1;
}


// ���� ǥ��� ������ ���� ǥ������� ��ȯ�ϴ� �Լ�
char* infixToPostfix(char infix[]) {
    int i = 0;
    char ch, top_op;
    int len = strlen(infix);
    char* postfix = (char*)malloc(sizeof(char) * (len * 2 + 1));
    Stack stack;
    initializeStack(&stack); // ���� �ʱ�ȭ
    int j = 0; // ����ǥ��� ���� �迭�� ���� j ����

    for (i = 0; i < len; i++) { // ���� ���̸�ŭ �ݺ�
        ch = infix[i];
        switch (ch) {
        case'+': case'-': case'*':case'/': // ������
            while (!isEmpty(&stack) && PIS(peek(&stack)) >= PIE(ch)) { // �������� ��� ISP�� ICP�� ����Ͽ� �켱������ ���Ͽ� ó��
                postfix[j++] = ' '; // �������� ���� ���� �߰�
                postfix[j++] = pop(&stack); // ���ÿ��� pop�� ���Ҹ� j�� ����
            }
            push(&stack, ch); // 
            postfix[j++] = ' ';
            break;

        case'(':case'{':case'[': // ���� ��ȣ�� ���
            push(&stack, ch); // ���ÿ� push
            break;
        case ')': case '}': case ']': // �ݴ� ��ȣ�� ���(��ȣ���� ¦�� �����ֱ�)
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

    while (!isEmpty(&stack)) { // ���ÿ� ���� ���ҵ��� ������ �� ������ ����
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
    initializeStack(&e, len); // ���� �ʱ�ȭ

    while (i < len) { // ���� ǥ��� ���̸�ŭ �ݺ�
        if (isdigit(postfix_exp[i])) { // ������ ��
            int value = 0;
            while (isdigit(postfix_exp[i])) {
                value = value * 10 + (postfix_exp[i] - '0'); // 10�� ���ؼ� value �ڸ��� �ø���, '0'���� �ƽ�Ű�ڵ� �̿�
                                                             // �ش� ���ڿ� �����ϴ� ���� ����
                i++; // ���� ���ڷ� �̵�
            }
            push(&e, value); // ������ ���� value�� ���ÿ� push
        }
        else if (postfix_exp[i] != ' ') { // ���ڰ� �ƴϸ鼭 ���鵵 �ƴ� ��� (������)
            op2 = pop(&e); // �ǿ�����2
            op1 = pop(&e); // �ǿ�����1
            switch (postfix_exp[i]) { // �����ڿ� �´� ���� ���� �� �ش� ����� ���ÿ� �ٽ� push
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
        i++; // ���� ���ڷ� �̵�
    }
    return pop(&e); // ���� ��� ��ȯ
}

int main() {
    char* infix_expression = "2*(10+15*3-5)+{[30/3-(4/2)*3]+8}+6";
    char* postfix_expression = infixToPostfix(infix_expression);
    printf("Postfix expression: %s\n", postfix_expression);
    int result = evaluatePostfix(postfix_expression);
    printf("��, ��� ����� %d\n", result);
    free(postfix_expression);
    return 0;
}
