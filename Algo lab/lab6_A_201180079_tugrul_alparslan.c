#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};
int calculate_1(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

void insert(struct node** head_ref, int new_data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct node* node) {
    printf("List: ");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void printBinary(int n) {
    int binary[32], i = 0;
    while (n > 0) {
        binary[i] = n % 2;
        n = n / 2;
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binary[j]);
    }
}

void printBinaryList(struct node* node) {
    printf("binary list: ");
    while (node != NULL) {
        printBinary(node->data);
        printf(" ");
        node = node->next;
    }
    printf("\n");
}

struct node* last_node(struct node* head) {
    struct node* temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

struct node* partition(struct node* first, struct node* last) {
    struct node* pivot = first;
    struct node* front = first;
    int temp = 0;
    while (front != NULL && front != last) {
        if (calculate_1(front->data) < calculate_1(last->data)) {
            pivot = first;
            temp = first->data;
            first->data = front->data;
            front->data = temp;
            first = first->next;
        }
        else if(calculate_1(front->data)==calculate_1(last->data)){
              pivot = first;
            temp = first->data;
            first->data = front->data;
            front->data = temp;
            first = first->next;
        }
        front = front->next;
        
    }
    temp = first->data;
    first->data = last->data;
    last->data = temp;
    return pivot;
}

void quick_sort(struct node* first, struct node* last) {
    if (first == last) {
        return;
    }
    struct node* pivot = partition(first, last);
    if (pivot != NULL && pivot->next != NULL) {
        quick_sort(pivot->next, last);
    }
    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot);
    }
}

int main() {
    struct node* head = NULL;
    int data;
    do {
        printf("sayi gir (0 girince durur!) ");
        scanf("%d", &data);
        if (data > 0) {
            insert(&head, data);
        }
    } while (data != 0);
    printList(head);
    printBinaryList(head);
    quick_sort(head, last_node(head));
    printf("binarye gore siralanmis ");
    printList(head);
    return 0;
}
