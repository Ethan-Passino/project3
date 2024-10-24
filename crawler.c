#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ADDR_LENGTH 1000

/*
 * a node in our linked-list of web addresses
 */
struct listNode{
  char addr[MAX_ADDR_LENGTH];

  struct listNode *next;
};

/*
 * returns 1 if the list starting at pNode contains the address addr,
 *    and returns 0 otherwise
 */
int contains(const struct listNode *pNode, const char *addr);

/*
 * inserts the address addr as a new listNode at the end of
 *    the list
 */
void insertBack(struct listNode *pNode, const char *addr);

/*
 * prints the addresses from pNode to the end of the list,
 *   one on each line
 */
void printAddresses(const struct listNode *pNode);

/*
 * frees the memory associated with this node and all subsequent nodes
 */
void destroyList(struct listNode *pNode);
  
/*
 * srcAddr should be a web address (e.g., http://www.yahoo.com).
 * link should point to an array of maxLinkLength characters.
 * getLink returns 1 if a link was found and 0 otherwise.
 * If a link was found, "link" will be filled in with the web address.
 */
int getLink(const char* srcAddr, char* link, const int maxLinkLength);

struct listNode* crawl(char* url, int hops) {
    struct listNode *pListStart;
    char startAddr[MAX_ADDR_LENGTH];
    char destAddr[MAX_ADDR_LENGTH];
    int hopNum, numHops;
    numHops = hops;
    pListStart = malloc(sizeof(struct listNode));

    strncpy(pListStart->addr, url, MAX_ADDR_LENGTH);
    strncpy(startAddr, url, MAX_ADDR_LENGTH);
    for(hopNum = 1; hopNum <= numHops; hopNum++) {
      int res = getLink(startAddr, destAddr, MAX_ADDR_LENGTH);

      if(!res) {
        // dead end return
        break;
      }

      if(contains(pListStart, destAddr)) {
        continue;
      }
      
      insertBack(pListStart, destAddr);
      strncpy(startAddr, destAddr, MAX_ADDR_LENGTH);
    }

    return pListStart;

}


/*
 * returns 1 if the list starting at pNode contains the address addr,
 *    and returns 0 otherwise
 */
int contains(const struct listNode *pNode, const char *addr){
  if(pNode == NULL) {
    return 0;
  }
  if(strcmp(((*pNode).addr), (addr)) == 0) {
    return 1;
  }
  if((pNode->next) != NULL) {
    return contains((*pNode).next, addr);
  }
  return 0;
    
  
}
    

/*
 * inserts the address addr as a new listNode at the end of
 *    the list
 */
void insertBack(struct listNode *pNode, const char *addr){
  if((*pNode).next != NULL) {
    insertBack((*pNode).next, addr);
  } else {
    struct listNode *newNode;
    newNode = malloc(sizeof(struct listNode));
    newNode->next = NULL;
    strcpy((*newNode).addr, addr);
    (*pNode).next = newNode;
  }
}


/*
 * prints the addresses from pNode to the end of the list,
 *   one on each line
 */
void printAddresses(const struct listNode *pNode){
  // TODO: complete this
  printf("Printing addrs...\n");
  if(pNode == NULL) {
    printf("NULL NODE\n");
    return;
  }
  printf("%s\n", (*pNode).addr);
  printf("Printed addresses\n");
  if((*pNode).next != NULL) {
    printf("next addr\n");
    printAddresses(((*pNode).next));
  }
}

/*
 * frees the memory associated with this node and all subsequent nodes
 */
void destroyList(struct listNode *pNode){

  if(((*pNode).next) != NULL) {
    destroyList(((*pNode).next));
  }

  // Method that frees memory.
  free(pNode);
  // TODO: complete this
}
  


int getLink(const char* srcAddr, char* link, const int maxLinkLength){
  const int bufSize = 1000;
  char buffer[bufSize];

  int numLinks = 0;

  FILE *pipe;

  snprintf(buffer, bufSize, "curl -s \"%s\" | python3 getLinks.py", srcAddr);

  pipe = popen(buffer, "r");
  if(pipe == NULL){
    fprintf(stderr, "ERROR: could not open the pipe for command %s\n", buffer);
    return 0;
  }

  fscanf(pipe, "%d\n", &numLinks);

  if(numLinks > 0){
    int linkNum;
    double r = (double)rand() / ((double)RAND_MAX + 1.0);

    for(linkNum=0; linkNum<numLinks; linkNum++){
      fgets(buffer, bufSize, pipe);
      
      if(r < (linkNum + 1.0) / numLinks){
		    break;
      }
    }

    /* copy the address from buffer to link */
    strncpy(link, buffer, maxLinkLength);
    link[maxLinkLength-1] = '\0';
    
    /* get rid of the newline */
    {
      char* pNewline = strchr(link, '\n');
      if(pNewline != NULL){
		    *pNewline = '\0';
      }
    }
  }

  pclose(pipe);

  if(numLinks > 0){
    return 1;
  }
  else{
    return 0;
  }
}
