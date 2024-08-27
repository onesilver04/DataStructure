// 인공지능공학부 2311613 한은정 (A) Program Code_2번째 게임 24.05.14~15

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

// 헤드
typedef struct {
    listNode* head;
} L;

// 이름 리스트 20개
char* names[20] = { "Kim", "Lee", "Choi", "Yoon", "Park", "Jung", "Kang", "Lim", "Hong", "Oh",
                 "Shin", "Song", "Hwang", "Han", "Kwon", "Jegal", "Cho", "Jang", "Moon", "Seo" };

// 새로운 노드 생성 함수
listNode* createNode(int data, char* name) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode)); // malloc이용해서 필요할 때마다 새로운 노드 생성
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
    for (int i = 0; i < numNodes; i++) { // 노드 개수만큼 반복
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
    if (head == NULL) { // 헤드가 비어 있다면
        printf("리스트가 비어 있습니다.\n"); // 안내문 출력
        return;
    }
    listNode* current = head;
    do { // 원형 리스트를 순회하며 포인터를 이동시키면서 읽음
        printf("%d - %s\n", current->num, current->name); // 출력
        current = current->right; // current를 오른쪽으로 이동시킴
    } while (current != head); // current가 헤드로 돌아올 때까지 반복
    printf("\n"); // 가독성을 위해 추가
}

// 해당 숫자를 가진 노드 찾기
listNode* findNode(listNode* head, int* target) { // target은 컴퓨터가 랜덤으로 고른 숫자가 될 것
                                                  // 처음 수건을 가질 노드 찾는 과정
    listNode* current = head;
    do {
        if (current->num == *target) { // target을 찾았다면
            return current; // 해당 포인터 반환
        }
        current = current->right; // current를 오른쪽으로 이동시킴
    } while (current != head); // current가 헤드로 돌아올 때까지 반복
    return NULL;
}

// 홀수 번째에 오른쪽 노드 삭제
listNode* deleteRightNode(listNode* head, listNode* target) {
    if (head == NULL || target == NULL) {
        return head;
    }
    listNode* nodeToDelete = target->right;
    if (nodeToDelete == head) { // 삭제할 노드가 헤드인 경우
        head = head->right; // 헤드 포인터를 오른쪽으로 이동시킴
    }
    nodeToDelete->left->right = nodeToDelete->right; // 삭제할 노드 전후로 연결 시킴
    nodeToDelete->right->left = nodeToDelete->left; // 양방향 원형 연결 리스트 유지
    free(nodeToDelete); // free를 통해 삭제 노드의 데이터상 미아 방지
    return head; // 가독성을 위해 헤드 반환
}

// 짝수 번째에 왼쪽 노드 삭제
listNode* deleteLeftNode(listNode* head, listNode* target) {
    if (head == NULL || target == NULL) {
        return head;
    }
    listNode* nodeToDelete = target->left;
    if (nodeToDelete == head) { // 삭제 노드가 헤드인 경우
        head = head->right; // 헤드 포인터를 오른쪽으로 이동시킴
    }
    nodeToDelete->left->right = nodeToDelete->right; // 삭제할 노드 전후로 연결시킴
    nodeToDelete->right->left = nodeToDelete->left; // 양방향 원형 연결 리스트 유지
    free(nodeToDelete); // free를 통해 삭제 노드의 데이터상 미아 방지
    return head; // 가독성을 위해 헤드 반환
}

// 남은 사람들 출력
void printList(listNode* head) {
    if (head == NULL) { // 헤드가 비어있는 경우
        printf("리스트가 비어 있습니다.\n"); // 안내문 출력
        return;
    }
    listNode* current = head;
    do { // 리스트 순회하면서 출력
        printf("%d - %s\n", current->num, current->name); // 현재 포인터 내용 출력
        current = current->right; // 포인터 오른쪽으로 이동
    } while (current != head); // 포인터가 헤드로 돌아올 때까지 반복
    printf("\n"); // 가독성을 위해 추가
}

int main() {
    listNode* C = createDoubleCircular(20); // 20개의 노드 생성

    printf("Initial Doubly Circle Linked List:\n");
    printDoubleCircularLinkedList(C); // 초기 20개의 노드가 연결된 양방향 연결 리스트 출력

    srand(time(NULL));
    int randomNum = rand() % 20 + 1; // 랜덤 숫자 1~20 생성
    for (int remainedNodes = 20; remainedNodes > 4; remainedNodes--) { // 남은 노드(=remainedNodes)가 4개가 될 때까지 반복
        listNode* targetNode = findNode(C, &randomNum); // 삭제할 노드(해당 포인터) 찾기

        if (remainedNodes % 2 == 0) { // 남아있는 노드의 개수가 짝수=홀수번째 횟수
            printf("수건 가진 사람: %d - %s\n", targetNode->num, targetNode->name); // 현재 수건 가진 사람의 노드 내용 출력
            listNode* removeRightPerson = targetNode->right; // 오른쪽에 있는 사람이 제거
            printf("빠진 사람: %d - %s\n", removeRightPerson->right->num, removeRightPerson->right->name); // 제거될 노드의 내용 출력
            C = deleteRightNode(C, removeRightPerson); // 노드 제거
            printf("남은 사람들:\n");
            printList(C);
            randomNum = removeRightPerson->num; // 수건 가진 사람을 왼쪽 방향으로 틀기
        }

        else { // 남아 있는 노드의 개수가 홀수=짝수 번째 횟수
            printf("수건 가진 사람: %d - %s\n", targetNode->num, targetNode->name); // 현재 수건 가진 사람의 노드 내용 출력
            listNode* removeLeftPerson = targetNode->left->left->left->left->left->left; // 왼쪽에 있는 사람이 제거
            printf("빠진 사람: %d - %s\n", removeLeftPerson->left->num, removeLeftPerson->left->name); // 제거될 노드의 내용 출력
            C = deleteLeftNode(C, removeLeftPerson); // 노드 제거
            printf("남은 사람들:\n");
            printList(C);
            randomNum = removeLeftPerson->num; // 수건 가진 사람을 오른쪽 방향으로 틀기
        }
    }
    printf("********LUCKY GUYS********\n"); // 최종 4인 출력
    printList(C);

    return 0;
}
