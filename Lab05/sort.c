// Heap size 1024 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "LinkedList.h"

// **** Set any macros or preprocessor directives here ****
#define LINKED_LIST_TESTING  //comment this out once the LinkedList Library is working

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
static char *dog = "dog";
static char *pig1 = "pig";
static char *pig2 = "pig";
static char *cow = "cow";
static char *cat = "cat";
static char *turtle = "turtle";
static char *bird = "bird";
static char *crab = "crab";

// **** Declare any function prototypes here ****
int InitializeUnsortedWordList(ListItem **unsortedWordList);
int UnsortedWordCount(ListItem *list, int *wordCount);
int SortedWordCount(ListItem *list, int *wordCount);

int main()
{
    BOARD_Init();

    /**
     * ----------------------- STARTER CODE --------------------------
     * This segment of code obtains an unsorted word list, prints it out,
     * and displays the number of occurrences of each word in the list as
     * described by UnsortedWordCount() below.
     */
    // Initialize an unsorted word list.
    ListItem *unsortedWordList = NULL;
    if (!InitializeUnsortedWordList(&unsortedWordList) || !unsortedWordList) {
        printf("ERROR: Failed to initialize word list\n");
        while (1);
    }

    // Print the list
    LinkedListPrint(unsortedWordList);

    // Get the word counts for every string in the list
    int g = LinkedListSize(unsortedWordList);
    int wordCount[g];

    // Print the word count results
    unsortedWordList = LinkedListGetFirst(unsortedWordList);
    if (UnsortedWordCount(unsortedWordList, wordCount)) {
        printf("[%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n",
                wordCount[0], wordCount[1], wordCount[2],
                wordCount[3], wordCount[4], wordCount[5],
                wordCount[6], wordCount[7], wordCount[8],
                wordCount[9]);
    } else {
        printf("ERROR\n");
    }
    printf("\n");

    /******************************** Your custom code goes below here ********************************/

    int i;
    LinkedListSort(unsortedWordList);
    LinkedListPrint(unsortedWordList);
    if (SortedWordCount(unsortedWordList, wordCount)) {
        printf("[");
        for (i = 0; i < g - 1; i++) {
            printf("%d, ", wordCount[i]);
        }
        printf("%d]", wordCount[g - 1]);
    } else {
        printf("Error, you failed!\n");
    }

    /******************************** Your custom code goes above here ********************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}

//#ifndef LINKED_LIST_TESTING

/**
 * This functions takes in the head of an unsorted list of words, and an array to store the number
 * of occurrences of each word.  The first time a word appears, the number of occurrences of that
 * word should be stored in the corresponding position in the array.  For repeated words the
 * negative of the number of occurrences should be stored.  For example, a list of the following
 * words should return an array with the following values:
 *     {"hair", "comb", "brush", "brush"} -> {1, 1, 2, -2}
 *
 * NULL values are treated as non-strings, so they always count as 0. Every other string is treated
 * as regular strings that can have multiple occurrences, including the empty string, as the
 * following output demonstrates.
 *     {NULL, "platypus", "giraffe", "", "corvid", "slug", "", NULL, "platypus", "platypus"} ->
 *     [0   , 3         , 1        , 2 , 1       , 1     , -2, 0   , -3        , -3}
 *
 * NOTE: This function assumes that wordCount is the same length as list.
 * @param list A pointer to the head of a doubly-linked list containing unsorted words.
 * @param wordCount An array of integers. The output of this function is stored here. It must be
 *                  at least as big as the linked list pointed to be `list` is.
 * @return Either SUCCESS or STANDARD_ERROR if the head of the doubly-linked list isn't passed.
 */
int UnsortedWordCount(ListItem *list, int *wordCount)
{
    // Make sure the head of the list was given.
    if (list->previousItem != NULL) {
        return STANDARD_ERROR;
    }

    char *word1;
    char *word2;
    char *repCheck;
    ListItem *item1 = list;
    ListItem *item2;
    int temp, firstOccurencePos;
    int repetitionFlag = 0;
    int i, j;

    i = 0;
    while (item1 != NULL) {
        // Count first occurrence
        j = 1;
        // Ignore NULL words
        word1 = item1->data;
        if (word1 == NULL) {
            wordCount[i++] = 0;
            item1 = item1->nextItem;
            continue;
        }

        // Check previous occurrences
        temp = i;
        item2 = item1->previousItem;
        while (item2 != NULL) {
            --temp;
            repCheck = item2->data;
            if (repCheck != NULL && strcmp(repCheck, word1) == 0) {
                repetitionFlag = 1;
                firstOccurencePos = temp;
            }
            item2 = item2->previousItem;
        }

        // Count new occurrences
        if (repetitionFlag == 0) {
            item2 = LinkedListGetFirst(list);
            while (item2 != NULL) {
                word2 = item2->data;
                if (word2 != NULL && item1 != item2 && strcmp(word1, word2) == 0) {
                    ++j;
                }
                item2 = item2->nextItem;
            }
            wordCount[i++] = j;
        } else {
            wordCount[i++] = -wordCount[firstOccurencePos];
            repetitionFlag = 0;
        }
        item1 = item1->nextItem;
    }
    return SUCCESS;
}

/**
 * This function initializes a list of ListItems for use when testing the LinkedList implementation
 * and word count algorithms.
 *
 * Usage:
 * ListItem *newList;
 * InitializeUnsortedWordList(&newList);
 *
 * @param unsortedWordList[out] Where to store the pointer to the head of the list.
 * @return SUCCESS if it succeeds, STANDARD_ERROR if it fails to allocate necessary memory.
 */
int InitializeUnsortedWordList(ListItem **unsortedWordList)
{
    ListItem *tmp = LinkedListNew(crab);
    if (!tmp) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, pig1)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, cow)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, NULL)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, dog)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, cow)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, bird)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, pig2)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, cat)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, turtle)) {
        return STANDARD_ERROR;
    }
    *unsortedWordList = tmp;
    return SUCCESS;
}

