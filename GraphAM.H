#include "Graph.cpp"

//ͼ���ڽӾ����ʾ
//���г�Ա�����Ĳ����У������ž���1��ʼ
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

	//�����ж���ĺ���
	virtual int InsertVex(EleType Name,int &VexID);
	virtual int DeleteVex(EleType Name);
	virtual int DeleteVex(int VexID);

	virtual int GetVex(int VexID, EleType& Name);
	virtual int GetPositionOf(int VexID,int &x,int &y);//��ȡ����λ��,�ṹ������ֵ����ͨ���ݸ�ֵ�к�����,�ܷ񴫽ṹ��ֵ(�ǵ�ַ)���ȥ
	virtual int GetNeighborPositionOf(EleType Name,PositionStruct*& pPositions);//��ȡ�ڽӵ�λ��
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
	EleType *m_Vexs;			//������������
	int *visited;
	int *m_Arcs;			//�ڽӾ���
	int m_MaxVexCount;		//��󶥵���
	PositionStruct** pPoints;//������������
};
#endif
