// 인공지능공학부 2311613 한은정 (A) Program Code_1번째 게임 24.05.14~15

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
    newNode->link = NULL;
    return newNode;
}

// singly circle linked list를 생성하는 함수
listNode* createCircular(int numNodes) {
    listNode* p = NULL; // 현재 노드를 가리키는 포인터
    listNode* q = NULL; // 추가할 노드 가리키는 포인터
    for (int i = 0; i < numNodes; i++) { // 노드 개수만큼 반복
        char* name = names[i % 20]; // 이름 배열을 순환하면서 이름 선택
        listNode* newNode = createNode(i + 1, name);

        if (p == NULL) { // 현재 노드 p가 비었다면 p를 새 노드로 함
            p = newNode;
        }
        else { // 비어 있지 않다면 q를 전진시켜 p다음에 새로운 노드 생성
            q->link = newNode;
        }
        q = newNode; // q를 새로운 노드로 함
    }
    q->link = p; // 마지막 노드와 처음 노드를 연결하여 원형으로 만듦
    return p;
}

// 생성된 원형 연결 리스트를 출력하는 함수
void printCircularLinkedList(listNode* head) {
    if (head == NULL) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }
    listNode* current = head;
    do { // 원형 연결 리스트를 탐색하면서 출력
        printf("%d - %s\n", current->num, current->name); // 출력
        current = current->link; // 다음 노드로 이동
    } while (current != head); // current가 다시 헤드로 돌아오면 반복문 끝
    printf("\n"); // 출력문의 가독성을 위해 추가
}

// 랜덤으로 배정된 정수 target인 num에 해당하는 노드를 찾는 함수
listNode* findNode(listNode* head, int* target) { // 컴퓨터가 랜덤으로 정할 맨 처음 숫자(=target)
    listNode* current = head;

    do { // 원형 연결 리스트를 탐색하면서 해당 num을 가진 노드를 찾음
        if (current->num == *target) { // 찾고자 하는 숫자와 일치
            return current; // 해당 포인터 반환
        }
        current = current->link; // target을 찾기 위해 다음 노드로 이동
    } while (current != head); // current가 헤드로 돌아오면 반복문 끝
}

// 노드를 삭제하는 함수
listNode* deleteNode(listNode* head, listNode* target) {
    listNode* p = head; // 현재 원형 리스트의 첫 번째 노드   // head는 리스트의 1번째 노드 지칭함
    listNode* q = NULL; // 삭제할 노드
    
    if (p == target) { // 삭제 대상이 헤더 노드인 경우
        listNode* temp = head;
        while (temp->link != head) {
            temp = temp->link;
        }
        temp->link = head->link; // 마지막 노드의 링크를 두 번째 노드로 연결
                                 // 원형 연결 리스트 유지

        free(head); // 헤드 노드 free해줌으로써 데이터상 미아 방지
        return temp->link; // 새로운 헤드 반환
    }
    else { // 삭제 대상이 헤더가 아닌 경우
        while (p->link != target) { // target이 될 때까지
            p = p->link; // p를 다음 노드로 이동
        }
        // 일반적인 경우의 노드 삭제
        q = p->link; // 삭제할 노드
        p->link = q->link; // 노드의 연결 끊김
        free(q); // q를 free해줌으로써 데이터상 미아 방지
        return head; // 가독성을 위해 head 반환
    }
}

// 현재 원형 리스트에 남아 있는 것들 출력 함수
void printList(listNode* L) {
    listNode* temp = L;
    do {
        printf("%d - %s\n", temp->num, temp->name); // 출력
        temp = temp->link; // 다음 노드로 포인터 이동
    } while (temp != L); // 맨 처음으로 돌아올 때까지 반복
    printf("\n"); // 가독성을 위해 추가
}

int main() {
    // 20개의 노드로 구성된 원형 연결 리스트 생성
    listNode* C = createCircular(20);

    // 원형 연결 리스트 출력
    printf("Initial Singly Circle Linked List:\n");
    printCircularLinkedList(C);
    // 남은 노드의 개수를 나타내는 변수 설정
    int remainedNodes = 20;
    // 랜덤으로 num 선택
    srand(time(NULL));
    int randomNum = rand() % 20 + 1; // 1부터 20까지의 랜덤한 수 배정(처음 수건을 가질 사람 설정)

    for (remainedNodes = 20; remainedNodes > 4; remainedNodes--) { // 남은 노드의 개수가 4개가 될때까지 반복해서 노드 제거
        listNode* targetNode = findNode(C, &randomNum); // 선택한 num에 해당하는 노드 찾기
        printf("수건 가진 사람: %d - %s\n", targetNode->num, targetNode->name); // 수건 가진 사람 출력
        // 선택된 노드의 옆옆 노드 찾기(삭제될 노드 찾기)
        listNode* removePerson = targetNode->link->link; // 삭제될 노드에 포인터 걸기
        printf("빠진 사람: %d - %s\n", removePerson->num, removePerson->name);
        randomNum=removePerson->link->num; // 다음 숫자를 포인터로 표현
        // 노드 삭제
        C = deleteNode(C, removePerson);
        printf("남은 사람들:\n");
        printList(C);
    }
    printf("********LUCKY GUYS********\n"); // 최종 4인 출력
    printList(C);
    return 0;
}