//
//  main.c
//  AVL-Tree
//
//  Created by Ahmed Masoud on 4/29/15.
//  Copyright (c) 2015 Ahmed Masoud. All rights reserved.
//

#include <stdio.h>

typedef struct node{
    double value;
    struct node*left;
    struct node*right;
    // struct node*parent;
    short balance_factor;
} node;

typedef struct avltree{
    node *root;
} avltree;

node* initializenode(double value){
    node *start=malloc(sizeof(node));
    start->left=NULL;
    start->right=NULL;
    // start->parent=NULL;
    start->value=value;
    start->balance_factor=0;
    return start;
}

void initializetree(avltree *newtree){
    newtree->root=NULL;
}

int c=0;

void pre_order(node *head){
    if (head)
    {
        printf("%g\t",head->value);
        if(!(head->right)&&!(head->left))
            c++;
        pre_order(head->left);
        pre_order(head->right);
        
    }
}

void in_order(node *head){
    if (head)
    {
        pre_order(head->left);
        printf("%g\t",head->value);
        pre_order(head->right);
    }
}

void post_order(node *head){
    if (head)
    {
        pre_order(head->left);
        pre_order(head->right);
        printf("%g\t",head->value);
    }
}

double search(node *head,double val){
    if(!head)  return 0;
    if (head->value==val) return 1;
    else
    {
        if (val<head->value)
        {
            return search(head->left, val);
        }
        else return search(head->right, val);
    }
}

double max(double x,double y){
    return x>y? x : y;
}

node *rotate_RL(node *head){
    node *temp;
    node *parent=NULL;
    temp=NULL;
    temp=head->right;
    parent=temp->left;
    temp->left=parent->right;
    parent->right=temp;
    head->right=parent->left;
    parent->left=head;
    
    return parent;
}

node *rotate_LR(node *head){
    node *temp;
    node *parent=NULL;
    temp=NULL;
    temp=head->left;
    parent=temp->right;
    head->left=parent->right;
    parent->right=head;
    temp->right=parent->left;
    parent->left=temp;
    return parent;
}

node *rotate_RR( node*head){
    node*parent=head->right;
    head->right=parent->left;
    //if (parent->left)
    // parent->left->parent=head;
    parent->left=head;
    //  parent->parent=head->parent;
    // head->parent=parent;
    return parent;
}

node *rotate_LL( node*head){
    node*parent=head->left;
    head->left=parent->right;
    parent->right=head;
    return parent;
}

int depth(node *head){
    if (!head )
    {
        return 0;
    }
    if (depth(head->right)>depth(head->left))
    {
        return depth(head->right)+1;
    }
    return depth(head->left)+1;
}

short getbalance(node *head){
    return depth(head->left)-depth(head->right);
}

node* balancing(node *head){
    int balancefactor= getbalance(head);
    if (balancefactor >1)
    {
        if (getbalance(head->left) >0)
            head=rotate_LL(head);
        else
            head=rotate_LR(head);
    }
    else if(balancefactor < -1)
    {
        if(getbalance(head ->right) >0)
            head=rotate_RL(head);
        else
            head=rotate_RR(head);
    }
    return head;
}

node* insert(node * root,double val){
    if (!root)
    {
        root = ( node*) malloc(sizeof(node));
        root ->value = val;
        root -> left = NULL;
        root -> right = NULL;
        return root;
    }
    else if (val < root->value)
    {
        root->left = insert(root->left, val);
        root=balancing(root);
    }
    else if (val > root->value)
    {
        root->right = insert(root->right, val);
        root=balancing(root);
    }
    return root;
}

node *getmin(node *start){
    if (!start->left)
    {
        return start;
    }
    return getmin(start->left);
}

void delete(avltree* tree,double val){
    if(!tree->root) return;
    if (!search(tree->root, val)) return;
    node *temp = tree->root;
    node *parent = NULL;
    while (temp)
    {
        if(temp->value==val)break;
        parent = temp;
        if (val<temp->value)
            temp=temp->left;
        else
            temp=temp->right;
    }
    if (!parent) {
        if (temp->left!=NULL && temp->right==NULL)//1 younger child
        {
            tree->root=tree->root->left;
            
        }
        if (temp->left==NULL && temp->right!=NULL)//1 older child
        {
            tree->root=tree->root->right;
        }
        if (temp->left==NULL && temp->right==NULL)//leaf
        {
            tree->root=NULL;
            printf("\nNote the tree is now empty !!\n");
        }
        if (temp->left!=NULL && temp->right!=NULL)//2 children
        {
            double bibo=getmin(tree->root->right)->value;
            delete(tree, getmin(tree->root->right)->value);
            tree->root->value=bibo;
            
            
        }
        return;

    }
    //printf("temp : %g\tparent : %g\n",temp->value,parent->value);
    if (temp->left!=NULL && temp->right==NULL)//1 younger child
    {
        if (temp->value>parent->value)
        {
            //temp->left->parent=temp->parent;
            parent->right=temp->left;
        }
        else
        {
            // temp->left->parent=temp->parent;
            parent->left=temp->left;
        }
        
        
    }
    if (temp->left==NULL && temp->right!=NULL)//1 older child
    {
        if (temp->value>parent->value)
        {
            // temp->right->parent=temp->parent;
            parent->right=temp->right;
        }
        else
        {
            //temp->left->parent=temp->parent;
            parent->left=temp->right;
        }
    }
    if (temp->left==NULL && temp->right==NULL)//leaf
    {
        if (val>parent->value)
            parent->right=NULL;
        else parent->left=NULL;
    }
    if (temp->left!=NULL && temp->right!=NULL)//2 children
    {
        double bibo=getmin(temp->right)->value;
        delete(tree, getmin(temp->right)->value);
        temp->value=bibo;
        
        
    }
    
}

int main(int argc, const char * argv[]){
    
    avltree testtree;
    initializetree(&testtree);
    /* testtree.root=insert(testtree.root, 1);
     testtree.root=insert(testtree.root, 2);
     testtree.root=insert(testtree.root, 3);
     testtree.root=insert(testtree.root, 4);
     testtree.root=insert(testtree.root, 5);
     testtree.root=insert(testtree.root, 6);
     testtree.root=insert(testtree.root, 7);
     testtree.root=insert(testtree.root, 8);
     testtree.root=insert(testtree.root, 9);
     testtree.root=insert(testtree.root, 10);
     testtree.root=insert(testtree.root, 11);*/
    for (int i=1; i<10; i++) {
        testtree.root=insert(testtree.root, i);
    }//testtree.root=insert(testtree.root, 20);
    /*
    testtree.root=insert(testtree.root, 20);
     for (int i=10; i!=0; i--) {
     testtree.root=insert(testtree.root, i);
     }
    testtree.root=insert(testtree.root, 13);
    testtree.root=insert(testtree.root, 10);
    testtree.root=insert(testtree.root, 2);
    testtree.root=insert(testtree.root, 12);
    testtree.root=insert(testtree.root, 25);
    testtree.root=insert(testtree.root, 20);
    testtree.root=insert(testtree.root, 22);
    testtree.root=insert(testtree.root, 31);
    testtree.root=insert(testtree.root, 18);
    testtree.root=insert(testtree.root, 17);*/
    
    
    
    //delete(&testtree, 23);
   // printf("\n");
    pre_order(testtree.root);
    
    
    printf("\n leaf nodes number : %d\n",c);
    
    return 0;
}