/**
 * SortedWordCount() takes in the head of a sorted list of words arranged lexicographically, and an
 * array to store the number of occurrences of each word.  The first time a word appears, the number
 * of occurrences of that word should be stored in the corresponding position in the array.  For
 * duplicate words a negative value of the number of occurrences should be stored.  For example, a
 * list of the following words should return an array with the following values:
 *     {"brush", "brush", "comb", "hair"} -> {2, -2, 1, 1}
 *
 * NULL values are treated as non-strings, so they always count as 0. Every other string is treated
 * as regular strings that can have multiple occurrences, including the empty string, as the
 * following output demonstrates.
 *     {NULL, "platypus", "giraffe", "", "corvid", "slug", "", NULL, "platypus", "platypus"} ->
 *     [0   , 3         , 1        , 2 , 1       , 1     , -2, 0   , -3        , -3}
 *
 * NOTE: This function assumes that wordCount is the same length as list.
 * @param list A pointer to the head of a doubly-linked list containing sorted words.
 * @param wordCount An array of integers. The output of this function is stored here. It must be
 *                  at least as big as the linked list pointed to be `list` is.
 * @return Either SUCCESS or STANDARD_ERROR if the head of the doubly-linked list isn't passed.
 */

int SortedWordCount(ListItem *list, int *wordCount)
{
    ListItem *i, *j;
    int count = 0;
    int k = 0;
    int p = 0;


    //checks if previousitem in list is NULL
    if (list -> previousItem == NULL) {
        //goes to first item in list and then goes through entire list
        for (i = LinkedListGetFirst(list); i -> nextItem != NULL; i = i -> nextItem) {
            //checks if null,
            if (i -> data == NULL) {
                //iterates thru list
                for (j = i -> nextItem; j != NULL; j = j -> nextItem) {
                    //checks to see if data in both list are the same
                    if (i->data == j->data) {
                        count++;
                    }
                }
                wordCount[k] = count;
                for (j = i -> nextItem; j != NULL; j = j -> nextItem) {
                    if (i->data == j->data) {
                        wordCount[p] = -1 * count;
                    }
                    p++;
                }
            } else {

                wordCount = 0;
                continue;
            }
            k++;

        }
        return SUCCESS;

        //returns error if not NULL
    } else {
        return STANDARD_ERROR;
    }
}