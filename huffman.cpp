//#include<iostream>
#include<fstream>
//#include<conio.h> does not work in linux
#include"krishna.h"
#include"mohit.h"
#include<bitset>
//#include<string.h>

using namespace std;

char tobin(char*); // converting binary string to single char
void encodeFile(ofstream&,ifstream&);
void decodeFile(ofstream&,ifstream&);
void saveTree(hufftree*,ofstream&);
void treeRecover(hufftree**,ifstream&);
hufftree* treeFetch(hufftree*,string,ofstream&);

int main()
{
	ifstream file;
	string fileName,eFileName,tFileName;
	char x;
	int fList[128];
	for(int i=0;i<128;i++)
        fList[i]=0;
    cout<<"Input File: ";
	getline(cin,fileName);
    cout<<"Output File: ";
	getline(cin,eFileName);
	//gets(tFileName);
	file.open(fileName,ios::in|ios::binary);
	//creating freq list of all characters in the file
	while(1)
	{
	    file>>noskipws>>x;
	    if(file.eof())break;
	    fList[x]++;
	}
	cout<<"\ngenerated flist\n";
	for(int i=0;i<128;i++)
        if(fList[i]!=0)
            cout<<char(i)<<" "<<fList[i]<<endl;
    tree_creator(fList); // frequency tree generated

    cout<<"tree created\n";

    treeprint(root);
    cout<<"\n";
    
    //testing treerecovery
    cout<<"\nTree File: ";
	getline(cin,tFileName);
    ofstream tfile(tFileName);
    saveTree(root,tfile);
    tfile.close();
    ifstream rtfile(tFileName);
    hufftree *rRoot=NULL;
    treeRecover(&rRoot,rtfile);
    treeprint(rRoot);

    //debugging -done
    char earr[17]={'\0'};
    hufftree_parser(root,earr); // encoded letters
    cout<<"encoded the letters";
    //debugging -done

    ofstream efile;
    efile.open(eFileName);//,ios::app);
    
    // writing encoded characters to file
    file.clear();
    file.seekg(0,ios::beg);
    encodeFile(efile,file); //working properly
    file.close();
    efile.close();
    
    //--------Debugging 
    ifstream efile2(eFileName);
    ofstream dfile("dtest.txt");
    decodeFile(dfile,efile2); //not working
    //--------Debugging

    for(int i=0;i<128;i++)
        if(fList[i]!=0)
        {
            cout<<char(i)<<" "<<fList[i]<<" ";
            cout<<encoded[i]<<" "<<strlen(encoded[i])<<endl;
        }
}

char tobin(char *a)
{
    char s=0;
    for(int i=0;a[i]!='\0';i++)
    {
        s<<=1;
        s+=(a[i]-'0');
    }
    return s;
}

void encodeFile(ofstream &efile,ifstream &file)
{
    char extra[8],code[16],x;
    extra[0]=code[0]='\0';
    while(!file.eof())
    {
        strcat(code,extra);
        while(strlen(code)<8)
        {
            file>>x;
            strcat(code,encoded[x]);
        }
        int i=8;
        for(;code[i]!='\0';i++)
            extra[i-8]=code[i];
        extra[i-8]='\0';
        code[8]='\0';
        char toWrite=tobin(code);
        efile<<toWrite;
        code[0]='\0';
    }
    // rounding remaining bits to bytes and writing to file
    if(extra[0]!='\0')
    {
        for(int i=strlen(extra);i<8;i++)
            extra[i]='0';
        char toWrite=tobin(extra);
        efile<<toWrite;
    }
}

/*
tree saving format rlr
      w
     / \
    a   b
   / \ / \
  c    s  r

w<a<c<.,.>,.>,b<s<............
*/
void saveTree(hufftree *tnd, ofstream &cout)
{
    if(tnd==NULL)
    {
        cout<<'.';
        return;
    }
    if(tnd->c=='<' || tnd->c=='.' || tnd->c=='~' || tnd->c=='>')
        cout<<'~';
    cout<<tnd->c<<'<';
    saveTree(tnd->left, cout);
    cout<<',';
    saveTree(tnd->right, cout);
    cout<<'>';
}

void treeRecover(hufftree **r,ifstream &file) // not being used right now
{
    if(file.eof())return;
    char c;
    file>>noskipws>>c;
    if(c=='.')return;
    if(c=='~')file>>c;
    /*{
        cout<<"Null";
        return;
    }*/
    hufftree *t=new hufftree;
    t->left=t->right=NULL;
    t->fr=-86;
    t->c=c;
    *r=t;
    file>>c;
    if(c=='<')
        treeRecover(&(*r)->left,file);
    file>>c;
    if(c==',')
        treeRecover(&(*r)->right,file);
    file>>c;
    if(c=='>')
        return;
}

hufftree* treeFetch(hufftree *r,string s,ofstream &file)
{
    hufftree *ret=r;
    if(r->left==NULL && r->right==NULL)
    {
        file<<r->c;
        return NULL;
    }
    if(s.length()!=0)
    {
        string t(s.begin()+1,s.end());
        if(s.front()=='0')
            ret = treeFetch(r->left,t,file);
        else
            ret = treeFetch(r->right,t,file);
    }
    return ret;
}

void decodeFile(ofstream &dfile,ifstream &efile)
{
    /*char tfileName[50],x;
    gets(tfileName);
    hufftree *abs;*/
    hufftree *t=NULL;
    char x;
    while(efile.read(&x,sizeof(char)))
    {
        string bin=bitset<8>((int)x).to_string();
        if(t==NULL)
            t=root;
        t=treeFetch(root,bin,dfile);
    }
}
