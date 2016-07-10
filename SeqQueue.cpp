/*
	ѭ��˳�����ʵ�֡�
*/
#include "Queue.cpp"

#if !defined(_CPP_CSEQQUEUE)

#define _CPP_CSEQQUEUE

template <class EleType>
class CSeqQueue:public CQueue<EleType>
{
public:
	CSeqQueue(int nMaxLength);
	CSeqQueue(void);
	~CSeqQueue();

	virtual int EnQueue(EleType newValue);
	virtual int DeQueue(EleType &Result);
	virtual int GetQueue(EleType &Result);
	
protected:
	EleType *m_Datas;
	int m_MaxLength;
	int m_Front;		//��ͷָ��
	int m_Rear;			//��βָ��
};

//���캯��-Ĭ�ϵģ������СĬ��Ϊ100
template <class EleType>
CSeqQueue<EleType>::CSeqQueue(void):CQueue<EleType>()
{
	m_MaxLength=100;

	//���г�ʼʱΪ��
	m_Front=0;
	m_Rear=0;

	//����ռ�
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//���캯��-ָ�������С
template <class EleType>
CSeqQueue<EleType>::CSeqQueue(int nMaxLength):CQueue<EleType>()
{
	m_MaxLength=nMaxLength;

	//���г�ʼʱΪ��
	m_Front=0;
	m_Rear=0;

	//����ռ�
	m_Datas=new EleType[nMaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//��������
template <class EleType>
CSeqQueue<EleType>::~CSeqQueue(void)
{
	delete[] m_Datas;
}


//���
template <class EleType>
int CSeqQueue<EleType>::EnQueue(EleType newValue)
{
	//��������������0
	if((m_Rear+1)%m_MaxLength==m_Front)
		return 0;
	else
	{
		//�ȸı��βָ��
		m_Rear=(m_Rear+1)%m_MaxLength;
		//�洢����
		m_Datas[m_Rear]=newValue;
		//���ȱ仯
		m_Length++;

		return 1;
	}
}

//����
template <class EleType>
int CSeqQueue<EleType>::DeQueue(EleType &Result)
{
	//�ӿգ����ܳ��ӣ�����0
	if(m_Rear==m_Front)
		return 0;
	else
	{
		//�޸Ķ�ͷָ��
		m_Front=(m_Front+1)%m_MaxLength;

		//ȡԪ��ֵ
		Result=m_Datas[m_Front];

		//���ȼ�1
		m_Length--;

		return 1;
	}
}

//ȡ��ͷԪ��
template <class EleType>
int CSeqQueue<EleType>::GetQueue(EleType &Result)
{
	//�ӿգ�����ȡ������0
	if(m_Rear==m_Front)
		return 0;
	else
	{
		//ȡԪ��ֵ
		Result=m_Datas[(m_Front+1)%m_MaxLength];

		return 1;
	}
}

#endif