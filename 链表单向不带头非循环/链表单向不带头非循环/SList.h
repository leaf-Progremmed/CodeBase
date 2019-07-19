#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int SLDataType;

typedef struct SLNode{   //结点的结构体
	SLDataType value;
	struct SLNode *next;//逻辑上表示下一个值
}SListNode;

typedef struct SList{
	SListNode *first;//一个关于链表的结构体
} SList;

//初始化
void SListInit(SList *list){
	assert(list != NULL);
	list->first = NULL;
}
//void SListInit(SListNode **first)
//{
//	*first = NULL;
//}
//销毁
void SListDestory(SList *list)
{
	assert(list != NULL);
	SListNode *cur = list->first;
	SListNode *next;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	list->first = NULL;
}
//申请新结点
SListNode * SListBuyNode(SLDataType value)
{
	//空链表头插，已经有的头插
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));//申请一个新节点
	assert(node);
	node->value = value;//新的值
	node->next = NULL;
	return node;
}
//增
//头插
void SListPushFront(SList *list, SLDataType value)
{
	assert(list != NULL);
	//空链表头插，已经有的头插
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));//申请一个新节点
	assert(node);
	node->value = value;//新的值
	node->next = list->first;//让这个值的下一个值，指向刚才的第一个值
	list->first = node;//从新让第一个节点指向这个值的数值
}
//尾插
void SListPushBack(SList *list, SLDataType vaule)
{
	assert(list != NULL);
	//链表中没有结点的情况
	if (list->first == NULL)
	{
		SListPushFront(list, vaule);
		return;
	}
	//链表上面有结点的情况
	SListNode *cur;
	//找链表中最后一个结点
	for (cur = list->first; cur->next != NULL; cur = cur->next){
	}
	//cur就是最后一个结点了
	SListNode *node = SListBuyNode(vaule);
	cur->next = node;
}
//中间插入pos后面一定是一个有效结点
void SListInsetAfter(SListNode *pos, SLDataType value)
{
	SListNode *node = SListBuyNode(value);
	node->next = pos->next;
	pos->next = node;
}
//插入pos前面
void SListEraseBefore(SList *list, SListNode *pos, SLDataType value)
{
	SListNode *cur;
	for (cur = list->first; cur->next != pos; cur = cur->next){
	}
	SListNode *node = SListBuyNode(value);
	cur->next = node;
	node->next = pos;
}
void SListEraseAfter(SListNode *pos)
{
	SListNode *next = pos->next;
	pos->next = next->next;
	free(next);
}
//删
//头删
void SListPopFront(SList *list)
{
	assert(list != NULL);//保证链表不为空
	assert(list->first != NULL);//保证链表里面有值存在
	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}
//尾删
void SListPopBack(SList *list)
{
	assert(list != NULL);//保证链表不为空
	assert(list->first != NULL);//保证链表里面有值存在
	//如果只有一个结点
	if (list->first->next == NULL){
		SListPopFront(list);
		return;
	}
	//链表不为空的情况
	SListNode *cur=list->first;
	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}
	free(cur->next);
	cur->next = NULL;
}

//改
void SListUpdate(SListNode *node, SLDataType value)
{
	node->value = value;
}
//打印
void SListPrint(const SList *list)
{
	SListNode *cur;
	for (cur = list->first; cur != NULL; cur = cur->next)
	{
		printf("%d-->", cur->value);
	}
	printf("NULL\n");
}

//查
//查找链表中第一个value,如果没找到，返回NULL
SListNode * SListFind(const SList *list, SLDataType value)//返回结点的地址
{
	SListNode *cur;
	for (cur = list->first; cur != NULL; cur = cur->next)
	{
		if (cur->value == value){
			return cur;
		}
	}
	return NULL;
}
void TestSList1(){
	SList list;
	SListInit(&list);
	assert(list.first == NULL);

	//SListNode *first;//指向链表的第一个节点
	//SListInit(&first);
	//assert(first == NULL);
	SListPushFront(&list, 1);
	SListPushFront(&list, 2);
	SListPushFront(&list, 3);
	//3,2,1
	SListPrint(&list);
	SListPushBack(&list, 11);
	SListPushBack(&list, 12);
	SListPushBack(&list, 13);
	SListPrint(&list);

	//3 2 1 11 12 13
	SListPopFront(&list);
	SListNode *cur = SListFind(&list,12);
	assert(cur != NULL);
	SListPrint(&list);
	//SListInsertAfter(cur, 103);
	SListPopBack(&list);
	SListPrint(&list);
	//SListEraseAfter(cur);
	//SListPrint(&list);
	//SListInsertBerfore(&list,cur, 101);
	//SListPrint(&list);
}