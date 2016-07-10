/*
	二叉树的抽象基类定义。
*/

#if !defined(_CPP_BINTREE)
#define _CPP_BINTREE

#include "DataStructure.cpp"
template <class EleType>
class CBinTree:public DataStructure<EleType>  
{
public:
	CBinTree();
	virtual ~CBinTree();

	virtual int GetNodeCount(void);

	virtual int Serialize(const char * const FileName,int IsSaveToFile);

	//下面的操作完全取决于二叉树的具体实现，设计为纯虚函数
	virtual int InsertL(EleType Parent,EleType Child)=0;
	virtual int DeleteL(EleType)=0;
	virtual int InsertR(EleType Parent,EleType Child)=0;
	virtual int DeleteR(EleType)=0;

	virtual void PreOrder() const=0;
	virtual void PostOrder() const=0;
	virtual void LevelOrder() const=0;
	virtual void InOrder() const=0;
	virtual void PreOrder2() const=0;

	virtual int Root(EleType&,int&,int&)=0;
	virtual int Search(EleType)=0;
	virtual int Parent(EleType Child,EleType& Parent)=0;
	virtual int Depth() const=0;

	//添加方法
	virtual int GetLeftChildOf(EleType parentValue,EleType& childValue,int &x,int &y)=0;
	virtual int GetRightChildOf(EleType parentValue,EleType& childValue,int &x,int &y)=0;
	virtual int SetPositionOf(EleType selfValue,int x,int y,int width)=0;
	virtual int GetPositionOf(EleType selfValue,int &x,int &y)=0;
protected:
	int m_NodeCount;
};

template <class EleType>
CBinTree<EleType>::CBinTree()
{
	m_NodeCount=0;
}

template <class EleType>
CBinTree<EleType>::~CBinTree()
{

}

template <class EleType>
int CBinTree<EleType>::GetNodeCount(void)
{
	return m_NodeCount;
}

/*
	将树信息保存到文件，或从文件中读取树信息并创建树。未实现。
	输入参数：
		FileName		文件名称，二进制格式
		IsSaveToFile	文件操作，0、1表示读文件和写文件
	返回值：
		0	操作失败
		1	操作成功
*/
template <class EleType>
int CBinTree<EleType>::Serialize(const char* const FileName,int IsSaveToFile)
{
	return 0;
}

#endif
