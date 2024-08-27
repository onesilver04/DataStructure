// �ΰ����ɰ��к� 2311613 ������ (A) Program Code_���� 24.05.17

#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    int data;
    struct Node* link;
} Node;

// ���ο� ��� ���� �Լ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->link = NULL;
    return newNode;
}

// ��� �߰� �Լ� (����Ʈ�� ���� �߰�)
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
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

// selection sort ���� �Լ�
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
            // ������ ��ȯ
            tempData = current->data;
            current->data = min->data;
            min->data = tempData;
        }
    }
}

// ����Ʈ�� ���� ��ȯ �Լ�
int getLength(Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->link;
    }
    return length;
}

// Ư�� ��ġ�� '���'�� ��ȯ�ϴ� �Լ�
Node* getNodeAtPosition(Node* head, int position) {
    struct Node* current = head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->link;
    }
    return current;
}

// ���� Ž�� �Լ�
Node* binarySearch(Node* head, int keys[], int*position) {
    int left = 0;
    int right = getLength(head) - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        Node* midNode = getNodeAtPosition(head, mid);// current ��� ��ȯ

        if (midNode == NULL) { // ����Ʈ�� ���� ���� ���
            return NULL;
        }
        if (midNode->data == keys) { // key���� ã�� ���
            *position = mid; // key�� ��ġ ����
            return midNode;
        }
        else if (midNode->data < keys) { // mid���� ���� ������
            left = mid + 1;
        }
        else { // mid���� ������ ������
            right = mid - 1;
        }
    }
    return NULL;
}

// ���� �Լ�
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
            printf("(%d) - True\t/\tKey %d found at position %d��° in the Selection Sorted List.\n\n", i+1, key, position+1);
        }
        else {
            printf("(%d) - False\t/\tNo Result in List.\n\n", i+1);
        }
    }
    return 0;
}
