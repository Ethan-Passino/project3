#ifndef INDEXPAGE_H
#define INDEXPAGE_H


#define ALPHA_SIZE 26
#define MAX_BUFFER_SIZE 300000

/* TODO: structure definitions */
struct TrieNode
{
  int letter;
  struct TrieNode* nextNode[ALPHA_SIZE];
  int count;
};

/* NOTE: int return values can be used to indicate errors (typically non-zero)
   or success (typically zero return value) */

/* TODO: change this return type */
struct TrieNode* indexPage(const char* url, struct TrieNode* root);

int addWordOccurrence(const char* word, struct TrieNode* root);

void printTrieContents(struct TrieNode* root, char *word, int *count);

int freeTrieMemory(struct TrieNode* root);

int getText(const char* srcAddr, char* buffer, const int bufSize);

void setupNode(struct TrieNode* node);

void addWordProcess(char *arr, int bytes, struct TrieNode *root);

void removeSpaces(char *str);


#endif