/*
	�������Ķ��������ʾ����
*/
#include <stdio.h>
#include "Queue.cpp"
#include "SeqQueue.cpp"
#include "BinTree.cpp"
#include "Stack.cpp"
#include "SeqStack.cpp"

#if !defined(_CPP_CBINTREELINK)

#define _CPP_CBINTREELINK

//�������ڵ㶨��
template <class EleType>
struct BINODE  
{
	EleType Data;
	int x;
	int y;
	int width;
	BINODE<EleType> *pLeft,*pRight;
};

template <class EleType>
class CBinTreeLink : public CBinTree<EleType>
{
public:
	CBinTreeLink();
	virtual ~CBinTreeLink();

	virtual int Serialize(const char * const FileName,int IsSaveToFile);

	//��ҵ�����Ӷ�������ȣ�11.18��
	virtual int InsertL(EleType Parent,EleType Child);
	virtual int DeleteL(EleType);
	virtual int InsertR(EleType Parent,EleType Child);
	virtual int DeleteR(EleType);

	virtual void PreOrder() const;
	virtual void PostOrder() const;
	virtual void LevelOrder() const;
	virtual void InOrder() const;

	//ǰ������ķǵݹ�ӿ�
	virtual void PreOrder2() const;

	virtual int Root(EleType&,int&,int&);
	virtual int Parent(EleType Child,EleType& Parent);
	virtual int Search(EleType Value);
	virtual int Depth() const;

	//��ӷ���
	virtual int GetLeftChildOf(EleType parentValue,EleType& childValue,int &x,int &y);
	virtual int GetRightChildOf(EleType parentValue,EleType& childValue,int &x,int &y);
	virtual int SetPositionOf(EleType selfValue,int x,int y,int width);
	virtual int GetPositionOf(EleType selfValue,int &x,int &y);
protected:

	void InnerPreOrder(BINODE<EleType> *pRoot) const;
	void InnerPostOrder(BINODE<EleType> *pRoot) const;
	void InnerInOrder(BINODE<EleType> *pRoot) const ;

	int InnerInsertL(BINODE<EleType> *pRoot,EleType Parent,EleType Child);
	int InnerInsertR(BINODE<EleType> *pRoot,EleType Parent,EleType Child);
	int InnerDepth(BINODE<EleType> *pRoot) const;

	void InnerDelete(BINODE<EleType>* pRoot);

	void InnerFindParent(BINODE<EleType> *pRoot,BINODE<EleType> *pParent,EleType Child,EleType& Parent);

	void InnerFindNode(BINODE<EleType> *pParent,
							BINODE<EleType> *pRoot,
							EleType Value,
							BINODE<EleType>* &pNode);


	//Ѱ�ҽ��ʱ�ı�ʶ
	int m_Found;
	//���������ڵ�ָ��
	BINODE<EleType> *m_Root;

};

//OK
template <class EleType>
CBinTreeLink<EleType>::CBinTreeLink()
{
	m_Root=NULL;
}

//OK
template <class EleType>
CBinTreeLink<EleType>::~CBinTreeLink()
{
	InnerDelete(m_Root);
}

/*
	�������������ֵ��
	������
		������������������͵ı���
	����ֵ��
		����������������ֵ

	����ֵ��
		0	������Ϊ�գ����÷��ص�Rootֵ������
		1	���������գ����÷��ص�RootֵΪ������������ֵ

	ע�⺯������ֵ��ͨ�����÷���ֵ������
	OK
*/
template <class EleType>
int CBinTreeLink<EleType>::Root(EleType& Root,int& x,int& y)
{
	if(m_Root==NULL)
	{
		return 0;
	}
	else
	{
		Root=m_Root->Data;
        x=m_Root->x;
		y=m_Root->y;
		return 1;
	}
}

