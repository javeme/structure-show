/*
	树的孩子兄弟结点表示法。
	假设在该树中，每个结点的值都是惟一的。
*/
#include <stdio.h>
#include <iostream>
#include "Tree.cpp"
#include "Queue.cpp"
#include "SeqQueue.cpp"

#if !defined(_CPP_CTREECHILDSIB)
#define _CPP_CTREECHILDSIB

//树节点定义
template <class EleType>
struct TREENODE_CS  
{
	EleType Data;
	int childrenCount;//孩子数
	int width;//该子树拥有的区域宽度
	int x;//横坐标
	int y;//纵坐标
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
	//作业：求子树深度，11.18交
	virtual int Depth();
	virtual void PreOrder();
	virtual void PostOrder();
	virtual void LevelOrder();
	virtual int Insert(EleType Parent,EleType Child);
	virtual void Delete(EleType);
	//新加方法
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

	//寻找结点时的标识
	int m_Found;
	//树根节点指针
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
	求树根结点的值。
	参数：
		树根结点数据类型的变量
	返回值：
		树根结点的数据值

	返回值：
		0	树为空，引用返回的Root值无意义
		1	树不空，引用返回的Root值为树根结点的值

	注意函数返回值与通过引用返回值的区别。
*/
template <class EleType>
int CTreeChildSib<EleType>::Root(EleType& Root,int& x,int& y)
{
	if(m_Root==NULL)
	{
		//Root=NULL;//CString 时编译不过??
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
	指定结点的值，求其双新结点的值。。
	参数：
		Child	
	返回值：
		无
	该函数为接口函数。

  pParent=NULL;
	pChild=m_Root;

	按子树查找。
	从子树的树根开始查找。
	1)如果子树树根pChild->Data=Child，找到孩子节点，返回其双亲节点值pParent->Data(pParent不空)
	2)否则，依次查找pChild所有子树，按上述方法（pParent=pChild,pChild=pChild->pFirstChild)
	3)如果pChild为空，返回，查找其兄弟节点(pChild=pChild->pNextSibiling)
	4)设置一个标志，成员变量m_Found，找到令其为1，初始值=0

*/
template <class EleType>
int CTreeChildSib<EleType>::Parent(EleType Child,EleType& Parent)
{
	m_Found=0;
	FindParent(m_Root,NULL,Child,Parent);

	return m_Found;
}

