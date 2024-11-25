#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct trie
{
    int sumFrequency;
    int currentMaxFrequency;
    int frequency;
    struct trie *next[26];
};

struct trie *init();
struct trie *deleteEntry(struct trie *root, char key[], int depth);
void insertEntry(struct trie *tree, char word[], int k, int f);
void printTree(struct trie *tree, char cur[]);
void freeTrie(struct trie *root);
int searchEntry(struct trie *tree, char word[], int k);
int isEmpty(struct trie *root);

int main()
{
    struct trie *dictionary = init(); // Initialize the trie

    int entryAmount = 0;
    scanf("%d", &entryAmount);
    printf("DEBUG: Amount of entries: %d\n", entryAmount);

    int i;

    for (i = 0; i < entryAmount; i++)
    {
        int mode = 0;
        scanf("%d", &mode);

        if (mode == 1)
        {
            char *inputEntry = (char *)malloc(sizeof(char) * 2000000);
            int entryFrequency = 0;
            scanf("%s %d", inputEntry, &entryFrequency);
            if (entryFrequency < 0 || entryFrequency > 1000000000)
            {
                printf("ERROR: Frequency is an invalid number\n");
                return -1;
            }
            insertEntry(dictionary, inputEntry, 0, entryFrequency);
            printf("1 %s %d\n", inputEntry, entryFrequency);
            free(inputEntry);
        }
        if (mode == 2)
        {
            char *inputEntry = (char *)malloc(sizeof(char) * 2000000);
            scanf("%s", inputEntry);
            printf("2 %s\n", inputEntry);
            free(inputEntry);
        }
    }
  

    return 0;
}

struct trie *init()
{
    struct trie *myTree = (struct trie *)malloc(sizeof(struct trie));
    myTree->sumFrequency = 0;
    myTree->currentMaxFrequency = 0;
    myTree->frequency = 0;

    for (int i = 0; i < 26; i++)
    {
        myTree->next[i] = NULL;
    }
    return myTree;
}

void insertEntry(struct trie *tree, char word[], int k, int f)
{

    if (word[k] == '\0')
    {
        tree->frequency = f;
        return;
    }

    int nextIndex = word[k] - 'a';

    tree->currentMaxFrequency += f; // Add the frequency to the currentMaxFrequency
    tree->sumFrequency += f;        // Add the frequency to the sumFrequency

    if (tree->next[nextIndex] == NULL) {
        tree->next[nextIndex] = init();
        printf("DEBUG: Created new node\n");
    }
    insertEntry(tree->next[nextIndex], word, k + 1, f);
}

void printTree(struct trie *tree, char cur[])
{
    if (tree == NULL)
        return;

    if (tree->frequency > 0)
        printf("%s %d\n", cur, tree->frequency);

    for (int i = 0; i < 26; i++)
    {
        if (tree->next[i] != NULL)
        {
            char *newCur = (char *)malloc(sizeof(char) * 2000000);
            strcpy(newCur, cur);
            newCur[strlen(newCur)] = i + 'a';
            newCur[strlen(newCur) + 1] = '\0';
            printTree(tree->next[i], newCur);
            free(newCur);
        }
    }
}
