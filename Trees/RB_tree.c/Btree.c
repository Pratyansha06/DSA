#include <stdio.h>
#include <stdlib.h>

#define M 4

struct BTreeNode {
    int leaf;
    int n;
    int keys[M - 1];
    struct BTreeNode* children[M];
};

typedef struct BTreeNode BTreeNode;

BTreeNode* createNode() {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->leaf = 1;
    newNode->n = 0;
    for (int i = 0; i < M; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

int searchKey(int key, const int keys[], int n) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (keys[mid] == key) return mid;
        if (keys[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->n == M - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void splitChild(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* newNode = createNode();
    for (int i = 0; i < M - 1; i++) {
        newNode->keys[i] = child->keys[i + M];
    }
    if (!child->leaf) {
        for (int i = 0; i < M; i++) {
            newNode->children[i] = child->children[i + M];
        }
    }
    child->n = M - 1;
    for (int i = parent->n; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    parent->children[index + 1] = newNode;
    for (int i = parent->n - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    parent->keys[index] = child->keys[M - 1];
    parent->n++;
}

void insert(BTreeNode** root, int key) {
    BTreeNode* node = *root;
    if (node->n == M - 1) {
        BTreeNode* newNode = createNode();
        newNode->children[0] = node;
        *root = newNode;
        splitChild(newNode, 0, node);
        insertNonFull(newNode, key);
    } else {
        insertNonFull(node, key);
    }
}

void traverse(BTreeNode* node) {
    for (int i = 0; i < node->n; i++) {
        if (!node->leaf) {
            traverse(node->children[i]);
        }
        printf("%d ", node->keys[i]);
    }
    if (!node->leaf) {
        traverse(node->children[node->n]);
    }
}

int main() {
    BTreeNode* root = createNode();
    int keys[] = {3, 7, 11, 20, 29, 5, 17, 8, 1, 9};
    for (int i = 0; i < 10; i++) {
        insert(&root, keys[i]);
    }
    printf("B-tree traversal: ");
    traverse(root);
    printf("\n");
    return 0;
}
