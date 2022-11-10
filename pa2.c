//
//  pa2.c
//  
//
//  Created by Pranav Sangam on 11/10/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"
#include "build.h"
#include "evaluate.h"

int main (int argc, char * * argv)
{
    if (!strcmp(argv[1], "-b") && argc == 4)
    {
        int size = findsize(argv[2]);
        int * iarr = (int*) malloc (size * sizeof(int));
        char * carr = (char*) malloc (size * sizeof(char));
        readB(argv[2], size, iarr, carr);
        int i = 0;
        Tnode * root = NULL;
        for (i = 0; i < size; i++)
        {
            if (carr[i] == 'i')
            {
                root = insertN(root, iarr[i]);
                if (getB(root) <= 1 && getB(root) >= -1)
                {
                    root = rotate(root);
                }
                else
                {
                    while(getB(root) > 1 || getB(root) < -1)
                    {
                            root = rotate(root);
                    }
                }
            }
            else if (carr[i] == 'd')
            {
                root = deleteN(root, iarr[i]);
                if (getB(root) <= 1 && getB(root) >= -1)
                {
                    root = rotate(root);
                }
                else
                {
                    while(getB(root) > 1 || getB(root) < -1)
                    {
                            root = rotate(root);
                    }
                }
            }
            else
            {
                return EXIT_FAILURE;
            }
        }
        free(iarr);
        free(carr);
        //root = updateB(root);
        //inorder(root);
        writeB(argv[3], root);
        postfree(root);
    }
    else if (!strcmp(argv[1], "-e") && argc == 3)
        {
            int val = 1;
            int bst = -1;
            int hb = 0;
            eval(argv[2], &val, &bst, &hb);
            fprintf(stdout, "%d,%d,%d\n", val, bst, hb);
            if (val == 1)
            {
                return EXIT_SUCCESS;
            }
            else
            {
                return EXIT_FAILURE;
            }
        }
        else
        {
            fprintf(stdout, "-1");
            return EXIT_FAILURE;
        }
    }
