#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
   struct node * next;
};
struct node *insert(struct node*newnode,int data){
    struct node * iter=newnode;
    if(newnode==NULL) {
        newnode=(struct node*)malloc(sizeof(struct node));
        newnode->next=NULL;
        newnode->data=data;
        return newnode;
    }

    struct node*temp=(struct node*)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=newnode;
    return temp;

}
void print(struct node * root){
    while(root!=NULL) {
        printf("%d\n",root->data);
        root=root->next;
    }
}
int issorted_iterative(struct node * root) {
if(root==NULL || root->next==NULL){
    return 1;
}
while(root->next!=NULL) {
    if(root->data>root->next->data){
        return 0;
    }
    root=root->next;
}
return 1;
}
int isprimenumber(int data){
    if(data<=1) {
        return 0;
    }
    for(int i=2;i<=data/2;i++) {
      if(data%i==0) {
        return 0;
      }
    }
    return 1;
}
void print_prime_number(struct node * root){
    struct node * iter=root;
    while(iter!=NULL){
        if(isprimenumber(iter->data)){
            printf("\nprime number: %d\n",iter->data);
        }
       
        iter=iter->next;
    }
}
int isharshad(int num) {
   int sum = 0, temp = num;
   while (temp != 0) {
      sum += temp % 10;
      temp /= 10;
   }
   return (num % sum == 0);
}
int issorted(struct node * root){
   
    if(root->data>root->next->data) {
        return 0;
    }
    return issorted(root->next);
}
void printharshad(struct node *head) {
   printf("Harshad Sayilari: ");
   while (head != NULL) {
      if (isharshad(head->data)) {
         printf("%d ", head->data);
      }
      head = head->next;
   }
   printf("\n");
}

int main() {
int count;
// printf("kac eleman eklenecek");
// scanf("%d",&count);
struct node * root=NULL;
root=insert(root,100);
root=insert(root,50);
root=insert(root,17);
root=insert(root,30);
root=insert(root,80);
root=insert(root,73);
print(root);
if(issorted_iterative(root)){
    printf("\nsorted");
}
else{
    printf("\nnot sorted");
}
print_prime_number(root);
if(issorted_iterative(root)){
    printf("\nis already sorted");
}
else{
    printharshad(root);
}

}