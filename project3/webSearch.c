/* File: indexPage.c */
/* Author: Britton Wolfe */
/* Date: September 3rd, 2010 */

/* This program indexes a web page, printing out the counts of words on that page */

#include "crawler.h"
#include "indexPage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
  /* TODO: write the (simple) main function
  argv[1] will be the URL to index, if argc > 1 */
if(argc <= 2) {
  printf("You need to input a file and max number of hops. Execute like\n./webSearch <file> <max number of hops>\n");
  exit(-1);
}

char startAddr[MAX_ADDR_LENGTH];

int maxHops = atoi(argv[2]);
if(maxHops <= 0) { //err handling
  printf("You need to input a file and max number of hops. Execute like\n./webSearch <file> <max number of hops>\n");
  printf("Make sure that maxHops is a integer and that it is greater than zero.\n");
  exit(-2);
}

FILE *fptr = fopen(argv[1], "r"); // read only
if(fptr == NULL) {
  printf("Unable to open the file specified.");
  printf("You need to input a file and max number of hops. Execute like\n./webSearch <file> <max number of hops>\n");
  exit(-3);
}

long seed;

int hopNum;

struct listNode *pListStart;

seed = time(NULL);
srand(seed);

strncpy(startAddr, argv[1], MAX_ADDR_LENGTH);
startAddr[MAX_ADDR_LENGTH - 1] = '\0';

pListStart = malloc(sizeof(struct listNode));
if(pListStart == NULL) {
    fprintf(stderr, "ERROR: could not allocate memory.\n");
    exit(-4);
}

strncpy(pListStart->addr, startAddr, MAX_ADDR_LENGTH);
pListStart->next = NULL;
int n = 0;
char url[MAX_ADDR_LENGTH];
char destAddr[MAX_ADDR_LENGTH];
int hopsLimit;
// Start Crawling (USE PSEDUEO CODE IN PROJECT DESCRIPTION)
    while (fgets(url, sizeof(url), fptr) && n < maxHops) {
        //?hopsLimit = 10;  // example value
        hopNum = 0;
        hopsLimit = maxHops; //????        while (1) {
            // check if url is already crawled/indexed
            int res = 0;
            if (!(contains(pListStart, url))) { 
              printf("getting links\n");
              res = getLink(url, destAddr, MAX_ADDR_LENGTH);
              n++;
            }
            hopNum++;
            
            if (hopNum <= hopsLimit && n < maxHops) {
                printf("%s\n", destAddr);
                if (!res) { // Check dead ends "check crawler.c"
                printf("dead end\n");
                  break;  // url was a dead end
                }
                insertBack(pListStart, url);
                strcpy(url, destAddr);
                printf("Inserting in the back and setting url to new url.\n");
            } else {
                break;  // hop limit or max N reached
            }
        }


  //struct TrieNode *root = malloc(sizeof(struct TrieNode));
  //setupNode(root);
  //root-> count = -100;
  
  //char *wrd = malloc(sizeof(char) * 50);
  //int *count = malloc(sizeof(int));
  //*count = 0;

  //freeTrieMemory(root);
  //free(root);
  //free(wrd);
  //free(count);
  fclose(fptr);
  destroyList(pListStart);
  return 0;
}