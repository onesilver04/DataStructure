// 인공지능공학부 2311613 한은정 (A) Program Code_정렬 24.05.17

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;
    struct Node* link;
} Node;

// 새로운 노드 생성 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// 노드 추가 함수 (리스트의 끝에 추가)
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
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

// selection sort 정렬 함수
void selectionSort(Node* head) {
    Node* current, * min, * temp;
    int tempData;
    for (current = head; current != NULL; current = current->link) {
        min = current;
        for (temp = current->link; temp != NULL; temp = temp->link) {
            if (temp->data < min->data) {
                min = temp;
            }
        }
        if (min != current) {
            // 데이터 교환
            tempData = current->data;
            current->data = min->data;
            min->data = tempData;
        }
    }
}

// 리스트의 길이 반환 함수
int getLength(Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->link;
    }
    return length;
}

// 특정 위치의 '노드'를 반환하는 함수
Node* getNodeAtPosition(Node* head, int position) {
    struct Node* current = head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->link;
    }
    return current;
}

// 이진 탐색 함수
Node* binarySearch(Node* head, int keys[], int*position) {
    int left = 0;
    int right = getLength(head) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        Node* midNode = getNodeAtPosition(head, mid);// current 노드 반환

        if (midNode == NULL) { // 리스트에 값이 없을 경우
            return NULL;
        }
        if (midNode->data == keys) { // key값을 찾은 경우
            *position = mid; // key의 위치 저장
            return midNode;
        }
        else if (midNode->data < keys) { // mid포함 왼쪽 날리기
            left = mid + 1;
        }
        else { // mid포함 오른쪽 날리기
            right = mid - 1;
        }
    }
    return NULL;
}

// 메인 함수
int main() {
    //int temp;
    int data[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };
    int searchKeys[] = { 3, 97, 96, 111, 15, 9, 66, 120, 99, 59 };
    Node* head = NULL;

    for (int i = 0; i < 31; i++) {
        appendNode(&head, data[i]);
    }
    printf("********Original Linked List********\n");
    printList(head);
    selectionSort(head);

    printf("\n****Selection Sorted Linked List****\n");
    printList(head);
    printf("\n");

    //int x = getNodeAtPotitionInt(head, keys);
    for (int i = 0; i < 10; i++) {
        int key = searchKeys[i];
        int position = 0;
        Node* result = binarySearch(head, key, &position);
        if (result != NULL) {
            printf("(%d) - True\t/\tKey %d found at position %d번째 in the Selection Sorted List.\n\n", i+1, key, position+1);
        }
        else {
            printf("(%d) - False\t/\tNo Result in List.\n\n", i+1);
        }
    }
    return 0;
}
