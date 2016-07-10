#if !defined(_CPP_DataStructure)
#define _CPP_DataStructure
//*
#include "DataStructure.h"

template <class EleType>
DataStructure<EleType>::DataStructure()
{
	;
}
template <class EleType>
DataStructure<EleType>::~DataStructure()
{
	;
}
//"实现"虚方法
template <class EleType>
int DataStructure<EleType>::Insert(int nPos,EleType newValue){return 0;}
template <class EleType>
int DataStructure<EleType>::Delete(int nPos,EleType &Result){return 0;}
template <class EleType>
int DataStructure<EleType>:: Get(int nPos,EleType &Result){return 0;}


/*/

template <class EleType>
class DataStructure
{
public:
	DataStructure(){};
	virtual ~DataStructure(){};
	
	virtual int Insert(int,EleType)=0;//为何非得纯虚函数???
	virtual int Get(int,EleType&)=0;
};
/**/
#endif