/*
	ָ������ֵ������˫�׽���ֵ��
	������
		Child	
	����ֵ��
		��
	�ú���Ϊ�ӿں�����

  pParent=NULL;
	pChild=m_Root;

	���Ӷ��������ҡ�
	���Ӷ������Ķ���������ʼ���ҡ�
	1)����Ӷ�������������pChild->Data=Child���ҵ����ӽڵ㣬������˫�׽ڵ�ֵpParent->Data(pParent����)
	2)�������β���pChild�����Ӷ�������������������pParent=pChild,pChild=pChild->pLeft)
	3)���pChildΪ�գ����أ��������ֵܽڵ�(pChild=pChild->pNextSibiling)
	4)����һ����־����Ա����m_Found���ҵ�����Ϊ1����ʼֵ=0

*/
template <class EleType>
int CBinTreeLink<EleType>::Parent(EleType Child,EleType& Parent)
{
	m_Found=0;
	InnerFindParent(m_Root,NULL,Child,Parent);

	return m_Found;
}

/*
	���ܣ�
		Ѱ��˫�׽ڵ��ֵ
	������
		pRoot	[in]	�������ڵ�ָ��
		pParent	[in]	�������ڵ��˫�׽ڵ�ָ��
		Child	[in]	�����Һ��ӽڵ�ֵ
		Parent	[out]	�ú��ӽڵ��˫�׽ڵ�ֵ������������
	����ֵ��
		��
	˵����
		ִ�й����п����޸�m_Foundֵ��
		m_Foundֵ���壺
		0	δ�ҵ�ֵ��Ӧ�Ľڵ�
		1	�ҵ�ֵ��Ӧ�Ľڵ㣬��˫�׽ڵ�ֵͨ��Parent����
		2	�ҵ�ֵ��Ӧ�Ľڵ㣬������˫�׽ڵ㣨���ڵ㣩
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerFindParent(
							BINODE<EleType> *pRoot,
							BINODE<EleType> *pParent,
							EleType Child,
							EleType& Parent)
{

	//������ʱֱ�ӷ���
	if(pRoot==NULL)
		return;

	//�������ڵ�ֵΪ����ֵ�����ҽ���������		
	if(pRoot->Data==Child)
	{
		//m_Found=1;
		if(pParent!=NULL)
		{
			Parent=pParent->Data;
			m_Found=1;
		}
		else
		{
			m_Found=2;
		}
	}
	//�������ڵ�ֵ���Ǵ���ֵ���������еݹ����		
	else
	{
		//�����������в���
		InnerFindParent(pRoot->pLeft,pRoot,Child,Parent);

		//����������û�ҵ������������в���
		if(m_Found==0)
			InnerFindParent(pRoot->pRight,pRoot,Child,Parent);
	}
}

/*
	���ܣ�
		����ֵ��Ӧ�Ľڵ�ָ��
	������
		pParent	[in]	�������ڵ�˫�׵�ָ��
		pRoot	[in]	�������ڵ�ָ��
		Value	[in]	�����ҽڵ�ֵ
		pNode	[out]	ָ��ýڵ��ָ��
	����ֵ��
		��
	˵����
		�ڲ�������
		��ǰ�������ʽ����
*/
template <class EleType>
int CBinTreeLink<EleType>::Search(EleType Value)
{
	BINODE<EleType> *pNode=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,Value,pNode);
	return m_Found;

}
/*************************************************************��������************************************************************/
template <class EleType>
int CBinTreeLink<EleType>::SetPositionOf(EleType selfValue,int x,int y,int width)
{
	BINODE<EleType> *pNode=NULL;
	m_Found=0;
	InnerFindNode(NULL,m_Root,selfValue,pNode);
	if(pNode)
	{
		pNode->x=x;
		pNode->y=y;
		pNode->width=width;
	}
	return m_Found;
}////////////////////////////////////////////��ȡ�ڵ�λ��
template <class EleType>
int CBinTreeLink<EleType>::GetPositionOf(EleType selfValue,int &x,int &y)
{
	BINODE<EleType> *pToFindNode;
	m_Found=0;
	InnerFindNode(NULL,m_Root,selfValue,pToFindNode);
	if(m_Found)
	{
		x=pToFindNode->x;
		y=pToFindNode->y;
	}
	return m_Found;
}
//��ú���
template <class EleType>
int CBinTreeLink<EleType>::GetLeftChildOf(EleType parentValue,EleType& childValue,int &x,int &y)
{
	BINODE<EleType> *pNode=NULL;
	m_Found=0;
	InnerFindNode(NULL,m_Root,parentValue,pNode);
	if(pNode)
	{
		pNode=pNode->pLeft;
		if(!pNode)
			return 0;
		childValue=pNode->Data;
		x=pNode->x;
		y=pNode->y;		
	}
	return m_Found;
}
template <class EleType>
int CBinTreeLink<EleType>::GetRightChildOf(EleType parentValue,EleType& childValue,int &x,int &y)
{
	BINODE<EleType> *pNode=NULL;
	m_Found=0;
	InnerFindNode(NULL,m_Root,parentValue,pNode);
	if(pNode)
	{
		pNode=pNode->pRight;
		if(!pNode)
			return 0;
		childValue=pNode->Data;
		x=pNode->x;
		y=pNode->y;		
	}
	return m_Found;
}
/*
	���ܣ�
		����ֵ��Ӧ�Ľڵ�ָ��
	������
		pParent	[in]	�������ڵ�˫�׵�ָ��
		pRoot	[in]	�������ڵ�ָ��
		Value	[in]	�����ҽڵ�ֵ
		pNode	[out]	ָ��ýڵ��ָ��
	����ֵ��
		��
	˵����
		�ڲ�������
		��ǰ�������ʽ����
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerFindNode(
							BINODE<EleType> *pParent,
							BINODE<EleType> *pRoot,
							EleType Value,
							BINODE<EleType>* &pNode
							)
{
	//������ʱֱ�ӷ���
	if(pRoot==NULL)
	{
		pNode=NULL;
		return;
	}

	//�������ڵ�ֵΪ����ֵ�����ҽ���������		
	if(pRoot->Data==Value)
	{
		pNode=pRoot;
		m_Found=1;
	}
	//�ݹ����������
	else
	{
		InnerFindNode(pRoot,pRoot->pLeft,Value,pNode);
		if(m_Found==0)
			InnerFindNode(pRoot,pRoot->pRight,Value,pNode);
	}
}

/*
	���ܣ�
		���������������
	������
		��
	����ֵ��
		����ֵ�����������
	˵����
		�ú���Ϊ�ӿں�����ͨ�������ڲ�����ʵ�֡�
*/
template <class EleType>
int CBinTreeLink<EleType>::Depth() const
{
	return InnerDepth(m_Root);
}

