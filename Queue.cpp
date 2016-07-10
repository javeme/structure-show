/*
	���еĳ����ඨ�塣
*/
#if !defined(_CPP_CQUEUE)

#define _CPP_CQUEUE

template <class EleType>
class CQueue
{
public:
	CQueue(void);
	~CQueue();

	virtual int InitOK();
	virtual int Length();
	virtual int EnQueue(EleType newValue)=0;
	virtual int DeQueue(EleType &Result)=0;
	virtual int GetQueue(EleType &Result)=0;
	
protected:
	int m_InitOK;
	int m_Length;
};


//���캯��
template <class EleType>
CQueue<EleType>::CQueue(void)
{
	//���г�ʼʱΪ��
	m_Length=0;
	m_InitOK=0;
}

//��������
template <class EleType>
CQueue<EleType>::~CQueue(void)
{
}

//����г���
template <class EleType>
int CQueue<EleType>::Length(void)
{
	return m_Length;
}

template <class EleType>
int CQueue<EleType>::InitOK()
{
	return m_InitOK;
}

#endif