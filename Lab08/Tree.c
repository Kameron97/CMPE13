//Kameron Gill
//kgill2@ucsc.edu

//Tree.c


#include "Tree.h"
#include "Buttons.h"
#include "Board.h"

Node *TreeCreate(int level, const char *data) {
    Node *temp = NULL;
    if ((temp = (Node*) (malloc(sizeof (Node))))) {
        temp->data = *data;
        if (level == 1) {
            temp->leftChild = NULL;
            temp->rightChild = NULL;
            return temp;
        }

        temp->leftChild = TreeCreate(level - 1, data + 1);

        temp->rightChild = TreeCreate(level - 1, data + (1 << (level - 1)));
    }
    return temp;
}
