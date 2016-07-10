/*
	��̬������ʵ�֣��ڵ������������ʵ�֡�
	2010-10-15
*/
#include "List.cpp"

#if !defined(_CPP_STATICLIST)

#define _CPP_STATICLIST

//��̬����Ľڵ㶨��
template <class EleType>
struct STATICNODE
{
	EleType Data;
	int Next;				//ָ����һ��Ԫ�ص��α꣬-1��ʾΪ���һ��
};

//��̬�����ඨ��
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
	STATICNODE<EleType> *m_Datas;			//ָ��̬�����ָ��
	int m_FirstFreeIndex;					//��һ����������Ԫ���±꣨�α꣩
	int m_FirstUsedIndex;					//���Ա��һ����ЧԪ�����������±꣨�α꣩
	int m_MaxLength;						//�����С��Ĭ��10
};

//Ĭ�Ϲ��캯���������СΪ10
template <class EleType>
STATICLIST<EleType>::STATICLIST(void):LIST<EleType>()
{
	//Ĭ�������СΪ10
	m_MaxLength=10;
	//����ռ�
	m_Datas=new STATICNODE<EleType>[m_MaxLength];
	//����ɹ�
	if(m_Datas)
	{
		m_InitOK=1;
		//�����һ��Ԫ�ؿ���ʹ��
		m_FirstFreeIndex=0;
		//��ʼʱΪ�ձ���������ЧԪ��
		m_FirstUsedIndex=-1;
		//��ʼ�����ÿռ�����
		int i;
		//ÿ������Ԫ�ص��α�Ϊ����һ��Ԫ���±�
		for(i=0;i<m_MaxLength;i++)
			m_Datas[i].Next=i+1;
		//�������һ��Ԫ��Ϊ��1
		m_Datas[m_MaxLength-1].Next=-1;
	}
	else
	{
		m_FirstFreeIndex=-1;
		m_FirstUsedIndex=-1;
	}
}

//��ָ����С�Ĺ��캯��
template <class EleType>
STATICLIST<EleType>::STATICLIST(int nMaxLength):LIST<EleType>()
{
	//����ָ�������鳤��
	m_MaxLength=nMaxLength;
	//����ռ�
	m_Datas=new STATICNODE<EleType>[m_MaxLength];
	//����ɹ�
	if(m_Datas)
	{
		m_InitOK=1;
		//�����һ��Ԫ�ؿ���ʹ��
		m_FirstFreeIndex=0;
		//��ʼʱΪ�ձ���������ЧԪ��
		m_FirstUsedIndex=-1;
		//��ʼ�����ÿռ�����
		int i;
		//ÿ������Ԫ�ص��α�Ϊ����һ��Ԫ���±�
		for(i=0;i<m_MaxLength;i++)
			m_Datas[i].Next=i+1;
		//�������һ��Ԫ��Ϊ��1
		m_Datas[m_MaxLength-1].Next=-1;
	}
	else
	{
		m_FirstFreeIndex=-1;
		m_FirstUsedIndex=-1;
	}
		
}

//��������
template <class EleType>
STATICLIST<EleType>::~STATICLIST(void)
{
	delete[] m_Datas;
}

//������Ԫ��
template <class EleType>
int STATICLIST<EleType>::Insert(int nPos,EleType newValue)
{
	//�ж����޿�������Ԫ�ؿɹ�ʹ�ã����ޣ����أ�1
	if(m_FirstFreeIndex==-1)
		return -1;

	//�жϲ���λ�ã������Ϸ������أ�2
	else if(nPos<1 || nPos>m_Length+1)
	{
		return -2;
	}

	//����λ�úϷ�
	else
	{
		
		int FreeIndex;		//�ҵ��ĵ�һ����������Ԫ�ص��±�

		FreeIndex=m_FirstFreeIndex;
		m_FirstFreeIndex=m_Datas[FreeIndex].Next;
		m_Datas[FreeIndex].Data=newValue;

		//Ѱ�Ҳ���λ��
		int iPos=1;
		
		int CurrIndex,LastIndex;

		//�����Ա�Ϊ��
		if(m_FirstUsedIndex==-1)
		{
			m_FirstUsedIndex=FreeIndex;
			m_Datas[FreeIndex].Next=-1;
		}
		//�����Ա���
		else
		{
			//Ѱ�Ҳ���λ�õ�ǰһ��Ԫ�����������±�
			CurrIndex=m_FirstUsedIndex;
			LastIndex=-1;
			while(iPos<nPos)
			{
				LastIndex=CurrIndex;
				CurrIndex=m_Datas[CurrIndex].Next;
				iPos++;
			}
			
			//����λ��Ϊ��1��
			if(LastIndex==-1)
			{
				m_Datas[FreeIndex].Next=m_FirstUsedIndex;
				m_FirstUsedIndex=FreeIndex;
			}
			//����λ�ò�Ϊ��1��
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

//ɾ��ָ��λ��Ԫ��
template <class EleType>
int STATICLIST<EleType>::Delete(int nPos,EleType &Result)
{
	//ɾ��λ�ò��Ϸ�������-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else
	{
		int iPos=1;
		int CurrIndex,LastIndex;

		//��p��λ��Ҫɾ���ڵ��ֱ��ǰ��
		LastIndex=-1;
		CurrIndex=m_FirstUsedIndex;
		while(iPos<nPos)
		{
			LastIndex=CurrIndex;
			CurrIndex=m_Datas[CurrIndex].Next;
			iPos++;
		}

		//CurrIndexΪ��ɾ��������������±꣬LastIndexΪ��ֱ��ǰ�����±�
		//Ҫɾ�����ǵ�һ�����
		if(LastIndex==-1)
		{
			m_FirstUsedIndex=m_Datas[CurrIndex].Next;
		}
		//Ҫɾ���Ĳ��ǵ�һ�����
		{
			m_Datas[LastIndex].Next=m_Datas[CurrIndex].Next;
		}

		//��������
		Result=m_Datas[CurrIndex].Data;

		//��CurrIndex��ָ������Ϊ���ý��ĵ�1��
		m_Datas[CurrIndex].Next=m_FirstFreeIndex;
		m_FirstFreeIndex=CurrIndex;

		m_Length--;
		return 1;

	}
}

//��λ�ò���
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

//�����ݲ���
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

//�͵�����
template <class EleType>
void STATICLIST<EleType>::Reverse(void)
{
	int Curr,Last;		//�����α�
	
	Curr=m_FirstUsedIndex;
	if(Curr!=-1)
	{
		Last=m_Datas[Curr].Next;
		while(Last!=-1)
		{
			//��Curr�ĺ�̸�Ϊm_FirstUsedIndex��ǰ��
			m_Datas[Curr].Next=m_Datas[Last].Next;
			m_Datas[Last].Next=m_FirstUsedIndex;
			m_FirstUsedIndex=Last;

			//��LastΪCurr�ĺ���α�
			Last=m_Datas[Curr].Next;
		}
	}
}

#endif