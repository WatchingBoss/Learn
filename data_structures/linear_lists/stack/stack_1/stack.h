#ifndef STACK_H
#define STACK_H

extern void push(char);
extern char pop();
extern int isEmpty(void);
extern int isFull(void);
extern void initStack(int);
extern void destroyStack();

#endif
