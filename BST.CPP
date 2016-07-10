/*
	二叉排序树的二叉链表实现。
*/
#include <iostream>
using namespace std;
#include "BST.h"
/*
	功能：
		默认构造函数
	参数：
		无
	返回值：
		无
	说明：
		设置一棵空树。
*/
CBST::CBST()
{
	this->m_Root=NULL;
}

/*
	功能：
		析构函数
	参数：
		无
	返回值：
		无
	说明：
		删除所有结点
*/
CBST::~CBST()
{
	;
}

/*
	功能：
		插入一个新结点
	参数：
		pNewNode	[in]	已经填充内容的新结点的指针
	返回值：
		0	操作失败
		1	操作成功
	说明：
		若树为空，则新结点即为树结点，否则将其插入到树中，仍然保持排序的特性。
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
	功能：
		插入一个新结点
	参数：
		pRoot		[in,out]	子树根结点。若传入不为空值，则该值不变，否则会变为pNewNode值
		pNewNode	[in]		已经填充内容的新结点的指针
	返回值：
		0	操作失败
		1	操作成功
	说明：
		InsertBST调用的内部函数，思想为递归式插入结点。
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
	功能：
		查找结点是否存在
	参数：
		Key		[in]		键值
		pNode	[in,out]	结点指针
	返回值：
		0	操作失败
		1	结点存在，pNode有意义
	说明：
		无
*/
bool CBST::Search(int Key,LPBSTNODE &pNode)
{
	m_Found=false;
	InnerSearch(m_Root,Key,pNode);
	return m_Found;
}

/*
	功能：
		查找结点是否存在
	参数：
		pRoot	[in]		子树根结点指针
		Key		[in]		键值
		pNode	[in,out]	结点指针
	返回值：
		无
	说明：
		Search调用的内部函数。若找到，置m_Found为true
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
	功能：
		中序遍历二叉树
	参数：
		无
	返回值：
		无
	说明：
		该函数为接口函数，通过调用内部函数实现
*/
void CBST::InOrder()
{
	m_Index=0;
	InnerInOrder(m_Root);
}

/*
	功能：
		中序遍历二叉树的递归实现
	参数：
		pRoot	[in]	子树根结点指针		
	返回值：
		无
	说明：
		内部函数，递归，供InOrder调用
*/
void CBST::InnerInOrder(LPBSTNODE pRoot)
{
	//子树为空，直接返回
	if(!pRoot)
		return;

	//1.访问左子树
	InnerInOrder(pRoot->LChild);

	//2.访问根
	m_Index++;
	cout<<" "<<m_Index<<" "<<pRoot->Key<<endl;

	//3.访问右子树
	InnerInOrder(pRoot->RChild);
}
