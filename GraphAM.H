#include "Graph.cpp"

//图的邻接矩阵表示
//所有成员函数的参数中，顶点编号均从1开始
#if !defined(_H_CGRAPHAM_)
#define _H_CGRAPHAM_

#include <math.h>

template <class EleType>
class CGraphAM:public CGraph<EleType>
{
public:
	CGraphAM();
	CGraphAM(int MaxVexCount,int Type);
	CGraphAM(int Type);
	~CGraphAM();

	//基类中定义的函数
	virtual int InsertVex(EleType Name,int &VexID);
	virtual int DeleteVex(EleType Name);
	virtual int DeleteVex(int VexID);

	virtual int GetVex(int VexID, EleType& Name);
	virtual int GetPositionOf(int VexID,int &x,int &y);//获取顶点位置,结构体或对象赋值与普通数据赋值有何区别,能否传结构的值(非地址)体出去
	virtual int GetNeighborPositionOf(EleType Name,PositionStruct*& pPositions);//获取邻接点位置
	virtual int SetVex(int VexID, EleType NewName);
	virtual int SetVex(EleType OldName,EleType NewName);

	virtual int InsertArc(int FromVexID,int ToVexID,int Weight);
	virtual int DeleteArc(int FromVexID,int TovexID);
	virtual int GetArc(int FromVexID,int ToVexID,int &Weight);
	virtual int SetArc(int FromVexID,int ToVexID,int Weight);
	
	virtual void DFSTraverse();	
	virtual void BFSTraverse();

	virtual int SaveToFile(const char* FileName);
	virtual int LoadFromFile(const char* FileName);
private:
	virtual void innerDFSTraverse(int index);
	virtual void innerBFSTraverse(int index);
	void clearVisit();
	int SetPosition();

protected:
	EleType *m_Vexs;			//顶点名称数组
	int *visited;
	int *m_Arcs;			//邻接矩阵
	int m_MaxVexCount;		//最大顶点数
	PositionStruct** pPoints;//顶点坐标数组
};
#endif

