#include <bits/stdc++.h>
using namespace std;

//Global variables to store maximum size and cur size of the merkel tree.
int max_tree_size;
int cur_tree_size=0;

// Merkel Tree Structure
struct merkel_tree{
    string key;
    int value;
    struct merkel_tree *left,*right;
    merkel_tree()
    {
        key="0"; // default hash value of node.
        value=-1;
        left=right=NULL;
    }
};

//Function to generate hash value.
string generateHashValue()
{
	return "1";
}

//Function to make parent key = combination of all child keys
string generateHeadKey(int st_index,int en_index,merkel_tree *root)
{
    if(st_index==en_index)
    	return root->key;
    int mid=(en_index+st_index-1)/2;
    return root->key=generateHeadKey(st_index,mid,root->left)+generateHeadKey(mid+1,en_index,root->right);
}

// Function to generate the merkel tree of maximum capacity.
struct merkel_tree* generate_tree()
{
    struct merkel_tree *head=  new merkel_tree();
    queue<merkel_tree*> q;
    q.push(head);
    while(q.size()!=max_tree_size)
    {
        struct merkel_tree* pt=q.front();
        q.pop();
        pt->left=new merkel_tree();
        pt->right=new merkel_tree();
        q.push(pt->left);
        q.push(pt->right);
    }
    generateHeadKey(1,max_tree_size,head);
    return head;
}

//Function to insert the value.
string insert_value(int val,struct merkel_tree* root,int st_index,int en_index,int req_index)
{
    if(st_index>req_index || req_index>en_index)
        return root->key;
    if(st_index==en_index)
    {
   	cout<<"Value inserted "<<val<<"\n";
        root->value=val;
        return root->key=generateHashValue();
    }
    int mid=(en_index+st_index-1)/2;
    return root->key=insert_value(val,root->left,st_index,mid,req_index)+insert_value(val,root->right,mid+1,en_index,req_index);
}

void insert_value_util(merkel_tree *head)
{
    if(cur_tree_size==max_tree_size){
        cout<<"Merkel Tree is already full.\n";return;}
    int val;
    cout<<"Enter value for new transaction: ";
    cin>>val;
    cur_tree_size++;
    insert_value(val,head,1,max_tree_size,cur_tree_size);
    cout<<"Value Successfully Added. New head key is ";
    cout<<head->key<<"\n";
}

//Function to display inserted/default values of all nodes in merkel tree. 
void displayAll(int st_index,int en_index,merkel_tree *root)
{
    if(st_index==en_index)
    {
        cout<<" Transaction Key: "<<root->key;
        cout<<"\n Transaction Value: "<<root->value<<"\n";
        return;
    }
    int mid=(en_index+st_index-1)/2;
    displayAll(st_index,mid,root->left);
    displayAll(mid+1,en_index,root->right);
}

void displayAllUtil(merkel_tree *head)
{
    displayAll(1,max_tree_size,head);
}

//Function to display only the nodes whose value is inserted by user.
void displayAllHappen(int st_index,int en_index,merkel_tree *root)
{
    
    if(st_index>cur_tree_size)
    	return;
    if(st_index==en_index)
    {
        cout<<" Transaction Key: "<<root->key;
        cout<<"\n Transaction Value: "<<root->value<<"\n";
        return;
    }
    int mid=(en_index+st_index-1)/2;
    displayAllHappen(st_index,mid,root->left);
    displayAllHappen(mid+1,en_index,root->right);
}

void displayAllHappenUtil(merkel_tree *head)
{
    if(cur_tree_size==0)
    {
    	cout<<" No Transactions happened yet\n";
    	return;
    }
    displayAllHappen(1,max_tree_size,head);
}

//Function to find value of nth transaction.
void displayTransaction(int st_index,int en_index,merkel_tree *root,int req_index)
{

    if(st_index>req_index || en_index<req_index)
    	return;
    if(st_index==en_index)
    {
    	cout<<" Transaction Key: "<<root->key;
        cout<<"\n Transaction Value: "<<root->value<<"\n";
        return;
    }
    int mid=(en_index+st_index-1)/2;
    displayTransaction(st_index,mid,root->left,req_index);
    displayTransaction(mid+1,en_index,root->right,req_index);
}

void displayTransactionUtil(merkel_tree *head)
{
    cout<<"Enter the transaction number: ";   
    int n;
    cin>>n;
    if(n<1 || n>cur_tree_size)
    {
    	cout<<"\nInvalid Input\n";
    	return;
    }
    displayTransaction(1,max_tree_size,head,n);
}

//Function to get HeadKey 
string getHeadKey(merkel_tree *head)
{
    return head->key;
}

//main function
int main() {
    int capacity;
    cout<<"Enter the maximum capacity of merkel tree ";
    cin>>capacity;
    max_tree_size=1;
    while(max_tree_size<capacity)
    {
        max_tree_size<<=1;
    }
    struct merkel_tree *head= generate_tree();

    bool flag=0;
    while(!flag)
    {
        flag=0;
        cout<<"Enter your query:\n 1-Insert new value\n 2-Display all happened transactions\n 3-Display All Transactions \n 4-Display Nth Transaction\n 5-Get Head Key\n 6-exit\n";
        int ans;
        cout<<"Enter your choice: ";
        cin>>ans;
        cout<<"\n";
        switch(ans)
        {
            case 1: insert_value_util(head);break;
            case 2: displayAllHappenUtil(head);break;
            case 3: displayAllUtil(head);break;
            case 4: displayTransactionUtil(head);break;
            case 5: cout<<getHeadKey(head)<<"\n";break;
            case 6: flag=1;break;
            default:"Invalid Input\n";
        }
    }
    return 0;
}
/*
Logic Used-
Ask user for the maximum capacity he requires. Generate tree such tha number of leaf nodes= 2^x such that 2^x>= required capacity. 
Initially, default key/hash value of all nodes is "0". Whenever a new transaction say nth transaction happens, the key/hash value of nth leaf node becomes "1", hence changing the hash value of entire tree.  
*/
