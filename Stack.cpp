/*
	ջ�ĳ����ඨ�壬����ջ��ʵ�־�Ӧ�Ը���Ϊ���ಢʵ���������
*/
#if !defined(_CPP_STACK)

#define _CPP_STACK

#include "DataStructure.cpp"

template <class EleType>
class STACK:public DataStructure<EleType>
{
public:
	STACK();
	virtual ~STACK();

	int InitOK();
	int Length();

	//�������ֲ�����ʵ��ȡ���ھ���洢�ṹ������Ϊ���麯��
	virtual int Push(EleType newValue)=0;
	virtual int Pop(EleType &Result)=0;
	virtual int GetTop(EleType &Result)=0;	

	virtual int GetElement(int i,EleType &returnValue)=0;

protected:
	int m_InitOK;				//��ʼ���Ƿ�ɹ�
	int m_Length;				//ջ��Ԫ�ظ�����������
};

//Ĭ�Ϲ��캯��
template <class EleType>
STACK<EleType>::STACK(void)
{
	m_InitOK=0;
	m_Length=0;
}

//Ĭ����������
template <class EleType>
STACK<EleType>::~STACK(void)
{
}

//�Ƿ��ʼ���ɹ�
template <class EleType>
int STACK<EleType>::InitOK()
{
	return m_InitOK;
}

//��ջ����
template <class EleType>
int STACK<EleType>::Length(void)
{
	return m_Length;
}


#endif