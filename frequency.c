#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE ((int)26)
#define MAX_WORD_SIZE 80
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])


struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    int freq;
};

struct TrieNode* newNode()
{
    struct TrieNode* node = NULL;

    node = (struct TrieNode*)malloc(sizeof(struct TrieNode));

    if(node)
    {
        int i;
        node->isEndOfWord=false;
        node->freq=0;

        for(i=0;i<ALPHABET_SIZE;i++)
            node->children[i]=NULL;
    }
    return node;
} 

void insert(struct TrieNode* root, const char* word)
{
    int letterPos;
    int index;
    int length = strlen(word);
    char letter;

    struct TrieNode *runner = root;

    for(letterPos=0; letterPos<length; letterPos++)
    {
        letter = word[letterPos];
        letter = tolower(letter);
        if(letter<'a'||letter>'z')      //ignore non letter chars
            continue;
        index = letter-'a';

        if(runner->children[index]==NULL)
            runner->children[index] = newNode();

        runner = runner->children[index];
    }

    runner->isEndOfWord=true;
    (runner->freq)++;
}

void display(struct TrieNode* root, char* word, int level, char **arr, int arrIndex, int *freqArr)
{
    if(root->isEndOfWord)
    {
        int j = 0;
        word[level] = '\0';
        while(freqArr[j]!=0){       //find next free spot, not very elegant
            j++;
        }
        freqArr[j] = root->freq;
        strcpy(arr[j], word);              
    }

    int i;
    for(i=0; i<ALPHABET_SIZE; i++)
    {
        if(root->children[i])
        {
            word[level] = i+'a';
            display(root->children[i], word, level+1, arr, arrIndex, freqArr);
        }
        
    }
}

bool freeSpace(struct TrieNode *root)
{
    for(int i=0; i<ALPHABET_SIZE; i++)
    {
        if(root->children[i]!=NULL)
        {
            freeSpace(root->children[i]);
        }
    }
    free(root);
    return true;
}

int main(int argc, char **argv) 
{ 
    bool reverse=false;
    if(argc==2)
    {
        if(!strncmp(argv[1], "r", 1))
        reverse=true;

    }

    struct TrieNode *root = newNode(); 
  
    size_t numOfWords = 0;

    char toInsert [256];
    while (scanf(" %s", toInsert)!=EOF)
    {
        insert(root, toInsert);
        numOfWords++;
    }
    
    char **arrOfWords;
    int *arrOfFreq;

    int i;
    
    arrOfFreq = (int*)malloc(numOfWords*sizeof(int));
   

    arrOfWords = (char**)malloc(numOfWords*sizeof(char*));
    for(i=0; i<numOfWords; i++)
        arrOfWords[i] = malloc(MAX_WORD_SIZE*sizeof(char));
   

    int level = 0;
    char word[MAX_WORD_SIZE];
    int arrIndex = 0;

    
    display(root, word, level, arrOfWords, arrIndex, arrOfFreq);

    if(reverse==true)
    {
        for(i=numOfWords-1;i>=0;i--)
        {
            if(arrOfFreq[i]==0)
                continue;
            printf("%s  ", arrOfWords[i]);
            printf("%d\n", arrOfFreq[i]);
        }
    }
    else
    {
        for(i=0;i<numOfWords;i++){
        if(arrOfFreq[i]==0)
            break;
        printf("%s\t", arrOfWords[i]);
        printf("%d\n", arrOfFreq[i]);
    }
    }

    free(arrOfFreq);

    for(i=0;i<numOfWords;i++)
        free(arrOfWords[i]);
    
    free(arrOfWords);

    freeSpace(root);   
  
    return 0;
} 
