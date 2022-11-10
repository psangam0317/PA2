//
//  build.c
//  
//
//  Created by Pranav Sangam on 11/10/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "build.h"

int findsize (char * filename)
{
    FILE * fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        fprintf(stdout, "%d\n", -1);
        return 0;
    }
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr) / (sizeof(int) + sizeof(char));
    fclose(fptr);
    return size;
}

void readB (char * filename, int size, int * iarr, char * carr)
{
    FILE * fptr;
    fptr = fopen(filename, "rb");
    if (fptr == NULL)
    {
        fprintf(stdout, "%d\n", -1);
        return;
    }
    fseek(fptr, 0, SEEK_SET);
    int i;
    for (i = 0; i < size; i++)
    {
        fread(&iarr[i], sizeof(int), 1, fptr);
        fread(&carr[i], sizeof(char), 1, fptr);
    }
    fclose(fptr);
    return;
}

Tnode * newNode (int item)
{
    Tnode * temp = (Tnode*)malloc(sizeof(Tnode));
    temp -> balance = 0;
    temp -> key = item;
    temp -> left = NULL;
    temp -> right = NULL;
    return temp;
}

Tnode * insertN (Tnode * Node, int item)
{
    
    if (Node == NULL)
    {
        return newNode(item);
    }
    if (item <= Node -> key)
    {
        Node -> left = insertN (Node -> left, item);
    }
    else
    {
        Node -> right = insertN (Node -> right, item);
    }
    return Node;
}

Tnode * rotate(Tnode * head)
{
    if(head == NULL)
    {
        return head;
    }

    head -> left = rotate(head -> left);
    head -> right = rotate(head -> right);
    int bal = getB(head);

    if(bal > 1)
    {
        Tnode * temp = head -> left;
        if (temp -> left != NULL)
        {
            head -> left = temp -> right;
            temp -> right = head;
            temp = updateB(temp);
            return temp;
        }
        else
        {
            Tnode * temp2 = temp -> right;
            temp -> right = temp2 -> left;
            head -> left = temp2 -> right;
            temp2 -> left = temp;
            temp2 -> right = head;
            temp2 = updateB(temp2);
            return temp2;
        }
    }
    else if(bal < -1)
    {
        Tnode * temp = head -> right;
        if (temp -> right != NULL)
        {
            head -> right = temp -> left;
            temp -> left = head;
            temp = updateB(temp);
            return temp;
        }
        else
        {
            Tnode * temp2 = temp -> left;
            temp -> left = temp2 -> right;
            head -> right = temp2 -> left;
            temp2 -> right = temp;
            temp2 -> left = head;
            temp2 = updateB(temp2);
            return temp2;
        }
    }
    else
    {
        return head;
    }
}

void inorder(Tnode * root)
{
    if (root != NULL) {
        fprintf(stderr, "%d %d\n", root->key, getB(root));
        inorder(root->left);
        inorder(root->right);
    }
}

Tnode * maxValueNode (Tnode * Node)
{
    Tnode * curr = Node;
    while (curr && curr -> right != NULL)
    {
        curr = curr -> right;
    }
    return curr;
}

Tnode * deleteN (Tnode * root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    else if (key < root -> key)
    {
        root -> left = deleteN (root -> left, key);
    }
    else if (key > root -> key)
    {
        root -> right = deleteN (root -> right, key);
    }
    else
    {
        if (root -> left == NULL)
        {
            Tnode * temp = root -> right;
            free(root);
            return temp;
        }
        else if (root -> right == NULL)
        {
            Tnode * temp = root -> left;
            free(root);
            return temp;
        }
        Tnode * temp = maxValueNode(root -> left);
        root -> key = temp -> key;
        root -> left = deleteN(root -> left, temp -> key);
    }
    return root;
}

Tnode * updateB (Tnode * Node)
{
    if(Node != NULL)
    {
        Node -> balance = getB(Node);
        updateB(Node -> left);
        updateB(Node -> right);
    }
    return Node;
}

int maxDepth(Tnode * node)
{
    if (node == NULL)
        return 0;
    else {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node -> left);
        int rDepth = maxDepth(node -> right);

        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

int getB (Tnode * Node)
{
    return (maxDepth(Node -> left) - maxDepth(Node -> right));
}

void writeB(char * filename, Tnode * Node)
{
    if (Node == NULL)
    {
        return;
    }

    FILE * fptr;
    fptr = fopen(filename, "ab");

    int value = Node -> key;
    char bal = 0x00;


    if (Node -> right != NULL)
    {
        bal |= 0x01;
    }
    if (Node -> left != NULL)
    {
        bal |= 0x02;
    }
    printf("%d %c\n", value, bal);
    fwrite(&value, sizeof(value), 1, fptr);
    fwrite(&bal, sizeof(bal), 1, fptr);
    fclose(fptr);
    writeB(filename, Node -> left);
    writeB(filename, Node -> right);
    return;
}

void postfree(Tnode * head)
{
      if(head == NULL)
      {
          return;
      }
      postfree(head -> left);
      postfree(head -> right);
      free(head);
}
