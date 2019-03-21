//Kameron Gill
//kgill2@ucsc.edu

//lab 5 LinkedList.c
//Linked list adt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "BOARD.h"


//creates new LinkedList
//will give a pointer to an item if malloc'd
//if not return NULL

ListItem *LinkedListNew(char *data)
{
    //creates temp LinkedList
    ListItem *temp = malloc(sizeof (ListItem));

    //checks to see if temp is null
    if (temp == NULL) {
        //IF THERE IS RETUrn error
        return STANDARD_ERROR;
    } else {
        temp -> nextItem = NULL;
        temp -> previousItem = NULL;
        temp -> data = data;
        return temp;
    }
}




//create new item infront of list

ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *temp;
    temp = NULL;
    //checks to see if temp was macclocd
    if ((temp = (ListItem *) (malloc(sizeof (ListItem))))) {
        //checks if not NULL
        if (item->nextItem != NULL) {
            //if not null then inserts temp into 
            temp->previousItem = item;
            temp->nextItem = item->nextItem;
            item->nextItem->previousItem = temp;
            item->nextItem = temp;


        } else {
            //if is null, then set item to temp
            item->nextItem = temp;
            temp->previousItem = item;
            temp->nextItem = NULL;
            ;
        }
        temp->data = data;
    }
    return temp;
}


//retruns first element in the list or NULL if invalid

ListItem *LinkedListGetFirst(ListItem *list)
{
    while (list->previousItem) { //while list can go to previous item
        list = list->previousItem; //then go to previous item in list
    }
    //eventualy returns the top of the list
    return list;
}


//reutrns number of items in list

int LinkedListSize(ListItem *list)
{
    if (list != NULL) {
        int listSize = 0;
        if (list->nextItem) {
            list = LinkedListGetFirst(list);
            //Iterate through list until NULL
            while (list->nextItem) {
                listSize++;
                list = list->nextItem;
            }
        }
        return listSize + 1;

    }
    //else return null sicne list == null
    return NULL;
}



//prints out Linkedlist properly

int LinkedListPrint(ListItem *list)

{
    //creates temp list
    ListItem *temp;

    if (list != NULL) {


        temp = LinkedListGetFirst(list);
        printf("\n[ ");
        while (temp != NULL) {
            printf("%s, ", temp -> data);
            temp = temp -> nextItem;
        }
        printf(" ]");
        return SUCCESS;

    } else {
        return STANDARD_ERROR;
    }
}


//swaps position of data in the list
//success is retruns if swaps
//error if it fails

int LinkedListSwapData(ListItem *firstItem, ListItem * secondItem)
{
    //NULL pointers return ERROR
    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    } else {
        char *temp = NULL; //temporary variable
        temp = firstItem->data;
        firstItem->data = secondItem->data; //swap
        secondItem->data = temp; //swap
        return SUCCESS;
    }
}


//modify this later
//get help from tytior

int LinkedListSort(ListItem *list)
{
    ListItem *i, *j;
    int value;
    i = list;
    


    for (i = LinkedListGetFirst(list); i -> nextItem != NULL; i = i -> nextItem) {

        for (j = i -> nextItem; j != NULL; j = j -> nextItem) { // checks for next item and 
            if (i -> data != NULL && j -> data != NULL) {       // increments with if statement
			
			
			 value = strcmp(j -> data, i -> data); // stores value and compares two strings I,J
                if(strlen(j -> data) < strlen(i -> data)){
                    
                    LinkedListSwapData(j, i);       // swaps the data (i and j)
                }
                if (value < 0 && (strlen(i -> data) == strlen(j -> data))) {
                    LinkedListSwapData(i, j);
                }
               
            } else {
                ListItem *temp;
               // ListItem *temp1;
                //while (temp1 != NULL) {
                temp = LinkedListGetFirst(list);           
                LinkedListSwapData(j, temp);
               // temp = temp -> previousItem;
               // }
            }

        }
    }
    return SUCCESS;
}


