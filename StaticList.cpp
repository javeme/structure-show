/*
	静态链表类实现，在单链表类基础上实现。
	2010-10-15
*/
#include "List.cpp"

#if !defined(_CPP_STATICLIST)

#define _CPP_STATICLIST

//静态链表的节点定义
template <class EleType>
struct STATICNODE
{
	EleType Data;
	int Next;				//指向下一个元素的游标，-1表示为最后一个
};

//静态链表类定义
template <class EleType>
class STATICLIST:public LIST<EleType>
{
public:
	STATICLIST(void);
	STATICLIST(int nMaxLength);
	~STATICLIST();

	int Insert(int nPos,EleType newValue);
	int Delete(int nPos,EleType &Result);
	int Get(int nPos,EleType &Result);
	int Locate(EleType nValue);

	void Reverse(void);

protected:
	STATICNODE<EleType> *m_Datas;			//指向动态数组的指针
	int m_FirstFreeIndex;					//第一个空闲数组元素下标（游标）
	int m_FirstUsedIndex;					//线性表第一个有效元素所在数组下标（游标）
	int m_MaxLength;						//数组大小，默认10
};

//默认构造函数，数组大小为10
template <class EleType>
STATICLIST<EleType>::STATICLIST(void):LIST<EleType>()
{
	//默认数组大小为10
	m_MaxLength=10;
	//申请空间
	m_Datas=new STATICNODE<EleType>[m_MaxLength];
	//申请成功
	if(m_Datas)
	{
		m_InitOK=1;
		//数组第一个元素可以使用
		m_FirstFreeIndex=0;
		//开始时为空表，不存在有效元素
		m_FirstUsedIndex=-1;
		//初始化可用空间链表
		int i;
		//每个数组元素的游标为其下一个元素下标
		for(i=0;i<m_MaxLength;i++)
			m_Datas[i].Next=i+1;
		//数组最后一个元素为－1
		m_Datas[m_MaxLength-1].Next=-1;
	}
	else
	{
		m_FirstFreeIndex=-1;
		m_FirstUsedIndex=-1;
	}
}

//可指定大小的构造函数
template <class EleType>
STATICLIST<EleType>::STATICLIST(int nMaxLength):LIST<EleType>()
{
	//保存指定的数组长度
	m_MaxLength=nMaxLength;
	//申请空间
	m_Datas=new STATICNODE<EleType>[m_MaxLength];
	//申请成功
	if(m_Datas)
	{
		m_InitOK=1;
		//数组第一个元素可以使用
		m_FirstFreeIndex=0;
		//开始时为空表，不存在有效元素
		m_FirstUsedIndex=-1;
		//初始化可用空间链表
		int i;
		//每个数组元素的游标为其下一个元素下标
		for(i=0;i<m_MaxLength;i++)
			m_Datas[i].Next=i+1;
		//数组最后一个元素为－1
		m_Datas[m_MaxLength-1].Next=-1;
	}
	else
	{
		m_FirstFreeIndex=-1;
		m_FirstUsedIndex=-1;
	}
		
}

//析构函数
template <class EleType>
STATICLIST<EleType>::~STATICLIST(void)
{
	delete[] m_Datas;
}

