#include "stdafx.h"
#include "CircleBuffer.h"

CircleBuffer::CircleBuffer(HWND hWnd)
{
	head = NULL;
	head = (NODE*)malloc(sizeof(NODE));//建立第一个节点
	if (head == NULL){
		MessageBox(hWnd,_T("内存申请失败！"),_T("环形缓冲区的创建"),MB_OK);
		return;
	}
	memset(head, 0, sizeof(NODE));
	head->next = head;
	NODE* temp;
	for (int i = 1; i < RING_SIZE; i++){
		temp = (NODE*)malloc(sizeof(NODE));
		if (temp == NULL){
			MessageBox(hWnd, _T("内存申请失败！"),_T("环形缓冲区的创建"),MB_OK);
			return;
		}
		memset(temp, 0, sizeof(NODE));
		temp->next = head->next;
		head->next = temp;
	}//循环建立其他节点
	lastRead = head;//读起点设为head指向的节点
	lastWrite = head;//写起点设为head指向的节点
}

CircleBuffer::~CircleBuffer()
{
	if (head == NULL)
		return;
	NODE *temp = head->next;//先从第二个节点开始释放
	while (temp != head)
	{
		NODE* p = temp->next;
		free(temp);
		temp = p;
	}//当前指针和头指针相同时，表示其他节点已经释放完毕
	free(head);//释放最后一个节点
	head = NULL;
}

BOOL CircleBuffer::ReadBuffer(NODE* data)
{
	if (lastRead->next->valid == FALSE)
		return FALSE;//当前需要读的节点还未写入，读取失败，读线程应当进入等待状态
	lastRead = lastRead->next;//可以读取，则更新最近读节点
	//读取数据
	data->dataSize = lastRead->dataSize;
	data->valid = TRUE;
	data->next = NULL;
	for (int i = 0; i < lastRead->dataSize;i++){
		data->data[i] = lastRead->data[i];
	}
	lastRead->valid = FALSE;//数据已读取，当前可以写入。
	return TRUE;
}

BOOL CircleBuffer::WriteBuffer(NODE* data)
{
	if (lastWrite->next->valid == TRUE)
		return FALSE;//当前需要写的节点还未读取，写入失败，写入线程应当进入等待状态
	lastWrite = lastWrite->next;//可以写入，则更新最近写节点
	//写入数据
	lastWrite->dataSize = data->dataSize;
	for (int i = 0; i < data->dataSize; i++){
		lastWrite->data[i] = data->data[i];
	}
	lastWrite->valid = TRUE;//数据已写入，当前可以读取
	return TRUE;
}