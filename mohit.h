//#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

/*struct hufftree
{
    char c;
    int fr;
    struct hufftree *left, *right;
}*root;*/

struct hufftree *root;

char encoded[128][16];

//int TheGivenList[127];

void tree_creator(int TheGivenList[128])
{
    int counter = 0;
    for(int i = 0; i < 128; i++)
    {
        if(TheGivenList[i]!=0)
        {
            struct hufftree *temp = (struct hufftree *)malloc(sizeof(struct hufftree));
            temp->c = i;
            temp->fr = TheGivenList[i];
            temp->left=NULL;
            temp->right=NULL;
            push(temp, TheGivenList[i]);
            counter++;
        }
    }
    view();
    for(int i = 0; i < counter-1; i++)
    {
        struct hufftree *temp = (struct hufftree *)malloc(sizeof(struct hufftree));
        temp->left = pop();
        temp->right = pop();
        cout<<temp->left->c<<" "<<temp->left->fr<<endl;
        cout<<temp->right->c<<" "<<temp->right->fr<<endl;
        temp->c='`';
        temp->fr = temp->left->fr + temp->right->fr;
        push(temp, temp->fr);
        view();
    }
    root = pop();
}

void hufftree_parser(struct hufftree *root, char encode[17])
{
    if(root->left==NULL && root->right==NULL)
    {
        strcpy(encoded[root->c],encode);
        return;
    }
    char tmp1[17]={'\0'};
    strcpy(tmp1,encode);strcat(tmp1,"0");
    hufftree_parser(root->left,tmp1);
    char tmp2[17]={'\0'};
    strcpy(tmp2,encode);strcat(tmp2,"1");
    hufftree_parser(root->right,tmp2);
}

void treeprint(hufftree *tnd)
{
    if(tnd==NULL)
    {
        cout<<'.';
        return;
    }
    cout<<tnd->c<<'<';
    treeprint(tnd->left);
    cout<<',';
    //cout<<tnd->c<<" "<<tnd->fr<<endl;
    treeprint(tnd->right);
    cout<<'>';
}
