//ͼ���ڽӾ���ʵ��
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#include "GraphAM.h"

/*
	���ܣ�
		Ĭ�Ϲ��캯��
	������
		��
  ����ֵ��
		��
	˵����
		Ĭ�϶������Ϊ20��Ĭ������Ϊ����ͼ
*/
template <class EleType>
CGraphAM<EleType>::CGraphAM():CGraph<EleType>()
{
	int i,j;
	
	this->m_MaxVexCount=20;
	m_Type=0;

	//���������
	m_Vexs=new EleType[m_MaxVexCount];
	visited=new int[m_MaxVexCount];
	pPoints=new PositionStruct*[m_MaxVexCount];
	if(m_Vexs==NULL||visited==NULL)
		return;
	//ÿ�������ʼ����Ϊ��
	for(i=0;i<m_MaxVexCount;i++)
	{
		//m_Vexs[i]=NULL;//CString ʱ�޷���ֵ!
		visited[i]=0;
		pPoints[i]=new PositionStruct;
	}
	//�����ڽӾ���
	j=m_MaxVexCount*m_MaxVexCount;
	m_Arcs=new int[j];

	if(m_Arcs==NULL)
		return;

	for(i=0;i<j;i++)
	{
		m_Arcs[i]=0;	
	}

	m_InitOK=1;
}

/*
	���ܣ�
		ָ����󶥵������ͼ���͵Ĺ��캯��
	������
		��
  ����ֵ��
		��
	˵����
		��
*/
template <class EleType>
CGraphAM<EleType>::CGraphAM(int MaxVexCount,int Type):CGraph<EleType>()
{
	int i,j;

	m_MaxVexCount=MaxVexCount;
	m_Type=Type;

	//���������
	this->m_Vexs=new EleType[m_MaxVexCount];
	if(m_Vexs==NULL)
		return;

	for(i=0;i<m_MaxVexCount;i++)
		m_Vexs[i]=NULL;

	//�����ڽӾ���
	j=m_MaxVexCount*m_MaxVexCount;
	m_Arcs=new int[j];
	if(m_Arcs==NULL)
		return;

	switch(m_Type)
	{
	case 0:
	case 1:
		for(i=0;i<j;i++)
		{
			m_Arcs[i]=0;
		}
		break;

	case 2:
	case 3:
		for(i=0;i<j;i++)
		{
			m_Arcs[i]=INT_INFINITY;
		}
		for(i=0;i<j;i+=m_MaxVexCount+1)
			m_Arcs[i]=0;

		break;
	}
	m_InitOK=1;

	//���ԣ�����þ���
	for(i=0;i<m_MaxVexCount;i++)
	{
		for(j=0;j<m_MaxVexCount;j++)
			cout<<"\t"<<m_Arcs[i*m_MaxVexCount+j];
		cout<<endl;
	}
}

/*
	���ܣ�
		ָ��ͼ���͵Ĺ��캯��
	������
		��
  ����ֵ��
		��
	˵����
		Ĭ����󶥵����Ϊ20
*/
template <class EleType>
CGraphAM<EleType>::CGraphAM(int Type):CGraph<EleType>()
{
	int i,j;

	m_VexCount=20;
	m_Type=Type;

	/*
	//���������
	this->m_Vexs=new char*[m_MaxVexCount];
	if(m_Vexs==NULL)
		return;

	for(i=0;i<m_MaxVexCount;i++)
		m_Vexs[i]=NULL;

	//�����ڽӾ���
	j=m_MaxVexCount*m_MaxVexCount;//m_MaxVexCountû�г�ʼ��?
	m_Arcs=new int[j];
	if(m_Arcs==NULL)
		return;
		
	//*/
	this->CGraphAM::CGraphAM();//���½�����?
	j=m_MaxVexCount*m_MaxVexCount;

	switch(m_Type)
	{
	case 0:
	case 1:
		for(i=0;i<j;i++)
		{
			m_Arcs[i]=0;
		}
		break;

	case 2:
	case 3:
		for(i=0;i<j;i++)
		{
			m_Arcs[i]=INT_INFINITY;
		}
		for(i=0;i<j;i+=m_MaxVexCount+1)
			m_Arcs[i]=0;

		break;
	}
	m_InitOK=1;
}

