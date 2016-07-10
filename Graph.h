
//图的基类定义
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

	//公共接口函数
	virtual int GetVexCount();
	virtual int GetArcCount();
	virtual int GetType();
	virtual int InitOK();
	virtual void GetGraphInfo();

	//取决于具体实现的纯虚接口函数
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
	//添加方法
	virtual int GetPositionOf(int VexID,int &x,int &y)=0;
	virtual int GetNeighborPositionOf(EleType Name,PositionStruct*& pPositions)=0;

	virtual void DFSTraverse()=0;
	virtual void BFSTraverse()=0;

	virtual int SaveToFile(const char* FileName)=0;
	virtual int LoadFromFile(const char* FileName)=0;

protected:
	int m_InitOK;		//初始化是否成功
	int m_VexCount;		//顶点个数
	int m_ArcCount;		//边个数
	int m_Type;			//图类型，0、1、2、3分别表示无向图、有向图、无向网、有向网	 
	static EleType TypeName[];	//图的类型名称
};

#endif