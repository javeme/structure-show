/*
	树的基类定义。
*/
#include "DataStructure.cpp"

#if !defined(_CPP_TREE)
#define _CPP_TREE

template <class EleType>
class CTree :public DataStructure<EleType>
{
public:
	CTree();
	virtual ~CTree();

	virtual int GetNodeCount(void);

	virtual int Serialize(char *FileName,int IsSaveToFile);

	//下面的操作完全取决于树的具体实现，设计为纯虚函数
	virtual int Root(EleType&,int&,int&)=0;
	virtual int Parent(EleType Child,EleType& Parent)=0;
	virtual int Depth()=0;
	virtual void PreOrder()=0;
	virtual void PostOrder()=0;
	virtual void LevelOrder()=0;
	virtual int Insert(EleType Parent,EleType Child)=0;
	virtual void Delete(EleType)=0;

	virtual int GetFirstChildOf(EleType,EleType&,int &x,int &y)=0;
	virtual int GetNextSibOf(EleType,EleType&,int &x,int &y)=0;
	virtual int GetLevelOf(EleType value)=0;
	virtual int SetPositionOf(EleType selfValue,int x,int y,int width)=0;
	virtual int GetPositionOf(EleType selfValue,int &x,int &y)=0;
	//virtual int SetTreeWidth(EleType selfValue,int width)=0;

protected:
	int m_NodeCount;
};

template <class EleType>
CTree<EleType>::CTree()
{
	m_NodeCount=0;
}

template <class EleType>
CTree<EleType>::~CTree()
{

}

template <class EleType>
int CTree<EleType>::GetNodeCount(void)
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
int CTree<EleType>::Serialize(char *FileName,int IsSaveToFile)
{
	return 0;
}

#endif
