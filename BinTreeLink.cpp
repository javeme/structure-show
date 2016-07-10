/*
	二叉树的二叉链表表示法。
*/
#include <stdio.h>
#include "Queue.cpp"
#include "SeqQueue.cpp"
#include "BinTree.cpp"
#include "Stack.cpp"
#include "SeqStack.cpp"

#if !defined(_CPP_CBINTREELINK)

#define _CPP_CBINTREELINK

//二叉树节点定义
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

	//作业：求子二叉树深度，11.18交
	virtual int InsertL(EleType Parent,EleType Child);
	virtual int DeleteL(EleType);
	virtual int InsertR(EleType Parent,EleType Child);
	virtual int DeleteR(EleType);

	virtual void PreOrder() const;
	virtual void PostOrder() const;
	virtual void LevelOrder() const;
	virtual void InOrder() const;

	//前序遍历的非递归接口
	virtual void PreOrder2() const;

	virtual int Root(EleType&,int&,int&);
	virtual int Parent(EleType Child,EleType& Parent);
	virtual int Search(EleType Value);
	virtual int Depth() const;

	//添加方法
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


	//寻找结点时的标识
	int m_Found;
	//二叉树根节点指针
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
	求二叉树根结点的值。
	参数：
		二叉树根结点数据类型的变量
	返回值：
		二叉树根结点的数据值

	返回值：
		0	二叉树为空，引用返回的Root值无意义
		1	二叉树不空，引用返回的Root值为二叉树根结点的值

	注意函数返回值与通过引用返回值的区别。
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
	指定结点的值，求其双亲结点的值。
	参数：
		Child	
	返回值：
		无
	该函数为接口函数。

  pParent=NULL;
	pChild=m_Root;

	按子二叉树查找。
	从子二叉树的二叉树根开始查找。
	1)如果子二叉树二叉树根pChild->Data=Child，找到孩子节点，返回其双亲节点值pParent->Data(pParent不空)
	2)否则，依次查找pChild所有子二叉树，按上述方法（pParent=pChild,pChild=pChild->pLeft)
	3)如果pChild为空，返回，查找其兄弟节点(pChild=pChild->pNextSibiling)
	4)设置一个标志，成员变量m_Found，找到令其为1，初始值=0

*/
template <class EleType>
int CBinTreeLink<EleType>::Parent(EleType Child,EleType& Parent)
{
	m_Found=0;
	InnerFindParent(m_Root,NULL,Child,Parent);

	return m_Found;
}

/*
	功能：
		寻找双亲节点的值
	参数：
		pRoot	[in]	子树根节点指针
		pParent	[in]	子树根节点的双亲节点指针
		Child	[in]	待查找孩子节点值
		Parent	[out]	该孩子节点的双亲节点值，可能无意义
	返回值：
		无
	说明：
		执行过程中可能修改m_Found值。
		m_Found值含义：
		0	未找到值对应的节点
		1	找到值对应的节点，其双亲节点值通过Parent返回
		2	找到值对应的节点，但其无双亲节点（根节点）
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerFindParent(
							BINODE<EleType> *pRoot,
							BINODE<EleType> *pParent,
							EleType Child,
							EleType& Parent)
{

	//子树空时直接返回
	if(pRoot==NULL)
		return;

	//子树根节点值为待查值，查找结束，返回		
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
	//子树根节点值不是待查值，在子树中递归查找		
	else
	{
		//先在左子树中查找
		InnerFindParent(pRoot->pLeft,pRoot,Child,Parent);

		//在左子树中没找到，在右子树中查找
		if(m_Found==0)
			InnerFindParent(pRoot->pRight,pRoot,Child,Parent);
	}
}

/*
	功能：
		查找值对应的节点指针
	参数：
		pParent	[in]	子树根节点双亲的指针
		pRoot	[in]	子树根节点指针
		Value	[in]	待查找节点值
		pNode	[out]	指向该节点的指针
	返回值：
		无
	说明：
		内部函数。
		按前序遍历方式查找
*/
template <class EleType>
int CBinTreeLink<EleType>::Search(EleType Value)
{
	BINODE<EleType> *pNode=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,Value,pNode);
	return m_Found;

}
/*************************************************************设置坐标************************************************************/
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
}////////////////////////////////////////////获取节点位置
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
//获得孩子
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
	功能：
		查找值对应的节点指针
	参数：
		pParent	[in]	子树根节点双亲的指针
		pRoot	[in]	子树根节点指针
		Value	[in]	待查找节点值
		pNode	[out]	指向该节点的指针
	返回值：
		无
	说明：
		内部函数。
		按前序遍历方式查找
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerFindNode(
							BINODE<EleType> *pParent,
							BINODE<EleType> *pRoot,
							EleType Value,
							BINODE<EleType>* &pNode
							)
{
	//子树空时直接返回
	if(pRoot==NULL)
	{
		pNode=NULL;
		return;
	}

	//子树根节点值为待查值，查找结束，返回		
	if(pRoot->Data==Value)
	{
		pNode=pRoot;
		m_Found=1;
	}
	//递归查找其子树
	else
	{
		InnerFindNode(pRoot,pRoot->pLeft,Value,pNode);
		if(m_Found==0)
			InnerFindNode(pRoot,pRoot->pRight,Value,pNode);
	}
}

