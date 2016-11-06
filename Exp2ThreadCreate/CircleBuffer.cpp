#include "stdafx.h"
#include "CircleBuffer.h"

CircleBuffer::CircleBuffer(HWND hWnd)
{
	head = NULL;
	head = (NODE*)malloc(sizeof(NODE));//������һ���ڵ�
	if (head == NULL){
		MessageBox(hWnd,_T("�ڴ�����ʧ�ܣ�"),_T("���λ������Ĵ���"),MB_OK);
		return;
	}
	memset(head, 0, sizeof(NODE));
	head->next = head;
	NODE* temp;
	for (int i = 1; i < RING_SIZE; i++){
		temp = (NODE*)malloc(sizeof(NODE));
		if (temp == NULL){
			MessageBox(hWnd, _T("�ڴ�����ʧ�ܣ�"),_T("���λ������Ĵ���"),MB_OK);
			return;
		}
		memset(temp, 0, sizeof(NODE));
		temp->next = head->next;
		head->next = temp;
	}//ѭ�����������ڵ�
	lastRead = head;//�������Ϊheadָ��Ľڵ�
	lastWrite = head;//д�����Ϊheadָ��Ľڵ�
}

CircleBuffer::~CircleBuffer()
{
	if (head == NULL)
		return;
	NODE *temp = head->next;//�ȴӵڶ����ڵ㿪ʼ�ͷ�
	while (temp != head)
	{
		NODE* p = temp->next;
		free(temp);
		temp = p;
	}//��ǰָ���ͷָ����ͬʱ����ʾ�����ڵ��Ѿ��ͷ����
	free(head);//�ͷ����һ���ڵ�
	head = NULL;
}

BOOL CircleBuffer::ReadBuffer(NODE* data)
{
	if (lastRead->next->valid == FALSE)
		return FALSE;//��ǰ��Ҫ���Ľڵ㻹δд�룬��ȡʧ�ܣ����߳�Ӧ������ȴ�״̬
	lastRead = lastRead->next;//���Զ�ȡ�������������ڵ�
	//��ȡ����
	data->dataSize = lastRead->dataSize;
	data->valid = TRUE;
	data->next = NULL;
	for (int i = 0; i < lastRead->dataSize;i++){
		data->data[i] = lastRead->data[i];
	}
	lastRead->valid = FALSE;//�����Ѷ�ȡ����ǰ����д�롣
	return TRUE;
}

BOOL CircleBuffer::WriteBuffer(NODE* data)
{
	if (lastWrite->next->valid == TRUE)
		return FALSE;//��ǰ��Ҫд�Ľڵ㻹δ��ȡ��д��ʧ�ܣ�д���߳�Ӧ������ȴ�״̬
	lastWrite = lastWrite->next;//����д�룬��������д�ڵ�
	//д������
	lastWrite->dataSize = data->dataSize;
	for (int i = 0; i < data->dataSize; i++){
		lastWrite->data[i] = data->data[i];
	}
	lastWrite->valid = TRUE;//������д�룬��ǰ���Զ�ȡ
	return TRUE;
}