#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef int SLDataType;

typedef struct SLNode{   //���Ľṹ��
	SLDataType value;
	struct SLNode *next;//�߼��ϱ�ʾ��һ��ֵ
}SListNode;

typedef struct SList{
	SListNode *first;//һ����������Ľṹ��
} SList;

//��ʼ��
void SListInit(SList *list){
	assert(list != NULL);
	list->first = NULL;
}
//void SListInit(SListNode **first)
//{
//	*first = NULL;
//}
//����
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
//�����½��
SListNode * SListBuyNode(SLDataType value)
{
	//������ͷ�壬�Ѿ��е�ͷ��
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));//����һ���½ڵ�
	assert(node);
	node->value = value;//�µ�ֵ
	node->next = NULL;
	return node;
}
//��
//ͷ��
void SListPushFront(SList *list, SLDataType value)
{
	assert(list != NULL);
	//������ͷ�壬�Ѿ��е�ͷ��
	SListNode *node = (SListNode *)malloc(sizeof(SListNode));//����һ���½ڵ�
	assert(node);
	node->value = value;//�µ�ֵ
	node->next = list->first;//�����ֵ����һ��ֵ��ָ��ղŵĵ�һ��ֵ
	list->first = node;//�����õ�һ���ڵ�ָ�����ֵ����ֵ
}
//β��
void SListPushBack(SList *list, SLDataType vaule)
{
	assert(list != NULL);
	//������û�н������
	if (list->first == NULL)
	{
		SListPushFront(list, vaule);
		return;
	}
	//���������н������
	SListNode *cur;
	//�����������һ�����
	for (cur = list->first; cur->next != NULL; cur = cur->next){
	}
	//cur�������һ�������
	SListNode *node = SListBuyNode(vaule);
	cur->next = node;
}
//�м����pos����һ����һ����Ч���
void SListInsetAfter(SListNode *pos, SLDataType value)
{
	SListNode *node = SListBuyNode(value);
	node->next = pos->next;
	pos->next = node;
}
//����posǰ��
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
//ɾ
//ͷɾ
void SListPopFront(SList *list)
{
	assert(list != NULL);//��֤����Ϊ��
	assert(list->first != NULL);//��֤����������ֵ����
	SListNode *old_first = list->first;
	list->first = list->first->next;
	free(old_first);
}
//βɾ
void SListPopBack(SList *list)
{
	assert(list != NULL);//��֤����Ϊ��
	assert(list->first != NULL);//��֤����������ֵ����
	//���ֻ��һ�����
	if (list->first->next == NULL){
		SListPopFront(list);
		return;
	}
	//����Ϊ�յ����
	SListNode *cur=list->first;
	while (cur->next->next != NULL)
	{
		cur = cur->next;
	}
	free(cur->next);
	cur->next = NULL;
}

//��
void SListUpdate(SListNode *node, SLDataType value)
{
	node->value = value;
}
//��ӡ
void SListPrint(const SList *list)
{
	SListNode *cur;
	for (cur = list->first; cur != NULL; cur = cur->next)
	{
		printf("%d-->", cur->value);
	}
	printf("NULL\n");
}

//��
//���������е�һ��value,���û�ҵ�������NULL
SListNode * SListFind(const SList *list, SLDataType value)//���ؽ��ĵ�ַ
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

	//SListNode *first;//ָ������ĵ�һ���ڵ�
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