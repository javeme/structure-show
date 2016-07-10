/*
	���ĺ����ֵܽ���ʾ����
	�����ڸ����У�ÿ������ֵ����Ωһ�ġ�
*/
#include <stdio.h>
#include <iostream>
#include "Tree.cpp"
#include "Queue.cpp"
#include "SeqQueue.cpp"

#if !defined(_CPP_CTREECHILDSIB)
#define _CPP_CTREECHILDSIB

//���ڵ㶨��
template <class EleType>
struct TREENODE_CS  
{
	EleType Data;
	int childrenCount;//������
	int width;//������ӵ�е�������
	int x;//������
	int y;//������
	TREENODE_CS<EleType> *pFirstChild,*pNextSib;
};

template <class EleType>
class CTreeChildSib : public CTree<EleType>
{
public:
	CTreeChildSib();
	virtual ~CTreeChildSib();

	virtual int Serialize(char *FileName,int IsSaveToFile);

	virtual int Root(EleType&,int&,int&);
	virtual int Parent(EleType Child,EleType& Parent);
	//��ҵ����������ȣ�11.18��
	virtual int Depth();
	virtual void PreOrder();
	virtual void PostOrder();
	virtual void LevelOrder();
	virtual int Insert(EleType Parent,EleType Child);
	virtual void Delete(EleType);
	//�¼ӷ���
	virtual int GetFirstChildOf(EleType,EleType&,int &x,int &y);
	virtual int GetNextSibOf(EleType,EleType&,int &x,int &y);
	virtual int GetLevelOf(EleType);
	//virtual int SetPosition(EleType selfValue,int x,int y);
	virtual int SetPositionOf(EleType selfValue,int x,int y,int width);
	virtual int GetPositionOf(EleType selfValue,int &x,int &y);
	//virtual int SetTreeWidth(EleType selfValue,int width);
protected:
	void SetChildPositionOf(TREENODE_CS<EleType> *pRoot);
public:

	void FindParent(TREENODE_CS<EleType> *pRoot,TREENODE_CS<EleType> *pParent,EleType Child,EleType& Parent);
	int InnerInsert(TREENODE_CS<EleType> *pRoot,EleType Parent,EleType Child);
	void InnerPreOrder(TREENODE_CS<EleType> *pRoot);
	void InnerPostOrder(TREENODE_CS<EleType> *pRoot);
	int InnerDepth(TREENODE_CS<EleType> *pRoot);

	void FindNode(TREENODE_CS<EleType> *pParent,
							TREENODE_CS<EleType> *pRoot,
							EleType Value,
							TREENODE_CS<EleType>* &pNode,
							TREENODE_CS<EleType>* &pRetParent);
	void InnerDelete(TREENODE_CS<EleType>* pRoot);

	//Ѱ�ҽ��ʱ�ı�ʶ
	int m_Found;
	//�����ڵ�ָ��
	TREENODE_CS<EleType> *m_Root;

};

template <class EleType>
CTreeChildSib<EleType>::CTreeChildSib()
{
	m_Root=NULL;
}

template <class EleType>
CTreeChildSib<EleType>::~CTreeChildSib()
{
	InnerDelete(m_Root);
}

/*
	����������ֵ��
	������
		��������������͵ı���
	����ֵ��
		������������ֵ

	����ֵ��
		0	��Ϊ�գ����÷��ص�Rootֵ������
		1	�����գ����÷��ص�RootֵΪ��������ֵ

	ע�⺯������ֵ��ͨ�����÷���ֵ������
*/
template <class EleType>
int CTreeChildSib<EleType>::Root(EleType& Root,int& x,int& y)
{
	if(m_Root==NULL)
	{
		//Root=NULL;//CString ʱ���벻��??
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
	ָ������ֵ������˫�½���ֵ����
	������
		Child	
	����ֵ��
		��
	�ú���Ϊ�ӿں�����

  pParent=NULL;
	pChild=m_Root;

	���������ҡ�
	��������������ʼ���ҡ�
	1)�����������pChild->Data=Child���ҵ����ӽڵ㣬������˫�׽ڵ�ֵpParent->Data(pParent����)
	2)�������β���pChild����������������������pParent=pChild,pChild=pChild->pFirstChild)
	3)���pChildΪ�գ����أ��������ֵܽڵ�(pChild=pChild->pNextSibiling)
	4)����һ����־����Ա����m_Found���ҵ�����Ϊ1����ʼֵ=0