/*
	���ܣ�
		���������
	������
		pRoot	[in]	���������ָ��
	����ֵ��
		���ͣ������������
	˵����
		�涨�������������Ϊ1��
		�ڲ��������ݹ飬��Depth����
*/
template <class EleType>
int CBinTreeLink<EleType>::InnerDepth(BINODE<EleType> *pRoot) const
{
	//����Ϊ�գ�ֱ�ӷ���0
	if(pRoot==NULL)
		return 0;

	int nDepthLeft,nDepthRight;

	//�������������������
	nDepthLeft=InnerDepth(pRoot->pLeft);
	nDepthRight=InnerDepth(pRoot->pRight);

	if(nDepthLeft>nDepthRight)
		return nDepthLeft+1;
	else
		return nDepthRight+1;
}

/*
	���ܣ�
		�������������
	������
		��
	����ֵ��
		��
	˵����
		�ú���Ϊ�ӿں�����ͨ�������ڲ�����ʵ��
*/
template <class EleType>
void CBinTreeLink<EleType>::PreOrder() const
{
	InnerPreOrder(m_Root);
}

/*
	���ܣ�
		��������������ĵݹ�ʵ��
	������
		pRoot	[in]	���������ָ��		
	����ֵ��
		��
	˵����
		�ڲ��������ݹ飬��PreOrder����
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerPreOrder(BINODE<EleType> *pRoot) const
{
	//����Ϊ�գ�ֱ�ӷ���
	if(!pRoot)
		return;

	//1.���ʸ�
	cout<<pRoot->Data<<endl;

	//2.���������������������
	InnerPreOrder(pRoot->pLeft);
	InnerPreOrder(pRoot->pRight);
}

/*
//�̲Ĵ���
template <class EleType>
void CBinTreeLink<EleType>::PreOrder2() const
{
	//����ָ��
	BINODE<EleType> *pRoot;
	//����ջ
	STACK<BINODE<EleType> *> *pStack;

	pStack=new SEQSTACK<BINODE<EleType>*>(m_NodeCount);

	if(!pStack)
		return;

	pRoot=m_Root;
	while(pRoot || pStack->Length()>0)
	{
		while(pRoot)
		{
			cout<<pRoot->Data<<endl;
			pStack->Push(pRoot);
			pRoot=pRoot->pLeft;
		}

		if(pStack->Length()>0)
		{
			pStack->Pop(pRoot);
			pRoot=pRoot->pRight;
		}
	}
}
*/

