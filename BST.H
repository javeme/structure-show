/*
	二叉排序树结点结构
*/
#if !defined(_H_BST_)
#define _H_BST_

typedef struct tagBSTNODE
{
	int Key;
	struct tagBSTNODE *LChild,*RChild;
}BSTNODE,*LPBSTNODE;

//二叉排序树类
class CBST
{
public:
	CBST();
	~CBST();
	virtual int InsertBST(LPBSTNODE pNewNode);
	virtual bool Search(int Key,LPBSTNODE &pNode);
	virtual void InOrder();
	
protected:
	void InnerInsertBST(LPBSTNODE &pRoot,LPBSTNODE pNewNode);
	void InnerSearch(LPBSTNODE pRoot,int Key,LPBSTNODE &pNode);
	void InnerInOrder(LPBSTNODE pRoot);

protected:
	LPBSTNODE m_Root;		//树根结点
	bool m_Found;			//是否找到满足条件的结点
	int m_Index;			//内部遍历时的序号
};
#endif