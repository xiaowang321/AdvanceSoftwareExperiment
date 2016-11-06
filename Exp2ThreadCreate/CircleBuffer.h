#pragma once
//���λ������Ĳ�����װ

#define NODE_SIZE 4  //���浥Ԫ��С
#define RING_SIZE 6 //��������Ԫ����

typedef struct node {
	BOOL valid;//��Ǹõ�Ԫ�����Ƿ񱻶�ȡ,FALSEΪδд�룬TRUEΪδ��ȡ��
	unsigned int data[NODE_SIZE];//����������
	int dataSize;//��������Ч���ݵĸ���
	struct node* next;
}NODE;//���浥Ԫ����

class CircleBuffer
{
private:
	NODE* head;//��������ͷָ��
	NODE* lastRead;//���һ���Ѷ��Ľڵ�ָ��
	NODE* lastWrite;//���һ����д�Ľڵ�ָ��
public:
	CircleBuffer(HWND hWnd);//��ʼ��һ�����λ�����
	~CircleBuffer();//���ٵ�ǰ�Ļ��λ�����
	BOOL ReadBuffer(NODE* data);//�����ȡһ����Ԫ�����ݣ������øõ�Ԫ����
	BOOL WriteBuffer(NODE* data);//������һ�����õ�Ԫд�����ݣ������б��
	//void Test();
};