/*
	功能：
		求整个二叉树深度
	参数：
		无
	返回值：
		整型值，二叉树深度
	说明：
		该函数为接口函数，通过调用内部函数实现。
*/
template <class EleType>
int CBinTreeLink<EleType>::Depth() const
{
	return InnerDepth(m_Root);
}

/*
	功能：
		求子树深度
	参数：
		pRoot	[in]	子树根结点指针
	返回值：
		整型，该子树的深度
	说明：
		规定：树根所在深度为1。
		内部函数，递归，供Depth调用
*/
template <class EleType>
int CBinTreeLink<EleType>::InnerDepth(BINODE<EleType> *pRoot) const
{
	//子树为空，直接返回0
	if(pRoot==NULL)
		return 0;

	int nDepthLeft,nDepthRight;

	//求左子树和右子树深度
	nDepthLeft=InnerDepth(pRoot->pLeft);
	nDepthRight=InnerDepth(pRoot->pRight);

	if(nDepthLeft>nDepthRight)
		return nDepthLeft+1;
	else
		return nDepthRight+1;
}

/*
	功能：
		先序遍历二叉树
	参数：
		无
	返回值：
		无
	说明：
		该函数为接口函数，通过调用内部函数实现
*/
template <class EleType>
void CBinTreeLink<EleType>::PreOrder() const
{
	InnerPreOrder(m_Root);
}

/*
	功能：
		先序遍历二叉树的递归实现
	参数：
		pRoot	[in]	子树根结点指针		
	返回值：
		无
	说明：
		内部函数，递归，供PreOrder调用
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerPreOrder(BINODE<EleType> *pRoot) const
{
	//子树为空，直接返回
	if(!pRoot)
		return;

	//1.访问根
	cout<<pRoot->Data<<endl;

	//2.访问两个子树，先左后右
	InnerPreOrder(pRoot->pLeft);
	InnerPreOrder(pRoot->pRight);
}

/*
//教材代码
template <class EleType>
void CBinTreeLink<EleType>::PreOrder2() const
{
	//工作指针
	BINODE<EleType> *pRoot;
	//定义栈
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

//教材代码的改进
template <class EleType>
void CBinTreeLink<EleType>::PreOrder2() const
{
	//工作指针
	BINODE<EleType> *pRoot;
	//定义栈
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
	功能：
		后序遍历二叉树
	参数：
		无
	返回值：
		无
	说明：
		该函数为接口函数，通过调用内部函数实现
*/
template <class EleType>
void CBinTreeLink<EleType>::PostOrder() const
{
	InnerPostOrder(m_Root);
}