/*
	���ܣ�
		��������
	������
		��
	����ֵ��
		��
	˵����
		��
*/
template <class EleType>
CGraphAM<EleType>::~CGraphAM()
{
	/*int i;	
	if(m_Vexs)
		for(i=0;i<m_MaxVexCount;i++)
			delete m_Vexs[i];
	if(pPoints)
		for(i=0;i<m_MaxVexCount;i++)
			delete pPoints[i];
	*/
	delete[] m_Vexs;
	delete[] m_Arcs;
	delete[] pPoints;
}
/****************************************************��ȡλ��****************************************************/
template <class EleType>
int CGraphAM<EleType>::GetPositionOf(int VexID,int &x,int &y)
{
	if(VexID<1 || VexID>m_VexCount)
		return 0;

	VexID=VexID-1;
	if(pPoints[VexID]!=NULL && pPoints[VexID]->x >0 && pPoints[VexID]->y >0)
	{		
		x=pPoints[VexID]->x;
		y=pPoints[VexID]->y;
		return 1;
	}
	else
		return 0;
}
/****************************************************���ڽӵ�λ��****************************************************/
template <class EleType>
int CGraphAM<EleType>::GetNeighborPositionOf(EleType Name,PositionStruct*& pPositions)
{
	int vexID=0,i,index;
	bool isFirst=true;
	PositionStruct *pNewPosition;
	pPositions=NULL;
	//�ҵ�����id
	for(i=0;i<m_VexCount;i++)
	{
		if(m_Vexs[i]==Name)
		{
			vexID=i;
			break;
		}
	}
	//�ҵ��ڽӵ�
	for(i=0;i<m_VexCount;i++)
	{
		index=vexID*m_MaxVexCount + i;
		if(m_Arcs[index]==1)
		{
			//pNewPosition=new Position;
			//pNewPosition->x=pPoints[i]->x;
			//pNewPosition->y=pPoints[i]->y;
			pNewPosition=pPoints[i];
			if(isFirst)
			{
				pNewPosition->pNext=NULL;
				pPositions=pNewPosition;				
			}
			else
			{
				pNewPosition->pNext=pPositions;
				pPositions=pNewPosition;
			}
			isFirst=false;
		}
	}
	if(isFirst)
		return 0;
	else
		return 1;
}
/*
	���ܣ�
		��Ӷ���
	������
		Name	[in]	����
		VexID	[out]	������
	����ֵ��
		0	����ʧ��
		1	����ɹ�
	˵����
		��
*/
template <class EleType>
int CGraphAM<EleType>::InsertVex(EleType Name,int &VexID)
{
	if(m_InitOK==0)
	{
		cout<<"��ʼ��ʧ��"<<endl;
		return 0;	
	}
	//�����ѵ�������
	if(m_VexCount==m_MaxVexCount)
		return 0;

	/*
	//�����ڴ�ռ�
	char *p;
	p=new char[strlen(Name)+1];
	if(p==NULL)
		return 0;
		
	strcpy(p,Name);
	m_Vexs[m_VexCount]=p;
	*/
	m_Vexs[m_VexCount]=Name;
	VexID=m_VexCount+1;
	SetPosition();//��������
	m_VexCount++;

	return 1;

}
/******************************************************************��������**************************************/
template <class EleType>
int CGraphAM<EleType>::SetPosition()
{
	int x,y;
	x=rand()%700+200;//�����
	y=rand()%430+20;
	for(int i=1;i<=m_VexCount;i++)
	{
		/*
		do{
			x=rand();//�����
			y=rand();
		}while(x>1000 || y>800);
		*/		
		double distance= (x-pPoints[i]->x)*(x-pPoints[i]->x) + (y-pPoints[i]->y)*(y-pPoints[i]->y);
		distance=sqrt(distance);
		if(distance<60)//��ͷ����
		{
			i=1;
			x=rand()%700+200;
			y=rand()%430+20;
		}
	}
	pPoints[m_VexCount]->x=x;
	pPoints[m_VexCount]->y=y;	//CString str; str.Format("λ��:(%d,%d)",x,y); ::AfxMessageBox(str);
	return 1;
}
/*
	���ܣ�
		ɾ������
	������
		Name	[in]		��ɾ�����������
	����ֵ��
		0	ɾ��ʧ��
		1	ɾ���ɹ�
	˵����
		��
*/
template <class EleType>
int CGraphAM<EleType>::DeleteVex(EleType Name)
{
	if(m_InitOK==0)
		return 0;

	int VexID=-1,i,Index;
	//���Ҹö���ı��
	for(i=0;VexID==-1 && i<m_VexCount;i++)
		if( Name==m_Vexs[i])
			VexID=i;

	//û�ҵ��ö���
	if(VexID==-1)
		return 0;

	//��ɾ����ö����йصı�
	switch(m_Type)
	{
	case 0:
		//ɾ���ö��������еķ���ֵ
		Index=VexID*m_MaxVexCount;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index+i]==1)
			{
				m_ArcCount--;
				m_Arcs[Index+i]=0;
			}
		}
		//ɾ���ö��������еķ���ֵ
		Index=VexID;
		for(i=0;i<m_MaxVexCount;i++)
		{
			m_Arcs[Index]=0;
			Index+=m_MaxVexCount;
		}
		break;

	case 1:
		Index=VexID*m_MaxVexCount;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index+i]==1)
			{
				m_ArcCount--;
				m_Arcs[Index+i]=0;
			}
		}
		Index=VexID;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index]==1)
			{
				m_ArcCount--;
				m_Arcs[Index]=0;
				Index+=m_MaxVexCount;
			}
		}
		break;

	case 2:
		Index=VexID*m_MaxVexCount;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index+i]!=INT_INFINITY && m_Arcs[Index+i]!=0)
			{
				m_ArcCount--;
				m_Arcs[Index+i]=INT_INFINITY;
			}
		}
		Index=VexID;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index]!=0 && m_Arcs[Index]!=INT_INFINITY)
				m_Arcs[Index]=INT_INFINITY;
			Index+=m_MaxVexCount;
		}
		break;

	case 3:
		Index=VexID*m_MaxVexCount;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index+i]!=INT_INFINITY && m_Arcs[Index+i]!=0)
			{
				m_ArcCount--;
				m_Arcs[Index+i]=INT_INFINITY;
			}
		}
		Index=VexID;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index]!=0 && m_Arcs[Index]!=INT_INFINITY)
			{
				m_ArcCount--;
				m_Arcs[Index]=INT_INFINITY;
			}
			Index+=m_MaxVexCount;
		}
		break;

	}

	//��ɾ���ö���
	for(i=VexID;i<m_VexCount-1;i++)
		m_Vexs[i]=m_Vexs[i+1];

	//��������1
	m_VexCount--;

	return 1;
}

