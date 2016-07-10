//Graph.cpp - 图的抽象类的实现

#include "Graph.h"

template <class EleType>
CGraph<EleType>::CGraph()
{	
	m_VexCount=0;
	m_ArcCount=0;
	m_Type=0;			//默认为无向图
	m_InitOK=0;
}

template <class EleType>
CGraph<EleType>::~CGraph()
{
}

template <class EleType>
int CGraph<EleType>::GetVexCount()
{
	return m_VexCount;
}
template <class EleType>
int CGraph<EleType>::GetArcCount()
{
	return m_ArcCount;
}
template <class EleType>
int CGraph<EleType>::GetType()
{
	return m_Type;
}

template <class EleType>
int CGraph<EleType>::InitOK()
{
	return m_InitOK;
}

template <class EleType>
void CGraph<EleType>::GetGraphInfo()
{
	;
}

template <class EleType>
char* CGraph<EleType>::TypeName[]={"无向图","有向图","无向网","有向网"};
