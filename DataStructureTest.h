//#include "DataStructure.cpp"//±ØÐëcpp!!!!
#include "SeqList.cpp"
#include "LinkList2.cpp"
#include "LinkList.cpp"
#include "StaticLIST.cpp"
#include "CycleLinkList.cpp"

#include "SEQSTACK.cpp"
#include "LINKSTACK.cpp"

#include "TreeChildSib.cpp"

#include "BinTreeLink.CPP"

#include "GraphAM.cpp"

template <class EleType>
class DataStructureTest
{
public:
	DataStructureTest();
	virtual ~DataStructureTest();
	DataStructure<EleType>* Test(int structureType,int itemType);
	
	DataStructure<EleType>* TestList(int itemType);
	DataStructure<EleType>* TestStack(int itemType);	
	DataStructure<EleType>* TestQueue(int itemType);
	DataStructure<EleType>* TestTree(int itemType);
	DataStructure<EleType>* TestBinTree(int itemType);
	DataStructure<EleType>* TestGraph(int itemType);
	DataStructure<EleType>* TestSort(int itemType);
	DataStructure<EleType>* TestQuery(int itemType);


protected:	
};