/*
	���ܣ�
		ɾ������
	������
		VexID	[in]		������
	����ֵ��
		0	ɾ��ʧ��
		1	ɾ���ɹ�
	˵����
		�ù��ܲ����ã��ܷ���0
*/
template <class EleType>
int CGraphAM<EleType>::DeleteVex(int VexID)
{
	return 0;
}

/*
	���ܣ�
		��ȡ��������
	������
		VexID	[in]		������
		Name	[out]		��������
	����ֵ��
		0	ָ�����㲻����
		1	ָ��������ڣ�Name������
	˵����
		Ҫ��Name�����Ѿ��ڵ��ú����з����пռ�
*/
template <class EleType>
int CGraphAM<EleType>::GetVex(int VexID, EleType& Name)
{
	if(m_InitOK==0)
		return 0;

	if(VexID>m_VexCount || VexID<1)
		return 0;
	
	//strcpy(Name,m_Vexs[VexID-1]);
	Name=m_Vexs[VexID-1];
	return 1;
}

/*
	���ܣ�
		���ö�������
	������
		VexID	[in]	������
		NewName	[in]	����������
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		�ò�����ȷ�Ϲ��̣�Ӧ�ڵ��ú�����Ҫ��ȷ�����Ƶ��޸ģ����������
*/
template <class EleType>
int CGraphAM<EleType>::SetVex(int VexID,EleType NewName)
{
	if(m_InitOK==0)
		return 0;

	if(VexID>m_VexCount || VexID<1)
		return 0;
	/*
	//Ϊ����������ռ�
	char *p;
	p=new char[strlen(NewName)+1];
	if(p==NULL)
		return 0;

	//�ͷ�ԭ������ռ�ռ�
	delete[] m_Vexs[VexID-1];

	strcpy(p,NewName);
	m_Vexs[VexID-1]=p;
	*/
	m_Vexs[VexID-1]=NewName;
	return 1;
}

