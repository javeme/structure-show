#include "List.cpp"
#include "Node.h"

#if !defined(_CPP_CYCLELINKLIST)
#define _CPP_CYCLELINKLIST



//����ר��ͷ�ڵ�ĵ������ඨ��
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

//��������
template <class EleType>
CYCLELINKLIST<EleType>::~CYCLELINKLIST(void)
{
	EleType nValue;
	//��һɾ��������Ч�ڵ�
	while(Length()>0)
		Delete(1,nValue);

	delete m_First;

}

//�����Ա���
template <class EleType>
int CYCLELINKLIST<EleType>::Length(void)
{
	return m_Length;
}

//��λ�ò���
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

//�����ݲ���
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

//������Ԫ��
template <class EleType>
int CYCLELINKLIST<EleType>::Insert(int nPos,EleType newValue)
{
	LINKNODE<EleType> *s=NULL;
	//1.����ڵ�ռ�
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

//ɾ��ָ��λ��Ԫ��
template <class EleType>
int CYCLELINKLIST<EleType>::Delete(int nPos,EleType &Result)
{
	//ɾ��λ�ò��Ϸ�������-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else
	{
		int iPos=1;
		
		LINKNODE<EleType> *p=m_First,*q;		//����ָ��

		//��p��λ��Ҫɾ���ڵ��ֱ��ǰ��
		while(iPos<nPos && NULL!=p)
		{
			p=p->Next;
			iPos++;
		}

		//ɾ��p��ֱ�Ӻ��
		//��qָ���ɾ���ڵ�
		q=p->Next;
		//p��ָ���򲿷�ָ���ɾ���ڵ��ֱ�Ӻ��
		p->Next=q->Next;
		//����ֵ
		Result=q->Data;
		//ɾ���ڵ�
		delete q;

		m_Length--;
		return 1;

	}
}

//�Ƿ��ʼ���ɹ�
template <class EleType>
int CYCLELINKLIST<EleType>::InitOK()
{
	return m_InitOK;
}

//Ĭ�Ϲ��캯��
template <class EleType>
CYCLELINKLIST<EleType>::CYCLELINKLIST(void)
{
	LINKNODE<EleType> *p=NULL;

	//����ר��ͷ�ڵ�
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