*/
template <class EleType>
int CTreeChildSib<EleType>::Parent(EleType Child,EleType& Parent)
{
	m_Found=0;
	FindParent(m_Root,NULL,Child,Parent);

	return m_Found;
}

/*
	��ڲ�����
	pRoot		�������ڵ��ָ��
	pParent		���������ڵ��˫�׽ڵ�ָ��
	Child		�����Һ��ӽڵ�ֵ
	Parent		�ú��ӽڵ��˫�׽ڵ�ֵ������������
*/
template <class EleType>
void CTreeChildSib<EleType>::FindParent(
							TREENODE_CS<EleType> *pRoot,
							TREENODE_CS<EleType> *pParent,
							EleType Child,
							EleType& Parent)
{
	//��������ʱ��������ֱ�ӷ���
	if(pRoot!=NULL)
	{
		//���������ڵ�ֵΪ����ֵ�����ҽ���������		
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
		//���������ڵ�ֵ���Ǵ���ֵ���ݹ����		
		else
		{
			TREENODE_CS<EleType> *p;

			p=pRoot->pFirstChild;
			while(p && m_Found==0)
			{
				FindParent(p,pRoot,Child,Parent);
				if(m_Found==0)
				{
					p=p->pNextSib;
				}
			}
		}
	}

}
/*****************************************************************���ӷ���**********************************************/
//�õ����ڲ�
template <class EleType>
int CTreeChildSib<EleType>::GetLevelOf(EleType value)
{	
	EleType parentValue,childValue=value;
	int level=0;
	while(Parent(childValue,parentValue)==1)
	{
		level++;
		childValue=parentValue;
	}
	return level;
}
//�õ���һ������
template <class EleType>
int CTreeChildSib<EleType>::GetFirstChildOf(EleType selfValue,EleType& childValue,int &x,int &y)
{
	TREENODE_CS<EleType> *pToFindNode, *pRetParent;
	m_Found=0;
	FindNode(NULL,m_Root,selfValue,pToFindNode,pRetParent);
	
	if(m_Found && pToFindNode->pFirstChild)
	{
		childValue=pToFindNode->pFirstChild->Data;
		x=pToFindNode->pFirstChild->x;
		y=pToFindNode->pFirstChild->y;
		return 1;
	}
	else
		return 0;	
}
//�õ���һ���ֵ�
template <class EleType>
int CTreeChildSib<EleType>::GetNextSibOf(EleType selfValue,EleType& nextSibValue,int &x,int &y)
{	
	TREENODE_CS<EleType> *pToFindNode, *pRetParent;
	m_Found=0;
	FindNode(NULL,m_Root,selfValue,pToFindNode,pRetParent);

	if(m_Found && pToFindNode->pNextSib)
	{
		nextSibValue=pToFindNode->pNextSib->Data;
		x=pToFindNode->pNextSib->x;
		y=pToFindNode->pNextSib->y;
		return 1;
	}
	else
		return 0;
}
//��������,�ⲿ�ӿ�
template <class EleType>
int CTreeChildSib<EleType>::SetPositionOf(EleType selfValue,int x,int y,int width)
{
	TREENODE_CS<EleType> *pToFindNode, *pRetParent;
	m_Found=0;
	FindNode(NULL,m_Root,selfValue,pToFindNode,pRetParent);
	if(m_Found)
	{
		pToFindNode->x=x;
		pToFindNode->y=y;
		pToFindNode->width=width;
	}
	return m_Found;
}
//�õ�����
template <class EleType>
int CTreeChildSib<EleType>::GetPositionOf(EleType selfValue,int &x,int &y)
{
	TREENODE_CS<EleType> *pToFindNode, *pRetParent;
	m_Found=0;
	FindNode(NULL,m_Root,selfValue,pToFindNode,pRetParent);
	if(m_Found)
	{
		x=pToFindNode->x;
		y=pToFindNode->y;
	}
	return m_Found;
}
//������ӵ�еĿ��,�ⲿ�ӿ�
/*
template <class EleType>
int CTreeChildSib<EleType>::SetTreeWidth(EleType selfValue,int width)
{
	if(width<0)
		return 0;
	TREENODE_CS<EleType> *pToFindNode, *pRetParent;
	m_Found=0;
	FindNode(NULL,m_Root,selfValue,pToFindNode,pRetParent);
	if(m_Found)
	{
		pToFindNode->width=width;
	}
	return m_Found;
}*/
/*****************************************************************���ӷ���**********************************************/
/*
	����ֵ��Ӧ�Ľڵ�ָ�롣
	������
		pRoot		ָ���������ڵ�ָ��
		Value			�����ҽڵ�ֵ
		pNode		ָ��ýڵ��ָ��
	����ֵ��
		��
	˵������ǰ�������ʽ����
*/
template <class EleType>
void CTreeChildSib<EleType>::FindNode(
							TREENODE_CS<EleType> *pParent,
							TREENODE_CS<EleType> *pRoot,
							EleType Value,
							TREENODE_CS<EleType>* &pNode,
							TREENODE_CS<EleType>* &pRetParent
							)
{
	pNode=NULL;
	//��������ʱ��������ֱ�ӷ���
	if(pRoot!=NULL)
	{
		//���������ڵ�ֵΪ����ֵ�����ҽ���������		
		if(pRoot->Data==Value)
		{
			pRetParent=pParent;
			pNode=pRoot;
			m_Found=1;
		}
		//���������ڵ�ֵ���Ǵ���ֵ���ݹ����		
		else
		{
			TREENODE_CS<EleType> *p;

			p=pRoot->pFirstChild;
			while(p && m_Found==0)
			{
				FindNode(pRoot,p,Value,pNode,pRetParent);
				if(m_Found==0)
				{
					p=p->pNextSib;
				}
			}
		}
	}

}