/*
	���ܣ�
		�޸Ķ�������
	������
		OldName	[in]	ԭ����
		NewName	[in]	������
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		�ò�����ȷ�Ϲ��̣�Ӧ�ڵ��ú�����Ҫ��ȷ�����Ƶ��޸ģ����������
*/
template <class EleType>
int CGraphAM<EleType>::SetVex(EleType OldName,EleType NewName)
{
	if(m_InitOK==0)
		return 0;

	//Ѱ����OldName��������Ķ���
	int VexID=-1,Index;

	for(Index=0;VexID==-1 && Index<m_VexCount;Index++)
	{
		//if(strcmp(OldName,m_Vexs[Index])==0)
		if( OldName == m_Vexs[Index] )
		{
			VexID=Index;
		}
	}

	//δ�ҵ�ƥ�䶥�㣬�˳�
	if(VexID==-1)
		return 0;

	/*
	//�������������ÿռ�
	char *p;
	p=new char[strlen(NewName)+1];
	if(p==NULL)
		return 0;

	delete m_Vexs[VexID];

	strcpy(p,NewName);
	m_Vexs[VexID]=p;
	*/
	m_Vexs[VexID]=NewName;
	return 1;
}

/*
	���ܣ�
		���һ����
	������
		FromVexID	[in]	��ʼ������
		ToVexID		[in]	��ֹ������
		Weight		[in]	�ߵ�Ȩ
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		��
*/
template <class EleType>
int CGraphAM<EleType>::InsertArc(int FromVexID,int ToVexID,int Weight)
{
	if(m_InitOK==0)
		return 0;

	//�����Ų��Ϸ����������
	if(FromVexID==ToVexID || FromVexID>m_VexCount || FromVexID<1 || ToVexID>m_VexCount || ToVexID<1)
		return 0;

	//���ܼ�����������ı�
	if(FromVexID==ToVexID)
		return 0;


	int InsertOK=0;
	int Index1,Index2;
	Index1=(FromVexID-1)*m_MaxVexCount+ToVexID-1;
	Index2=(ToVexID-1)*m_MaxVexCount+FromVexID-1;

	//����ͼ�����ͣ�ִ�в�ͬ�Ĳ������
	switch(m_Type)
	{
	case 0://����ͼ
		if(m_Arcs[Index1]==0)
		{
			m_Arcs[Index1]=1;
			m_Arcs[Index2]=1;
			m_ArcCount++;
			InsertOK=1;
		}
		break;

	case 1://����ͼ
		if(m_Arcs[Index1]==0)
		{
			m_Arcs[Index1]=1;
			m_ArcCount++;
			InsertOK=1;
		}
		break;

	case 2://������
		if(m_Arcs[Index1]==INT_INFINITY)
		{
			m_Arcs[Index1]=Weight;
			m_Arcs[Index2]=Weight;
			m_ArcCount++;
			InsertOK=1;
		}
		break;

	case 3://������
		if(m_Arcs[Index1]==INT_INFINITY)
		{
			m_Arcs[Index1]=Weight;
			m_ArcCount++;
			InsertOK=1;
		}
		break;
	}
	
	return InsertOK;
}

/*
	���ܣ�
		ɾ��һ����
	������
		FromVexID	[in]	��ʼ���㣬��Ŵ�1��ʼ
		ToVexID		[in]	��ֹ���㣬��Ŵ�1��ʼ
	����ֵ��
		
	˵����
		
*/
template <class EleType>
int CGraphAM<EleType>::DeleteArc(int FromVexID,int ToVexID)
{
	if(m_InitOK==0)
		return 0;

	if(FromVexID==ToVexID || FromVexID<1 || FromVexID>m_VexCount || ToVexID<1 || ToVexID>m_VexCount)
		return 0;

	int Index1,Index2,DeleteOK=0;

	Index1=(FromVexID-1)*m_MaxVexCount+ToVexID-1;
	Index2=(ToVexID-1)*m_MaxVexCount+FromVexID-1;

	switch(m_Type)
	{
	case 0:
		if(m_Arcs[Index1]==1)
		{
			m_Arcs[Index1]=0;
			m_Arcs[Index2]=0;
			DeleteOK=1;
		}
		break;

	case 1:
		if(m_Arcs[Index1]==1)
		{
			m_Arcs[Index1]=0;
			DeleteOK=1;
		}
		break;

	case 2:
		if(m_Arcs[Index1]!=INT_INFINITY)
		{
			m_Arcs[Index1]=INT_INFINITY;
			m_Arcs[Index2]=INT_INFINITY;
			DeleteOK=1;
		}
		break;

	case 3:
		if(m_Arcs[Index1]!=INT_INFINITY)
		{
			m_Arcs[Index1]=INT_INFINITY;
			DeleteOK=1;
		}
		break;
	}
	if(DeleteOK==1)
		m_ArcCount--;

	return DeleteOK;
}