/*
	功能：
		后序遍历二叉树的递归实现
	参数：
		pRoot	[in]	子树根结点指针		
	返回值：
		无
	说明：
		内部函数，递归，供PostOrder调用
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerPostOrder(BINODE<EleType> *pRoot) const
{
	//子树为空，直接返回
	if(!pRoot)
		return;

	//1.访问两个子树，先左后右
	InnerPostOrder(pRoot->pLeft);
	InnerPostOrder(pRoot->pRight);

	//2.访问根
	cout<<pRoot->Data<<endl;
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
template <class EleType>
void CBinTreeLink<EleType>::InOrder() const
{
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
template <class EleType>
void CBinTreeLink<EleType>::InnerInOrder(BINODE<EleType> *pRoot) const
{
	//子树为空，直接返回
	if(!pRoot)
		return;

	//1.访问左子树
	InnerInOrder(pRoot->pLeft);

	//2.访问根
	cout<<pRoot->Data<<endl;

	//3.访问右子树
	InnerInOrder(pRoot->pRight);
}

/*
	功能：
		层序遍历二叉树
	参数：
		无
	返回值：
		无
	说明：
		该函数为接口函数，非递归实现
	思路：
		1)首先访问根节点
		2)访问完根节点后，将其指针入队
		3)当队列不空时：
			3.1)出队，该指针所指节点已经访问过，
			3.2)若左孩子不空，访问，将其指针入队
			3.3)若右孩子不空，访问，将其指针入队
*/
template <class EleType>
void CBinTreeLink<EleType>::LevelOrder() const
{
	//空树直接
	if(m_Root==NULL)
		return;

	//创建一个长度与树结点个数相同的循环队列，元素类型为树结点指针
	CQueue<BINODE<EleType>*> *pQueue;
	pQueue=new CSeqQueue<BINODE<EleType>*>(m_NodeCount);
	
	//队列创建不成功，退出
	if(!pQueue)
		return;

	//队列初始化失败，退出
	if(pQueue->InitOK()==0)
	{
		delete pQueue;
		return;
	}

	BINODE<EleType> *pNode,*pChild;

	//访问根节点
	pNode=m_Root;
	cout<<pNode->Data<<endl;

	//根结点指针入队
	pQueue->EnQueue(pNode);

	//当队列不空时
	while(pQueue->Length()>0)
	{
		//取出队头元素，其所指结点已经访问过
		pQueue->DeQueue(pNode);

		//先访问左孩子
		pChild=pNode->pLeft;
		if(pChild)
		{
			cout<<pChild->Data<<endl;
			pQueue->EnQueue(pChild);
		}
		//再访问右孩子
		pChild=pNode->pRight;
		if(pChild)
		{
			cout<<pChild->Data<<endl;
			pQueue->EnQueue(pChild);
		}
	}

	//操作结束，删除队列
	delete pQueue;
}

/*
	功能：
		插入左孩子
	参数：
		Parent	[in]	双亲结点值
		Child	[in]	待插入右孩子结点值
	返回值：
		0	找到双亲结点，但内存不足，不能创建新结点
		1	未找到双亲结点
		2	找到双亲结点，插入成功
		3	在单值树中，值为Child的结点已经存在
	说明：
		若树为空，则直接用Child值创建根结点，忽略Parent值
		若树不空，调用内部函数InnerInsertR执行插入操作
*/
template <class EleType>
int CBinTreeLink<EleType>::InsertL(EleType Parent,EleType Child)
{
	//先检查待插入值是否已经存在。适用于值不重复的树
	BINODE<EleType> *pNode=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,Child,pNode);
	if(pNode!=NULL)
		return 3;

	//树空时插入节点为根节点，此时忽略其双亲结点值
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
	//树不空时，调用其内部函数递归执行
	else
		return InnerInsertL(m_Root,Parent,Child);
}

/*
	功能：
		插入左孩子
	参数：
		pRoot	[in]	子树根结点指针
		Parent	[in]	双亲结点值
		Child	[in]	待插入左孩子结点值
	返回值：
		0	找到双亲结点，但内存不足，不能创建新结点
		1	未找到双亲结点
		2	找到双亲结点，插入成功
	说明：
		内部函数，递归调用
*/
template <class EleType>
int CBinTreeLink<EleType>::InnerInsertL(BINODE<EleType> *pRoot,EleType Parent,EleType Child)
{
	//子树为空，直接返回1
	if(!pRoot)
		return 1;


	//1.子树根节点是待插入节点的双亲
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
	//2.子树根节点不是待插入节点的双亲
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
	功能：
		插入右孩子
	参数：
		Parent	[in]	双亲结点值
		Child	[in]	待插入右孩子结点值
	返回值：
		0	找到双亲结点，但内存不足，不能创建新结点
		1	未找到双亲结点
		2	找到双亲结点，插入成功
		3	在单值树中，值为Child的结点已经存在
	说明：
		若树为空，则直接用Child值创建根结点，忽略Parent值
		若树不空，调用内部函数InnerInsertR执行插入操作
*/
template <class EleType>
int CBinTreeLink<EleType>::InsertR(EleType Parent,EleType Child)
{
	//先检查待插入值是否已经存在。适用于值不重复的树
	BINODE<EleType> *pNode=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,Child,pNode);
	if(pNode!=NULL)
		return 3;

	//树空时插入节点为根节点，此时忽略其双亲结点值
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
	//树不空时，调用内部函数递归执行
	else
		return InnerInsertR(m_Root,Parent,Child);
}