//�̲Ĵ���ĸĽ�
template <class EleType>
void CBinTreeLink<EleType>::PreOrder2() const
{
	//����ָ��
	BINODE<EleType> *pRoot;
	//����ջ
	STACK<BINODE<EleType> *> *pStack;

	pStack=new SEQSTACK<BINODE<EleType>*>(m_NodeCount);

	if(!pStack)
		return;

	pRoot=m_Root;
	while(pRoot || pStack->Length()>0)
	{
		while(pRoot)
		{
			cout<<pRoot->Data<<endl;
			if(pRoot->pRight)
				pStack->Push(pRoot->pRight);
			pRoot=pRoot->pLeft;
		}

		if(pStack->Length()>0)
		{
			pStack->Pop(pRoot);
			//pRoot=pRoot->pRight;
		}
	}
}

/*
	���ܣ�
		�������������
	������
		��
	����ֵ��
		��
	˵����
		�ú���Ϊ�ӿں�����ͨ�������ڲ�����ʵ��
*/
template <class EleType>
void CBinTreeLink<EleType>::PostOrder() const
{
	InnerPostOrder(m_Root);
}

/*
	���ܣ�
		��������������ĵݹ�ʵ��
	������
		pRoot	[in]	���������ָ��		
	����ֵ��
		��
	˵����
		�ڲ��������ݹ飬��PostOrder����
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerPostOrder(BINODE<EleType> *pRoot) const
{
	//����Ϊ�գ�ֱ�ӷ���
	if(!pRoot)
		return;

	//1.���������������������
	InnerPostOrder(pRoot->pLeft);
	InnerPostOrder(pRoot->pRight);

	//2.���ʸ�
	cout<<pRoot->Data<<endl;
}

/*
	���ܣ�
		�������������
	������
		��
	����ֵ��
		��
	˵����
		�ú���Ϊ�ӿں�����ͨ�������ڲ�����ʵ��
*/
template <class EleType>
void CBinTreeLink<EleType>::InOrder() const
{
	InnerInOrder(m_Root);
}

