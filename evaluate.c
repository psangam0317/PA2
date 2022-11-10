//
//  evaluate.c
//  
//
//  Created by Pranav Sangam on 11/10/22.
//

#include "evaluate.h"
#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>


int calc_height(int*values, char*nodes, int size, int ind, int stop){
  if(nodes[ind] == 0){return 1;}
  int left;
  int right;
  int LH;
  int RH;

  right = ind + 1;
  while(values[right] <= values[ind]){right++;}
  int end = right;

  if(values[ind+1] < values[ind]){
    left = ind + 1;
    LH = calc_height(values, nodes, size, left, end);
  }else{LH = 0;}

  if(right < stop){
    RH = calc_height(values, nodes, size, right, HBT_MAX);
  }else{RH = 0;}

  int max;
  if(LH > RH){max = LH;}
  else{max = RH;}

  return(max + 1);
}


int hbcheck(int*values, char*nodes, int size){
  //Left Subtree
  if(values[1] > values[0]){return 0;}
  int left = 1;
  
  //Find Right Subtree(First value greater than Root in Array)
  int right = 1;
  while(values[right] <= values[0]){right++;}

  if(left == right){return 0;}

  int Lheight = calc_height(values, nodes, size, left, right);
  int Rheight = calc_height(values, nodes, size, right, HBT_MAX);

  int bal = Lheight - Rheight;

  if(bal < -2 || bal > 2){return 0;}
  else{return 1;}
}


int bstcheck(int*values, int size){
  //Check if Values List is BST
  //For every Value in List
  for(int root = 0; root < size-1; root++){
    //Find Right Subtree(First value greater than Root in Array)
    int right  = root + 1;
    while(values[right] <= values[root] && right < size - 1){right++;}
    //Check That Every element after is also greater than root
    for(int c = (right); c < size; c++){
      if(values[c] < values[root]){return 0;}
    }
  }
  return 1;
}


void eval(char*filename, int*valid, int*bst, int*hb){
  //1)Check File
  FILE * fptr = fopen(filename, "rb");
  if(fptr == NULL){
    *valid -= 1;
    return;
  }

  //i)Checks if there are even amount of int and char
  fseek(fptr, 0, SEEK_END);
  int size = ftell(fptr) / (sizeof(int) + sizeof(char));
  int check = size * (sizeof(int) + sizeof(char));
  if(check != ftell(fptr)){
    *valid -= 1;
    return;
  }
  fseek(fptr, 0, SEEK_SET);
  //ii)Reads Values and Checks them
  int * values = (int*)malloc((size) * sizeof(int));
  char * nodes = (char*)malloc(size * sizeof(char));
  for(int i = 0; i < size; i++){
    int Vcheck;
    char Ncheck;
    fread(&Vcheck, sizeof(int), 1, fptr);
    fread(&Ncheck, sizeof(char), 1, fptr);
    if(Vcheck > HBT_MAX || Vcheck < HBT_MIN || Ncheck < 0x00 || Ncheck > 0x03){
      *valid -= 1;
      return;
    }else{
      values[i] = Vcheck;
      nodes[i] = Ncheck;
    }
  }
  fclose(fptr);
  //2)Check BST
  *bst = bstcheck(values, size);

  //3)Check HBT
  if(size < 3){*hb = 1;}
  else{*hb = hbcheck(values, nodes,size);}

  free(values);
  free(nodes);
}


void convert(char*filename){
  FILE * fptr = fopen(filename, "rb");

  if(fptr == NULL){exit(EXIT_FAILURE);}
  fseek(fptr, 0, SEEK_END);
  int size = ftell(fptr) / (sizeof(int) + sizeof(char));
  
  fseek(fptr, 0, SEEK_SET);

  int value;
  char instr;
  for(int i = 0; i<size; i++){
    fread(&value, sizeof(int),1, fptr);
    fread(&instr, sizeof(char),1, fptr);
    printf("%d %c\n", value, instr);
  }

  fclose(fptr);
}
