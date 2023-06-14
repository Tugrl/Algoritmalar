
#include <stdio.h>
#include <stdlib.h>


struct treenode {
    int data;
    struct treenode* left;
    struct treenode* right;
};

struct listnode {
    int data;
    struct listnode* prev;
    struct listnode* next;
};


struct treenode* createtree(struct listnode** head_ref) {
    int data;
    scanf_s("%d", &data);

   
    if (data == 0) {
        return NULL;
    }

   
    struct treenode* node = (struct treenode*)malloc(sizeof(struct treenode));
    node->data = data;
    node->left = createtree(head_ref);
    if (*head_ref != NULL) {
        (*head_ref)->prev = node;
    }
    node->right = createtree(head_ref);
    return node;
}


void createlist(struct listnode** head_ref, struct treenode* node) {
    if (node == NULL) {
        return;
    }

   
    struct listnode* new_node = (struct listnode*)malloc(sizeof(struct listnode));
    new_node->data = node->data;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (*head_ref == NULL) {
        *head_ref = new_node;
    }
    else {
        struct listnode* curr = *head_ref;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = new_node;
        new_node->prev = curr;
    }

    createlist(head_ref, node->left);
    createlist(head_ref, node->right);
}


void printlist(struct listnode* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() {
    struct treenode* root = NULL;
    struct listnode* head = NULL;

    printf("Pozitif sayilari giriniz (sonlandirmak icin 0 a bas!):\n");
    root = createtree(&head);

    printf("level-order siralamasi:\n");
    createlist(&head, root);
    printlist(head);

    return 0;
}