/*
	入口参数：
	pRoot		子树根节点的指针
	pParent		子树树根节点的双亲节点指针
	Child		待查找孩子节点值
	Parent		该孩子节点的双亲节点值，可能无意义
*/
template <class EleType>
void CTreeChildSib<EleType>::FindParent(
							TREENODE_CS<EleType> *pRoot,
							TREENODE_CS<EleType> *pParent,
							EleType Child,
							EleType& Parent)
{
	//子树不空时处理；否则直接返回
	if(pRoot!=NULL)
	{
		//子树树根节点值为待查值，查找结束，返回		
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
		//子树树根节点值不是待查值，递归查找		
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
/*****************************************************************增加方法**********************************************/
//得到所在层
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
//得到第一个孩子
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
//得到下一个兄弟
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
//设置坐标,外部接口
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
//得到坐标
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
//设置树拥有的宽度,外部接口
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
/*****************************************************************增加方法**********************************************/
/*
	查找值对应的节点指针。
	参数：
		pRoot		指向子树根节点指针
		Value			待查找节点值
		pNode		指向该节点的指针
	返回值：
		无
	说明：按前序遍历方式查找
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
	//子树不空时处理；否则直接返回
	if(pRoot!=NULL)
	{
		//子树树根节点值为待查值，查找结束，返回		
		if(pRoot->Data==Value)
		{
			pRetParent=pParent;
			pNode=pRoot;
			m_Found=1;
		}
		//子树树根节点值不是待查值，递归查找		
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
	求树深度。
	参数：
		无
	返回值：
		无
	该函数为接口函数。
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
	求子树深度。
	参数：
		pRoot	指向子树根结点的指针
	返回值：
		无
	内部函数，递归，供Depth调用。
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
	先序遍历树。
	参数：
		无，表示对整棵树遍历
	返回值：
		无
	该函数为接口函数。
*/
template <class EleType>
void CTreeChildSib<EleType>::PreOrder()
{
	InnerPreOrder(m_Root);
}

/*
	先序遍历树。
	参数：
		pRoot	指向某个子树根结点的指针
	返回值：
		无
	内部函数，递归，供PreOrder调用。
*/
template <class EleType>
void CTreeChildSib<EleType>::InnerPreOrder(TREENODE_CS<EleType> *pRoot)
{
	TREENODE_CS<EleType> *p;
	if(pRoot)
	{
		//1.访问根
		cout<<pRoot->Data<<endl;

		//2.自左至右访问子树
		p=pRoot->pFirstChild;
		while(p)
		{
			InnerPreOrder(p);
			p=p->pNextSib;
		}
	}

}

/*
	后序遍历树。
	参数：
		无，表示对整棵树遍历
	返回值：
		无
	该函数为接口函数。
*/
template <class EleType>
void CTreeChildSib<EleType>::PostOrder()
{
	InnerPostOrder(m_Root);
}

/*
	后序遍历树。
	参数：
		pRoot	指向某个子树根结点的指针
	返回值：
		无
	内部函数，递归，供PostOrder调用。
*/
template <class EleType>
void CTreeChildSib<EleType>::InnerPostOrder(TREENODE_CS<EleType> *pRoot)
{
	TREENODE_CS<EleType> *p;
	if(pRoot)
	{
		//1.自左至右访问子树
		p=pRoot->pFirstChild;
		while(p)
		{
			InnerPostOrder(p);
			p=p->pNextSib;
		}

		//2.访问根
		cout<<pRoot->Data<<endl;

	}

}

/*
	层序遍历树。
	参数：
		无，表示对整棵树遍历
	返回值：
		无
	思路：
	1)首先访问根节点
	2)访问完根节点后，将其指针入队
	3)当队列不空时：
		3.1)出队，该指针所指节点已经访问过，
		3.2)自左至右访问其孩子节点，
		3.3)每个孩子节点访问完成后，其指针入队
*/
template <class EleType>
void CTreeChildSib<EleType>::LevelOrder()
{
	//树空时退出，不进行遍历操作
	if(!m_Root)
		return;

	//创建一个长度与树结点个数相同的循环队列，队列的元素类型为指向树结点的指针
	CQueue<TREENODE_CS<EleType>*> *pQueue;
	pQueue=new CSeqQueue<TREENODE_CS<EleType>*>(m_NodeCount);
	
	//队列创建不成功，退出
	if(!pQueue)
		return;

	//队列初始化失败，退出
	if(pQueue->InitOK()==0)
	{
		delete pQueue;
		return;
	}

	TREENODE_CS<EleType> *pNode,*pChild;
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

		//自左至右访问其所有孩子并入队
		pChild=pNode->pFirstChild;
		while(pChild)
		{
			cout<<pChild->Data<<endl;

			pQueue->EnQueue(pChild);
			pChild=pChild->pNextSib;
		}
	}

	//操作结束，删除队列
	delete pQueue;
}

/*
	返回值：
	0-找到Parent,内存不足
	1-没找到
	2-找到，插入成功
*/
template <class EleType>
int CTreeChildSib<EleType>::Insert(EleType Parent,EleType Child)
{
	//树空，插入节点为根节点，此时忽略其双亲结点值
	if(m_Root==NULL)
	{
		TREENODE_CS<EleType> *newNode;
		newNode=new TREENODE_CS<EleType>;
		if(newNode)
		{
			newNode->Data=Child;
			newNode->pFirstChild=NULL;
			newNode->pNextSib=NULL;
			//坐标为初始化为0
			newNode->x=0;
			newNode->y=0;
			//孩子数为0
			newNode->childrenCount=0;
			m_Root=newNode;

			m_NodeCount++;

			return 2;
		}
		else
			return 0;
	}
	//树不空时，调用其内部函数递归执行
	else
		return InnerInsert(m_Root,Parent,Child);
}

/*
	返回值：
	0-找到Parent,内存不足
	1-没找到
	2-找到，插入成功
*/
template <class EleType>
int CTreeChildSib<EleType>::InnerInsert(TREENODE_CS<EleType> *pRoot,EleType Parent,EleType Child)
{
	TREENODE_CS<EleType> *newNode;
	TREENODE_CS<EleType> *p;

	if(pRoot)
	{
		//1.子数树根节点是待插入节点的双亲
		if(pRoot->Data==Parent)
		{
			newNode=new TREENODE_CS<EleType>;
			if(newNode)
			{
				newNode->Data=Child;			
				//坐标为初始化							
				//newNode->x=0;
				//newNode->y=0;
				//孩子数为0
				newNode->childrenCount=0;
				newNode->pFirstChild=NULL;
				newNode->pNextSib=NULL;
			}
			//内存不足
			else
				return 0;
			
			//p指向子树树根节点的第一个孩子节点
			p=pRoot->pFirstChild;

			//子树树根节点没有孩子节点，
			//直接作为其第一个孩子节点
			if(p==NULL)
			{
				pRoot->pFirstChild=newNode;
				pRoot->childrenCount=1;
				SetChildPositionOf(pRoot);//调整孩子坐标
			}
			else
			{
				//防止重复
				if(p->Data==Child)
				{
					delete newNode;
					return -1;//表示重复
				}
				//找到子树树根节点的最右孩子节点
				while(p->pNextSib!=NULL)
				{
					p=p->pNextSib;
					//防止重复
					if(p->Data==Child)
					{
						delete newNode;
						return -1;//表示重复
					}
				}

				p->pNextSib=newNode;
				pRoot->childrenCount++;
				SetChildPositionOf(pRoot);//调整孩子坐标
			}

			m_NodeCount++;
			return 2;
		}
		//2.子数树根节点不是待插入节点的双亲
		else
		{
			p=pRoot->pFirstChild;
			while(p!=NULL)
			{				
				//找到并且插入，直接返回
				if(InnerInsert(p,Parent,Child)==2)
					return 2;
				//未找到返回
				else if(InnerInsert(p,Parent,Child)==0)
					return 0;
				//继续找
				else
					p=p->pNextSib;
			}
			return -1;//
		}

	}
	return 1;
}
/***************************************************************调整孩子坐标**********************************************/
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
/***************************************************************调整孩子坐标**********************************************/
/*
	删除子树，子树根节点的值为指定值。
	参数：
		NodeValue		待删除子树根节点的值
	返回值：
		1	操作成功，总返回该值
*/
template <class EleType>
void CTreeChildSib<EleType>::Delete(EleType NodeValue)
{
	//1.找Root值所在的节点
	TREENODE_CS<EleType> *pResult=NULL,*pParent=NULL,*pRetParent;

	m_Found=0;
	FindNode(pParent,m_Root,NodeValue,pResult,pRetParent);
	
	//2.如果找到该节点，删除之。
	//删除前可能要调整父、兄弟的关系
	if(pResult)
	{
		//如果是根节点，不用调整关系
		if(pRetParent==NULL)
			InnerDelete(pResult);
		else
		{
			
			//调整关系
			//1)是父节点的第一个孩子
			if(pRetParent->pFirstChild==pResult)
				pRetParent->pFirstChild=pResult->pNextSib;
			//2)不是父节点的第一个孩子
			else
			{
				TREENODE_CS<EleType> *pLeftSib;
				pLeftSib=pRetParent->pFirstChild;
				while(pLeftSib && pLeftSib->pNextSib!=pResult)
						pLeftSib=pLeftSib->pNextSib;
				
				pLeftSib->pNextSib=pResult->pNextSib;
			}
			

			//3)删除
			InnerDelete(pResult);
		}
	}
}

template <class EleType>
void CTreeChildSib<EleType>::InnerDelete(TREENODE_CS<EleType> *pRoot)
{
	if(pRoot==NULL)
		return;

	//当pRoot为叶子时直接删除，结点个数减一
	if(pRoot->pFirstChild==NULL)
	{
		delete pRoot;
		m_NodeCount--;
	}
	//当pRoot为分支递归删除
	else
	{
		TREENODE_CS<EleType> *pChild,*pChild2;
		//先删除其子树
		pChild=pRoot->pFirstChild;
		while(pChild)
		{
			pChild2=pChild->pNextSib;
			InnerDelete(pChild);
			pChild=pChild2;
			//pChild=pChild->pNextSib;
		}
		//再删除本身
		delete pRoot;
	}
}

/*
	将树信息保存到文件，或从文件中读取树信息并创建树。未实现。
	参数：
		FileName		文件名称，二进制格式
		IsSaveToFile	文件操作，0、1表示读文件和写文件
	返回值：
		0	操作失败
		1	操作成功
*/
template <class EleType>
int CTreeChildSib<EleType>::Serialize(char *FileName,int IsSaveToFile)
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
	//读文件
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