/*
	���ܣ�
		��������������ĵݹ�ʵ��
	������
		pRoot	[in]	���������ָ��		
	����ֵ��
		��
	˵����
		�ڲ��������ݹ飬��InOrder����
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerInOrder(BINODE<EleType> *pRoot) const
{
	//����Ϊ�գ�ֱ�ӷ���
	if(!pRoot)
		return;

	//1.����������
	InnerInOrder(pRoot->pLeft);

	//2.���ʸ�
	cout<<pRoot->Data<<endl;

	//3.����������
	InnerInOrder(pRoot->pRight);
}

/*
	���ܣ�
		�������������
	������
		��
	����ֵ��
		��
	˵����
		�ú���Ϊ�ӿں������ǵݹ�ʵ��
	˼·��
		1)���ȷ��ʸ��ڵ�
		2)��������ڵ�󣬽���ָ�����
		3)�����в���ʱ��
			3.1)���ӣ���ָ����ָ�ڵ��Ѿ����ʹ���
			3.2)�����Ӳ��գ����ʣ�����ָ�����
			3.3)���Һ��Ӳ��գ����ʣ�����ָ�����
*/
template <class EleType>
void CBinTreeLink<EleType>::LevelOrder() const
{
	//����ֱ��
	if(m_Root==NULL)
		return;

	//����һ������������������ͬ��ѭ�����У�Ԫ������Ϊ�����ָ��
	CQueue<BINODE<EleType>*> *pQueue;
	pQueue=new CSeqQueue<BINODE<EleType>*>(m_NodeCount);
	
	//���д������ɹ����˳�
	if(!pQueue)
		return;

	//���г�ʼ��ʧ�ܣ��˳�
	if(pQueue->InitOK()==0)
	{
		delete pQueue;
		return;
	}

	BINODE<EleType> *pNode,*pChild;

	//���ʸ��ڵ�
	pNode=m_Root;
	cout<<pNode->Data<<endl;

	//�����ָ�����
	pQueue->EnQueue(pNode);

	//�����в���ʱ
	while(pQueue->Length()>0)
	{
		//ȡ����ͷԪ�أ�����ָ����Ѿ����ʹ�
		pQueue->DeQueue(pNode);

		//�ȷ�������
		pChild=pNode->pLeft;
		if(pChild)
		{
			cout<<pChild->Data<<endl;
			pQueue->EnQueue(pChild);
		}
		//�ٷ����Һ���
		pChild=pNode->pRight;
		if(pChild)
		{
			cout<<pChild->Data<<endl;
			pQueue->EnQueue(pChild);
		}
	}

	//����������ɾ������
	delete pQueue;
}

/*
	���ܣ�
		��������
	������
		Parent	[in]	˫�׽��ֵ
		Child	[in]	�������Һ��ӽ��ֵ
	����ֵ��
		0	�ҵ�˫�׽�㣬���ڴ治�㣬���ܴ����½��
		1	δ�ҵ�˫�׽��
		2	�ҵ�˫�׽�㣬����ɹ�
		3	�ڵ�ֵ���У�ֵΪChild�Ľ���Ѿ�����
	˵����
		����Ϊ�գ���ֱ����Childֵ��������㣬����Parentֵ
		�������գ������ڲ�����InnerInsertRִ�в������
*/
template <class EleType>
int CBinTreeLink<EleType>::InsertL(EleType Parent,EleType Child)
{
	//�ȼ�������ֵ�Ƿ��Ѿ����ڡ�������ֵ���ظ�����
	BINODE<EleType> *pNode=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,Child,pNode);
	if(pNode!=NULL)
		return 3;

	//����ʱ����ڵ�Ϊ���ڵ㣬��ʱ������˫�׽��ֵ
	if(m_Root==NULL)
	{
		BINODE<EleType> *newNode;
		newNode=new BINODE<EleType>;
		if(newNode)
		{
			newNode->Data=Child;
			newNode->pLeft=NULL;
			newNode->pRight=NULL;
			m_Root=newNode;

			m_NodeCount++;
			return 2;
		}
		else
			return 0;
	}
	//������ʱ���������ڲ������ݹ�ִ��
	else
		return InnerInsertL(m_Root,Parent,Child);
}

