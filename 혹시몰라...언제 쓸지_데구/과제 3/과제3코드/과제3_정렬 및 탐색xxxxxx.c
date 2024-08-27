// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_���� �� Ž�� 24.05.17
#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    int data;
    struct Node* link;
} Node;

// ���ο� ��� ���� �Լ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // malloc �̿��� �ʿ��� ������ ���ο� ��� ����
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// ����Ʈ ���� ��带 �߰��ϴ� �Լ�
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

// ����Ʈ ��� �Լ�
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) { // ����Ʈ�� ��ȸ�ϸ鼭
        printf("%d ", temp->data); // �����Ͱ� ����Ű�� data���
        temp = temp->link; // �����͸� ���� ���� �̵�
    }
}

// selection sort ���� �Լ�
void selectionSort(Node* head) {
    Node* current, * min, * temp;
    int tempData;
    for (current = head; current != NULL; current = current->link) {
        min = current; // ���� �����͸� min���� ����
        for (temp = current->link; temp != NULL; temp = temp->link) { // ����Ʈ ��ȸ�ϸ鼭 �ּڰ� Ž��
            if (temp->data < min->data) { // ���� ã�� �ּڰ����� �� ���� ���� ã���� �� ���� min���� ����
                min = temp;
            }
        }
        if (min != current) { // ���� ã�� ���� �ּڰ��� �ٸ��� �����͸� ��ȯ
            // ������ ��ȯ
            tempData = current->data;
            current->data = min->data;
            min->data = tempData;
        }
    }
}



// ���� �Լ�
int main() {
    int temp; // �ӽ� ������ ����
    int data[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };
    Node* head = NULL;
    for (int i = 0; i < 31; i++) { // 31��ŭ �ݺ�
        appendNode(&head, data[i]); // ��忡 ������ �߰�
    }
    printf("===Original List===\n");
    printList(head);
    selectionSort(head);

    printf("\n====Sorted List====\n"); // ���ĵ� ����Ʈ ���
    printList(head);
    printf("\n");

    return 0;
}
