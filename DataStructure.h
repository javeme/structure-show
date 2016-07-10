
#ifndef DataStructure_H_H
#define DataStructure_H_H

#include "Position.h"

template <class EleType>
class DataStructure
{
public:
	DataStructure();
	virtual ~DataStructure();
	
	virtual int Insert(int nPos,EleType newValue);
	virtual int Delete(int nPos,EleType &Result);
	virtual int Get(int nPos,EleType &Result);

	virtual int Push(EleType newValue){return 0;}
	virtual int Pop(EleType &Result){return 0;}
	virtual int GetElement(int index,EleType &returnValue){return 0;}
	
	virtual int Insert(EleType parentValue,EleType newValue){return 0;}//Ê÷
	virtual int Root(EleType&,int&,int&){return 0;}
	virtual int Parent(EleType Child,EleType& Parent){return 0;}
	virtual int GetFirstChildOf(EleType,EleType&,int &x,int &y){return 0;}
	virtual int GetNextSibOf(EleType,EleType&,int &x,int &y){return 0;}
	virtual int GetLevelOf(EleType value){return 0;}
	//virtual int SetPosition(EleType selfValue,int x,int y){return 0;}
	virtual int GetPositionOf(EleType selfValue,int &x,int &y){return 0;}
	virtual int SetTreeWidth(EleType selfValue,int width){return 0;}

	//virtual int InsertVex(char *Name,int &VexID){return 0;}//Í¼
	virtual int InsertVex(EleType Name,int &VexID){return 0;}
	virtual int GetVex(int VexID, EleType& Name){return 0;}
	virtual int GetPositionOf(int VexID,int &x,int &y){return 0;}
	virtual int InsertArc(int FromVexID,int ToVexID,int Weight){return 0;}
	virtual int GetNeighborPositionOf(EleType Name,PositionStruct*& pPositions){return 0;}
	
	virtual int SetPositionOf(EleType selfValue,int x,int y,int width){return 0;}//¶þ²æÊ÷
	virtual int InsertL(EleType parentValue,EleType newValue){return 0;}
	virtual int InsertR(EleType parentValue,EleType newValue){return 0;}
	virtual int GetLeftChildOf(EleType parentValue,EleType& childValue,int &x,int &y){return 0;}
	virtual int GetRightChildOf(EleType parentValue,EleType& childValue,int &x,int &y){return 0;}

};

#endif
  