// 인공지능공학부 2311613 한은정 (A) Program Code 24.05.14
// 수건의 위치가 정확히 출력됨
// 랜덤수가 이상함
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 구조체 정의
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

// 새로운 노드 생성 함수
struct listNode* createNode(int data, char*name) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->num = data;
    strcpy(newNode->name, name);    
    newNode->link = NULL;
    return newNode;
}

// 원형 연결 리스트를 생성하는 함수
struct listNode* createCircular(int numNodes) {

    struct listNode* p = NULL; // 현재 노드를 가리키는 포인터
    struct listNode* q = NULL; // 삭제할 노드 가리키는 포인터

    // 원형 연결 리스트 생성
    for (int i = 0; i < numNodes; i++) {
        char* name = names[i % 20]; // 이름 배열을 순환하면서 이름 선택
        listNode* newNode = createNode(i + 1, name);

        if (p == NULL) {
            p = newNode;
        }
        else {
            q->link = newNode;
        }

        q = newNode;
    }
    // 마지막 노드와 처음 노드를 연결하여 원형으로 만듭니다.
    q->link = p;
    return p;
}

// 생성된 원형 연결 리스트를 출력하는 함수
void printCircularLinkedList(listNode* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }
    listNode* current = head;
    // 원형 연결 리스트를 탐색하면서 출력
    do {
        printf("%d - %s\n", current->num, current->name);
        current = current->link;
    } while (current != head);
    printf("\n");
}

// 랜덤으로 배정된 정수 target인 num에 해당하는 노드를 찾는 함수
listNode* findNode(listNode* head, int target) {
    listNode* current = head;

    // 원형 연결 리스트를 탐색하면서 해당 num을 가진 노드를 찾음
    if (current->num == target) {
        return current;
    }
    current = current->link;
}

// 노드를 삭제하는 함수
listNode* deleteNode(listNode* head, listNode* target) {

    listNode* p = head; // 현재 원형 리스트의 첫 번째 노드   // head는 리스트의 1번째 노드 지칭함
    listNode* q = NULL; // 삭제할 노드

    // target찾을 떄까지 반복
    while (p->num != target->num) {// target->num은 삭제되기 전 노드의 숫자임
        q = p; // q에 p를 맡김
        p = p->link; // p는 다음 노드로 전진
    }
    printf("게임에서 빠질 사람: %d - %s\n", p->link->num, p->link->name);
    q = p->link; // q가 p 다음 노드로 이동
    p->link = q->link; // 노드의 연결 끊김
    q = p; // q와p는 같은 노드(=삭제된 다음 노드)를 가리키고 있다.
    return(q);
    while (p != head) {
        printf("%d - %s\n", p->num, p->name);
        break;
    }
    return head;
}

// 현재 원형 리스트에 남아 있는 것들 내림차순으로 출력 함수
void printList(listNode* L) {
    listNode* temp = L;
    do {
        printf("%d - %s\n", temp->num, temp->name);
        temp = temp->link;
    } while (temp != L);
    printf("\n");
}

int main() {
    // 20개의 노드로 구성된 원형 연결 리스트 생성
    listNode* C = createCircular(20);

    // 원형 연결 리스트 출력
    printf("초기 단방향 원형 연결 리스트:\n");
    printCircularLinkedList(C);

    // 남은 노드의 개수를 나타내는 변수 설정
    int remainedNodes = 20;

    // 랜덤으로 num 선택
    srand(time(NULL));
    int randomNum = rand() % 20 + 1; // 1부터 20까지의 랜덤한 수 배정(처음 수건을 가질 사람 설정)
    // 남은 노드의 개수가 4개가 될때까지 반복해서 노드 제거
    for (remainedNodes = 20; remainedNodes > 4; remainedNodes--) {
        // 선택한 num에 해당하는 노드 찾기
        listNode* targetNode = findNode(C, randomNum);
        printf("수건 가진 사람: %d - %s\n", targetNode->num, targetNode->name);

        // 선택된 노드의 옆옆 노드 찾기
        listNode* nextNextNode = targetNode->link;

        // 노드 삭제
        C = deleteNode(C, nextNextNode);
        printf("남은 사람들:\n");
        printList(C);
    }
    return 0;
}