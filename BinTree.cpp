/*
	�������ĳ�����ඨ�塣
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

	//����Ĳ�����ȫȡ���ڶ������ľ���ʵ�֣����Ϊ���麯��
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

	//��ӷ���
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
	������Ϣ���浽�ļ�������ļ��ж�ȡ����Ϣ����������δʵ�֡�
	���������
		FileName		�ļ����ƣ������Ƹ�ʽ
		IsSaveToFile	�ļ�������0��1��ʾ���ļ���д�ļ�
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
*/
template <class EleType>
int CBinTree<EleType>::Serialize(const char* const FileName,int IsSaveToFile)
{
	return 0;
}

#endif
