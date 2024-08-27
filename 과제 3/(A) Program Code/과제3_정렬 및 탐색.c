// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_���� 24.05.17~18

#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    int data;
    struct Node* link;
} Node;

// ���ο� ��� ���� �Լ�
Node* createNode(int num) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = num;
    newNode->link = NULL;
    return newNode;
}

// ����Ʈ�� ���� ��带 �߰��ϴ� �Լ�
void appendNode(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) { // ����Ʈ�� ��� �ִ� ���
        *head = newNode; // ���ο� ��带 ���� ����
    }
    else { // ����Ʈ�� ��� ���� ���� ���
        Node* temp = *head; // �ӽ� ���� ��� ����
        while (temp->link != NULL) { // ����Ʈ�� ������ Ž��
            temp = temp->link; // ���� ���� �̵�
        }
        temp->link = newNode; // ������ ��忡 ���ο� ��� ����
    }
}

// ����Ʈ ��� �Լ�
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) { // ����Ʈ ������ ���
        printf("%d ", temp->data); // ���� �����Ͱ� ����Ű�� data ���
        temp = temp->link; // ���� ���� �̵�
    }
    printf("\n"); // �������� ���� �߰�
}

// selection sort ���� �Լ�
void selectionSort(Node* head) {
    Node* current, * min, * temp;
    int tempData;
    for (current = head; current != NULL; current = current->link) { // ����Ʈ ��ȸ
        min = current; // ���� ��带 �ּҰ� ���� ����
        for (temp = current->link; temp != NULL; temp = temp->link) { // ���� ��� ������ ��� ���
            if (temp->data < min->data) { // ���� ������ �� ���� ���� ã����
                min = temp; // �ּҰ� ��带 �ٲ�
            }
        }
        if (min != current) { // �ּҰ� ��尡 ���� ��尡 �ƴ� ���
            // ������ ��ȯ �Ͼ
            tempData = current->data;
            current->data = min->data;
            min->data = tempData;
        }
    }
}

// ����Ʈ�� ���� ��ȯ �Լ�
int getLength(Node* head) {
    int length = 0;
    while (head != NULL) { // ����Ʈ ������ Ž��
        length++; // ���� �ϳ��� ����
        head = head->link; // ���� ���� �̵�
    }
    return length; // ����Ʈ ���� ��ȯ
}

// Ư�� ��ġ�� '���'�� ��ȯ�ϴ� �Լ�
Node* getNodeAtPosition(Node* head, int position) {
    struct Node* current = head;
    for (int i = 0; i < position && current != NULL; i++) { // �־��� ��ġ���� ������ �̵�
        current = current->link; // ���� ���� �̵�
    }
    return current;
}

// ���� Ž�� �Լ�
Node* binarySearch(Node* head, int keys[], int* position) {
    int left = 0; // �� ����
    int right = 30; // �� ������
    while (left <= right) { // Ž�� ������ ��ȿ�� ����
        int mid = (left + right) / 2; // �߰� ��ġ
        Node* midNode = getNodeAtPosition(head, mid); // current ��� ��ȯ

        if (midNode == NULL) { // ����Ʈ�� ���� ���� ���
            return NULL;
        }
        if (midNode->data == keys) { // key���� ã�� ���
            *position = mid; // key�� ��ġ ����
            return midNode; // ã�� ��� ��ȯ
        }
        else if (midNode->data < keys) { // �߰���<key�� ���, mid���� ���� ������
            left = mid + 1; // Ž�� ������ ���������� �̵�
        }
        else { // �߰���>key�� ���, mid���� ������ ������
            right = mid - 1; // Ž�� ������ �������� �̵�
        }
    }
    return NULL; // key�� ã�� ���� ��� null��ȯ
}

// ���� �Լ�
int main() {
    int data[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 }; // �ʱ� ������ �迭
    int searchKeys[] = { 3, 97, 96, 111, 15, 9, 66, 120, 99, 59 }; // Ž���� key �迭
    Node* head = NULL;

    for (int i = 0; i < 31; i++) { // ������ �迭 ���� ���� ����Ʈ�� �߰�
        appendNode(&head, data[i]);
    }
    printf("********Original Linked List********\n");
    printList(head); // ���� ���� ����Ʈ ���

    selectionSort(head); // ���� ����Ʈ ���� ����

    printf("\n****Selection Sorted Linked List****\n");
    printList(head); // ���� ���ĵ� ����Ʈ ���

    printf("\n"); // ������ ���� �߰�

    for (int i = 0; i < 10; i++) {
        int key = searchKeys[i];
        int position = 0;
        Node* result = binarySearch(head, key, &position); // ���� Ž�� ����
        if (result != NULL) { // key�� ã�� ��� �Ʒ� ���� ���
            printf("(%d) - True\t/\tKey %d found at position %d��° in the Selection Sorted List.\n\n", i + 1, key, position + 1);
        }
        else { // key�� ã�� ���� ���
            printf("(%d) - False\t/\tNo Result in List.\n\n", i + 1);
        }
    }
    return 0;
}
