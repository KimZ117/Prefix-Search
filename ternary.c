/*program to insert data into a ternary search tree and traverse to search for certain words contain the same prefix
created by Keming Zhang Stu# 813368*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX 250

#include "ternary.h"


/*function to insert word into linked list*/
void insertList(list_t** head, char *word, int weight){
	//printf("init\n");
	list_t* newLnode = (list_t*)malloc(sizeof(list_t));
	list_t* lastNode = *head;
	int i;
	for(i=0; i<strlen(word); i++){
		newLnode->word[i] = word[i];
	}
	newLnode->word[i] = '\0';
	newLnode->weight = weight;
	newLnode->next = NULL;
	//printf("%s\n", newLnode->word);
	/*base case: empty list*/
	if(*head == NULL){
		*head = newLnode;
		return;
	}
	/*traverse through list untill null*/
	while(lastNode->next != NULL)
		lastNode = lastNode->next;
	lastNode->next = newLnode;
	return;
}

/*create a new node*/
node_t* newNode(char data){
    node_t* temp = (node_t*) malloc(sizeof(node_t));
    temp->data = data;
    temp->weight = 0;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

/*Function to insert a new word in a Ternary Search Tree*/
void insert(node_t** root, char *word, int weight){
    /*Tree is empty*/
    if (!(*root))
        *root = newNode(*word);
 
    /*If current character of word is smaller than root's character,
    then insert this word in left subtree of root*/
    if ((*word) < (*root)->data)
        insert(&((*root)->left), word, weight);
 
    /* If current character of word is greate than root's character,
    then insert this word in right subtree of root*/
    else if ((*word) > (*root)->data)
        insert(&((*root)->right), word, weight);
 
    /*If current character of word is same as root's character*/
    else{
        if (*(word+1))
            insert(&((*root)->eq), word+1, weight);
 
        /*last character of the word, insert weight*/
        else{
            (*root)->isEndOfString = 1;
            (*root)->weight = weight;
        }
    }
}
 
/*A recursive function to traverse Ternary Search Tree*/
void traverseTST(node_t* root, list_t** listNode, char* buffer, int depth){
	if (root){
        /*First traverse the left subtree*/
        traverseTST(root->left, listNode, buffer, depth);
 
        /*Store the character of this node*/
        buffer[depth] = root->data;
        if (root->isEndOfString){
            buffer[depth+1] = '\0';
			insertList(listNode, buffer, root->weight);
        }
 
        /*Traverse the subtree using equal pointer (middle subtree)*/
        traverseTST(root->eq, listNode, buffer, depth + 1);
 
        /*Finally Traverse the right subtree*/
        traverseTST(root->right, listNode, buffer, depth);
    }
}
 
/*Function to search a given word in TST*/
int search(node_t *root, list_t** listNode, char *word, char *buffer, int compare){
    if (!root){
        return compare;
    }
    if (*word < root->data){
        compare++;
        return search(root->left, listNode, word, buffer, compare);
    }
 
    else if (*word > root->data){
        compare++;
        return search(root->right, listNode, word, buffer, compare);
    }
 
    else{
        compare++;
        if (*(word+1) == '\0'){
            traverseTST(root->eq, listNode, buffer, strlen(buffer));
            return compare;
        } 
        return search(root->eq, listNode, word+1, buffer, compare);
    }
}

/*swap strings*/
void swapString(char *str1, char *str2){
    char *temp = (char*)malloc(MAX*sizeof(char));
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
    free(temp);
}

/*sort the linked list*/
void sortList(list_t *head){
    list_t *temp = (list_t*)malloc(sizeof(list_t));
    list_t *i = (list_t*)malloc(sizeof(list_t));
    list_t *j = (list_t*)malloc(sizeof(list_t));
    temp = head;
    int compare = 0;
    for(i=temp; i!=NULL && i->next!=NULL; i=i->next){
        list_t *maxNode;
        maxNode = i;
        for(j=i->next; j!=NULL; j=j->next){
            compare++;
            if(j->weight > maxNode->weight)
                maxNode = j;
        }
        if(maxNode != i){
            int data;
            char *str = (char*)malloc(MAX*sizeof(char));
            data = maxNode->weight;
            strcpy(str, maxNode->word);
            maxNode->weight = i->weight;
            i->weight = data;
            swapString(maxNode->word, i->word);
            swapString(i->word, str);
            free(str);
        }
    }
    printf("Selection Sort:  %d weight comparison\n", compare);
    compare = 0;
}

void printList(list_t *list, FILE* fout){
	if(list == NULL)
		fprintf(fout, "NOTFOUND\n");
	while(list != NULL){
		fprintf(fout, "key: %s --> weight: %d\n", list->word, list->weight);
		list = list->next;
	}
}