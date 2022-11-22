#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>

typedef struct Data
{
    int number;//值
    int symbol;//符号
}Data;

//定义栈里的元素
typedef struct StackMember
{
    struct StackMember *next;
    Data data;
    
}StackMember;

//定义栈
typedef struct Stack
{
    struct StackMember *top;
    int size;
}Stack;

//初始化栈
Stack *Init()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));//申请栈的内存空间,并将空间的地址传给栈数据类型的指针.
    s->top=NULL;
    s->size=0;
    return s;//返回初始话栈的地址
}

//初始化栈的成员
StackMember *InitStackMember(Data x)
{
    StackMember *tempStackMember=(StackMember *)malloc(sizeof(StackMember));
    tempStackMember->data=x;
    tempStackMember->next=NULL;
    return tempStackMember;
}

//判断栈是否为空
bool Empty(Stack *s)
{
    return s->top==NULL;//如果栈为空，栈顶为-1
}

//返回栈顶元素
StackMember *Top(Stack *s)
{
    if (Empty(s))//判断栈是否为空
        return NULL;
    return s->top;//返回栈顶元素
}

//入栈操作
bool Push(Stack *s,StackMember *val)
{
    if (s==NULL)//判断栈是否存在
        return false;
    val->next=s->top;
    s->top=val;
    (s->size)++;
    return true;
}

//出栈操作
bool Pop(Stack *s)
{
    if (s == NULL)//判断栈是否存在
        return false;
    if (Empty(s))//判断栈内是否为空
        return false;
    StackMember *topMember=s->top;
    s->top=s->top->next;
    free(topMember); //释放出栈成员的空间
    (s->size)--;
    return true;
}