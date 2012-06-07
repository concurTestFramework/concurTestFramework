//  types.cpp : data types and helper functions for synchronization problems

#include <iostream>
#include <string>
#include <sstream>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include "typeUtils.h"
using namespace std;

bool debug = false;


// prototypes
ThreadNode* addThreadNode(int size, ThreadNode *head, int nodeId);
ThreadNode* deleteThreadNode(int size, ThreadNode *head, int position);
ThreadNode* retrieveThreadNode(int size, ThreadNode *head, int position);


// Adds a new ThreadNode to the end of the list
ThreadNode*  addThreadNode(int originalSize, ThreadNode *head, int newNode) {
  if (debug) {
    printf("typeUtils - addThreadNode:  originalSize=%d, newNode=%d\n", originalSize, newNode);
  }

  ThreadNode *temp = new ThreadNode;
  ThreadNode *newHead = head;
  temp->id = newNode;
  temp->next = NULL;
  if(originalSize == 0) { // first node
    newHead = temp;
  }
  else {
    retrieveThreadNode(originalSize, head, originalSize-1)->next = temp;
  }
  return newHead;
}

// Deletes a ThreadNode at specified position
ThreadNode* deleteThreadNode(int size, ThreadNode *head, int position) {
  ThreadNode *newHead = head;
  if( (position > -1) && (position < size) ) {
    if(position == 0) { // delete first element
      newHead = retrieveThreadNode(size, head, position+1);
    }
    else if(position == size) { // delete last element
      retrieveThreadNode(size, head, position-1)->next = NULL;
    }
    else {
      retrieveThreadNode(size, head, position - 1)->next = retrieveThreadNode(size, head, position+1);
    }
  }
  return newHead;
}

// Retrieves a ThreadNode at specified position.
ThreadNode *retrieveThreadNode(int size, ThreadNode *head,  int position ) {
  if (debug) {
    printf("typeUtils - retrieveThreadNode: size=%d, position=%d\n", size, position);
  }
  ThreadNode *current = NULL;
  if( (position > -1) && (position < size) ) {
    current = head;
    for(int i=0; i < position; i++) {
      current = current->next;
    }
  }
  return current;
}

// Prints thread list
string printThreads(int size, ThreadNode *head) {
  if (debug) {
    printf("typeUtils - printThreads: size=%d, id=%d\n", size, head->id);
  }

  // printout thread list
  stringstream threadListing;
  threadListing << "";
  for(int i=0; i< size; i++) {
    ThreadNode* thread = retrieveThreadNode(size, head, i);
    if(thread == NULL) {
      printf("typeUtils - printThreads:  Error retrieving threadNode for threadNode.id=%d\n", head->id);
      exit(EXIT_FAILURE);
    }
    threadListing << "[" << i << "]" << thread->id;
    if( i<size-1 )
      threadListing << ",";
  }
  return threadListing.str();
}

// Thread status
string getStatus(Status status) {
  string statName;
  switch(status) {
        case READY:
                statName = "Ready";
                break;
        case WAITING_LOCK:
                statName = "Waiting_Lock";
                break;
        case WAITING_SEM:
                statName = "Waiting_Sem";
                break;
        case RUNNING:
                statName = "Running";
                break;
        case COMPLETED:
                statName = "Completed";
                break;
        case EXITED:
                statName = "Exited";
                break;
        case UNKNOWN:
                statName = "Unknown";
                break;
        default:
                statName = "Error";
        }
  return statName;
}

// Scheduler Mode
string getModeString(SchedulerMode mode) {
  string modeName;
  switch(mode) {
        case RANDOM:
                modeName = "RANDOM";
                break;
        case INTERACTIVE:
                modeName = "INTERACTIVE";
                break;
        case FIFO:
                modeName = "FIFO";
                break;
        case LIFO:
                modeName = "LIFO";
                break;
        default:
                modeName = "Error";
        }
  return modeName;
}
