#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
struct Student {
	char name[50];
	char gender;
	struct Student* next;
};
struct Student* insertNode(char* name, char gender, struct Student* list) {
	struct Student* s;
	s = malloc(sizeof(struct Student));
	if (s == NULL) {
		printf("Memory allocation failed. ");
		return list;
	}
	strcpy(s->name, name);
	s->gender = gender;
	s->next = list;
	list = s;
    
}
struct Student * sortList(struct Student * head) {  // sort function
struct Student * c2=head;  //the list is separated by gender
	while(c2!=NULL) {
		struct Student * c1=head;
		while(c1->next!=NULL) {
			if(c1->next->gender=='F') {
				struct Student * c3=c1->next;
				c1->next=c1->next->next;
				c3->next=head;
				head=c3;
			}
			c1=c1->next;
		}
		c2=c2->next;
	}
	c2=head;// end of seperated by gender


//reference from https://www.youtube.com/watch?v=pdMPvMM12G0
    struct Student* prev, * current, * first_temp, * second_temp, * third_temp; // sorting males by descending alphabetical
     for (prev  = NULL;prev!=head->next; prev=first_temp)
    {
        for (current=first_temp = head; first_temp->next!=prev; current=first_temp,first_temp=first_temp->next)
        {
            second_temp = first_temp->next;
            if (strcmp(first_temp->name,second_temp->name)<0&&first_temp->gender=='M'&&second_temp->gender=='M')
            {
                first_temp->next = second_temp->next;
                second_temp->next = first_temp;
                if (first_temp!=head)
                {
                    current->next = second_temp;
                }
                else
                {
                    head = second_temp;
                }
                third_temp = first_temp;
                first_temp = second_temp;
                second_temp = third_temp;
            }  
        }
    }// end of sorting males by descending alphabetical

    for (prev  = NULL;prev!=head->next; prev=first_temp)// sorting females by ascending alphabetical
    {
        for (current=first_temp = head; first_temp->next!=prev; current=first_temp,first_temp=first_temp->next)
        {
            second_temp = first_temp->next;
            if (strcmp(first_temp->name,second_temp->name)>0&&first_temp->gender=='F'&&second_temp->gender=='F')
            {
                first_temp->next = second_temp->next;
                second_temp->next = first_temp;
                if (first_temp!=head)
                {
                    current->next = second_temp;
                }
                else
                {
                    head = second_temp;
                }
                third_temp = first_temp;
                first_temp = second_temp;
                second_temp = third_temp;
            }
        }
    }//end of sorting females by ascending alphabetical
    
   
	return head;
}

void printlist(struct Student* list) {
	while (list != NULL) {
		printf("%s\t%c\n", list->name, list->gender);
		list = list->next;
	}
}
int main() {
	struct Student* head = NULL;
	head = insertNode("Cenk", 'M', head);
	head = insertNode("Ceyda", 'F', head);
	head = insertNode("Esra", 'F', head);
	head = insertNode("Okan", 'M', head);
	head = insertNode("Tugce", 'F', head);
	head = insertNode("Mehmet", 'M', head);
	head = insertNode("Ayse", 'F', head);
	head = insertNode("Merve", 'F', head);
	head = insertNode("Sedat", 'M', head);
	head = insertNode("Ahmet", 'M', head);
	printlist(head);
	printf("\n");
	head=sortList(head);
	printlist(head);
}