/*
	������ȡ�
	������
		��
	����ֵ��
		��
	�ú���Ϊ�ӿں�����
*/
template <class EleType>
int CTreeChildSib<EleType>::Depth()
{
	if(m_Root==NULL)
		return 0;
	else
		return InnerDepth(m_Root);
}

/*
	��������ȡ�
	������
		pRoot	ָ������������ָ��
	����ֵ��
		��
	�ڲ��������ݹ飬��Depth���á�
*/
template <class EleType>
int CTreeChildSib<EleType>::InnerDepth(TREENODE_CS<EleType> *pRoot)
{
	if(pRoot==NULL)
		return 0;
	else
	{
		int nMaxDepth=0,nDepth=-1;

		TREENODE_CS<EleType> *pSubRoot;
		pSubRoot=pRoot->pFirstChild;
		while(pSubRoot)
		{
			nDepth=InnerDepth(pSubRoot);
			if(nDepth>nMaxDepth)
				nMaxDepth=nDepth;

			pSubRoot=pSubRoot->pNextSib;
		}

		return nMaxDepth+1;
	}
}

/*
	�����������
	������
		�ޣ���ʾ������������
	����ֵ��
		��
	�ú���Ϊ�ӿں�����
*/
template <class EleType>
void CTreeChildSib<EleType>::PreOrder()
{
	InnerPreOrder(m_Root);
}

/*
	�����������
	������
		pRoot	ָ��ĳ������������ָ��
	����ֵ��
		��
	�ڲ��������ݹ飬��PreOrder���á�
*/
template <class EleType>
void CTreeChildSib<EleType>::InnerPreOrder(TREENODE_CS<EleType> *pRoot)
{
	TREENODE_CS<EleType> *p;
	if(pRoot)
	{
		//1.���ʸ�
		cout<<pRoot->Data<<endl;

		//2.�������ҷ�������
		p=pRoot->pFirstChild;
		while(p)
		{
			InnerPreOrder(p);
			p=p->pNextSib;
		}
	}

}

/*
	�����������
	������
		�ޣ���ʾ������������
	����ֵ��
		��
	�ú���Ϊ�ӿں�����
*/
template <class EleType>
void CTreeChildSib<EleType>::PostOrder()
{
	InnerPostOrder(m_Root);
}

