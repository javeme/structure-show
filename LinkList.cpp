/*
	带有专用头结点的单链表类实现
*/
#include "List.cpp"
#include "Node.h"

#if !defined(_CPP_LINKLIST)

#define _CPP_LINKLIST

//带有专用头节点的单链表类定义
template <class EleType>
class LINKLIST:public LIST<EleType>
{
public:
	LINKLIST(void);
	~LINKLIST();

	int Insert(int nPos,EleType newValue);
	int Delete(int nPos,EleType &Result);
	int Get(int nPos,EleType &Result);
	int Locate(EleType nValue);

	void Reverse(void);

protected:
	LINKNODE<EleType> *m_First;			
};

//默认构造函数
template <class EleType>
LINKLIST<EleType>::LINKLIST(void):LIST<EleType>()
{
	LINKNODE<EleType> *p=NULL;

	//创建专用头节点
	p=new LINKNODE<EleType>;
	if(p)
	{
		p->Next=NULL;
		m_First=p;
		m_InitOK=1;
	}
	else
	{
		m_First=NULL;
	}
}

//析构函数
template <class EleType>
LINKLIST<EleType>::~LINKLIST(void)
{
	EleType nValue;

	//逐一删除所有节点
	while(Length()>0)
		Delete(1,nValue);

	delete m_First;

}

//插入新元素
template <class EleType>
int LINKLIST<EleType>::Insert(int nPos,EleType newValue)
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
int LINKLIST<EleType>::Delete(int nPos,EleType &Result)
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

//按位置查找
template <class EleType>
int LINKLIST<EleType>::Get(int nPos,EleType &Result)
{
	if(nPos<1 || nPos>m_Length)
		return 0;
	else
	{
		int Count=0;
		LINKNODE<EleType> *p=NULL;

		p=m_First->Next;
		while(p)
		{
			Count++;
			if(Count==nPos)
				break;
			else
				p=p->Next;
		}
		Result=p->Data;
		return 1;
	}
}

//按内容查找
template <class EleType>
int LINKLIST<EleType>::Locate(EleType nValue)
{
	int iPos=1;
	LINKNODE<EleType> *p=m_First->Next;
	while(p)
	{
		if(p->Data==nValue)
			break;
		else
		{
			p=p->Next;
			iPos++;
		}
	}
	if(p)
		return iPos;
	else
		return 0;
}


//就地逆置
template <class EleType>
void LINKLIST<EleType>::Reverse(void)
{
	LINKNODE<EleType> *p,*q;
	
	p=m_First->Next;
	//若p指向第1个结点
	if(p)
	{
		q=p->Next;
		while(q)
		{
			//将p的后继结点插入到头结点后面
			p->Next=q->Next;
			q->Next=m_First->Next;
			m_First->Next=q;
			
			//令q指向p的新的后继
			q=p->Next;
		}
	}
}

#endif