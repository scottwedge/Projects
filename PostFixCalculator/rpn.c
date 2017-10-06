

/*   Author:   David Gutsch
     Date:     08/2017         */

#include <stdio.h>
#include <stdlib.h>
#include "rpn.h"
#include <ctype.h>

extern CELL *stack;


/* function implementations */
void push(int val) {
  CELL *c = (CELL *)malloc(sizeof(CELL));

  if(c) {
    c->val = val;
    c->next = stack;  
    stack  = c; // pushes new cell on stack
  } else {   /*handle error*/
    printf("something went wrong:\ncell memory did not get allocated properly\n");
  }
}

int pop() {
  CELL *c = stack;
  
  if(c) {
    
    stack = stack->next; //pop
    int val = c->val;
    free(c);
    return val;
  }
  else {
    printf("The stack is empty\n");
    exit(1);
  }

}

int stackOperator(char op, int first, int second) {
  
  switch((int)op) {
  case 42:
    return (second * first);
    break;
  case 43:
    return (first + second);
    break;
  case 45:
    return (second - first);
    break;
  case 47:
    return (second / first);
    break;
  default:
    exit(1);
    break;
  }
}

int main(void) {
  int returnValue = 0;
  char cur;

  //initialize stack
  stack = (CELL *)malloc(sizeof(CELL));
  stack->val = 0;
  stack->next = NULL;
 
  // continuously start reading input
  while(1) {
    //read input
    scanf("%c", &cur);
    // if it's not a space keep checking else move to the next
    if(!isspace(cur)) {
      // if it's a digit push it on the stack
      if(isdigit(cur)) {
	printf("pushing %d\n",(cur - 48));
	push((cur - 48));
      }
      // operate on the stack
      else if( cur == '/' || cur == '*' || cur == '+' || cur == '-') { 
	float result;
	printf("+-*/\n");
	
	if(stack && stack->next) {
	  int first = pop();
	  int second = pop();
	  result = stackOperator(cur, first, second);
	  push((int)result);
	}
	else {
	  printf("the stack doesn't have enough numbers upon which to operate\n");
	}
	
	printf("after calculation %f\n stack value: %d\n", result, stack->val);
      }
      else if(0) {
	// this will be for p,f,c,q commands
      }
    }
  }
  return 0;
  }