/*
	���ܣ�
		��������
	������
		pRoot	[in]	���������ָ��
		Parent	[in]	˫�׽��ֵ
		Child	[in]	���������ӽ��ֵ
	����ֵ��
		0	�ҵ�˫�׽�㣬���ڴ治�㣬���ܴ����½��
		1	δ�ҵ�˫�׽��
		2	�ҵ�˫�׽�㣬����ɹ�
	˵����
		�ڲ��������ݹ����
*/
template <class EleType>
int CBinTreeLink<EleType>::InnerInsertL(BINODE<EleType> *pRoot,EleType Parent,EleType Child)
{
	//����Ϊ�գ�ֱ�ӷ���1
	if(!pRoot)
		return 1;


	//1.�������ڵ��Ǵ�����ڵ��˫��
	if(pRoot->Data==Parent)
	{
		BINODE<EleType> *newNode;
		newNode=new BINODE<EleType>;
		if(newNode)
		{
			newNode->Data=Child;
			newNode->pLeft=pRoot->pLeft;
			newNode->pRight=NULL;
			pRoot->pLeft=newNode;
			newNode->x=pRoot->x - pRoot->width/4;
			newNode->y=pRoot->y + 80;
			newNode->width=pRoot->width/2;
			m_NodeCount++;
			return 2;
		}
		else
			return 0;
	}
	//2.�������ڵ㲻�Ǵ�����ڵ��˫��
	else
	{
		int nRetCode=InnerInsertL(pRoot->pLeft,Parent,Child);
		if(nRetCode!=1)
			return nRetCode;
		else
		{
			nRetCode=InnerInsertL(pRoot->pRight,Parent,Child);
			return nRetCode;
		}
	}
}

/*
	���ܣ�
		�����Һ���
	������
		Parent	[in]	˫�׽��ֵ
		Child	[in]	�������Һ��ӽ��ֵ
	����ֵ��
		0	�ҵ�˫�׽�㣬���ڴ治�㣬���ܴ����½��
		1	δ�ҵ�˫�׽��
		2	�ҵ�˫�׽�㣬����ɹ�
		3	�ڵ�ֵ���У�ֵΪChild�Ľ���Ѿ�����
	˵����
		����Ϊ�գ���ֱ����Childֵ��������㣬����Parentֵ
		�������գ������ڲ�����InnerInsertRִ�в������
*/
template <class EleType>
int CBinTreeLink<EleType>::InsertR(EleType Parent,EleType Child)
{
	//�ȼ�������ֵ�Ƿ��Ѿ����ڡ�������ֵ���ظ�����
	BINODE<EleType> *pNode=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,Child,pNode);
	if(pNode!=NULL)
		return 3;

	//����ʱ����ڵ�Ϊ���ڵ㣬��ʱ������˫�׽��ֵ
	if(m_Root==NULL)
	{
		BINODE<EleType> *newNode;
		newNode=new BINODE<EleType>;
		if(newNode)
		{
			newNode->Data=Child;
			newNode->pLeft=NULL;
			newNode->pRight=NULL;
			m_Root=newNode;

			m_NodeCount++;
			return 2;
		}
		else
			return 0;
	}
	//������ʱ�������ڲ������ݹ�ִ��
	else
		return InnerInsertR(m_Root,Parent,Child);
}

/*
	���ܣ�
		�����Һ���
	������
		pRoot	[in]	���������ָ��
		Parent	[in]	˫�׽��ֵ
		Child	[in]	�������Һ��ӽ��ֵ
	����ֵ��
		0	�ҵ�˫�׽�㣬���ڴ治�㣬���ܴ����½��
		1	δ�ҵ�˫�׽��
		2	�ҵ�˫�׽�㣬����ɹ�
	˵����
		�ڲ��������ݹ����
*/
template <class EleType>
int CBinTreeLink<EleType>::InnerInsertR(BINODE<EleType> *pRoot,EleType Parent,EleType Child)
{
	//����Ϊ�գ�ֱ�ӷ���1
	if(!pRoot)
		return 1;


	//1.�������ڵ��Ǵ�����ڵ��˫��
	if(pRoot->Data==Parent)
	{
		BINODE<EleType> *newNode;
		newNode=new BINODE<EleType>;
		if(newNode)
		{
			newNode->Data=Child;
			newNode->pLeft=NULL;
			newNode->pRight=pRoot->pRight;
			newNode->x=pRoot->x + pRoot->width/4;
			newNode->y=pRoot->y + 80;
			newNode->width=pRoot->width/2;
			pRoot->pRight=newNode;
			
			m_NodeCount++;
			return 2;
		}
		else
			return 0;
	}
	//2.�������ڵ㲻�Ǵ�����ڵ��˫��
	else
	{
		//������������ִ�в������
		int nRetCode=InnerInsertR(pRoot->pLeft,Parent,Child);
		//�����������ҵ�˫�ף����۲����Ƿ�ɹ�������
		if(nRetCode!=1)
			return nRetCode;
		//û�����������ҵ�˫�ף�����������ִ�в������
		else
		{
			nRetCode=InnerInsertR(pRoot->pRight,Parent,Child);
			return nRetCode;
		}
	}
}