/*
	功能：
		插入右孩子
	参数：
		pRoot	[in]	子树根结点指针
		Parent	[in]	双亲结点值
		Child	[in]	待插入右孩子结点值
	返回值：
		0	找到双亲结点，但内存不足，不能创建新结点
		1	未找到双亲结点
		2	找到双亲结点，插入成功
	说明：
		内部函数，递归调用
*/
template <class EleType>
int CBinTreeLink<EleType>::InnerInsertR(BINODE<EleType> *pRoot,EleType Parent,EleType Child)
{
	//子树为空，直接返回1
	if(!pRoot)
		return 1;


	//1.子树根节点是待插入节点的双亲
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
	//2.子树根节点不是待插入节点的双亲
	else
	{
		//先在左子树中执行插入操作
		int nRetCode=InnerInsertR(pRoot->pLeft,Parent,Child);
		//在左子树中找到双亲，无论插入是否成功都返回
		if(nRetCode!=1)
			return nRetCode;
		//没在左子树中找到双亲，在右子树中执行插入操作
		else
		{
			nRetCode=InnerInsertR(pRoot->pRight,Parent,Child);
			return nRetCode;
		}
	}
}


/*
	功能：
		删除左子树
	参数：
		NodeValue	[in]	待操作结点的值
	返回值：
		0	没找到该结点，操作失败
		1	操作成功
	说明：
		若找到该结点，则删除其左子树
*/
template <class EleType>
int CBinTreeLink<EleType>::DeleteL(EleType NodeValue)
{
	//1.找Root值所在的节点
	BINODE<EleType> *pResult=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,NodeValue,pResult);

	if(m_Found==0)
		return 0;

	//删除左子树
	InnerDelete(pResult->pLeft);
	//pResult指向待操作结点，令其左子树为空
	pResult->pLeft=NULL;
	return 1;
}


/*
	功能：
		删除右子树
	参数：
		NodeValue	[in]	待操作结点的值
	返回值：
		0	没找到该结点，操作失败
		1	操作成功
	说明：
		若找到该结点，则删除其右子树
*/
template <class EleType>
int CBinTreeLink<EleType>::DeleteR(EleType NodeValue)
{
	//1.找Root值所在的节点
	BINODE<EleType> *pResult=NULL;

	m_Found=0;
	InnerFindNode(NULL,m_Root,NodeValue,pResult);

	if(m_Found==0)
		return 0;

	//删除右子树
	InnerDelete(pResult->pRight);
	//pResult指向待操作结点，令其右子树为空
	pResult->pRight=NULL;
	return 1;
}

/*
	功能：
		删除子树
	参数：
		pRoot	[in]	子树根结点指针
	返回值：
		无
	说明：
		递归函数
*/
template <class EleType>
void CBinTreeLink<EleType>::InnerDelete(BINODE<EleType> *pRoot)
{
	//子树空时直接返回
	if(pRoot==NULL)
		return;

	//先删除左子树，再删除右子树
	InnerDelete(pRoot->pLeft);
	InnerDelete(pRoot->pRight);

	//再删除该结点本身，结点计数减1
	delete pRoot;
	m_NodeCount--;
}

/*
	功能：
		将二叉树信息保存到文件，或从文件中读取二叉树信息并创建二叉树
	参数：
		FileName		[in]	文件名称，二进制格式
		IsSaveToFile	[in]	文件操作，0、1表示读文件和写文件
	返回值：
		0	操作失败
		1	操作成功
	说明：
		无
*/
template <class EleType>
int CBinTreeLink<EleType>::Serialize(const char* const FileName,int IsSaveToFile)
{
	//写文件
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
	//读文件
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