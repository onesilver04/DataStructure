// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_2��° ���� 24.05.14~15

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

// ���
typedef struct {
    listNode* head;
} L;

// �̸� ����Ʈ 20��
char* names[20] = { "Kim", "Lee", "Choi", "Yoon", "Park", "Jung", "Kang", "Lim", "Hong", "Oh",
                 "Shin", "Song", "Hwang", "Han", "Kwon", "Jegal", "Cho", "Jang", "Moon", "Seo" };

// ���ο� ��� ���� �Լ�
listNode* createNode(int data, char* name) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // malloc�̿��ؼ� �ʿ��� ������ ���ο� ��� ����
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
    for (int i = 0; i < numNodes; i++) { // ��� ������ŭ �ݺ�
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
    if (head == NULL) { // ��尡 ��� �ִٸ�
        printf("����Ʈ�� ��� �ֽ��ϴ�.\n"); // �ȳ��� ���
        return;
    }
    listNode* current = head;
    do { // ���� ����Ʈ�� ��ȸ�ϸ� �����͸� �̵���Ű�鼭 ����
        printf("%d - %s\n", current->num, current->name); // ���
        current = current->right; // current�� ���������� �̵���Ŵ
    } while (current != head); // current�� ���� ���ƿ� ������ �ݺ�
    printf("\n"); // �������� ���� �߰�
}

// �ش� ���ڸ� ���� ��� ã��
listNode* findNode(listNode* head, int* target) { // target�� ��ǻ�Ͱ� �������� �� ���ڰ� �� ��
                                                  // ó�� ������ ���� ��� ã�� ����
    listNode* current = head;
    do {
        if (current->num == *target) { // target�� ã�Ҵٸ�
            return current; // �ش� ������ ��ȯ
        }
        current = current->right; // current�� ���������� �̵���Ŵ
    } while (current != head); // current�� ���� ���ƿ� ������ �ݺ�
    return NULL;
}

// Ȧ�� ��°�� ������ ��� ����
listNode* deleteRightNode(listNode* head, listNode* target) {
    if (head == NULL || target == NULL) {
        return head;
    }
    listNode* nodeToDelete = target->right;
    if (nodeToDelete == head) { // ������ ��尡 ����� ���
        head = head->right; // ��� �����͸� ���������� �̵���Ŵ
    }
    nodeToDelete->left->right = nodeToDelete->right; // ������ ��� ���ķ� ���� ��Ŵ
    nodeToDelete->right->left = nodeToDelete->left; // ����� ���� ���� ����Ʈ ����
    free(nodeToDelete); // free�� ���� ���� ����� �����ͻ� �̾� ����
    return head; // �������� ���� ��� ��ȯ
}

// ¦�� ��°�� ���� ��� ����
listNode* deleteLeftNode(listNode* head, listNode* target) {
    if (head == NULL || target == NULL) {
        return head;
    }
    listNode* nodeToDelete = target->left;
    if (nodeToDelete == head) { // ���� ��尡 ����� ���
        head = head->right; // ��� �����͸� ���������� �̵���Ŵ
    }
    nodeToDelete->left->right = nodeToDelete->right; // ������ ��� ���ķ� �����Ŵ
    nodeToDelete->right->left = nodeToDelete->left; // ����� ���� ���� ����Ʈ ����
    free(nodeToDelete); // free�� ���� ���� ����� �����ͻ� �̾� ����
    return head; // �������� ���� ��� ��ȯ
}

// ���� ����� ���
void printList(listNode* head) {
    if (head == NULL) { // ��尡 ����ִ� ���
        printf("����Ʈ�� ��� �ֽ��ϴ�.\n"); // �ȳ��� ���
        return;
    }
    listNode* current = head;
    do { // ����Ʈ ��ȸ�ϸ鼭 ���
        printf("%d - %s\n", current->num, current->name); // ���� ������ ���� ���
        current = current->right; // ������ ���������� �̵�
    } while (current != head); // �����Ͱ� ���� ���ƿ� ������ �ݺ�
    printf("\n"); // �������� ���� �߰�
}

int main() {
    listNode* C = createDoubleCircular(20); // 20���� ��� ����

    printf("Initial Doubly Circle Linked List:\n");
    printDoubleCircularLinkedList(C); // �ʱ� 20���� ��尡 ����� ����� ���� ����Ʈ ���

    srand(time(NULL));
    int randomNum = rand() % 20 + 1; // ���� ���� 1~20 ����
    for (int remainedNodes = 20; remainedNodes > 4; remainedNodes--) { // ���� ���(=remainedNodes)�� 4���� �� ������ �ݺ�
        listNode* targetNode = findNode(C, &randomNum); // ������ ���(�ش� ������) ã��

        if (remainedNodes % 2 == 0) { // �����ִ� ����� ������ ¦��=Ȧ����° Ƚ��
            printf("���� ���� ���: %d - %s\n", targetNode->num, targetNode->name); // ���� ���� ���� ����� ��� ���� ���
            listNode* removeRightPerson = targetNode->right; // �����ʿ� �ִ� ����� ����
            printf("���� ���: %d - %s\n", removeRightPerson->right->num, removeRightPerson->right->name); // ���ŵ� ����� ���� ���
            C = deleteRightNode(C, removeRightPerson); // ��� ����
            printf("���� �����:\n");
            printList(C);
            randomNum = removeRightPerson->num; // ���� ���� ����� ���� �������� Ʋ��
        }

        else { // ���� �ִ� ����� ������ Ȧ��=¦�� ��° Ƚ��
            printf("���� ���� ���: %d - %s\n", targetNode->num, targetNode->name); // ���� ���� ���� ����� ��� ���� ���
            listNode* removeLeftPerson = targetNode->left->left->left->left->left->left; // ���ʿ� �ִ� ����� ����
            printf("���� ���: %d - %s\n", removeLeftPerson->left->num, removeLeftPerson->left->name); // ���ŵ� ����� ���� ���
            C = deleteLeftNode(C, removeLeftPerson); // ��� ����
            printf("���� �����:\n");
            printList(C);
            randomNum = removeLeftPerson->num; // ���� ���� ����� ������ �������� Ʋ��
        }
    }
    printf("********LUCKY GUYS********\n"); // ���� 4�� ���
    printList(C);

    return 0;
}
