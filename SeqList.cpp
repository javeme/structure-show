/*
	顺序链表的实现。
*/
#include "List.cpp"

#if !defined(_CPP_SEQLIST)

#define _CPP_SEQLIST

template <class EleType>
class SEQLIST:public LIST<EleType>
{
public:
	SEQLIST(void);
	SEQLIST(int nMaxLength);
	~SEQLIST();

	int Insert(int nPos,EleType newValue);
	int Delete(int nPos,EleType &Result);
	int Get(int nPos,EleType &Result);
	int Locate(EleType nValue);

	void Reverse(void);

protected:
	EleType *m_Datas;				
	int m_MaxLength;
};

//默认构造函数，数组大小默认为10
template <class EleType>
SEQLIST<EleType>::SEQLIST(void):LIST<EleType>()
{
	m_MaxLength=10;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//指定数组大小的构造函数
template <class EleType>
SEQLIST<EleType>::SEQLIST(int nMaxLength):LIST<EleType>()
{
	m_MaxLength=nMaxLength;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//析构函数，释放构造函数中申请的空间
template <class EleType>
SEQLIST<EleType>::~SEQLIST(void)
{
	delete[] m_Datas;
}

//插入新元素
template <class EleType>
int SEQLIST<EleType>::Insert(int nPos,EleType newValue)
{
	if(m_Length==m_MaxLength)
		return -1;
	else if(nPos<1 || nPos>m_Length+1)
		return -2;
	else
	{
		int iPos;
		//先将指定位置及以后的元素顺次向后移动一个位置
		for(iPos=m_Length;iPos>=nPos;iPos--)
			m_Datas[iPos]=m_Datas[iPos-1];

		//将新元素值存入腾出来的数组元素中
		m_Datas[nPos-1]=newValue;

		//长度增加1
		m_Length++;

		return 1;
	}
}

//删除指定位置的元素
template <class EleType>
int SEQLIST<EleType>::Delete(int nPos,EleType &Result)
{
	//删除位置不合法，返回-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else
	{
		int iPos;
		
		//先将指定位置的元素取出来
		Result=m_Datas[nPos-1];

		//该位置后面所有元素都向前移动一个位置
		for(iPos=nPos;iPos<m_Length;iPos++)
			m_Datas[iPos-1]=m_Datas[iPos];

		//长度减小1
		m_Length--;
		return 1;

	}
}

//按位置查找
template <class EleType>
int SEQLIST<EleType>::Get(int nPos,EleType &Result)
{	
	//if(nPos<1 || nPos>m_Length)
	//	return 0;
	if(nPos<1 || nPos>m_MaxLength)
		return 0;
	else if(nPos>m_Length)
	{
		Result = (EleType)'^';
		return 1;
	}
	else
	{
		Result=m_Datas[nPos-1];
		return 1;
	}
}

//按值查找
template <class EleType>
int SEQLIST<EleType>::Locate(EleType nValue)
{
	int iPos;
	for(iPos=1;iPos<=m_Length;iPos++)
	{
		if(m_Datas[iPos-1]==nValue)
			break;
	}
	if(iPos>m_Length)
		return 0;
	else
		return iPos;
}


//就地逆置
template <class EleType>
void SEQLIST<EleType>::Reverse(void)
{
	int Left,Right;
	EleType Temp;

	Left=0;
	Right=m_Length-1;
	while(Left<Right)
	{
		Temp=m_Datas[Left];
		m_Datas[Left]=m_Datas[Right];
		m_Datas[Right]=Temp;

		Left++;
		Right--;
	}
}

#endif