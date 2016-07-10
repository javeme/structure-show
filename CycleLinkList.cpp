#include "List.cpp"
#include "Node.h"

#if !defined(_CPP_CYCLELINKLIST)
#define _CPP_CYCLELINKLIST



//带有专用头节点的单链表类定义
template <class EleType>
class CYCLELINKLIST:public LIST<EleType>
{
public:
	int InitOK();
	CYCLELINKLIST(void);			//OK
	~CYCLELINKLIST();
	int Length();
	int Get(int nPos,EleType &Result);
	int Locate(EleType nValue);
	int Insert(int nPos,EleType newValue);
	int Delete(int nPos,EleType &Result);
	void Reverse(void);
protected:
	int m_InitOK;
	LINKNODE<EleType> *m_First;			
	int m_Length;
};

template <class EleType>
void CYCLELINKLIST<EleType>::Reverse(void)
{}

//析构函数
template <class EleType>
CYCLELINKLIST<EleType>::~CYCLELINKLIST(void)
{
	EleType nValue;
	//逐一删除所有有效节点
	while(Length()>0)
		Delete(1,nValue);

	delete m_First;

}

//求线性表长度
template <class EleType>
int CYCLELINKLIST<EleType>::Length(void)
{
	return m_Length;
}

//按位置查找
template <class EleType>
int CYCLELINKLIST<EleType>::Get(int nPos,EleType &Result)
{
	if(nPos<1 || nPos>m_Length)
		return 0;
	else
	{
		int Count=0;
		LINKNODE<EleType> *p=NULL;

		p=m_First->Next;
		while(p!=m_First)
		{
			Count++;
			if(Count==nPos)
				break;
			else
				p=p->Next;
		}
		if(p!=m_First)
		{
			Result=p->Data;
			return 1;
		}
		else
			return -1;
	}
}

//按内容查找
template <class EleType>
int CYCLELINKLIST<EleType>::Locate(EleType nValue)
{
	int iPos=1;
	LINKNODE<EleType> *p=m_First->Next;
	while(p!=m_First)
	{
		if(p->Data==nValue)
			break;
		else
		{
			p=p->Next;
			iPos++;
		}
	}
	if(p!=m_First)
		return iPos;
	else
		return 0;
}

//插入新元素
template <class EleType>
int CYCLELINKLIST<EleType>::Insert(int nPos,EleType newValue)
{
	LINKNODE<EleType> *s=NULL;
	//1.申请节点空间
	s=new LINKNODE<EleType>;
	if(!s)
		return -1;
	else if(nPos<1 || nPos>m_Length+1)
	{
		delete s;
		return -2;
	}
	else
	{
		int iPos=1;
		
		//
		s->Data=newValue;

		LINKNODE<EleType> *p=m_First;
		while(iPos<nPos && p)
		{
			p=p->Next;
			iPos++;
		}
		
		s->Next=p->Next;
		p->Next=s;

		m_Length++;

		return 1;
	}
}

//删除指定位置元素
template <class EleType>
int CYCLELINKLIST<EleType>::Delete(int nPos,EleType &Result)
{
	//删除位置不合法，返回-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else
	{
		int iPos=1;
		
		LINKNODE<EleType> *p=m_First,*q;		//工作指针

		//将p定位到要删除节点的直接前驱
		while(iPos<nPos && NULL!=p)
		{
			p=p->Next;
			iPos++;
		}

		//删除p的直接后继
		//令q指向待删除节点
		q=p->Next;
		//p的指针域部分指向待删除节点的直接后继
		p->Next=q->Next;
		//返回值
		Result=q->Data;
		//删除节点
		delete q;

		m_Length--;
		return 1;

	}
}

//是否初始化成功
template <class EleType>
int CYCLELINKLIST<EleType>::InitOK()
{
	return m_InitOK;
}

//默认构造函数
template <class EleType>
CYCLELINKLIST<EleType>::CYCLELINKLIST(void)
{
	LINKNODE<EleType> *p=NULL;

	//创建专用头节点
	p=new LINKNODE<EleType>;
	if(p)
	{
		p->Next=p;
		m_First=p;
		m_InitOK=1;
	}
	else
	{
		m_InitOK=0;
		m_First=NULL;
	}
	m_Length=0;
}
#endif
