// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_1��° ���� 24.05.14~15

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
    newNode->link = NULL;
    return newNode;
}

// singly circle linked list�� �����ϴ� �Լ�
listNode* createCircular(int numNodes) {
    listNode* p = NULL; // ���� ��带 ����Ű�� ������
    listNode* q = NULL; // �߰��� ��� ����Ű�� ������
    for (int i = 0; i < numNodes; i++) { // ��� ������ŭ �ݺ�
        char* name = names[i % 20]; // �̸� �迭�� ��ȯ�ϸ鼭 �̸� ����
        listNode* newNode = createNode(i + 1, name);

        if (p == NULL) { // ���� ��� p�� ����ٸ� p�� �� ���� ��
            p = newNode;
        }
        else { // ��� ���� �ʴٸ� q�� �������� p������ ���ο� ��� ����
            q->link = newNode;
        }
        q = newNode; // q�� ���ο� ���� ��
    }
    q->link = p; // ������ ���� ó�� ��带 �����Ͽ� �������� ����
    return p;
}

// ������ ���� ���� ����Ʈ�� ����ϴ� �Լ�
void printCircularLinkedList(listNode* head) {
    if (head == NULL) {
        printf("����Ʈ�� ��� �ֽ��ϴ�.\n");
        return;
    }
    listNode* current = head;
    do { // ���� ���� ����Ʈ�� Ž���ϸ鼭 ���
        printf("%d - %s\n", current->num, current->name); // ���
        current = current->link; // ���� ���� �̵�
    } while (current != head); // current�� �ٽ� ���� ���ƿ��� �ݺ��� ��
    printf("\n"); // ��¹��� �������� ���� �߰�
}

// �������� ������ ���� target�� num�� �ش��ϴ� ��带 ã�� �Լ�
listNode* findNode(listNode* head, int* target) { // ��ǻ�Ͱ� �������� ���� �� ó�� ����(=target)
    listNode* current = head;

    do { // ���� ���� ����Ʈ�� Ž���ϸ鼭 �ش� num�� ���� ��带 ã��
        if (current->num == *target) { // ã���� �ϴ� ���ڿ� ��ġ
            return current; // �ش� ������ ��ȯ
        }
        current = current->link; // target�� ã�� ���� ���� ���� �̵�
    } while (current != head); // current�� ���� ���ƿ��� �ݺ��� ��
}

// ��带 �����ϴ� �Լ�
listNode* deleteNode(listNode* head, listNode* target) {
    listNode* p = head; // ���� ���� ����Ʈ�� ù ��° ���   // head�� ����Ʈ�� 1��° ��� ��Ī��
    listNode* q = NULL; // ������ ���
    
    if (p == target) { // ���� ����� ��� ����� ���
        listNode* temp = head;
        while (temp->link != head) {
            temp = temp->link;
        }
        temp->link = head->link; // ������ ����� ��ũ�� �� ��° ���� ����
                                 // ���� ���� ����Ʈ ����

        free(head); // ��� ��� free�������ν� �����ͻ� �̾� ����
        return temp->link; // ���ο� ��� ��ȯ
    }
    else { // ���� ����� ����� �ƴ� ���
        while (p->link != target) { // target�� �� ������
            p = p->link; // p�� ���� ���� �̵�
        }
        // �Ϲ����� ����� ��� ����
        q = p->link; // ������ ���
        p->link = q->link; // ����� ���� ����
        free(q); // q�� free�������ν� �����ͻ� �̾� ����
        return head; // �������� ���� head ��ȯ
    }
}

// ���� ���� ����Ʈ�� ���� �ִ� �͵� ��� �Լ�
void printList(listNode* L) {
    listNode* temp = L;
    do {
        printf("%d - %s\n", temp->num, temp->name); // ���
        temp = temp->link; // ���� ���� ������ �̵�
    } while (temp != L); // �� ó������ ���ƿ� ������ �ݺ�
    printf("\n"); // �������� ���� �߰�
}

int main() {
    // 20���� ���� ������ ���� ���� ����Ʈ ����
    listNode* C = createCircular(20);

    // ���� ���� ����Ʈ ���
    printf("Initial Singly Circle Linked List:\n");
    printCircularLinkedList(C);
    // ���� ����� ������ ��Ÿ���� ���� ����
    int remainedNodes = 20;
    // �������� num ����
    srand(time(NULL));
    int randomNum = rand() % 20 + 1; // 1���� 20������ ������ �� ����(ó�� ������ ���� ��� ����)

    for (remainedNodes = 20; remainedNodes > 4; remainedNodes--) { // ���� ����� ������ 4���� �ɶ����� �ݺ��ؼ� ��� ����
        listNode* targetNode = findNode(C, &randomNum); // ������ num�� �ش��ϴ� ��� ã��
        printf("���� ���� ���: %d - %s\n", targetNode->num, targetNode->name); // ���� ���� ��� ���
        // ���õ� ����� ���� ��� ã��(������ ��� ã��)
        listNode* removePerson = targetNode->link->link; // ������ ��忡 ������ �ɱ�
        printf("���� ���: %d - %s\n", removePerson->num, removePerson->name);
        randomNum=removePerson->link->num; // ���� ���ڸ� �����ͷ� ǥ��
        // ��� ����
        C = deleteNode(C, removePerson);
        printf("���� �����:\n");
        printList(C);
    }
    printf("********LUCKY GUYS********\n"); // ���� 4�� ���
    printList(C);
    return 0;
}