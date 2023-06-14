#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
    int height;
};

struct node* newNode(int data) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int getHeight(struct node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int maxi(int a, int b) {
    return (a > b) ? a : b;
}

struct node* rotateLeft(struct node* z) {
    struct node* y = z->right;
    struct node* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = maxi(getHeight(z->left), getHeight(z->right)) + 1;
    y->height = maxi(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct node* rotateRight(struct node* y) {
    struct node* x = y->left;
    struct node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxi(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maxi(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

int getBalance(struct node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

struct node* insert(struct node* node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + maxi(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

int isPrime(int number) {
    if (number < 2)
        return 0;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0)
            return 0;
    }
    return 1;
}

void findWeakPrimes(struct node* root, int prevPrime, int nextPrime) {
    if (root == NULL)
        return;

    findWeakPrimes(root->left, prevPrime, root->data);

        if (prevPrime + nextPrime > root->data && isPrime(root->data)) {
        printf("%d ", root->data);
    }

    findWeakPrimes(root->right, root->data, nextPrime);

    return;
}
 void inorderTraversal(struct node* root) {
     if (root != NULL) {
         inorderTraversal(root->left);
         printf("%d \n", root->data);
         inorderTraversal(root->right);
     }
 }
void inorderTraversalWeakPrimes(struct node* root) {
    if (root != NULL) {
       
        findWeakPrimes(root, 2, 5);
        
    }
}
struct node* deleteNode(struct node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            struct node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + maxi(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

int main() {
    struct node* root = NULL;
    int n, data;

    printf("Kac adet sayi gireceksiniz? ");
    scanf("%d", &n);

    printf("Sayilari giriniz:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insert(root, data);
    }
    printf("AVL tree: \n");
    inorderTraversal(root);
    printf("\n");
    printf("Zayif asal sayilar: ");
    inorderTraversalWeakPrimes(root);
    printf("\n");
    //deleteNode(root,3);
    inorderTraversal(root);
    return 0;
}

