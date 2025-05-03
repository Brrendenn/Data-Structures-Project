#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct trie{//the structure for the trie
    char character;
    int Word;
    char *desc;
    struct trie *child[128];
};

struct trie *createNode(char character){
    struct trie *newNode = malloc(sizeof(struct trie)); //memory allocation for a node.
    newNode->character = character;
    newNode->Word = 0;
    newNode->desc = NULL;
    memset(newNode->child, 0, sizeof(newNode->child));//this line use memset to set the bytes in child to 0.
    return newNode;
}

void insertWord(struct trie **root, char *word, char *desc){//double pointer to the trie struct for the root of the trie
    if(*root == NULL) *root = createNode('*');//this line checks if the trie is NULL or empty
    //if it is empty then the root will be a character '*'.
	//curr = (current) saya hanya singkatkan saja biar tidak terlalu panjang
    struct trie *curr = *root;//this is for iterating the trie
    while(*word){//this loop iterates each char in the word
        if(curr->child[*word] == NULL){//if the curr trie node doesnt have a child that
            curr->child[*word] = createNode(*word);//corresponds to the word, it creates a new node with the curr character and assign it to the child
        }
        curr = curr->child[*word];//this line moves the curr pointer to the child corresponding to the curr character
        word++;//this line increments the word to move to the next character
    }
    curr->Word = 1;//because all the word have been iterated. this line marks the EOW
    curr->desc = malloc(strlen(desc) + 1);//this line allocates memory for the description
    strcpy(curr->desc, desc);//this line copies the description to the allocated memory.
}

void printTrie(struct trie *node, char *buffer, int depth, int *count){
    int i;
    if(node == NULL) return;//if the trie/node is NULL it returns 
	
    if(node->character != '*'){//if the character in the node is not
    						   //an asterisk then it will be added to the buffer at the curr depth
        buffer[depth] = node->character;
    }
	
    if(node->Word){//if the node marks the EOW
        buffer[depth + 1] = '\0';//a null char is added to the buffer to mark the EOW
        printf("%d. %s\n",(*count)++, buffer);//count is incremented for the numbering
    }

    for(i = 0; i < 128; i++){//for loop iterates the children using ASCII char 128 characters
        if(node->child[i] != NULL){//if the i-th child of the node exists it will call the function repeteadly
            if(node->character != '*') depth++;//this is for traversing through the depth of the trie
            printTrie(node->child[i], buffer, depth, count);//recursive
        }
    }
}

void searchPrefix(struct trie *root, char *prefix){
    int i;
    char buffer[100] = {0};
    int depth = 0;
    int count = 1;
    struct trie *curr = root;//curr is a pointer pointing to root for
    //traversing the trie node to node

    while(*prefix){
        if(curr == NULL){//if the curr is null
            break;
        }
        curr = curr->child[*prefix];//this makes curr point to the child that has the current character in the prefix.
        buffer[depth++] = *prefix++;//this one adds the current character in the prefix to the buffer and increments the depth and prefix.
    }
    
    if(curr == NULL){//if there are no prefix after traversing the trie
        printf("There is no prefix ""%s"" in the dictionary.\n", buffer);
        //it will print that
        return;
    }

    if(curr != NULL){//if the curr is not null then it will print the words starting with the prefix
        printf("Words starting with ""%s"": \n", buffer);
        if(curr->Word){
            printf("%d. %s\n", count++, buffer);
        }
    }

    for(i = 0; i < 128; i++){//for loop iterates the children using ASCII char 128 characters same as the function above
        if(curr->child[i] != NULL){
            printTrie(curr->child[i], buffer, depth, &count);//this calls the function again recursively.
        }
    }
}

void search(struct trie *root, char *word){
	char *saveWord = word;//this creates a pointer saveWord to keep the original word
    struct trie *curr = root;//this curr is the same for traversing the trie
    while(*word){//while loop for as long as the word is not a null character
        if (curr == NULL || curr->child[*word] == NULL) {//if the curr or the child
        	//of the curr is null then it will print this statement.
            printf("The word %s is not present in the dictionary.\n", word);
            return;
        }
        curr = curr->child[*word];//this line moves the curr poiinter to the child node that
        //corresponds to the curr character in word
        word++;//this is for going through the next character
    }
    if(curr != NULL && curr->Word){//if the curr is not null and it is thhe word
        printf("Slang word: %s\n", saveWord);
        printf("Description: %s\n", curr->desc);
    }
}

int haveSpace(char *str){//this function is for counting the spaces
    while(*str){
        if(*str == ' ') return 1;
        str++;
    }
    return 0;
}

int wordCount(char *str){//this function is for counting the words
    int count = 0;
    int inWord = 0;
    while(*str){
        if(*str == ' '){//if the character is a space
            inWord = 0;//we are not currently in a word
        }else{
            count += !inWord;
            inWord = 1;
        }
        str++;
    }
    return count;
}

int main(){//This is the main function
    struct trie *root = NULL;//set the trie root to null first
    char word[100];
    char description[100];
    int option;
    int count = 1;

    while(1){
    	system("cls");//clearing the screen
    	printf("============Boogle=============\n");//The menu
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);getchar();
        switch(option){
            case 1:
                do{
                    printf("Input a new slang word [Must be more than 1 character and contains no space]: ");
                    scanf("%[^\n]", word);getchar();
                }while(strlen(word) <= 1 || haveSpace(word));
				
				do{
                	printf("Input a new slang word description [Must be more than 2 words]: ");
                	scanf("%[^\n]", description);getchar();
				}while(wordCount(description) < 2);
                
                insertWord(&root, word, description);
                break;
            case 2:
                do {
                    printf("Input a slang word to be searched [Must be more than 1 character and contains no space]: ");
                    scanf("%s", word);getchar();
                } while(strlen(word) <= 1 || haveSpace(word));
				search(root, word);
                break;
            case 3:
                do {
                    printf("Input a prefix to be searched: ");
                    scanf("%s", word);getchar();
                } while(strlen(word) <= 1 || haveSpace(word));

                searchPrefix(root, word);
                break;
            case 4:
            	count = 1;
            	printf("List of all the slang words in the dictionary: \n");
                printTrie(root, word, 0, &count);
                break;
            case 5:
                printf("Thank you..., Have a nice day :))\n");
                exit(0);
        }
        printf("Press enter to continue...");
        getchar();
    }
	return 0;
}


