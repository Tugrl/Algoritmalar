#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100


typedef struct heap {
    int size;
    int data[MAX_SIZE];
} Heap;


void heap_insert(Heap *heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("Heap is full");
        return;
    }
    
    int i = heap->size;
    while (i > 0 && value < heap->data[(i-1)/2]) {
        heap->data[i] = heap->data[(i-1)/2];
        i = (i-1)/2;
    }
    heap->data[i] = value;
    heap->size++;
}


void heap_sort(Heap *heap) {
    int i, temp;
    for (i = heap->size-1; i > 0; i--) {
        temp = heap->data[0];
        heap->data[0] = heap->data[i];
        heap->data[i] = temp;
        heap->size--;
        heapify(heap, 0);
    }
}


void heap_remove(Heap *heap, int value) {
    int i, j, k;
    for (i = 0; i < heap->size; i++) {
        if (heap->data[i] == value) {
            heap->data[i] = heap->data[heap->size-1];
            heap->size--;
            k = (i-1)/2;
            j = i;
            while (j > 0 && heap->data[j] < heap->data[k]) {
                int temp = heap->data[k];
                heap->data[k] = heap->data[j];
                heap->data[j] = temp;
                j = k;
                k = (j-1)/2;
            }
            heapify(heap, i);
            printf("%d is removed from the heap.", value);
            return;
        }
    }
    printf("%d is not found in the heap.", value);
}


void convert_to_max_heap(Heap *heap) {
    int i, j, temp;
    for (i = 1; i < heap->size; i++) {
        j = i;
        while (j > 0 && heap->data[j] > heap->data[(j-1)/2]) {
            temp = heap->data[j];
            heap->data[j] = heap->data[(j-1)/2];
            heap->data[(j-1)/2] = temp;
            j = (j-1)/2;
        }
    }
}


void heapify(Heap *heap, int index) {
    int left_child, right_child, temp;
    left_child = 2*index + 1;
    right_child = 2*index + 2;
    if (left_child < heap->size && heap->data[left_child] < heap->data[index]) {
        temp = heap->data[index];
        heap->data;
    }
}
void print_heap(Heap *heap) {
    printf("\nHeap elements: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}


int main() {
    Heap heap = {0};
    
   
    heap_insert(&heap, 10);
    heap_insert(&heap, 20);
    heap_insert(&heap, 15);
    heap_insert(&heap, 30);
    heap_insert(&heap, 40);
    
    print_heap(&heap);
    
    heap_sort(&heap);

    print_heap(&heap);
    
    heap_remove(&heap, 20);

    print_heap(&heap);
    
    convert_to_max_heap(&heap);

    print_heap(&heap);
    
    return 0;
}
