//图的邻接矩阵实现
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

#include "GraphAM.h"

/*
	功能：
		默认构造函数
	参数：
		无
  返回值：
		无
	说明：
		默认顶点个数为20，默认类型为无向图
*/
template <class EleType>
CGraphAM<EleType>::CGraphAM():CGraph<EleType>()
{
	int i,j;
	
	this->m_MaxVexCount=20;
	m_Type=0;

	//创建顶点表
	m_Vexs=new EleType[m_MaxVexCount];
	visited=new int[m_MaxVexCount];
	pPoints=new PositionStruct*[m_MaxVexCount];
	if(m_Vexs==NULL||visited==NULL)
		return;
	//每个顶点初始名称为空
	for(i=0;i<m_MaxVexCount;i++)
	{
		//m_Vexs[i]=NULL;//CString 时无法赋值!
		visited[i]=0;
		pPoints[i]=new PositionStruct;
	}
	//创建邻接矩阵
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
	功能：
		指定最大顶点个数和图类型的构造函数
	参数：
		无
  返回值：
		无
	说明：
		无
*/
template <class EleType>
CGraphAM<EleType>::CGraphAM(int MaxVexCount,int Type):CGraph<EleType>()
{
	int i,j;

	m_MaxVexCount=MaxVexCount;
	m_Type=Type;

	//创建顶点表
	this->m_Vexs=new EleType[m_MaxVexCount];
	if(m_Vexs==NULL)
		return;

	for(i=0;i<m_MaxVexCount;i++)
		m_Vexs[i]=NULL;

	//创建邻接矩阵
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

	//调试：输出该矩阵
	for(i=0;i<m_MaxVexCount;i++)
	{
		for(j=0;j<m_MaxVexCount;j++)
			cout<<"\t"<<m_Arcs[i*m_MaxVexCount+j];
		cout<<endl;
	}
}

/*
	功能：
		指定图类型的构造函数
	参数：
		无
  返回值：
		无
	说明：
		默认最大顶点个数为20
*/
template <class EleType>
CGraphAM<EleType>::CGraphAM(int Type):CGraph<EleType>()
{
	int i,j;

	m_VexCount=20;
	m_Type=Type;

	/*
	//创建顶点表
	this->m_Vexs=new char*[m_MaxVexCount];
	if(m_Vexs==NULL)
		return;

	for(i=0;i<m_MaxVexCount;i++)
		m_Vexs[i]=NULL;

	//创建邻接矩阵
	j=m_MaxVexCount*m_MaxVexCount;//m_MaxVexCount没有初始化?
	m_Arcs=new int[j];
	if(m_Arcs==NULL)
		return;
		
	//*/
	this->CGraphAM::CGraphAM();//会新建对象?
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
	功能：
		析构函数
	参数：
		无
	返回值：
		无
	说明：
		无
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
/****************************************************获取位置****************************************************/
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
/****************************************************获邻接点位置****************************************************/
template <class EleType>
int CGraphAM<EleType>::GetNeighborPositionOf(EleType Name,PositionStruct*& pPositions)
{
	int vexID=0,i,index;
	bool isFirst=true;
	PositionStruct *pNewPosition;
	pPositions=NULL;
	//找到顶点id
	for(i=0;i<m_VexCount;i++)
	{
		if(m_Vexs[i]==Name)
		{
			vexID=i;
			break;
		}
	}
	//找到邻接点
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
	功能：
		添加顶点
	参数：
		Name	[in]	名称
		VexID	[out]	顶点编号
	返回值：
		0	插入失败
		1	插入成功
	说明：
		无
*/
template <class EleType>
int CGraphAM<EleType>::InsertVex(EleType Name,int &VexID)
{
	if(m_InitOK==0)
	{
		cout<<"初始化失败"<<endl;
		return 0;	
	}
	//顶点已到达上限
	if(m_VexCount==m_MaxVexCount)
		return 0;

	/*
	//申请内存空间
	char *p;
	p=new char[strlen(Name)+1];
	if(p==NULL)
		return 0;
		
	strcpy(p,Name);
	m_Vexs[m_VexCount]=p;
	*/
	m_Vexs[m_VexCount]=Name;
	VexID=m_VexCount+1;
	SetPosition();//设置坐标
	m_VexCount++;

	return 1;

}
/******************************************************************设置坐标**************************************/
template <class EleType>
int CGraphAM<EleType>::SetPosition()
{
	int x,y;
	x=rand()%700+200;//随机数
	y=rand()%430+20;
	for(int i=1;i<=m_VexCount;i++)
	{
		/*
		do{
			x=rand();//随机数
			y=rand();
		}while(x>1000 || y>800);
		*/		
		double distance= (x-pPoints[i]->x)*(x-pPoints[i]->x) + (y-pPoints[i]->y)*(y-pPoints[i]->y);
		distance=sqrt(distance);
		if(distance<60)//从头再来
		{
			i=1;
			x=rand()%700+200;
			y=rand()%430+20;
		}
	}
	pPoints[m_VexCount]->x=x;
	pPoints[m_VexCount]->y=y;	//CString str; str.Format("位置:(%d,%d)",x,y); ::AfxMessageBox(str);
	return 1;
}
/*
	功能：
		删除顶点
	参数：
		Name	[in]		待删除顶点的名称
	返回值：
		0	删除失败
		1	删除成功
	说明：
		无
*/
template <class EleType>
int CGraphAM<EleType>::DeleteVex(EleType Name)
{
	if(m_InitOK==0)
		return 0;

	int VexID=-1,i,Index;
	//查找该顶点的编号
	for(i=0;VexID==-1 && i<m_VexCount;i++)
		if( Name==m_Vexs[i])
			VexID=i;

	//没找到该顶点
	if(VexID==-1)
		return 0;

	//先删除与该顶点有关的边
	switch(m_Type)
	{
	case 0:
		//删除该顶点所在行的非零值
		Index=VexID*m_MaxVexCount;
		for(i=0;i<m_MaxVexCount;i++)
		{
			if(m_Arcs[Index+i]==1)
			{
				m_ArcCount--;
				m_Arcs[Index+i]=0;
			}
		}
		//删除该顶点所在列的非零值
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

	//再删除该顶点
	for(i=VexID;i<m_VexCount-1;i++)
		m_Vexs[i]=m_Vexs[i+1];

	//顶点数减1
	m_VexCount--;

	return 1;
}

/*
	功能：
		删除顶点
	参数：
		VexID	[in]		顶点编号
	返回值：
		0	删除失败
		1	删除成功
	说明：
		该功能不启用，总返回0
*/
template <class EleType>
int CGraphAM<EleType>::DeleteVex(int VexID)
{
	return 0;
}

/*
	功能：
		获取顶点名称
	参数：
		VexID	[in]		顶点编号
		Name	[out]		顶点名称
	返回值：
		0	指定顶点不存在
		1	指定顶点存在，Name有意义
	说明：
		要求Name必须已经在调用函数中分配有空间
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
	功能：
		设置顶点名称
	参数：
		VexID	[in]	顶点编号
		NewName	[in]	顶点新名称
	返回值：
		0	操作失败
		1	操作成功
	说明：
		该操作无确认过程，应在调用函数中要求确认名称的修改，以免误操作
*/
template <class EleType>
int CGraphAM<EleType>::SetVex(int VexID,EleType NewName)
{
	if(m_InitOK==0)
		return 0;

	if(VexID>m_VexCount || VexID<1)
		return 0;
	/*
	//为新名称申请空间
	char *p;
	p=new char[strlen(NewName)+1];
	if(p==NULL)
		return 0;

	//释放原名称所占空间
	delete[] m_Vexs[VexID-1];

	strcpy(p,NewName);
	m_Vexs[VexID-1]=p;
	*/
	m_Vexs[VexID-1]=NewName;
	return 1;
}

/*
	功能：
		修改顶点名称
	参数：
		OldName	[in]	原名称
		NewName	[in]	新名称
	返回值：
		0	操作失败
		1	操作成功
	说明：
		该操作无确认过程，应在调用函数中要求确认名称的修改，以免误操作
*/
template <class EleType>
int CGraphAM<EleType>::SetVex(EleType OldName,EleType NewName)
{
	if(m_InitOK==0)
		return 0;

	//寻找与OldName名称相符的顶点
	int VexID=-1,Index;

	for(Index=0;VexID==-1 && Index<m_VexCount;Index++)
	{
		//if(strcmp(OldName,m_Vexs[Index])==0)
		if( OldName == m_Vexs[Index] )
		{
			VexID=Index;
		}
	}

	//未找到匹配顶点，退出
	if(VexID==-1)
		return 0;

	/*
	//申请新名称所用空间
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
	功能：
		添加一条边
	参数：
		FromVexID	[in]	起始顶点编号
		ToVexID		[in]	终止顶点编号
		Weight		[in]	边的权
	返回值：
		0	操作失败
		1	操作成功
	说明：
		无
*/
template <class EleType>
int CGraphAM<EleType>::InsertArc(int FromVexID,int ToVexID,int Weight)
{
	if(m_InitOK==0)
		return 0;

	//顶点编号不合法，不能添加
	if(FromVexID==ToVexID || FromVexID>m_VexCount || FromVexID<1 || ToVexID>m_VexCount || ToVexID<1)
		return 0;

	//不能加入自身到自身的边
	if(FromVexID==ToVexID)
		return 0;


	int InsertOK=0;
	int Index1,Index2;
	Index1=(FromVexID-1)*m_MaxVexCount+ToVexID-1;
	Index2=(ToVexID-1)*m_MaxVexCount+FromVexID-1;

	//根据图的类型，执行不同的插入操作
	switch(m_Type)
	{
	case 0://无向图
		if(m_Arcs[Index1]==0)
		{
			m_Arcs[Index1]=1;
			m_Arcs[Index2]=1;
			m_ArcCount++;
			InsertOK=1;
		}
		break;

	case 1://有向图
		if(m_Arcs[Index1]==0)
		{
			m_Arcs[Index1]=1;
			m_ArcCount++;
			InsertOK=1;
		}
		break;

	case 2://无向网
		if(m_Arcs[Index1]==INT_INFINITY)
		{
			m_Arcs[Index1]=Weight;
			m_Arcs[Index2]=Weight;
			m_ArcCount++;
			InsertOK=1;
		}
		break;

	case 3://有向网
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
	功能：
		删除一条边
	参数：
		FromVexID	[in]	起始顶点，编号从1开始
		ToVexID		[in]	终止顶点，编号从1开始
	返回值：
		
	说明：
		
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
	功能：
		获取边信息
	参数：
		FromVexID	[in]	开始顶点编号
		ToVexID		[in]	终止顶点编号
		Weight		[out]	1或权值，其含义取决于图类型
	返回值：
		0	操作失败
		1	操作成功，Weight有意义
	说明：
		无
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
	功能：
		设置边的信息
	参数：
		FromVexID	[in]	开始顶点编号
		ToVexID		[in]	终止顶点编号
		Weight		[in]	权值，仅对网有意义
	返回值：
		0	操作失败
		1	操作成功
	说明：
		仅当边存在时操作有意义。
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
	功能：
		深度优先遍历
	参数：
		无
	返回值：
		无
	说明：
		无
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
		int arc=i*m_MaxVexCount+index;//每行的第index列
		if(m_Arcs[arc]==1 && visited[i]==0)
			innerDFSTraverse(i);
	}
}

/*
	功能：
		广度优先遍历
	参数： 
		无
	返回值：
		无
	说明：
		无
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
	queue[queueRear]=index;//入队
	while((index=queue[queueHead])>=0 && queueHead<m_MaxVexCount)//?
	{
		queueHead++;//出队后对头指针后移
		queueHead=queueHead%m_MaxVexCount;//防止溢出
		cout<<this->m_Vexs[index]<<endl;//访问
		this->visited[index]=1;
		for(int i=0;i<m_MaxVexCount;i++)//遍历列
		{
			int location=(index*m_MaxVexCount)+(i);
			if(this->m_Arcs[location] && visited[i]==0)
			{
				queueRear++;
				queue[queueRear%m_MaxVexCount]=i;//入队
			}
		}
	}

	delete[] queue;
}
//对visit数组清零
template <class EleType>
void CGraphAM<EleType>::clearVisit(){
	for(int i=0;i<m_MaxVexCount;i++)
		visited[i]=0;
}
/*
	功能：
		将图保存到文件中
	参数：
		FileName	[in]	文件名称
	返回值：
		0	操作失败
		1	操作成功
	说明：
		文件为二进制格式
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

	//写入图类型
	fwrite(&m_Type,sizeof(int),1,fp);

	//写入顶点数及所有顶点信息
	int VexID,Length;
	fwrite(&m_VexCount,sizeof(int),1,fp);//1?
	for(VexID=0;VexID<m_VexCount;VexID++)
	{
		fwrite(&VexID,sizeof(int),1,fp);
		Length=sizeof(m_Vexs[VexID]);
		fwrite(&Length,sizeof(int),1,fp);//?
		fwrite(m_Vexs[VexID],Length,1,fp);
	}
	//写入边数及所有边信息
	int Row,Col,Index;
	fwrite(&m_ArcCount,sizeof(int),1,fp);
	switch(m_Type)
	{
	//对无向图只保存主对角线上方边信息
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

	//对有向图需要遍历整个矩阵
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

	//对无向网只保存主对角线上方边信息
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

	//对有向网需要遍历整个矩阵
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
	功能：
		从文件中读取图信息
	参数：
		FileName	[in]	文件名称
	返回值：
		0	操作失败
		1	操作成功
	说明：
		文件为二进制格式
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

	//读取图类型
	int Type;
	fread(&Type,sizeof(int),1,fp);

	//读取顶点数
	int VexCount;
	fread(&VexCount,sizeof(int),1,fp);
	//文件中包含的顶点数大于目前图中的最大顶点数，不允许
	//改进方式：修改目前图的设置，将其最大顶点数扩大至满足需求。可自行完成
	if(VexCount>m_MaxVexCount)
	{
		fclose(fp);
		return 0;
	}
	m_VexCount=VexCount;
	m_Type=Type;

	//读取所有顶点名称
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

	//读取边数及所有边信息
	int ArcCount;
	fread(&ArcCount,sizeof(int),1,fp);
	m_ArcCount=ArcCount;

	int Row,Col,Index,ArcID,Weight;
	switch(Type)
	{
	//无向图
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

	//有向图
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

	//无向网
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

	//有向网
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