/*
	���ܣ�
		��ȡ����Ϣ
	������
		FromVexID	[in]	��ʼ������
		ToVexID		[in]	��ֹ������
		Weight		[out]	1��Ȩֵ���京��ȡ����ͼ����
	����ֵ��
		0	����ʧ��
		1	�����ɹ���Weight������
	˵����
		��
*/
template <class EleType>
int CGraphAM<EleType>::GetArc(int FromVexID,int ToVexID,int &Weight)
{
	if(m_InitOK==0)
		return 0;

	if(FromVexID==ToVexID || FromVexID<1 || FromVexID>m_VexCount || ToVexID<1 || ToVexID>m_VexCount)
		return 0;

	int Index1,Index2,ExistArc=0;

	Index1=(FromVexID-1)*m_MaxVexCount+ToVexID-1;
	Index2=(ToVexID-1)*m_MaxVexCount+FromVexID-1;

	switch(m_Type)
	{
	case 0:
	case 1:
		if(m_Arcs[Index1]==1)
		{
			Weight=1;
			ExistArc=1;
		}
		break;

	case 2:
	case 3:
		if(m_Arcs[Index1]!=INT_INFINITY)
		{
			Weight=m_Arcs[Index1];
			ExistArc=1;
		}
		break;

	}

	return ExistArc;

}

/*
	���ܣ�
		���ñߵ���Ϣ
	������
		FromVexID	[in]	��ʼ������
		ToVexID		[in]	��ֹ������
		Weight		[in]	Ȩֵ��������������
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		�����ߴ���ʱ���������塣
*/
template <class EleType>
int CGraphAM<EleType>::SetArc(int FromVexID,int ToVexID,int Weight)
{
	if(m_InitOK==0)
		return 0;

	if(FromVexID==ToVexID || FromVexID<1 || FromVexID>m_VexCount || ToVexID<1 || ToVexID>m_VexCount)
		return 0;

	int Index1,Index2,ExistArc=0;

	Index1=(FromVexID-1)*m_MaxVexCount+ToVexID-1;
	Index2=(ToVexID-1)*m_MaxVexCount+FromVexID-1;

	switch(m_Type)
	{
	case 0:
	case 1:
		if(m_Arcs[Index1]==1)
			ExistArc=1;
		break;

	case 2:
		if(m_Arcs[Index1]!=INT_INFINITY)
		{
			m_Arcs[Index1]=Weight;
			m_Arcs[Index2]=Weight;
			ExistArc=1;
		}
		break;

	case 3:
		if(m_Arcs[Index1]!=INT_INFINITY)
		{
			m_Arcs[Index1]=Weight;
			ExistArc=1;
		}
		break;

	}

	return ExistArc;
}

/*
	���ܣ�
		������ȱ���
	������
		��
	����ֵ��
		��
	˵����
		��
*/
template <class EleType>
void CGraphAM<EleType>::DFSTraverse()
{
	clearVisit();
	innerDFSTraverse(0);
}
template <class EleType>
void CGraphAM<EleType>::innerDFSTraverse(int index)
{
	cout<<m_Vexs[index]<<endl;
	visited[index]=1;
	for(int i=0;i<m_MaxVexCount;i++)
	{
		int arc=i*m_MaxVexCount+index;//ÿ�еĵ�index��
		if(m_Arcs[arc]==1 && visited[i]==0)
			innerDFSTraverse(i);
	}
}

