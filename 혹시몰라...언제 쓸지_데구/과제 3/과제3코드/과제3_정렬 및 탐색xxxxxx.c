// 인공지능공학부 2311613 한은정 (A) Program Code_정렬 및 탐색 24.05.17
#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* link;
} Node;

// 새로운 노드 생성 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // malloc 이용해 필요할 때마다 새로운 노드 생성
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// 리스트 끝에 노드를 추가하는 함수
void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    }
    else {
        Node* temp = *head;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = newNode;
    }
}

// 리스트 출력 함수
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) { // 리스트를 순회하면서
        printf("%d ", temp->data); // 포인터가 가리키는 data출력
        temp = temp->link; // 포인터를 다음 노드로 이동
    }
}

// selection sort 정렬 함수
void selectionSort(Node* head) {
    Node* current, * min, * temp;
    int tempData;
    for (current = head; current != NULL; current = current->link) {
        min = current; // 현재 포인터를 min으로 설정
        for (temp = current->link; temp != NULL; temp = temp->link) { // 리스트 순회하면서 최솟값 탐색
            if (temp->data < min->data) { // 현재 찾은 최솟값보다 더 작은 값을 찾으면 그 값을 min으로 변경
                min = temp;
            }
        }
        if (min != current) { // 현재 찾은 값과 최솟값이 다르면 데이터를 교환
            // 데이터 교환
            tempData = current->data;
            current->data = min->data;
            min->data = tempData;
        }
    }
}



// 메인 함수
int main() {
    int temp; // 임시 포인터 설정
    int data[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };
    Node* head = NULL;
    for (int i = 0; i < 31; i++) { // 31만큼 반복
        appendNode(&head, data[i]); // 노드에 데이터 추가
    }
    printf("===Original List===\n");
    printList(head);
    selectionSort(head);

    printf("\n====Sorted List====\n"); // 정렬된 리스트 출력
    printList(head);
    printf("\n");

    return 0;
}
