/*
	����ר��ͷ���ĵ�������ʵ��
*/
#include "List.cpp"
#include "Node.h"

#if !defined(_CPP_LINKLIST)

#define _CPP_LINKLIST

//����ר��ͷ�ڵ�ĵ������ඨ��
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

//Ĭ�Ϲ��캯��
template <class EleType>
LINKLIST<EleType>::LINKLIST(void):LIST<EleType>()
{
	LINKNODE<EleType> *p=NULL;

	//����ר��ͷ�ڵ�
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

//��������
template <class EleType>
LINKLIST<EleType>::~LINKLIST(void)
{
	EleType nValue;

	//��һɾ�����нڵ�
	while(Length()>0)
		Delete(1,nValue);

	delete m_First;

}

//������Ԫ��
template <class EleType>
int LINKLIST<EleType>::Insert(int nPos,EleType newValue)
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
int LINKLIST<EleType>::Delete(int nPos,EleType &Result)
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

//��λ�ò���
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

//�����ݲ���
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


//�͵�����
template <class EleType>
void LINKLIST<EleType>::Reverse(void)
{
	LINKNODE<EleType> *p,*q;
	
	p=m_First->Next;
	//��pָ���1�����
	if(p)
	{
		q=p->Next;
		while(q)
		{
			//��p�ĺ�̽����뵽ͷ������
			p->Next=q->Next;
			q->Next=m_First->Next;
			m_First->Next=q;
			
			//��qָ��p���µĺ��
			q=p->Next;
		}
	}
}

#endif