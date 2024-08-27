// 인공지능공학부 2311613 한은정 (A) Program Code_정렬 24.05.17~18

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* link;
} Node;

// 새로운 노드 생성 함수
Node* createNode(int num) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = num;
    newNode->link = NULL;
    return newNode;
}

// 리스트의 끝에 노드를 추가하는 함수
void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) { // 리스트가 비어 있는 경우
        *head = newNode; // 새로운 노드를 헤드로 설정
    }
    else { // 리스트가 비어 있지 않은 경우
        Node* temp = *head; // 임시 노드로 헤드 설정
        while (temp->link != NULL) { // 리스트의 끝까지 탐색
            temp = temp->link; // 다음 노드로 이동
        }
        temp->link = newNode; // 마지막 노드에 새로운 노드 연결
    }
}

// 리스트 출력 함수
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) { // 리스트 끝까지 출력
        printf("%d ", temp->data); // 현재 포인터가 가리키는 data 출력
        temp = temp->link; // 다음 노드로 이동
    }
    printf("\n"); // 가독성을 위해 추가
}

// selection sort 정렬 함수
void selectionSort(Node* head) {
    Node* current, * min, * temp;
    int tempData;
    for (current = head; current != NULL; current = current->link) { // 리스트 순회
        min = current; // 현재 노드를 최소값 노드로 설정
        for (temp = current->link; temp != NULL; temp = temp->link) { // 현재 노드 이후의 노드 출력
            if (temp->data < min->data) { // 현재 값보다 더 작은 값을 찾으면
                min = temp; // 최소값 노드를 바꿈
            }
        }
        if (min != current) { // 최소값 노드가 현재 노드가 아닌 경우
            // 데이터 교환 일어남
            tempData = current->data;
            current->data = min->data;
            min->data = tempData;
        }
    }
}

// 리스트의 길이 반환 함수
int getLength(Node* head) {
    int length = 0;
    while (head != NULL) { // 리스트 끝까지 탐색
        length++; // 길이 하나씩 증가
        head = head->link; // 다음 노드로 이동
    }
    return length; // 리스트 길이 반환
}

// 특정 위치의 '노드'를 반환하는 함수
Node* getNodeAtPosition(Node* head, int position) {
    struct Node* current = head;
    for (int i = 0; i < position && current != NULL; i++) { // 주어진 위치까지 포인터 이동
        current = current->link; // 다음 노드로 이동
    }
    return current;
}

// 이진 탐색 함수
Node* binarySearch(Node* head, int keys[], int* position) {
    int left = 0; // 맨 왼쪽
    int right = 30; // 맨 오른쪽
    while (left <= right) { // 탐색 범위가 유효안 동안
        int mid = (left + right) / 2; // 중간 위치
        Node* midNode = getNodeAtPosition(head, mid); // current 노드 반환

        if (midNode == NULL) { // 리스트에 값이 없을 경우
            return NULL;
        }
        if (midNode->data == keys) { // key값을 찾은 경우
            *position = mid; // key의 위치 저장
            return midNode; // 찾은 노드 반환
        }
        else if (midNode->data < keys) { // 중간값<key인 경우, mid포함 왼쪽 날리기
            left = mid + 1; // 탐색 범위를 오른쪽으로 이동
        }
        else { // 중간값>key인 경우, mid포함 오른쪽 날리기
            right = mid - 1; // 탐색 범위를 왼쪽으로 이동
        }
    }
    return NULL; // key를 찾지 못한 경우 null반환
}

// 메인 함수
int main() {
    int data[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 }; // 초기 데이터 배열
    int searchKeys[] = { 3, 97, 96, 111, 15, 9, 66, 120, 99, 59 }; // 탐색할 key 배열
    Node* head = NULL;

    for (int i = 0; i < 31; i++) { // 데이터 배열 값을 연결 리스트에 추가
        appendNode(&head, data[i]);
    }
    printf("********Original Linked List********\n");
    printList(head); // 원래 연결 리스트 출력

    selectionSort(head); // 연결 리스트 선택 정렬

    printf("\n****Selection Sorted Linked List****\n");
    printList(head); // 선택 정렬된 리스트 출력

    printf("\n"); // 가독성 위해 추가

    for (int i = 0; i < 10; i++) {
        int key = searchKeys[i];
        int position = 0;
        Node* result = binarySearch(head, key, &position); // 이진 탐색 수행
        if (result != NULL) { // key를 찾은 경우 아래 문장 출력
            printf("(%d) - True\t/\tKey %d found at position %d번째 in the Selection Sorted List.\n\n", i + 1, key, position + 1);
        }
        else { // key를 찾지 못한 경우
            printf("(%d) - False\t/\tNo Result in List.\n\n", i + 1);
        }
    }
    return 0;
}
