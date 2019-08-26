#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

struct hufftree
{
	char c;
	int fr;
	struct hufftree *left,*right;
};

struct node
{
	struct hufftree *val;
	int pr;
	struct node *next;
}*start=NULL;


void push(struct hufftree *, int);
struct hufftree* pop();

void view()//for testing
{
    node *ytemp = start;
    while(ytemp!=NULL)
    {
        cout<<ytemp->val->c<<"-"<<ytemp->val->fr<<" ";
        ytemp=ytemp->next;
    }
    cout<<endl;
}

void disp()
{
	struct node *temp;
	temp = start;
	printf("\nPriority Queue: ");
	while(temp!=NULL)
	{
		printf("%d,%d ",temp->val, temp->pr);
		temp=temp->next;
	}
printf("\n");
}


void push(struct hufftree *ele,int pri)//this funtion will be repeatedly called for insertion of each element in the stucture which would
{						  //be using huffman code
	struct node *temp, *t;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->val=ele;
	temp->pr=pri;
	temp->next=NULL;

	if(start==NULL)
		start = temp;
	else if(start->pr>pri)
	{
		temp->next=start;
		start=temp;
	}
	else
	{
		t=start;
		while(t->next!=NULL && (t->next)->pr<=pri )
			t=t->next;
		temp->next=t->next;
		t->next=temp;
	}
//disp();
}

struct hufftree* pop() //remove elements
{
	if(start!=NULL)
	{
		struct node *t;
		t=start;
		start = start->next;
		return t->val;
	}
	else
	printf("\nError List Empty");
}



//the disp and del funtions are only to be used during debugging
//there is no need for these in the code you are currently making
