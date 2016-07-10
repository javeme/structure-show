/*
	�����������Ķ�������ʵ�֡�
*/
#include <iostream>
using namespace std;
#include "BST.h"
/*
	���ܣ�
		Ĭ�Ϲ��캯��
	������
		��
	����ֵ��
		��
	˵����
		����һ�ÿ�����
*/
CBST::CBST()
{
	this->m_Root=NULL;
}

/*
	���ܣ�
		��������
	������
		��
	����ֵ��
		��
	˵����
		ɾ�����н��
*/
CBST::~CBST()
{
	;
}

/*
	���ܣ�
		����һ���½��
	������
		pNewNode	[in]	�Ѿ�������ݵ��½���ָ��
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		����Ϊ�գ����½�㼴Ϊ����㣬��������뵽���У���Ȼ������������ԡ�
*/
int CBST::InsertBST(LPBSTNODE pNewNode)
{
	m_Found=false;
	LPBSTNODE pNode=NULL;
	InnerSearch(m_Root,pNewNode->Key,pNode);

	if(m_Found)
		return 0;
	else
	{
		InnerInsertBST(m_Root,pNewNode);
		return 1;
	}
}

/*
	���ܣ�
		����һ���½��
	������
		pRoot		[in,out]	��������㡣�����벻Ϊ��ֵ�����ֵ���䣬������ΪpNewNodeֵ
		pNewNode	[in]		�Ѿ�������ݵ��½���ָ��
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		InsertBST���õ��ڲ�������˼��Ϊ�ݹ�ʽ�����㡣
*/
void CBST::InnerInsertBST(LPBSTNODE &pRoot,LPBSTNODE pNewNode)
{
	LPBSTNODE pChild;

	if(!pRoot)
	{
		pRoot=pNewNode;
	}
	else if(pNewNode->Key>pRoot->Key)
	{
		pChild=pRoot->RChild;
		InnerInsertBST(pChild,pNewNode);
		pRoot->RChild=pChild;
	}
	else
	{
		pChild=pRoot->LChild;
		InnerInsertBST(pChild,pNewNode);
		pRoot->LChild=pChild;
	}
}

/*
	���ܣ�
		���ҽ���Ƿ����
	������
		Key		[in]		��ֵ
		pNode	[in,out]	���ָ��
	����ֵ��
		0	����ʧ��
		1	�����ڣ�pNode������
	˵����
		��
*/
bool CBST::Search(int Key,LPBSTNODE &pNode)
{
	m_Found=false;
	InnerSearch(m_Root,Key,pNode);
	return m_Found;
}

/*
	���ܣ�
		���ҽ���Ƿ����
	������
		pRoot	[in]		���������ָ��
		Key		[in]		��ֵ
		pNode	[in,out]	���ָ��
	����ֵ��
		��
	˵����
		Search���õ��ڲ����������ҵ�����m_FoundΪtrue
*/
void CBST::InnerSearch(LPBSTNODE pRoot,int Key,LPBSTNODE &pNode)
{
	if(pRoot==NULL)
		return;
	
	if(pRoot->Key==Key)
	{
		m_Found=true;
		pNode=pRoot;
		return;
	}

	if(Key>pRoot->Key)
		InnerSearch(pRoot->RChild,Key,pNode);
	else
		InnerSearch(pRoot->LChild,Key,pNode);
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
void CBST::InOrder()
{
	m_Index=0;
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
void CBST::InnerInOrder(LPBSTNODE pRoot)
{
	//����Ϊ�գ�ֱ�ӷ���
	if(!pRoot)
		return;

	//1.����������
	InnerInOrder(pRoot->LChild);

	//2.���ʸ�
	m_Index++;
	cout<<" "<<m_Index<<" "<<pRoot->Key<<endl;

	//3.����������
	InnerInOrder(pRoot->RChild);
}