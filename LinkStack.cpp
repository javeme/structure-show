/*
	��ջ���ʵ�֣���˳��ջ��������޸ġ�
*/
#include "Node.h"
#include "Stack.cpp"

#if !defined(_CPP_LINKSTACK)

#define _CPP_LINKSTACK

//û��ר��ͷ�ڵ����ջ�ඨ��
template <class EleType>
class LINKSTACK:public STACK<EleType>
{
public:
	LINKSTACK(void);			
	~LINKSTACK();

	int Push(EleType newValue);
	int Pop(EleType &Result);
	int GetTop(EleType &Result);
	int GetElement(int index,EleType &returnValue);
protected:
	LINKNODE<EleType> *m_Top;	//NULL��ʾջ��		
};

//Ĭ�Ϲ��캯��
template <class EleType>
LINKSTACK<EleType>::LINKSTACK(void):STACK<EleType>()
{
	m_Top=NULL;
	m_InitOK=1;
}

//��������
template <class EleType>
LINKSTACK<EleType>::~LINKSTACK(void)
{
	EleType nValue;
	//��һɾ��������Ч�ڵ�
	while(Length()>0)
		Pop(nValue);
}

//��ջ
template <class EleType>
int LINKSTACK<EleType>::Push(EleType newValue)
{
	LINKNODE<EleType> *s=NULL;
	//1.����ڵ�ռ�
	s=new LINKNODE<EleType>;
	//�ռ䲻�㣬����-1
	if(!s)
		return -1;
	else
	{
		//���ݴ���ڵ�
		s->Data=newValue;

		//�޸����ӹ�ϵ
		s->Next=m_Top;

		//����ջ��
		m_Top=s;

		m_Length++;

		return 1;
	}
}

//��ջ
template <class EleType>
int LINKSTACK<EleType>::Pop(EleType &Result)
{
	//ջ�գ�
	if(!m_Top)
		return 0;
	else
	{
		Result=m_Top->Data;
		LINKNODE<EleType> *s;

		//sָ��ԭ����ջ���ڵ�
		s=m_Top;
		//�ƶ�ջ��ָ��
		m_Top=s->Next;
		s->Next=NULL;
		
		m_Length--;

		delete s;

		return 1;
	}
}
//��ȡ��index��Ԫ��
template <class EleType>
int LINKSTACK<EleType>::GetElement(int index,EleType &returnValue)
{
	if(!m_Top || index<1 || index>m_Length)
		return 0;
	else
	{
		LINKNODE<EleType> *p=m_Top;
		index=m_Length-index;
		while(index>0)
		{
			p=p->Next;
			index--;
		}
		returnValue=p->Data;
		return 1;
	}
}
//ȡջ��Ԫ��
template <class EleType>
int LINKSTACK<EleType>::GetTop(EleType &Result)
{
	//ջ�գ�
	if(!m_Top)
		return 0;
	else
	{
		Result=m_Top->Data;
		return 1;
	}
}

#endif