/*
	�����������
	������
		pRoot	ָ��ĳ������������ָ��
	����ֵ��
		��
	�ڲ��������ݹ飬��PostOrder���á�
*/
template <class EleType>
void CTreeChildSib<EleType>::InnerPostOrder(TREENODE_CS<EleType> *pRoot)
{
	TREENODE_CS<EleType> *p;
	if(pRoot)
	{
		//1.�������ҷ�������
		p=pRoot->pFirstChild;
		while(p)
		{
			InnerPostOrder(p);
			p=p->pNextSib;
		}

		//2.���ʸ�
		cout<<pRoot->Data<<endl;

	}

}

/*
	�����������
	������
		�ޣ���ʾ������������
	����ֵ��
		��
	˼·��
	1)���ȷ��ʸ��ڵ�
	2)��������ڵ�󣬽���ָ�����
	3)�����в���ʱ��
		3.1)���ӣ���ָ����ָ�ڵ��Ѿ����ʹ���
		3.2)�������ҷ����亢�ӽڵ㣬
		3.3)ÿ�����ӽڵ������ɺ���ָ�����
*/
template <class EleType>
void CTreeChildSib<EleType>::LevelOrder()
{
	//����ʱ�˳��������б�������
	if(!m_Root)
		return;

	//����һ������������������ͬ��ѭ�����У����е�Ԫ������Ϊָ��������ָ��
	CQueue<TREENODE_CS<EleType>*> *pQueue;
	pQueue=new CSeqQueue<TREENODE_CS<EleType>*>(m_NodeCount);
	
	//���д������ɹ����˳�
	if(!pQueue)
		return;

	//���г�ʼ��ʧ�ܣ��˳�
	if(pQueue->InitOK()==0)
	{
		delete pQueue;
		return;
	}

	TREENODE_CS<EleType> *pNode,*pChild;
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

		//�������ҷ��������к��Ӳ����
		pChild=pNode->pFirstChild;
		while(pChild)
		{
			cout<<pChild->Data<<endl;

			pQueue->EnQueue(pChild);
			pChild=pChild->pNextSib;
		}
	}

	//����������ɾ������
	delete pQueue;
}

/*
	����ֵ��
	0-�ҵ�Parent,�ڴ治��
	1-û�ҵ�
	2-�ҵ�������ɹ�
*/
template <class EleType>
int CTreeChildSib<EleType>::Insert(EleType Parent,EleType Child)
{
	//���գ�����ڵ�Ϊ���ڵ㣬��ʱ������˫�׽��ֵ
	if(m_Root==NULL)
	{
		TREENODE_CS<EleType> *newNode;
		newNode=new TREENODE_CS<EleType>;
		if(newNode)
		{
			newNode->Data=Child;
			newNode->pFirstChild=NULL;
			newNode->pNextSib=NULL;
			//����Ϊ��ʼ��Ϊ0
			newNode->x=0;
			newNode->y=0;
			//������Ϊ0
			newNode->childrenCount=0;
			m_Root=newNode;

			m_NodeCount++;

			return 2;
		}
		else
			return 0;
	}
	//������ʱ���������ڲ������ݹ�ִ��
	else
		return InnerInsert(m_Root,Parent,Child);
}

