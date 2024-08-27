// �ΰ����ɰ��к� 2311613 ������ (A) Program Code 24.05.14
// ������ ��ġ�� ��Ȯ�� ��µ�
// �������� �̻���
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ����ü ����
typedef struct listNode {
    int num;
    char name[20];
    struct listNode* link;
} listNode;

typedef struct {
    listNode* head;
}L;

char* names[20] = { "Kim", "Lee", "Choi", "Yoon", "Park", "Jung", "Kang", "Lim", "Hong", "Oh",
                 "Shin", "Song", "Hwang", "Han", "Kwon", "Jegal", "Cho", "Jang", "Moon", "Seo" };

// ���ο� ��� ���� �Լ�
struct listNode* createNode(int data, char*name) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->num = data;
    strcpy(newNode->name, name);    
    newNode->link = NULL;
    return newNode;
}

// ���� ���� ����Ʈ�� �����ϴ� �Լ�
struct listNode* createCircular(int numNodes) {

    struct listNode* p = NULL; // ���� ��带 ����Ű�� ������
    struct listNode* q = NULL; // ������ ��� ����Ű�� ������

    // ���� ���� ����Ʈ ����
    for (int i = 0; i < numNodes; i++) {
        char* name = names[i % 20]; // �̸� �迭�� ��ȯ�ϸ鼭 �̸� ����
        listNode* newNode = createNode(i + 1, name);

        if (p == NULL) {
            p = newNode;
        }
        else {
            q->link = newNode;
        }

        q = newNode;
    }
    // ������ ���� ó�� ��带 �����Ͽ� �������� ����ϴ�.
    q->link = p;
    return p;
}

// ������ ���� ���� ����Ʈ�� ����ϴ� �Լ�
void printCircularLinkedList(listNode* head) {
    if (head == NULL) {
        printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
        return;
    }
    listNode* current = head;
    // ���� ���� ����Ʈ�� Ž���ϸ鼭 ���
    do {
        printf("%d - %s\n", current->num, current->name);
        current = current->link;
    } while (current != head);
    printf("\n");
}

// �������� ������ ���� target�� num�� �ش��ϴ� ��带 ã�� �Լ�
listNode* findNode(listNode* head, int target) {
    listNode* current = head;

    // ���� ���� ����Ʈ�� Ž���ϸ鼭 �ش� num�� ���� ��带 ã��
    if (current->num == target) {
        return current;
    }
    current = current->link;
}

// ��带 �����ϴ� �Լ�
listNode* deleteNode(listNode* head, listNode* target) {

    listNode* p = head; // ���� ���� ����Ʈ�� ù ��° ���   // head�� ����Ʈ�� 1��° ��� ��Ī��
    listNode* q = NULL; // ������ ���

    // targetã�� ������ �ݺ�
    while (p->num != target->num) {// target->num�� �����Ǳ� �� ����� ������
        q = p; // q�� p�� �ñ�
        p = p->link; // p�� ���� ���� ����
    }
    printf("���ӿ��� ���� ���: %d - %s\n", p->link->num, p->link->name);
    q = p->link; // q�� p ���� ���� �̵�
    p->link = q->link; // ����� ���� ����
    q = p; // q��p�� ���� ���(=������ ���� ���)�� ����Ű�� �ִ�.
    return(q);
    while (p != head) {
        printf("%d - %s\n", p->num, p->name);
        break;
    }
    return head;
}

// ���� ���� ����Ʈ�� ���� �ִ� �͵� ������������ ��� �Լ�
void printList(listNode* L) {
    listNode* temp = L;
    do {
        printf("%d - %s\n", temp->num, temp->name);
        temp = temp->link;
    } while (temp != L);
    printf("\n");
}

int main() {
    // 20���� ���� ������ ���� ���� ����Ʈ ����
    listNode* C = createCircular(20);

    // ���� ���� ����Ʈ ���
    printf("�ʱ� �ܹ��� ���� ���� ����Ʈ:\n");
    printCircularLinkedList(C);

    // ���� ����� ������ ��Ÿ���� ���� ����
    int remainedNodes = 20;

    // �������� num ����
    srand(time(NULL));
    int randomNum = rand() % 20 + 1; // 1���� 20������ ������ �� ����(ó�� ������ ���� ��� ����)
    // ���� ����� ������ 4���� �ɶ����� �ݺ��ؼ� ��� ����
    for (remainedNodes = 20; remainedNodes > 4; remainedNodes--) {
        // ������ num�� �ش��ϴ� ��� ã��
        listNode* targetNode = findNode(C, randomNum);
        printf("���� ���� ���: %d - %s\n", targetNode->num, targetNode->name);

        // ���õ� ����� ���� ��� ã��
        listNode* nextNextNode = targetNode->link;

        // ��� ����
        C = deleteNode(C, nextNextNode);
        printf("���� �����:\n");
        printList(C);
    }
    return 0;
}