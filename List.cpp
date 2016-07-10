/*
	线性表的抽象基类。
	对于纯虚函数，应规定其接口和返回值的情况。
*/
#if !defined(_CPP_LIST)
#define _CPP_LIST

#include "DataStructure.cpp"

template <class EleType>
class LIST:public DataStructure<EleType>
{
public:
	LIST(void);
	virtual ~LIST();

	int InitOK();
	int Length();	

	virtual int Insert(int nPos,EleType newValue)=0;
	virtual int Delete(int nPos,EleType &Result)=0;
	virtual int Get(int nPos,EleType &Result)=0;
	virtual int Locate(EleType nValue)=0;
	virtual void Reverse(void)=0;

protected:
	int m_InitOK;
	int m_Length;
};

//默认构造函数
template <class EleType>
LIST<EleType>::LIST(void)
{
	m_Length=0;
	m_InitOK=0;
}

//析构函数
template <class EleType>
LIST<EleType>::~LIST(void)
{
	
}

//检测初始化是否成功
template <class EleType>
int LIST<EleType>::InitOK()
{
	return m_InitOK;
}

//返回线性表的长度
template <class EleType>
int LIST<EleType>::Length(void)
{
	return m_Length;
}


#endif