/*
	����ֵ��
	0-�ҵ�Parent,�ڴ治��
	1-û�ҵ�
	2-�ҵ�������ɹ�
*/
template <class EleType>
int CTreeChildSib<EleType>::InnerInsert(TREENODE_CS<EleType> *pRoot,EleType Parent,EleType Child)
{
	TREENODE_CS<EleType> *newNode;
	TREENODE_CS<EleType> *p;

	if(pRoot)
	{
		//1.���������ڵ��Ǵ�����ڵ��˫��
		if(pRoot->Data==Parent)
		{
			newNode=new TREENODE_CS<EleType>;
			if(newNode)
			{
				newNode->Data=Child;			
				//����Ϊ��ʼ��							
				//newNode->x=0;
				//newNode->y=0;
				//������Ϊ0
				newNode->childrenCount=0;
				newNode->pFirstChild=NULL;
				newNode->pNextSib=NULL;
			}
			//�ڴ治��
			else
				return 0;
			
			//pָ�����������ڵ�ĵ�һ�����ӽڵ�
			p=pRoot->pFirstChild;

			//���������ڵ�û�к��ӽڵ㣬
			//ֱ����Ϊ���һ�����ӽڵ�
			if(p==NULL)
			{
				pRoot->pFirstChild=newNode;
				pRoot->childrenCount=1;
				SetChildPositionOf(pRoot);//������������
			}
			else
			{
				//��ֹ�ظ�
				if(p->Data==Child)
				{
					delete newNode;
					return -1;//��ʾ�ظ�
				}
				//�ҵ����������ڵ�����Һ��ӽڵ�
				while(p->pNextSib!=NULL)
				{
					p=p->pNextSib;
					//��ֹ�ظ�
					if(p->Data==Child)
					{
						delete newNode;
						return -1;//��ʾ�ظ�
					}
				}

				p->pNextSib=newNode;
				pRoot->childrenCount++;
				SetChildPositionOf(pRoot);//������������
			}

			m_NodeCount++;
			return 2;
		}
		//2.���������ڵ㲻�Ǵ�����ڵ��˫��
		else
		{
			p=pRoot->pFirstChild;
			while(p!=NULL)
			{				
				//�ҵ����Ҳ��룬ֱ�ӷ���
				if(InnerInsert(p,Parent,Child)==2)
					return 2;
				//δ�ҵ�����
				else if(InnerInsert(p,Parent,Child)==0)
					return 0;
				//������
				else
					p=p->pNextSib;
			}
			return -1;//
		}

	}
	return 1;
}
/***************************************************************������������**********************************************/
template <class EleType>
void CTreeChildSib<EleType>::SetChildPositionOf(TREENODE_CS<EleType> *pRoot)
{
	int count=pRoot->childrenCount;
	int parentX=pRoot->x;
	int parentY=pRoot->y;
	int width=pRoot->width;
	int elementWidth=width/count;
	TREENODE_CS<EleType> *p=pRoot->pFirstChild;
	p->x=(parentX-width/2)+elementWidth/2;
	p->y=parentY+100;
	p->width=elementWidth;
	int i=0;
	while((p=p->pNextSib))
	{
		i++;
		p->x=(parentX-width/2)+elementWidth*i + elementWidth/2;
		p->y=parentY+100;
		p->width=elementWidth;
	}
}
/***************************************************************������������**********************************************/
/*
	ɾ���������������ڵ��ֵΪָ��ֵ��
	������
		NodeValue		��ɾ���������ڵ��ֵ
	����ֵ��
		1	�����ɹ����ܷ��ظ�ֵ
*/
template <class EleType>
void CTreeChildSib<EleType>::Delete(EleType NodeValue)
{
	//1.��Rootֵ���ڵĽڵ�
	TREENODE_CS<EleType> *pResult=NULL,*pParent=NULL,*pRetParent;

	m_Found=0;
	FindNode(pParent,m_Root,NodeValue,pResult,pRetParent);
	
	//2.����ҵ��ýڵ㣬ɾ��֮��
	//ɾ��ǰ����Ҫ���������ֵܵĹ�ϵ
	if(pResult)
	{
		//����Ǹ��ڵ㣬���õ�����ϵ
		if(pRetParent==NULL)
			InnerDelete(pResult);
		else
		{
			
			//������ϵ
			//1)�Ǹ��ڵ�ĵ�һ������
			if(pRetParent->pFirstChild==pResult)
				pRetParent->pFirstChild=pResult->pNextSib;
			//2)���Ǹ��ڵ�ĵ�һ������
			else
			{
				TREENODE_CS<EleType> *pLeftSib;
				pLeftSib=pRetParent->pFirstChild;
				while(pLeftSib && pLeftSib->pNextSib!=pResult)
						pLeftSib=pLeftSib->pNextSib;
				
				pLeftSib->pNextSib=pResult->pNextSib;
			}
			

			//3)ɾ��
			InnerDelete(pResult);
		}
	}
}

