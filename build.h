//
//  build.h
//  
//
//  Created by Pranav Sangam on 11/10/22.
//

int findsize (char * filename);
void readB (char * filename, int size, int * iarr, char * carr);
Tnode * newNode (int item);
Tnode * insertN (Tnode * Node, int item);
Tnode * rotate(Tnode * head);
void inorder(Tnode * root);
Tnode * maxValueNode (Tnode * Node);
Tnode * deleteN (Tnode * root, int key);
Tnode * updateB (Tnode * Node);
int maxDepth(Tnode * node);
int getB (Tnode * Node);
void writeB(char * filename, Tnode * Node);
void postfree(Tnode * head);