//插入新元素
template <class EleType>
int STATICLIST<EleType>::Insert(int nPos,EleType newValue)
{
	//判断有无空闲数组元素可供使用，若无，返回－1
	if(m_FirstFreeIndex==-1)
		return -1;

	//判断插入位置，若不合法，返回－2
	else if(nPos<1 || nPos>m_Length+1)
	{
		return -2;
	}

	//插入位置合法
	else
	{
		
		int FreeIndex;		//找到的第一个空闲数组元素的下标

		FreeIndex=m_FirstFreeIndex;
		m_FirstFreeIndex=m_Datas[FreeIndex].Next;
		m_Datas[FreeIndex].Data=newValue;

		//寻找插入位置
		int iPos=1;
		
		int CurrIndex,LastIndex;

		//若线性表为空
		if(m_FirstUsedIndex==-1)
		{
			m_FirstUsedIndex=FreeIndex;
			m_Datas[FreeIndex].Next=-1;
		}
		//若线性表不空
		else
		{
			//寻找插入位置的前一个元素所在数组下标
			CurrIndex=m_FirstUsedIndex;
			LastIndex=-1;
			while(iPos<nPos)
			{
				LastIndex=CurrIndex;
				CurrIndex=m_Datas[CurrIndex].Next;
				iPos++;
			}
			
			//插入位置为第1个
			if(LastIndex==-1)
			{
				m_Datas[FreeIndex].Next=m_FirstUsedIndex;
				m_FirstUsedIndex=FreeIndex;
			}
			//插入位置不为第1个
			else
			{
				m_Datas[FreeIndex].Next=CurrIndex;
				m_Datas[LastIndex].Next=FreeIndex;
			}
		}
		m_Length++;

		return 1;
	}
}

//删除指定位置元素
template <class EleType>
int STATICLIST<EleType>::Delete(int nPos,EleType &Result)
{
	//删除位置不合法，返回-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else
	{
		int iPos=1;
		int CurrIndex,LastIndex;

		//将p定位到要删除节点的直接前驱
		LastIndex=-1;
		CurrIndex=m_FirstUsedIndex;
		while(iPos<nPos)
		{
			LastIndex=CurrIndex;
			CurrIndex=m_Datas[CurrIndex].Next;
			iPos++;
		}

		//CurrIndex为待删除结点所在数组下标，LastIndex为其直接前趋的下标
		//要删除的是第一个结点
		if(LastIndex==-1)
		{
			m_FirstUsedIndex=m_Datas[CurrIndex].Next;
		}
		//要删除的不是第一个结点
		{
			m_Datas[LastIndex].Next=m_Datas[CurrIndex].Next;
		}

		//返回数据
		Result=m_Datas[CurrIndex].Data;

		//将CurrIndex所指结点添加为可用结点的第1个
		m_Datas[CurrIndex].Next=m_FirstFreeIndex;
		m_FirstFreeIndex=CurrIndex;

		m_Length--;
		return 1;

	}
}

//按位置查找
template <class EleType>
int STATICLIST<EleType>::Get(int nPos,EleType &Result)
{
	if(nPos<1 || nPos>m_Length)
		return 0;
	else
	{
		int iPos=1;
		int CurrIndex;

		CurrIndex=m_FirstUsedIndex;
		while(iPos<nPos)
		{
			CurrIndex=m_Datas[CurrIndex].Next;
			iPos++;
		}
		Result=m_Datas[CurrIndex].Data;
		return 1;
	}
}

//按内容查找
template <class EleType>
int STATICLIST<EleType>::Locate(EleType Value)
{
	int iPos=1;
	int CurrIndex;

	CurrIndex=m_FirstUsedIndex;
	while(CurrIndex!=-1)
	{
		if(m_Datas[CurrIndex].Data==Value)
			break;
		else
			CurrIndex=m_Datas[CurrIndex].Next;
		iPos++;
	}
	if(CurrIndex!=-1)
		return iPos;
	else
		return 0;
}

//就地逆置
template <class EleType>
void STATICLIST<EleType>::Reverse(void)
{
	int Curr,Last;		//两个游标
	
	Curr=m_FirstUsedIndex;
	if(Curr!=-1)
	{
		Last=m_Datas[Curr].Next;
		while(Last!=-1)
		{
			//将Curr的后继改为m_FirstUsedIndex的前趋
			m_Datas[Curr].Next=m_Datas[Last].Next;
			m_Datas[Last].Next=m_FirstUsedIndex;
			m_FirstUsedIndex=Last;

			//令Last为Curr的后继游标
			Last=m_Datas[Curr].Next;
		}
	}
}

#endif