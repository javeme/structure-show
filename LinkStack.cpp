/*
	链栈类的实现，在顺序栈类基础上修改。
*/
#include "Node.h"
#include "Stack.cpp"

#if !defined(_CPP_LINKSTACK)

#define _CPP_LINKSTACK

//没有专用头节点的链栈类定义
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
	LINKNODE<EleType> *m_Top;	//NULL表示栈空		
};

//默认构造函数
template <class EleType>
LINKSTACK<EleType>::LINKSTACK(void):STACK<EleType>()
{
	m_Top=NULL;
	m_InitOK=1;
}

//析构函数
template <class EleType>
LINKSTACK<EleType>::~LINKSTACK(void)
{
	EleType nValue;
	//逐一删除所有有效节点
	while(Length()>0)
		Pop(nValue);
}

//入栈
template <class EleType>
int LINKSTACK<EleType>::Push(EleType newValue)
{
	LINKNODE<EleType> *s=NULL;
	//1.申请节点空间
	s=new LINKNODE<EleType>;
	//空间不足，返回-1
	if(!s)
		return -1;
	else
	{
		//数据存入节点
		s->Data=newValue;

		//修改连接关系
		s->Next=m_Top;

		//调整栈顶
		m_Top=s;

		m_Length++;

		return 1;
	}
}

//出栈
template <class EleType>
int LINKSTACK<EleType>::Pop(EleType &Result)
{
	//栈空？
	if(!m_Top)
		return 0;
	else
	{
		Result=m_Top->Data;
		LINKNODE<EleType> *s;

		//s指向原来的栈顶节点
		s=m_Top;
		//移动栈顶指针
		m_Top=s->Next;
		s->Next=NULL;
		
		m_Length--;

		delete s;

		return 1;
	}
}
//获取第index个元素
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
//取栈顶元素
template <class EleType>
int LINKSTACK<EleType>::GetTop(EleType &Result)
{
	//栈空？
	if(!m_Top)
		return 0;
	else
	{
		Result=m_Top->Data;
		return 1;
	}
}

#endif