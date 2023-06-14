#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct node{
    int data;
    struct node *left;
    struct node *right;
};
struct node* new(int data){
    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->left=temp->right=NULL;
    return temp;
}
struct node* insert(struct node * node,int data) {

if(node==NULL){
    return new(data);
}
else if(data< node->data){
    node->left=insert(node->left,data);
}
else if(data>node->data){
node->right=insert(node->right,data);

}
return node;
}
int main() {
    struct node*root=NULL;
int size;
printf("dizinin eleman sayisini girin.");
scanf_s("%d",&size);
int *dizi=(int *)malloc(size*sizeof(int));
for (int i = 0; i < size; i++)
    {
        dizi[i] = (rand()%2001)-1000;
    } 

for(int i=0;i<size;i++){ // dizi elemanlarını bst ye yerleştirme
    root=insert(root,dizi[i]);
}
int min,max;
printf("min degeri girin");
scanf_s("%d",&min);
printf("max degeri girin");
scanf_s("%d",&max);

return 0;
}
