#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

typedef char datatype;

typedef struct _Stack
{
  datatype data[MAX];
  int top;
}Stack;

typedef struct _Queue
{
  datatype data[MAX];
  int front,rear;
}Queue;

void push(Stack *S,datatype data)
{
  if (S->top==MAX) printf("Full_Stack\n");
  else S->data[S->top++]=data;
}

datatype pop(Stack *S)
{
  if (S->top==0) printf("Empty_Stack\n");
  else return S->data[--S->top];
}

int sizeQueue(Queue *Q)
{
  return (MAX + Q->rear - Q->front) % MAX;
}

void enQueue(Queue *Q, datatype data)
{
  if (sizeQueue(Q)==MAX-1) printf("Full_Queue\n");
  else
    {
      Q->data[Q->rear]=data;
      Q->rear=(Q->rear++)%MAX;
    }
}

datatype deQueue(Queue *Q)
{
  if (sizeQueue(Q)==0) printf("Empty_Queue\n");
  else
    {
      int temp=Q->front;
      Q->front=(Q->front++)%MAX;
      return Q->data[temp];
    }
}

int main()
{
  Stack* S=(Stack*)malloc(sizeof(Stack));  S->top=0;
  Queue *Q=(Queue*)malloc(sizeof(Queue)); Q->front=0; Q->rear=0;

  int i;
  char str[MAX];
  scanf("%s",str);
  for (i=0; i<strlen(str); i++)
    {
      push(S,str[i]);
      enQueue(Q,str[i]);
    }

  int kt=1;	
  while (S->top!=0)
      if (pop(S)!=deQueue(Q))
      {
      	kt=0;
      	break;
      }
  if (kt) printf("Xau la xau doi xung\n"); 
  else printf("Xau khong la xau doi xung\n");
  
  return 0;
}
