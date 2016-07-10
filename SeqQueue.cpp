/*
	循环顺序队列实现。
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
	int m_Front;		//队头指针
	int m_Rear;			//队尾指针
};

//构造函数-默认的，数组大小默认为100
template <class EleType>
CSeqQueue<EleType>::CSeqQueue(void):CQueue<EleType>()
{
	m_MaxLength=100;

	//队列初始时为空
	m_Front=0;
	m_Rear=0;

	//申请空间
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//构造函数-指定数组大小
template <class EleType>
CSeqQueue<EleType>::CSeqQueue(int nMaxLength):CQueue<EleType>()
{
	m_MaxLength=nMaxLength;

	//队列初始时为空
	m_Front=0;
	m_Rear=0;

	//申请空间
	m_Datas=new EleType[nMaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//析构函数
template <class EleType>
CSeqQueue<EleType>::~CSeqQueue(void)
{
	delete[] m_Datas;
}


//入队
template <class EleType>
int CSeqQueue<EleType>::EnQueue(EleType newValue)
{
	//队列已满，返回0
	if((m_Rear+1)%m_MaxLength==m_Front)
		return 0;
	else
	{
		//先改变队尾指针
		m_Rear=(m_Rear+1)%m_MaxLength;
		//存储数据
		m_Datas[m_Rear]=newValue;
		//长度变化
		m_Length++;

		return 1;
	}
}

//出队
template <class EleType>
int CSeqQueue<EleType>::DeQueue(EleType &Result)
{
	//队空，不能出队，返回0
	if(m_Rear==m_Front)
		return 0;
	else
	{
		//修改队头指针
		m_Front=(m_Front+1)%m_MaxLength;

		//取元素值
		Result=m_Datas[m_Front];

		//长度减1
		m_Length--;

		return 1;
	}
}

//取队头元素
template <class EleType>
int CSeqQueue<EleType>::GetQueue(EleType &Result)
{
	//队空，不能取，返回0
	if(m_Rear==m_Front)
		return 0;
	else
	{
		//取元素值
		Result=m_Datas[(m_Front+1)%m_MaxLength];

		return 1;
	}
}

#endif