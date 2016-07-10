/*
	���Ա�ĳ�����ࡣ
	���ڴ��麯����Ӧ�涨��ӿںͷ���ֵ�������
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

//Ĭ�Ϲ��캯��
template <class EleType>
LIST<EleType>::LIST(void)
{
	m_Length=0;
	m_InitOK=0;
}

//��������
template <class EleType>
LIST<EleType>::~LIST(void)
{
	
}

//����ʼ���Ƿ�ɹ�
template <class EleType>
int LIST<EleType>::InitOK()
{
	return m_InitOK;
}

//�������Ա�ĳ���
template <class EleType>
int LIST<EleType>::Length(void)
{
	return m_Length;
}


#endif