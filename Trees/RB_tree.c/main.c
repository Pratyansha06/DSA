#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    Color color;
} Node;

Node* root = NULL;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->parent = newNode->left = newNode->right = NULL;
    newNode->color = RED;
    return newNode;
}

void leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void insert(int data) {
    Node* newNode = createNode(data);
    Node* y = NULL;
    Node* x = root;

    while (x != NULL) {
        y = x;
        if (newNode->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;
    if (y == NULL)
        root = newNode;
    else if (newNode->data < y->data)
        y->left = newNode;
    else
        y->right = newNode;

    fixInsert(newNode);
}

void inOrderTraversal(Node* node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d ", node->data);
        inOrderTraversal(node->right);
    }
}

int main() {
    int values[] = {7, 3, 18, 10, 22, 8, 11, 26, 2, 6};
    int i;

    for (i = 0; i < 10; i++) {
        insert(values[i]);
    }

    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}