template <class EleType>
void CTreeChildSib<EleType>::InnerDelete(TREENODE_CS<EleType> *pRoot)
{
	if(pRoot==NULL)
		return;

	//��pRootΪҶ��ʱֱ��ɾ������������һ
	if(pRoot->pFirstChild==NULL)
	{
		delete pRoot;
		m_NodeCount--;
	}
	//��pRootΪ��֧�ݹ�ɾ��
	else
	{
		TREENODE_CS<EleType> *pChild,*pChild2;
		//��ɾ��������
		pChild=pRoot->pFirstChild;
		while(pChild)
		{
			pChild2=pChild->pNextSib;
			InnerDelete(pChild);
			pChild=pChild2;
			//pChild=pChild->pNextSib;
		}
		//��ɾ������
		delete pRoot;
	}
}

/*
	������Ϣ���浽�ļ�������ļ��ж�ȡ����Ϣ����������δʵ�֡�
	������
		FileName		�ļ����ƣ������Ƹ�ʽ
		IsSaveToFile	�ļ�������0��1��ʾ���ļ���д�ļ�
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
*/
template <class EleType>
int CTreeChildSib<EleType>::Serialize(char *FileName,int IsSaveToFile)
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

		CQueue<TREENODE_CS<EleType>*> *pNodePtr;
		CQueue<int> *pNodeSeqID;
		pNodePtr=new CSeqQueue<TREENODE_CS<EleType>*>(m_NodeCount);
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

		TREENODE_CS<EleType> *pNode,*pChild;
		int ParentSeqID,CurrSeqID,LSSeqID;
		EleType NodeData;

		pNode=m_Root;
		NodeData=pNode->Data;
		CurrSeqID=0;
		ParentSeqID=-1;
		LSSeqID=-1;
		fwrite(&ParentSeqID,sizeof(ParentSeqID),1,fp);
		fwrite(&LSSeqID,sizeof(LSSeqID),1,fp);
		fwrite(&NodeData,sizeof(NodeData),1,fp);
		pNodePtr->EnQueue(pNode);
		pNodeSeqID->EnQueue(CurrSeqID);
		while(pNodePtr->Length()>0)
		{
			pNodePtr->DeQueue(pNode);
			pNodeSeqID->DeQueue(ParentSeqID);
			pChild=pNode->pFirstChild;
			LSSeqID=-1;
			while(pChild)
			{
				CurrSeqID++;
				NodeData=pChild->Data;
				fwrite(&ParentSeqID,sizeof(ParentSeqID),1,fp);
				fwrite(&LSSeqID,sizeof(LSSeqID),1,fp);
				fwrite(&NodeData,sizeof(NodeData),1,fp);

				LSSeqID=CurrSeqID;
				pNodePtr->EnQueue(pChild);
				pNodeSeqID->EnQueue(CurrSeqID);

				pChild=pChild->pNextSib;
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
		InnerDelete(m_Root);
		m_Root=NULL;

		FILE *fp;
		int NodeCount;

		fp=fopen(FileName,"rb");
		if(!fp)
			return 0;
		
		fread(&NodeCount,sizeof(NodeCount),1,fp);

		if(NodeCount==0)
		{
			fclose(fp);
			return 1;
		}

		TREENODE_CS<EleType> **pNodePtr;
		pNodePtr=new TREENODE_CS<EleType>*[NodeCount];

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
		TREENODE_CS<EleType> *pNode;
		pNode=new TREENODE_CS<EleType>;
		pNode->Data=NodeData;
		pNode->pFirstChild=NULL;
		pNode->pNextSib=NULL;
		pNodePtr[0]=pNode;
		m_Root=pNode;

		int Index;
		for(Index=1;Index<NodeCount;Index++)
		{
			fread(&ParentSeqID,sizeof(ParentSeqID),1,fp);
			fread(&LSSeqID,sizeof(LSSeqID),1,fp);
			fread(&NodeData,sizeof(NodeData),1,fp);
			pNode=new TREENODE_CS<EleType>;
			pNode->Data=NodeData;
			pNode->pFirstChild=NULL;
			pNode->pNextSib=NULL;
			pNodePtr[Index]=pNode;

			if(LSSeqID==-1)
				(pNodePtr[ParentSeqID])->pFirstChild=pNode;
			else
				(pNodePtr[LSSeqID])->pNextSib=pNode;

		}
		m_NodeCount=NodeCount;

		delete[] pNodePtr;
		fclose(fp);
		return 1;
		
	}
}

#endif