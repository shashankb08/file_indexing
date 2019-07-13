#include<stdio.h>
#include<stdlib.h>
 
typedef struct node
{
    int data;
    struct node *left,*right;
    int ht;
    long address;
}node;


struct tree
{
  int data;
  long add;
};

 
node *insert(node *,int,long);
node *Delete(node *,int);
void preorder(node *);
void inorder(node *);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
node *file_read(node *);
node* tree_search(node *,int);
void rec_print(node *);






 
int main()
{
    node *root=NULL,*p,*q;
    int roll,x,z=1;
    char ch='y'; 
    root=file_read(root);
    
    printf("\n1.Inorder");
    printf("\n2.Preorder");
    printf("\n3.Search ");
    printf("\n4.Exit");


    while(z)
   {
   
    printf("\n\nENter your choice..");
    scanf("%d",&x);
    switch(x)
    {
        case 1:printf("\nInorder sequence:\n");
               inorder(root);
               break;
        case 2: printf("\nPreorder sequence:\n");
               preorder(root);
               break;
        case 3:  
        printf("\n\nEnter the rollno to access for:\n");
        scanf("%d",&roll);
        q=root;
    p=tree_search(q,roll);
    if(p==NULL)
    {
      printf("\n Invalid roll number...!!\n");
      break;
    }
    else
     rec_print(p);
     break;
     case 4:exit(0);     
    }
//printf("\nDo you Want to continue???\n");
//scanf("%c",&ch);  

   }
   


   

    return 0;
}


node* tree_search(node *root , int roll)
{
  if (root==NULL || root->data == roll)
       {
        return root;}
  

    if (root->data < roll)
       return tree_search(root->right, roll);
 
    return tree_search(root->left, roll);
}



void rec_print(node *curr)
{
char str[100];
FILE *fp;
fp=fopen("record.txt","r");
fseek(fp,curr->address-18,SEEK_SET);
fgets(str,100,fp);
printf("%s",str);
//fflush(fp);
fclose(fp);
}


 
node * insert(node *T,int x,long add)
{
    if(T==NULL)
    {
        T=(node*)malloc(sizeof(node));
        T->data=x;
        T->left=NULL;
        T->right=NULL;
	T->address=add;
    }
    else
        if(x > T->data)        // insert in right subtree
        {
            T->right=insert(T->right,x,add);
            if(BF(T)==-2)
                if(x>T->right->data)
                    T=RR(T);
                else
                    T=RL(T);
        }
        else
            if(x<T->data)
            {
                T->left=insert(T->left,x,add);
                if(BF(T)==2)
                    if(x < T->left->data)
                        T=LL(T);
                    else
                        T=LR(T);
            }
        
        T->ht=height(T);
        
        return(T);
}
 
node * Delete(node *T,int x)
{
    node *p;
    
    if(T==NULL)
    {
        return NULL;
    }
    else
        if(x > T->data)        // insert in right subtree
        {
            T->right=Delete(T->right,x);
            if(BF(T)==2)
                if(BF(T->left)>=0)
                    T=LL(T);
                else
                    T=LR(T);
        }
        else
            if(x<T->data)
            {
                T->left=Delete(T->left,x);
                if(BF(T)==-2)    //Rebalance during windup
                    if(BF(T->right)<=0)
                        T=RR(T);
                    else
                        T=RL(T);
            }
            else
            {
                //data to be deleted is found
                if(T->right!=NULL)
                {    //delete its inorder succesor
                    p=T->right;
                    
                    while(p->left!= NULL)
                        p=p->left;
                    
                    T->data=p->data;
                    T->right=Delete(T->right,p->data);
                    
                    if(BF(T)==2)//Rebalance during windup
                        if(BF(T->left)>=0)
                            T=LL(T);
                        else
                            T=LR(T);\
                }
                else
                    return(T->left);
            }
    T->ht=height(T);
    return(T);
}
 
int height(node *T)
{
    int lh,rh;
    if(T==NULL)
        return(0);
    
    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->ht;
        
    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->ht;
    
    if(lh>rh)
        return(lh);
    
    return(rh);
}
 
node * rotateright(node *x)
{
    node *y;
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->ht=height(x);
    y->ht=height(y);
    return(y);
}
 
node * rotateleft(node *x)
{
    node *y;
    y=x->right;
    x->right=y->left;
    y->left=x;
    x->ht=height(x);
    y->ht=height(y);
    
    return(y);
}
 
node * RR(node *T)
{
    T=rotateleft(T);
    return(T);
}
 
node * LL(node *T)
{
    T=rotateright(T);
    return(T);
}
 
node * LR(node *T)
{
    T->left=rotateleft(T->left);
    T=rotateright(T);
    
    return(T);
}
 
node * RL(node *T)
{
    T->right=rotateright(T->right);
    T=rotateleft(T);
    return(T);
}
 
int BF(node *T)
{
    int lh,rh;
    if(T==NULL)
        return(0);
 
    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->ht;
 
    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->ht;
 
    return(lh-rh);
}

void preorder(node *T)
{
    if(T!=NULL)
    {
        printf("%d ",T->data);
        preorder(T->left);
        preorder(T->right);
    }
}
 
void inorder(node *T)
{
    if(T!=NULL)
    {
        inorder(T->left);
        printf("%d ,",T->data);
        inorder(T->right);
    }
}


node *file_read(node *root)
{
 struct tree tr[20];
 int j=0; 

 char a[10];
 char str[100];
 FILE *fp;
 int i=0;
 fp=fopen("record.txt","r");
 if(fp==NULL)
   printf("Couldnt read text file\n");
 else
   while(fgets(str,100,fp)!=NULL)
    {
	tr[j].add=ftell(fp);
	i=0;
        while ( (str[i]!=' ')&&(str[i]!='\n'))
	{ a[i]=str[i];
          i++; 	 
	}
	tr[j].data=atoi(a);
	//tr[0].add=0;
        root=insert(root,tr[j].data,tr[j].add);
        j++;
    }
fclose(fp);



//printf("\n Inorder Sequence:\n");
//inorder(root);
return root;
}
