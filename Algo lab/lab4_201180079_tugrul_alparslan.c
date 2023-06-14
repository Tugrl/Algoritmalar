#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct node* newnode(int data) {
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

void insert(struct node** root, int data) {
    struct node* temp = *root;
    struct node* parent = NULL;
    struct node* new = (struct node*) malloc(sizeof(struct node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    if (*root == NULL) {
        *root = new;
        return;
    }

    while (temp != NULL) {
        parent = temp;
        if (data < temp->data)
            temp = temp->left;
        else if (data > temp->data)
            temp = temp->right;
        else
            return;
    }

    if (data < parent->data)
        parent->left = new;
    else if (data > parent->data)
        parent->right = new;
}

void inorder(struct node* root, int k) {
    int steps = 0;
    if (root != NULL) {
        inorder(root->left, k);
        int num = root->data ^ k;
        if (isPrime(num)) {
            printf("%d ", num);
            steps++;
        }
        inorder(root->right, k);
    }
    printf("\nSteps taken: %d", steps);
}

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    struct node* root = NULL;
    int num, k;

    printf("Enter a positive integer k: ");
    scanf("%d", &k);
int k=5;
    do {
        printf("Enter a positive number (enter 0 to stop): ");
        scanf("%d", &num);
        if (num != 0) {
            insert(&root, num);
        }
    } while (num != 0);

    printf("\nPrime numbers found using inorder traversal: ");
    inorder(root, k);

    return 0;
}
