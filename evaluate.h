//
//  evaluate.h
//  
//
//  Created by Pranav Sangam on 11/10/22.
//

int calc_height(int*values, char*nodes, int size, int ind, int stop);
int hbcheck(int*values, char*nodes, int size);
int bstcheck(int*values, int size);
void eval(char*filename, int*valid, int*bst, int*hb);
void convert(char*filename);
