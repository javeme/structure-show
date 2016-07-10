/*
	栈的抽象类定义，所有栈的实现均应以该类为基类并实现其操作。
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

	//下面三种操作的实现取决于具体存储结构，定义为纯虚函数
	virtual int Push(EleType newValue)=0;
	virtual int Pop(EleType &Result)=0;
	virtual int GetTop(EleType &Result)=0;	

	virtual int GetElement(int i,EleType &returnValue)=0;

protected:
	int m_InitOK;				//初始化是否成功
	int m_Length;				//栈中元素个数，即长度
};

//默认构造函数
template <class EleType>
STACK<EleType>::STACK(void)
{
	m_InitOK=0;
	m_Length=0;
}

//默认析构函数
template <class EleType>
STACK<EleType>::~STACK(void)
{
}

//是否初始化成功
template <class EleType>
int STACK<EleType>::InitOK()
{
	return m_InitOK;
}

//求栈长度
template <class EleType>
int STACK<EleType>::Length(void)
{
	return m_Length;
}


#endif