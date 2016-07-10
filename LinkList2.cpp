/*
	����ר��ͷ���ĵ������ʵ��
*/
#include "List.cpp"
#include "Node.h"

#if !defined(_CPP_LINKLIST22)

#define _CPP_LINKLIST22

//����ר��ͷ�ڵ�ĵ������ඨ��
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


//Ĭ�Ϲ��캯��
template <class EleType>
LINKLIST2<EleType>::LINKLIST2(void):LIST<EleType>()
{
	m_First=NULL;
	m_InitOK=1;
}

//��������
template <class EleType>
LINKLIST2<EleType>::~LINKLIST2(void)
{
	EleType nValue;
	//��һɾ��������Ч�ڵ�
	while(Length()>0)
		Delete(1,nValue);
}

//������Ԫ��
template <class EleType>
int LINKLIST2<EleType>::Insert(int nPos,EleType newValue)
{
	LINKNODE<EleType> *s=NULL;
	//����ڵ�ռ�
	s=new LINKNODE<EleType>;

	//����ռ�ʧ�ܣ�����-1
	if(!s)
		return -1;

	//������λ�ò������ͷŸ�����Ľ��ռ䣬����-2
	if(nPos<1 || nPos>m_Length+1)
	{
		delete s;
		return -2;
	}
	//����λ�ú���
	else
	{
		int iPos;
		
		s->Data=newValue;

		LINKNODE<EleType> *p,*q;

		//��pָ��Ȳ������ǰ��,qָ�������λ�ô��Ľ��
		p=NULL;
		q=m_First;
		iPos=1;
		while(iPos<nPos && q)
		{
			p=q;
			q=q->Next;
			iPos++;
		}

		//��pΪ�գ�˵��������λ��Ϊ1����Ҫ�޸�m_Firstֵ
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

//ɾ��ָ��λ��Ԫ��
template <class EleType>
int LINKLIST2<EleType>::Delete(int nPos,EleType &Result)
{
	//ɾ��λ�ò��Ϸ�������-1
	if(nPos<1 || nPos>m_Length)
		return -1;
	else		//ִ�и÷�֧ʱ������
	{
		int iPos=1;
		
		LINKNODE<EleType> *p,*q;		//����ָ��

		q=m_First;
		p=NULL;
		//��p��λ��Ҫɾ���ڵ��ֱ��ǰ��
		while(iPos<nPos && NULL!=q)
		{
			p=q;
			q=q->Next;
			iPos++;
		}

		//Ҫɾ������ͷ���
		if(!p)
		{
			m_First=m_First->Next;
		}
		else
		{
			//p��ָ���򲿷�ָ���ɾ���ڵ�q��ֱ�Ӻ��
			p->Next=q->Next;
		}
		//����ֵ
		Result=q->Data;
		//ɾ���ڵ�
		q->Next=NULL;
		delete q;
		//���ȼ�1
		m_Length--;

		return 1;

	}
}

//��λ�ò���
template <class EleType>
int LINKLIST2<EleType>::Get(int nPos,EleType &Result)
{
	//��ָ���Ĳ���λ��nPos����������0
	if(nPos<1 || nPos>m_Length)
		return 0;
	//ָ���Ĳ���λ�ú�����������
	else
	{
		int iPos=1;
		LINKNODE<EleType> *p;

		//p����ָ��ͷ���
		p=m_First;
		//������δ��������δ�ﵽָ��nPosָ��λ��ʱָ�����
		while(iPos<nPos && p)
		{
			p=p->Next;
			iPos++;
		}

		Result=p->Data;
		return 1;
	}
}

//�����ݲ���
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


//�͵�����
template <class EleType>
void LINKLIST2<EleType>::Reverse(void)
{
	LINKNODE<EleType> *p,*q;
	
	p=m_First;
	//��pָ���1�����
	if(p)
	{
		q=p->Next;
		while(q)
		{
			//��p�ĺ�̽����Ϊ�µ�ͷ�����뵽��ͷ���ǰ��
			p->Next=q->Next;
			q->Next=m_First;
			m_First=q;
			
			//��qָ��p���µĺ��
			q=p->Next;
		}
	}
}


#endif