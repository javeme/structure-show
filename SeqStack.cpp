/*
	顺序栈类的实现。
*/
#include "Stack.cpp"

#if !defined(_CPP_SEQSTACK)

#define _CPP_SEQSTACK

//顺序栈类
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

//默认构造函数 - 默认创建大小为100的动态数组
template <class EleType>
SEQSTACK<EleType>::SEQSTACK(void):STACK<EleType>()
{
	m_MaxLength=100;
	m_Top=-1;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//指定最大长度的构造函数
template <class EleType>
SEQSTACK<EleType>::SEQSTACK(int nMaxLength):STACK<EleType>()
{
	m_MaxLength=nMaxLength;
	m_Top=-1;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//析构函数 - 释放构造函数中申请的动态空间
template <class EleType>
SEQSTACK<EleType>::~SEQSTACK(void)
{
	delete[] m_Datas;
}

//入栈
template <class EleType>
int SEQSTACK<EleType>::Push(EleType newValue)
{
	//栈满，返回-1
	if(m_Top==m_MaxLength-1)
		return -1;
	//压栈成功，返回1
	else
	{
		m_Top++;
		m_Datas[m_Top]=newValue;

		m_Length++;

		return 1;
	}
}

//出栈
template <class EleType>
int SEQSTACK<EleType>::Pop(EleType &Result)
{
	//栈空时返回-1，Result无意义
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
//用于图形显示所有元素
template <class EleType>
int SEQSTACK<EleType>::GetElement(int index,EleType &returnValue)
{
	if(m_Top==-1 || index<1 || index>m_Top+1)
		return -1;
	returnValue=m_Datas[index-1];
	return 1;
}
//获得栈顶元素
template <class EleType>
int SEQSTACK<EleType>::GetTop(EleType &Result)
{
	//栈空时，返回0，Result无意义
	if(m_Top==-1)
		return -1;
	//栈非空时，返回1，Result为栈顶元素值
	else
	{
		Result=m_Datas[m_Top];
		return 1;
	}
}

#endif