/*
	���ܣ�
		������ȱ���
	������ 
		��
	����ֵ��
		��
	˵����
		��
*/
template <class EleType>
void CGraphAM<EleType>::BFSTraverse()
{	
	clearVisit();
	innerBFSTraverse(0);
}
template <class EleType>
void CGraphAM<EleType>::innerBFSTraverse(int index)
{
	int* queue=new int[this->m_MaxVexCount];
	int queueHead=0;
	int queueRear=0;
	queue[queueRear]=index;//���
	while((index=queue[queueHead])>=0 && queueHead<m_MaxVexCount)//?
	{
		queueHead++;//���Ӻ��ͷָ�����
		queueHead=queueHead%m_MaxVexCount;//��ֹ���
		cout<<this->m_Vexs[index]<<endl;//����
		this->visited[index]=1;
		for(int i=0;i<m_MaxVexCount;i++)//������
		{
			int location=(index*m_MaxVexCount)+(i);
			if(this->m_Arcs[location] && visited[i]==0)
			{
				queueRear++;
				queue[queueRear%m_MaxVexCount]=i;//���
			}
		}
	}

	delete[] queue;
}
//��visit��������
template <class EleType>
void CGraphAM<EleType>::clearVisit(){
	for(int i=0;i<m_MaxVexCount;i++)
		visited[i]=0;
}
/*
	���ܣ�
		��ͼ���浽�ļ���
	������
		FileName	[in]	�ļ�����
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		�ļ�Ϊ�����Ƹ�ʽ
*/
template <class EleType>
int CGraphAM<EleType>::SaveToFile(const char *FileName)
{
	if(m_InitOK==0)
		return 0;

	FILE *fp;
	fp=fopen(FileName,"wb");
	if(!fp)
		return 0;

	//д��ͼ����
	fwrite(&m_Type,sizeof(int),1,fp);

	//д�붥���������ж�����Ϣ
	int VexID,Length;
	fwrite(&m_VexCount,sizeof(int),1,fp);//1?
	for(VexID=0;VexID<m_VexCount;VexID++)
	{
		fwrite(&VexID,sizeof(int),1,fp);
		Length=sizeof(m_Vexs[VexID]);
		fwrite(&Length,sizeof(int),1,fp);//?
		fwrite(m_Vexs[VexID],Length,1,fp);
	}
	//д����������б���Ϣ
	int Row,Col,Index;
	fwrite(&m_ArcCount,sizeof(int),1,fp);
	switch(m_Type)
	{
	//������ͼֻ�������Խ����Ϸ�����Ϣ
	case 0:
		for(Row=0;Row<m_MaxVexCount;Row++)
			for(Col=Row+1;Col<m_MaxVexCount;Col++)
			{
				Index=Row*m_MaxVexCount+Col;
				if(m_Arcs[Index]==1)
				{
					fwrite(&Row,sizeof(int),1,fp);
					fwrite(&Col,sizeof(int),1,fp);
				}
			}
		break;

	//������ͼ��Ҫ������������
	case 1:
		for(Row=0;Row<m_MaxVexCount;Row++)
			for(Col=0;Col<m_MaxVexCount;Col++)
			{
				Index=Row*m_MaxVexCount+Col;
				if(m_Arcs[Index]==1)
				{
					fwrite(&Row,sizeof(int),1,fp);
					fwrite(&Col,sizeof(int),1,fp);
				}
			}
		break;

	//��������ֻ�������Խ����Ϸ�����Ϣ
	case 2:
		for(Row=0;Row<m_MaxVexCount;Row++)
			for(Col=Row+1;Col<m_MaxVexCount;Col++)
			{
				Index=Row*m_MaxVexCount+Col;
				if(m_Arcs[Index]!=INT_INFINITY)
				{
					fwrite(&Row,sizeof(int),1,fp);
					fwrite(&Col,sizeof(int),1,fp);
					fwrite(m_Arcs+Index,sizeof(int),1,fp);
				}
			}
		break;

	//����������Ҫ������������
	case 3:
		for(Row=0;Row<m_MaxVexCount;Row++)
			for(Col=0;Col<m_MaxVexCount;Col++)
			{
				Index=Row*m_MaxVexCount+Col;
				if(m_Arcs[Index]!=0 && m_Arcs[Index]!=INT_INFINITY)
				{
					fwrite(&Row,sizeof(int),1,fp);
					fwrite(&Col,sizeof(int),1,fp);
					fwrite(m_Arcs+Index,sizeof(int),1,fp);
				}
			}
		break;

	}
	fclose(fp);
	return 1;
}

