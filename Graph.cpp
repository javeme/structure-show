//Graph.cpp - ͼ�ĳ������ʵ��

#include "Graph.h"

template <class EleType>
CGraph<EleType>::CGraph()
{	
	m_VexCount=0;
	m_ArcCount=0;
	m_Type=0;			//Ĭ��Ϊ����ͼ
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
char* CGraph<EleType>::TypeName[]={"����ͼ","����ͼ","������","������"};
