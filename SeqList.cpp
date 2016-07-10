/*
	˳�������ʵ�֡�
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

//Ĭ�Ϲ��캯���������СĬ��Ϊ10
template <class EleType>
SEQLIST<EleType>::SEQLIST(void):LIST<EleType>()
{
	m_MaxLength=10;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//ָ�������С�Ĺ��캯��
template <class EleType>
SEQLIST<EleType>::SEQLIST(int nMaxLength):LIST<EleType>()
{
	m_MaxLength=nMaxLength;
	m_Datas=new EleType[m_MaxLength];
	if(m_Datas)
		m_InitOK=1;
}

//�����������ͷŹ��캯��������Ŀռ�
template <class EleType>
SEQLIST<EleType>::~SEQLIST(void)
{
	delete[] m_Datas;
}

//������Ԫ��
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
		//�Ƚ�ָ��λ�ü��Ժ��Ԫ��˳������ƶ�һ��λ��
		for(iPos=m_Length;iPos>=nPos;iPos--)
			m_Datas[iPos]=m_Datas[iPos-1];

		//����Ԫ��ֵ�����ڳ���������Ԫ����
		m_Datas[nPos-1]=newValue;

		//��������1
		m_Length++;

		return 1;
	}
}

//ɾ��ָ��λ�õ�Ԫ��
template <class EleType>
int SEQLIST<EleType>::Delete(int nPos,EleType &Result)
{
	//ɾ��λ�ò��Ϸ�������-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else
	{
		int iPos;
		
		//�Ƚ�ָ��λ�õ�Ԫ��ȡ����
		Result=m_Datas[nPos-1];

		//��λ�ú�������Ԫ�ض���ǰ�ƶ�һ��λ��
		for(iPos=nPos;iPos<m_Length;iPos++)
			m_Datas[iPos-1]=m_Datas[iPos];

		//���ȼ�С1
		m_Length--;
		return 1;

	}
}

//��λ�ò���
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

//��ֵ����
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


//�͵�����
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