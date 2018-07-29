/*program to insert data into a ternary search tree and traverse to search for certain words contain the same prefix
created by Keming Zhang Stu# 813368*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX 250

/*A single node of ternary search tree*/
typedef struct node node_t;
struct node{
    char data; 
    int weight;
    unsigned isEndOfString: 1; 
    struct node *left, *eq, *right;
};

/*node of a linked list to store data*/
typedef struct list list_t;
struct list{
	char word[MAX];
	int weight;
	struct list* next;
};

node_t* newNode(char data);
void sortList(list_t *head);
void swapString(char *str1, char *str2);
void printList(list_t *list, FILE* fout);
void insert(node_t** root, char *word, int weight);
void insertList(list_t** head, char *word, int weight);
void traverseTST(node_t* root, list_t** listNode, char* buffer, int depth);
int search(node_t *root, list_t** listNode, char *word, char *buffer, int compare);