/*
	���ܣ�
		���ļ��ж�ȡͼ��Ϣ
	������
		FileName	[in]	�ļ�����
	����ֵ��
		0	����ʧ��
		1	�����ɹ�
	˵����
		�ļ�Ϊ�����Ƹ�ʽ
*/
template <class EleType>
int CGraphAM<EleType>::LoadFromFile(const char *FileName)
{
	if(m_InitOK==0)
		return 0;

	FILE *fp;
	fp=fopen(FileName,"rb");
	if(!fp)
		return 0;

	//��ȡͼ����
	int Type;
	fread(&Type,sizeof(int),1,fp);

	//��ȡ������
	int VexCount;
	fread(&VexCount,sizeof(int),1,fp);
	//�ļ��а����Ķ���������Ŀǰͼ�е���󶥵�����������
	//�Ľ���ʽ���޸�Ŀǰͼ�����ã�������󶥵����������������󡣿��������
	if(VexCount>m_MaxVexCount)
	{
		fclose(fp);
		return 0;
	}
	m_VexCount=VexCount;
	m_Type=Type;

	//��ȡ���ж�������
	int VexID,Length;
	//char VexName[255],*pName;
	EleType VexName;
	for(VexID=0;VexID<VexCount;VexID++)
	{
		fread(&VexID,sizeof(int),1,fp);
		fread(&Length,sizeof(int),1,fp);
		fread(&VexName,Length,1,fp);
		/*VexName[Length]='\0';

		delete m_Vexs[VexID];
		pName=new char[Length+1];
		if(pName)
			strcpy(pName,VexName);			
		m_Vexs[VexID]=pName;
		*/
		m_Vexs[VexID]=VexName;
	}

	//��ȡ���������б���Ϣ
	int ArcCount;
	fread(&ArcCount,sizeof(int),1,fp);
	m_ArcCount=ArcCount;

	int Row,Col,Index,ArcID,Weight;
	switch(Type)
	{
	//����ͼ
	case 0:
		Index=m_MaxVexCount*m_MaxVexCount;
		for(ArcID=0;ArcID<Index;ArcID++)
			m_Arcs[ArcID]=0;

		for(ArcID=0;ArcID<ArcCount;ArcID++)
		{
			fread(&Row,sizeof(int),1,fp);
			fread(&Col,sizeof(int),1,fp);
			m_Arcs[Row*m_MaxVexCount+Col]=1;
			m_Arcs[Col*m_MaxVexCount+Row]=1;
		}
		break;

	//����ͼ
	case 1:
		Index=m_MaxVexCount*m_MaxVexCount;
		for(ArcID=0;ArcID<Index;ArcID++)
			m_Arcs[ArcID]=0;

		for(ArcID=0;ArcID<ArcCount;ArcID++)
		{
			fread(&Row,sizeof(int),1,fp);
			fread(&Col,sizeof(int),1,fp);
			m_Arcs[Row*m_MaxVexCount+Col]=1;
		}
		break;

	//������
	case 2:
		Index=m_MaxVexCount*m_MaxVexCount;
		for(ArcID=0;ArcID<Index;ArcID++)
			m_Arcs[ArcID]=INT_INFINITY;
		for(ArcID=0;ArcID<Index;ArcID+=m_MaxVexCount+1)
			m_Arcs[ArcID]=0;

		for(ArcID=0;ArcID<ArcCount;ArcID++)
		{
			fread(&Row,sizeof(int),1,fp);
			fread(&Col,sizeof(int),1,fp);
			fread(&Weight,sizeof(int),1,fp);
			m_Arcs[Row*m_MaxVexCount+Col]=Weight;
			m_Arcs[Col*m_MaxVexCount+Row]=Weight;
		}
		break;

	//������
	case 3:
		Index=m_MaxVexCount*m_MaxVexCount;
		for(ArcID=0;ArcID<Index;ArcID++)
			m_Arcs[ArcID]=INT_INFINITY;
		for(ArcID=0;ArcID<Index;ArcID+=m_MaxVexCount+1)
			m_Arcs[ArcID]=0;

		for(ArcID=0;ArcID<ArcCount;ArcID++)
		{
			fread(&Row,sizeof(int),1,fp);
			fread(&Col,sizeof(int),1,fp);
			fread(&Weight,sizeof(int),1,fp);
			m_Arcs[Row*m_MaxVexCount+Col]=Weight;
		}
		break;

	}
	fclose(fp);
	return 1;

}
