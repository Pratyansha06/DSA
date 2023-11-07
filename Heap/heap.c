#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

struct MinHeap {
    int arr[MAX_HEAP_SIZE];
    int size;
};

typedef struct MinHeap MinHeap;

MinHeap* createMinHeap() {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
        smallest = left;
    if (right < heap->size && heap->arr[right] < heap->arr[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapify(heap, smallest);
    }
}

void insert(MinHeap* heap, int value) {
    if (heap->size >= MAX_HEAP_SIZE) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    int index = heap->size;
    heap->arr[index] = value;
    heap->size++;

    while (index > 0 && heap->arr[(index - 1) / 2] > heap->arr[index]) {
        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty. Cannot extract minimum.\n");
        return -1;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

int main() {
    MinHeap* heap = createMinHeap();
    int values[] = {3, 8, 5, 2, 9, 1, 6, 4, 7};

    for (int i = 0; i < 9; i++) {
        insert(heap, values[i]);
    }

    printf("Min-heap elements: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }

    printf("\nExtracting minimum value: %d\n", extractMin(heap));

    printf("Min-heap elements after extraction: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }

    free(heap);
    return 0;
}
