/*
	�������������ṹ
*/
#if !defined(_H_BST_)
#define _H_BST_

typedef struct tagBSTNODE
{
	int Key;
	struct tagBSTNODE *LChild,*RChild;
}BSTNODE,*LPBSTNODE;

//������������
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
	LPBSTNODE m_Root;		//�������
	bool m_Found;			//�Ƿ��ҵ����������Ľ��
	int m_Index;			//�ڲ�����ʱ�����
};
#endif