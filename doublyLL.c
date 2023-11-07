#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = *head;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

void delete(Node** head, int data) {
    if (*head == NULL) {
        return;
    }
    Node* current = *head;
    Node* prev = NULL;
    while (1) {
        if (current->data == data) {
            if (prev != NULL) {
                prev->next = current->next;
            }
            if (current == *head) {
                *head = (*head)->next;
            }
            free(current);
            return;
        }
        if (current->next == *head) {
            break;
        }
        prev = current;
        current = current->next;
    }
}

void display(Node* head) {
    Node* current = head;
    if (head != NULL) {
        do {
            printf("%d ", current->data);
            current = current->next;
        } while (current != head);
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);

    printf("Circular Linked List: ");
    display(head);

    delete(&head, 3);
    printf("After deleting 3: ");
    display(head);

    return 0;
}