/*
	���ܣ�
		ɾ��������
	������
		NodeValue	[in]	����������ֵ
	����ֵ��
		0	û�ҵ��ý�㣬����ʧ��
		1	�����ɹ�
	˵����
		���ҵ��ý�㣬��ɾ����������
*/
template <class EleType>
int CBinTreeLink<EleType>::DeleteL(EleType NodeValue)
{
	//1.��Rootֵ���ڵĽڵ�
	BINODE<EleType> *pResult=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,NodeValue,pResult);

	if(m_Found==0)
		return 0;

	//ɾ��������
	InnerDelete(pResult->pLeft);
	//pResultָ���������㣬����������Ϊ��
	pResult->pLeft=NULL;
	return 1;
}


/*
	���ܣ�
		ɾ��������
	������
		NodeValue	[in]	����������ֵ
	����ֵ��
		0	û�ҵ��ý�㣬����ʧ��
		1	�����ɹ�
	˵����
		���ҵ��ý�㣬��ɾ����������
*/
template <class EleType>
int CBinTreeLink<EleType>::DeleteR(EleType NodeValue)
{
	//1.��Rootֵ���ڵĽڵ�
	BINODE<EleType> *pResult=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,NodeValue,pResult);

	if(m_Found==0)
		return 0;

	//ɾ��������
	InnerDelete(pResult->pRight);
	//pResultָ���������㣬����������Ϊ��
	pResult->pRight=NULL;
	return 1;
}

