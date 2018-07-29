/*program to insert data into a ternary search tree and traverse to search for certain words contain the same prefix
created by Keming Zhang Stu# 813368*/

#include "ternary.h"

int main(int argc, char *argv[]){
	int i, len = 0, compare = 0, weight = 0;
    char c, prefix[MAX], buffer[MAX], *word;
    node_t *root = NULL;
	list_t *listNode = NULL;
	FILE *file;
	FILE *fout;
	file = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");
	while(!feof(file) && fscanf(file, "%d;", &weight)){
        word = (char *)malloc(MAX*sizeof(char));
		while(fscanf(file, "%c", &c)){
            if(c != '\n'){
                word[len] = c;
                len++;
            }else
                break;
		}
        if(word[len-1] == ','){
            word[len-1] = '\0';
        }else
            word[len] = '\0';
		insert(&root, word, weight);
        len = 0;
	}
    while(scanf("%s", prefix) != EOF){
        for(i=0; i<strlen(prefix); i++){
            buffer[i] = prefix[i];
        }
        buffer[i] = '\0';
        fprintf(fout, "\nPrefix: %s\n", prefix);
        compare = search(root, &listNode, prefix, buffer, compare);
        printf("Prefix:  %s found with %d char comparisons\n",prefix, compare);
        compare = 0;
        sortList(listNode);
		printList(listNode, fout);
		listNode = NULL;
    }
	return 0;
}