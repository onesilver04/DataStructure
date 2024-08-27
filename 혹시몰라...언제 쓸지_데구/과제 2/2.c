// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_2��° ���� 24.05.15
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ����ü ����
typedef struct listNode {
    int num;
    char name[20];
    struct listNode* right;
    struct listNode* left;
} listNode;

typedef struct {
    listNode* head;
} L;

// �̸� ����Ʈ
char* names[20] = { "Kim", "Lee", "Choi", "Yoon", "Park", "Jung", "Kang", "Lim", "Hong", "Oh",
                 "Shin", "Song", "Hwang", "Han", "Kwon", "Jegal", "Cho", "Jang", "Moon", "Seo" };

// ���ο� ��� ���� �Լ�
listNode* createNode(int data, char* name) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->num = data;
    strcpy(newNode->name, name);
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

// doubly circle linked list�� �����ϴ� �Լ�
listNode* createDoubleCircular(int numNodes) {
    listNode* head = NULL;
    listNode* tail = NULL;
    for (int i = 0; i < numNodes; i++) {
        char* name = names[i % 20]; // �̸� �迭�� ��ȯ�ϸ鼭 �̸� ����
        listNode* newNode = createNode(i + 1, name);

        if (head == NULL) { // head�� ����ٸ� head, tail �� �� �� ������
            head = newNode;
            tail = newNode;
        }
        else { // ��� ���� �ʴٸ�
            tail->right = newNode; // tail�� �����ʿ� ���ο� ��带 ����
            newNode->left = tail; // �� ����� ���ʸ�ũ�� tail�� ����
            tail = newNode;
        }
    }
    tail->right = head;
    head->left = tail;
    return head;
}

// �ʱ� ���� ���� ����Ʈ ���
void printDoubleCircularLinkedList(listNode* head) {
    if (head == NULL) {
        printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
        return;
    }
    listNode* current = head;
    do {
        printf("%d - %s\n", current->num, current->name);
        current = current->right;
    } while (current != head);
    printf("\n");
}

// �ش� ���ڸ� ���� ��� ã��
listNode* findNode(listNode* head, int* target) {
    listNode* current = head;
    do {
        if (current->num == *target) {
            return current;
        }
        current = current->right;
    } while (current != head);
    return NULL;
}

// Ȧ�� ��°�� ������ ��� ����
listNode* deleteRightNode(listNode* head, listNode* target) {
    if (head == NULL || target == NULL) {
        return head;
    }
    listNode* nodeToDelete = target->right; // Target node's right node is to be deleted
    if (nodeToDelete == head) {
        head = head->right;
    }
    nodeToDelete->left->right = nodeToDelete->right;
    nodeToDelete->right->left = nodeToDelete->left;
    free(nodeToDelete);
    return head;
}

// ¦�� ��°�� ���� ��� ����
listNode* deleteLeftNode(listNode* head, listNode* target) {
    if (head == NULL || target == NULL) {
        return head;
    }
    listNode* nodeToDelete = target->left; // Target node's left node is to be deleted
    if (nodeToDelete == head) {
        head = head->right;
    }
    nodeToDelete->left->right = nodeToDelete->right;
    nodeToDelete->right->left = nodeToDelete->left;
    free(nodeToDelete);
    return head;
}

// ���� ����� ���
void printList(listNode* head) {
    if (head == NULL) {
        printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
        return;
    }
    listNode* current = head;
    do {
        printf("%d - %s\n", current->num, current->name);
        current = current->right;
    } while (current != head);
    printf("\n");
}

int main() {
    listNode* C = createDoubleCircular(20);

    printf("Initial Doubly Circle Linked List:\n");
    printDoubleCircularLinkedList(C);

    srand(time(NULL));
    int randomNum = rand() % 20 + 1;
    for (int remainedNodes = 20; remainedNodes > 4; remainedNodes--) {
        listNode* targetNode = findNode(C, &randomNum); // ������ ��� ã��

        if (remainedNodes % 2 == 0) { // �����ִ� ����� ������ ¦��=Ȧ����° Ƚ��
            printf("���� ���� ���: %d - %s\n", targetNode->num, targetNode->name);
            listNode* removeRightPerson = targetNode->right; // �����ʿ� �ִ� ����� ����
            printf("���� ���: %d - %s\n", removeRightPerson->right->num, removeRightPerson->right->name);
            C = deleteRightNode(C, removeRightPerson);
            printf("���� �����:\n");
            printList(C);
            randomNum = removeRightPerson->num; // ���� ���� ����� ���� �������� Ʋ��
        }

        else { // ���� �ִ� ����� ������ Ȧ��=¦�� ��° Ƚ��
            printf("���� ���� ���: %d - %s\n", targetNode->num, targetNode->name);
            listNode* removeLeftPerson = targetNode->left->left->left->left->left->left; // ���ʿ� �ִ� ����� ����
            printf("���� ���: %d - %s\n", removeLeftPerson->left->num, removeLeftPerson->left->name);
            C = deleteLeftNode(C, removeLeftPerson);
            printf("���� �����:\n");
            printList(C);
            randomNum = removeLeftPerson->num; // ������ �������� Ʋ��
        }
    }
    printf("********LUCKY GUYS********\n");
    printList(C);

    return 0;
}
