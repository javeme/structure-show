/*
	���Ļ��ඨ�塣
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

	//����Ĳ�����ȫȡ�������ľ���ʵ�֣����Ϊ���麯��
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
	������Ϣ���浽�ļ�������ļ��ж�ȡ����Ϣ����������δʵ�֡�
	���������
		FileName		�ļ����ƣ������Ƹ�ʽ
		IsSaveToFile	�ļ�������0��1��ʾ���ļ���д�ļ�
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
*/
template <class EleType>
int CTree<EleType>::Serialize(char *FileName,int IsSaveToFile)
{
	return 0;
}

#endif
