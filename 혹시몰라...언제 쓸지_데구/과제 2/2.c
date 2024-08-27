// 인공지능공학부 2311613 한은정 (A) Program Code_2번째 게임 24.05.15
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 구조체 정의
typedef struct listNode {
    int num;
    char name[20];
    struct listNode* right;
    struct listNode* left;
} listNode;

typedef struct {
    listNode* head;
} L;

// 이름 리스트
char* names[20] = { "Kim", "Lee", "Choi", "Yoon", "Park", "Jung", "Kang", "Lim", "Hong", "Oh",
                 "Shin", "Song", "Hwang", "Han", "Kwon", "Jegal", "Cho", "Jang", "Moon", "Seo" };

// 새로운 노드 생성 함수
listNode* createNode(int data, char* name) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->num = data;
    strcpy(newNode->name, name);
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

// doubly circle linked list를 생성하는 함수
listNode* createDoubleCircular(int numNodes) {
    listNode* head = NULL;
    listNode* tail = NULL;
    for (int i = 0; i < numNodes; i++) {
        char* name = names[i % 20]; // 이름 배열을 순환하면서 이름 선택
        listNode* newNode = createNode(i + 1, name);

        if (head == NULL) { // head가 비었다면 head, tail 둘 다 새 노드로함
            head = newNode;
            tail = newNode;
        }
        else { // 비어 있지 않다면
            tail->right = newNode; // tail의 오른쪽에 새로운 노드를 생성
            newNode->left = tail; // 새 노드의 왼쪽링크를 tail로 지정
            tail = newNode;
        }
    }
    tail->right = head;
    head->left = tail;
    return head;
}

// 초기 원형 연결 리스트 출력
void printDoubleCircularLinkedList(listNode* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }
    listNode* current = head;
    do {
        printf("%d - %s\n", current->num, current->name);
        current = current->right;
    } while (current != head);
    printf("\n");
}

// 해당 숫자를 가진 노드 찾기
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

// 홀수 번째에 오른쪽 노드 삭제
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

// 짝수 번째에 왼쪽 노드 삭제
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

// 남은 사람들 출력
void printList(listNode* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다.\n");
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
        listNode* targetNode = findNode(C, &randomNum); // 삭제할 노드 찾기

        if (remainedNodes % 2 == 0) { // 남아있는 노드의 개수가 짝수=홀수번째 횟수
            printf("수건 가진 사람: %d - %s\n", targetNode->num, targetNode->name);
            listNode* removeRightPerson = targetNode->right; // 오른쪽에 있는 사람이 제거
            printf("빠진 사람: %d - %s\n", removeRightPerson->right->num, removeRightPerson->right->name);
            C = deleteRightNode(C, removeRightPerson);
            printf("남은 사람들:\n");
            printList(C);
            randomNum = removeRightPerson->num; // 수건 가진 사람을 왼쪽 방향으로 틀기
        }

        else { // 남아 있는 노드의 개수가 홀수=짝수 번째 횟수
            printf("수건 가진 사람: %d - %s\n", targetNode->num, targetNode->name);
            listNode* removeLeftPerson = targetNode->left->left->left->left->left->left; // 왼쪽에 있는 사람이 제거
            printf("빠진 사람: %d - %s\n", removeLeftPerson->left->num, removeLeftPerson->left->name);
            C = deleteLeftNode(C, removeLeftPerson);
            printf("남은 사람들:\n");
            printList(C);
            randomNum = removeLeftPerson->num; // 오른쪽 방향으로 틀기
        }
    }
    printf("********LUCKY GUYS********\n");
    printList(C);

    return 0;
}
