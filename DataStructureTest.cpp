#include "DataStructureTest.h"

template <class EleType>
DataStructureTest<EleType>::DataStructureTest()
{
	;
}
template <class EleType>
DataStructureTest<EleType>::~DataStructureTest()
{
	;
}
//*****************************************************************************//
//≤‚ ‘Ω”ø⁄
template <class EleType>
DataStructure<EleType>* DataStructureTest <EleType>::Test(int structureType,int itemType)
{
	DataStructure<EleType>*pTest=NULL;
	switch(structureType)
	{		
		case 0:
			pTest=TestList(itemType);
			break;
		
		case 1:
			pTest=TestStack(itemType);
			break;

		case 2:
			pTest=TestQueue(itemType);
			break;

		case 3:
			pTest=TestTree(itemType);
			break;

		case 4:
			pTest=TestBinTree(itemType);
			break;

		case 5:
			pTest=TestGraph(itemType);
			break;

		case 6:
			pTest=TestQuery(itemType);
			break;
		case 7:	
			pTest=TestSort(itemType);
			break;			
		default:
			break;
	}
	return pTest;
}
//œﬂ–‘±Ì≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestList(int itemType)
{
	DataStructure<EleType>* pTest=NULL;
	switch(itemType)
	{		
		case 0:
			pTest=new SEQLIST<EleType>();
			break;
		case 1:
			pTest=new LINKLIST2<EleType>();
			break;
		case 2:
			pTest=new LINKLIST<EleType>();
			break;
		case 3:
			pTest=new STATICLIST<EleType>();
			break;
		case 4:
			pTest=new CYCLELINKLIST<EleType>();
			break;
		default:
			break;
	}
	return pTest;
}

// ˜≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestTree(int itemType)
{
	DataStructure<EleType>* pTest=NULL;
	switch(itemType)
	{		
		case 0:
			pTest=new CTreeChildSib<EleType>();
			break;
		
		default:
			break;
	}
	return pTest;
}
//’ª≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestStack(int itemType)
{
	DataStructure<EleType>* pTest=NULL;
	switch(itemType)
	{		
		case 0:
			pTest=new SEQSTACK<EleType>();
			break;
		case 1:
			pTest=new LINKSTACK<EleType>();
			break;
		default:
			break;
	}
	return pTest;
}
//∂”¡–≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestQueue(int itemType)
{
	return NULL;
}
//∂˛≤Ê ˜≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestBinTree(int itemType)
{
	DataStructure<EleType>* pTest=NULL;   
	pTest=new CBinTreeLink<EleType>();
	return pTest;
}
//Õº≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestGraph(int itemType)
{
	DataStructure<EleType>* pTest=NULL;
	switch(itemType)
	{		
		case 0:
			pTest=new CGraphAM<EleType>();
			break;
		case 1:
			pTest=new CGraphAM<EleType>();
			break;
		case 2:
			pTest=new CGraphAM<EleType>();
			break;
		case 3:
			pTest=new CGraphAM<EleType>();
			break;
		default:
			break;
	}
	return pTest;
}
//≤È—Ø≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestQuery(int itemType)
{
	return NULL;
}
//≈≈–Ú≤‚ ‘
template <class EleType>
DataStructure<EleType>* DataStructureTest<EleType>::TestSort(int itemType)
{
	return NULL;
}