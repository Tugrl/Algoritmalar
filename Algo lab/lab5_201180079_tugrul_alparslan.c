#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};
int count_lasa;
void append(struct Node** head_ref, int new_data)
{ 
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }
    struct Node* last = *head_ref;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    new_node->prev = last;
}
int is_prime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
int is_all_prime(struct Node* head) {
    while (head != NULL) {
        if (!is_prime(head->data)) {
            count_lasa++;
        }
        head = head->next;
    }
    return 1;
}
int is_tau(int num) {
    int PBSCount = 0;
        for (int i = 1; i <= num; i++)
        {
            if (num % i == 0)
            {
                PBSCount++;
            }
        }

        if (num % PBSCount == 0)
        {
            return 1;
        }
        return 0;
}
void insertion_sort(struct Node** head_ref) {
    struct Node* current = *head_ref;
    struct Node* sorted = NULL;
    while (current != NULL) {
        struct Node* next = current->next;
        if (sorted == NULL || current->data < sorted->data) {
            current->next = sorted;
            if (sorted != NULL) {
                sorted->prev = current;
            }
            sorted = current;
            sorted->prev = NULL;
        } else {
            struct Node* temp = sorted;
            while (temp != NULL && temp->data < current->data) {
                temp = temp->next;
            }
            current->prev = temp->prev;
            current->next = temp;
            if (temp->prev != NULL) {
                temp->prev->next = current;
            }
            temp->prev = current;
        }
        current = next;
    }
    *head_ref = sorted;
}
void bubbleSort(struct Node** head_ref) {
    struct Node* i, * j;
    int temp;
    for (i = *head_ref; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
int main()
{
    FILE *fp;
    int num, i;   
    fp = fopen("sayilar.txt", "r");

    if (fp == NULL) {
        printf("Dosya yok.\n");
        exit(1);
    }
    struct Node* head = NULL;
    for (i = 0; i < 10; i++) {
        fscanf(fp, "%d", &num);
        append(&head, num);
    }
    fclose(fp);
    struct Node* node = head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    int tau_count;
    printf("%d",count_lasa);
    while(node!=NULL){
        if(is_tau(node->data)==1) {
            tau_count++;
        }
    }
printf("  %d",tau_count);
if(tau_count>count_lasa) {
    insertion_sort(&head);
}
if(count_lasa>tau_count){
    bubbleSort(&head);
}
while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    return 0;
}