#pragma once
//环形缓冲区的操作封装

#define NODE_SIZE 4  //缓存单元大小
#define RING_SIZE 6 //缓存区单元个数

typedef struct node {
	BOOL valid;//标记该单元数据是否被读取,FALSE为未写入，TRUE为未读取。
	unsigned int data[NODE_SIZE];//缓存区数据
	int dataSize;//缓存区有效数据的个数
	struct node* next;
}NODE;//缓存单元定义

class CircleBuffer
{
private:
	NODE* head;//缓存区的头指针
	NODE* lastRead;//最近一个已读的节点指针
	NODE* lastWrite;//最近一个已写的节点指针
public:
	CircleBuffer(HWND hWnd);//初始化一个环形缓存区
	~CircleBuffer();//销毁当前的环形缓存区
	BOOL ReadBuffer(NODE* data);//依序读取一个单元的数据，并重置该单元数据
	BOOL WriteBuffer(NODE* data);//依序在一个重置单元写入数据，并进行标记
	//void Test();
};