/*
	���ܣ�
		ɾ������
	������
		pRoot	[in]	���������ָ��
	����ֵ��
		��
	˵����
		�ݹ麯��
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerDelete(BINODE<EleType> *pRoot)
{
	//������ʱֱ�ӷ���
	if(pRoot==NULL)
		return;

	//��ɾ������������ɾ��������
	InnerDelete(pRoot->pLeft);
	InnerDelete(pRoot->pRight);

	//��ɾ���ý�㱾����������1
	delete pRoot;
	m_NodeCount--;
}

/*
	���ܣ�
		����������Ϣ���浽�ļ�������ļ��ж�ȡ��������Ϣ������������
	������
		FileName		[in]	�ļ����ƣ������Ƹ�ʽ
		IsSaveToFile	[in]	�ļ�������0��1��ʾ���ļ���д�ļ�
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		��
*/
template <class EleType>
int CBinTreeLink<EleType>::Serialize(const char* const FileName,int IsSaveToFile)
{
	//д�ļ�
	if(IsSaveToFile)
	{
		FILE *fp;

		fp=fopen(FileName,"wb");
		if(!fp)
			return 0;

		fwrite(&m_NodeCount,sizeof(m_NodeCount),1,fp);

		if(m_NodeCount==0)
		{
			fclose(fp);
			return 1;
		}

		CQueue<BINODE<EleType>*> *pNodePtr;
		CQueue<int> *pNodeSeqID;
		pNodePtr=new CSeqQueue<BINODE<EleType>*>(m_NodeCount);
		pNodeSeqID=new CSeqQueue<int>(m_NodeCount);

		if(!pNodePtr || !pNodeSeqID)
		{
			fclose(fp);
			return 0;
		}

		if(pNodePtr->InitOK()==0 || pNodeSeqID->InitOK()==0)
		{
			fclose(fp);
			return 0;
		}

		BINODE<EleType> *pNode,*pChild;
		int ParentSeqID,CurrSeqID,LSSeqID;
		EleType NodeData;

		pNode=m_Root;
		NodeData=pNode->Data;
		CurrSeqID=0;
		ParentSeqID=-1;
		LSSeqID=0;
		fwrite(&ParentSeqID,sizeof(ParentSeqID),1,fp);
		fwrite(&LSSeqID,sizeof(LSSeqID),1,fp);
		fwrite(&NodeData,sizeof(NodeData),1,fp);
		pNodePtr->EnQueue(pNode);
		pNodeSeqID->EnQueue(CurrSeqID);
		while(pNodePtr->Length()>0)
		{
			pNodePtr->DeQueue(pNode);
			pNodeSeqID->DeQueue(ParentSeqID);

			pChild=pNode->pLeft;
			if(pChild)
			{
				LSSeqID=0;
				CurrSeqID++;
				NodeData=pChild->Data;
				fwrite(&ParentSeqID,sizeof(ParentSeqID),1,fp);
				fwrite(&LSSeqID,sizeof(LSSeqID),1,fp);
				fwrite(&NodeData,sizeof(NodeData),1,fp);
				pNodePtr->EnQueue(pChild);
				pNodeSeqID->EnQueue(CurrSeqID);
			}

			pChild=pNode->pRight;
			if(pChild)
			{
				LSSeqID=1;
				CurrSeqID++;
				NodeData=pChild->Data;
				fwrite(&ParentSeqID,sizeof(ParentSeqID),1,fp);
				fwrite(&LSSeqID,sizeof(LSSeqID),1,fp);
				fwrite(&NodeData,sizeof(NodeData),1,fp);
				pNodePtr->EnQueue(pChild);
				pNodeSeqID->EnQueue(CurrSeqID);
			}
		}
		delete pNodePtr;
		delete pNodeSeqID;
		fclose(fp);
		return 1;
	}
	//���ļ�
	else
	{

		FILE *fp;
		int NodeCount;

		InnerDelete(m_Root);
		m_Root=NULL;

		fp=fopen(FileName,"rb");
		if(!fp)
			return 0;
		
		fread(&NodeCount,sizeof(NodeCount),1,fp);

		if(NodeCount==0)
		{
			fclose(fp);
			return 1;
		}

		BINODE<EleType> **pNodePtr;
		pNodePtr=new BINODE<EleType>*[NodeCount];

		if(!pNodePtr)
		{
			fclose(fp);
			return 0;
		}

		int ParentSeqID,LSSeqID;
		EleType NodeData;

		fread(&ParentSeqID,sizeof(ParentSeqID),1,fp);
		fread(&LSSeqID,sizeof(LSSeqID),1,fp);
		fread(&NodeData,sizeof(NodeData),1,fp);

		BINODE<EleType> *pNode;
		pNode=new BINODE<EleType>;
		pNode->Data=NodeData;
		pNode->pLeft=NULL;
		pNode->pRight=NULL;
		pNodePtr[0]=pNode;
		m_Root=pNode;

		int Index;
		for(Index=1;Index<NodeCount;Index++)
		{
			fread(&ParentSeqID,sizeof(ParentSeqID),1,fp);
			fread(&LSSeqID,sizeof(LSSeqID),1,fp);
			fread(&NodeData,sizeof(NodeData),1,fp);

			pNode=new BINODE<EleType>;
			pNode->Data=NodeData;
			pNode->pLeft=NULL;
			pNode->pRight=NULL;
			pNodePtr[Index]=pNode;

			if(LSSeqID==0)
				(pNodePtr[ParentSeqID])->pLeft=pNode;
			else if(LSSeqID==1)
				(pNodePtr[LSSeqID])->pRight=pNode;
		}
		m_NodeCount=NodeCount;

		delete[] pNodePtr;
		fclose(fp);
		return 1;
	}
}

#endif