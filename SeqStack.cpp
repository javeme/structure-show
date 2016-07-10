/*
	˳��ջ���ʵ�֡�
*/
#include "Stack.cpp"

#if !defined(_CPP_SEQSTACK)

#define _CPP_SEQSTACK

//˳��ջ��
template <class EleType>
class SEQSTACK:public STACK<EleType>
{
public:
	SEQSTACK(int nMaxLength);
	SEQSTACK(void);
	~SEQSTACK();

	int GetTop(EleType &Result);	
	int Push(EleType newValue);
	int Pop(EleType &Result);
	int GetElement(int i,EleType &returnValue);

protected:
	EleType *m_Datas;				
	int m_MaxLength;
	int m_Top;
};

//Ĭ�Ϲ��캯�� - Ĭ�ϴ�����СΪ100�Ķ�̬����
template <class EleType>
SEQSTACK<EleType>::SEQSTACK(void):STACK<EleType>()
{
	m_MaxLength=100;
	m_Top=-1;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//ָ����󳤶ȵĹ��캯��
template <class EleType>
SEQSTACK<EleType>::SEQSTACK(int nMaxLength):STACK<EleType>()
{
	m_MaxLength=nMaxLength;
	m_Top=-1;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//�������� - �ͷŹ��캯��������Ķ�̬�ռ�
template <class EleType>
SEQSTACK<EleType>::~SEQSTACK(void)
{
	delete[] m_Datas;
}

//��ջ
template <class EleType>
int SEQSTACK<EleType>::Push(EleType newValue)
{
	//ջ��������-1
	if(m_Top==m_MaxLength-1)
		return -1;
	//ѹջ�ɹ�������1
	else
	{
		m_Top++;
		m_Datas[m_Top]=newValue;

		m_Length++;

		return 1;
	}
}

//��ջ
template <class EleType>
int SEQSTACK<EleType>::Pop(EleType &Result)
{
	//ջ��ʱ����-1��Result������
	if(m_Top==-1)
		return -1;
	else
	{
		Result=m_Datas[m_Top];
		m_Top--;

		m_Length--;

		return 1;
	}
}
//����ͼ����ʾ����Ԫ��
template <class EleType>
int SEQSTACK<EleType>::GetElement(int index,EleType &returnValue)
{
	if(m_Top==-1 || index<1 || index>m_Top+1)
		return -1;
	returnValue=m_Datas[index-1];
	return 1;
}
//���ջ��Ԫ��
template <class EleType>
int SEQSTACK<EleType>::GetTop(EleType &Result)
{
	//ջ��ʱ������0��Result������
	if(m_Top==-1)
		return -1;
	//ջ�ǿ�ʱ������1��ResultΪջ��Ԫ��ֵ
	else
	{
		Result=m_Datas[m_Top];
		return 1;
	}
}

#endif