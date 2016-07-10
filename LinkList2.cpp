/*
	不带专用头结点的单链表的实现
*/
#include "List.cpp"
#include "Node.h"

#if !defined(_CPP_LINKLIST22)

#define _CPP_LINKLIST22

//不带专用头节点的单链表类定义
template <class EleType>
class LINKLIST2:public LIST<EleType>
{
public:
	LINKLIST2(void);
	~LINKLIST2();

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
LINKLIST2<EleType>::LINKLIST2(void):LIST<EleType>()
{
	m_First=NULL;
	m_InitOK=1;
}

//析构函数
template <class EleType>
LINKLIST2<EleType>::~LINKLIST2(void)
{
	EleType nValue;
	//逐一删除所有有效节点
	while(Length()>0)
		Delete(1,nValue);
}

//插入新元素
template <class EleType>
int LINKLIST2<EleType>::Insert(int nPos,EleType newValue)
{
	LINKNODE<EleType> *s=NULL;
	//申请节点空间
	s=new LINKNODE<EleType>;

	//申请空间失败，返回-1
	if(!s)
		return -1;

	//若插入位置不合理，释放刚申请的结点空间，返回-2
	if(nPos<1 || nPos>m_Length+1)
	{
		delete s;
		return -2;
	}
	//插入位置合理
	else
	{
		int iPos;
		
		s->Data=newValue;

		LINKNODE<EleType> *p,*q;

		//令p指向等插入结点的前趋,q指向待插入位置处的结点
		p=NULL;
		q=m_First;
		iPos=1;
		while(iPos<nPos && q)
		{
			p=q;
			q=q->Next;
			iPos++;
		}

		//若p为空，说明待插入位置为1，需要修改m_First值
		if(!p)
		{
			s->Next=m_First;
			m_First=s;
		}
		else
		{
			s->Next=p->Next;
			p->Next=s;
		}

		m_Length++;

		return 1;
	}
}

//删除指定位置元素
template <class EleType>
int LINKLIST2<EleType>::Delete(int nPos,EleType &Result)
{
	//删除位置不合法，返回-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else		//执行该分支时链表不空
	{
		int iPos=1;
		
		LINKNODE<EleType> *p,*q;		//工作指针

		q=m_First;
		p=NULL;
		//将p定位到要删除节点的直接前驱
		while(iPos<nPos && NULL!=q)
		{
			p=q;
			q=q->Next;
			iPos++;
		}

		//要删除的是头结点
		if(!p)
		{
			m_First=m_First->Next;
		}
		else
		{
			//p的指针域部分指向待删除节点q的直接后继
			p->Next=q->Next;
		}
		//返回值
		Result=q->Data;
		//删除节点
		q->Next=NULL;
		delete q;
		//表长度减1
		m_Length--;

		return 1;

	}
}

//按位置查找
template <class EleType>
int LINKLIST2<EleType>::Get(int nPos,EleType &Result)
{
	//若指定的查找位置nPos不合理，返回0
	if(nPos<1 || nPos>m_Length)
		return 0;
	//指定的查找位置合理，遍历链表
	else
	{
		int iPos=1;
		LINKNODE<EleType> *p;

		//p首先指向头结点
		p=m_First;
		//在链表未结束并且未达到指定nPos指定位置时指针后移
		while(iPos<nPos && p)
		{
			p=p->Next;
			iPos++;
		}

		Result=p->Data;
		return 1;
	}
}

//按内容查找
template <class EleType>
int LINKLIST2<EleType>::Locate(EleType nValue)
{
	int iPos=1;
	LINKNODE<EleType> *p;
	p=m_First;
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
void LINKLIST2<EleType>::Reverse(void)
{
	LINKNODE<EleType> *p,*q;
	
	p=m_First;
	//若p指向第1个结点
	if(p)
	{
		q=p->Next;
		while(q)
		{
			//将p的后继结点作为新的头结点插入到旧头结点前面
			p->Next=q->Next;
			q->Next=m_First;
			m_First=q;
			
			//令q指向p的新的后继
			q=p->Next;
		}
	}
}


#endif