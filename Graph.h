
//ͼ�Ļ��ඨ��
#if !defined(_H_GRAPH_)

#define _H_GRAPH_

#define INT_INFINITY	0x7FFFFFFF
#define SHORT_INFINITY	0x7FFF

#include "Position.h"
#include "DataStructure.cpp"

template <class EleType>
class CGraph:public DataStructure<EleType>
{
public:
	CGraph();
	~CGraph();

	//�����ӿں���
	virtual int GetVexCount();
	virtual int GetArcCount();
	virtual int GetType();
	virtual int InitOK();
	virtual void GetGraphInfo();

	//ȡ���ھ���ʵ�ֵĴ���ӿں���
	virtual int InsertVex(EleType Name,int &VexID)=0;
	virtual int DeleteVex(EleType Name)=0;
	virtual int DeleteVex(int VexID)=0;

	virtual int GetVex(int VexID, EleType& Name)=0;
	virtual int SetVex(int VexID, EleType NewName)=0;
	virtual int SetVex(EleType OldName,EleType NewName)=0;

	virtual int InsertArc(int FromVexID,int ToVexID,int Weight)=0;
	virtual int DeleteArc(int FromVexID,int ToVexID)=0;
	virtual int GetArc(int FromVexID,int ToVexID,int &Weight)=0;
	virtual int SetArc(int FromVexID,int ToVexID,int Weight)=0;
	//��ӷ���
	virtual int GetPositionOf(int VexID,int &x,int &y)=0;
	virtual int GetNeighborPositionOf(EleType Name,PositionStruct*& pPositions)=0;

	virtual void DFSTraverse()=0;
	virtual void BFSTraverse()=0;

	virtual int SaveToFile(const char* FileName)=0;
	virtual int LoadFromFile(const char* FileName)=0;

protected:
	int m_InitOK;		//��ʼ���Ƿ�ɹ�
	int m_VexCount;		//�������
	int m_ArcCount;		//�߸���
	int m_Type;			//ͼ���ͣ�0��1��2��3�ֱ��ʾ����ͼ������ͼ����������������	 
	static EleType TypeName[];	//ͼ����������
};

#endif