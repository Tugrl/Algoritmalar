#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node * next;
};
void print(struct node * r){
    while(r!=NULL) {
        printf("%d\n",r->data);
        r=r->next;
    }
}
struct node * end=NULL;
void enq(struct node * root,int data) {
    if(root==NULL){
        root=(struct node*)malloc(sizeof(struct node));
        root->data=data;
        root->next=NULL;
        end=root;
    }
    else {
        end->next=(struct node * )malloc(sizeof(struct node));
        end->next->data=data;
        end=end->next;
        end->next=NULL;
    }
}
int deq(struct node * root) {
    if(root==NULL) {
        printf("zaten bos");
    }
    else {
        int returnvalue=root->data;
        struct node * temp=root;
        root=root->next;
        free(temp);
        return returnvalue;
    }
}
struct node * root;
struct node* push(struct node* root,int a){
if(root==NULL) {
    root=(struct node*)malloc(sizeof(struct node));
    root->data=a;
    root->next=NULL;
    return root;
}
else {
struct node* iter=root;
while(iter->next!=NULL){
        iter=iter->next;
}
        struct node* temp=(struct node*)malloc(sizeof(struct node));
        temp->data=a;
        temp->next=NULL;
        iter->next=temp;
        return root;

}
}
int pop(struct node* root) {
    if(root==NULL) {
        printf("zaten bos");
        return -1;
    }
    else {
        struct node * iter=root;
        while(iter->next->next!=NULL) {
            iter=iter->next;
            struct node * temp=iter->next;
            int returnvalue=temp->data;
            iter->next=NULL;
            free(temp);
            
            return returnvalue;
        }
    }
}
int main() {
    int array[7]={1,3,4,6,11,8,13};
   struct node * head=(struct node*)malloc(sizeof(struct node));

   head->next=(struct node*)malloc(sizeof(struct node));

   head->next->next=(struct node*)malloc(sizeof(struct node));

    head->next->next->next=(struct node*)malloc(sizeof(struct node));
   
    head->next->next->next->next=(struct node*)malloc(sizeof(struct node));
  
     head->next->next->next->next->next=(struct node*)malloc(sizeof(struct node));
  
      head->next->next->next->next->next->next=(struct node*)malloc(sizeof(struct node));
    
        head->next->next->next->next->next->next->next=NULL;
        for(int i=0;i<7;i++) {
            head->data=array[i];
            head=head->next;
        }
        print(head);

 while(head!=NULL) {
     enq(head,head->data);
     head=head->next;
 }
 print(head);
  for(int i=0;i<4;i++) {
     deq(head);
     head=head->next;
  }
push(head,13);
push(head,8);
push(head,11);
print(head);
}