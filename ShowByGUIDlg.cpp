// ShowByGUIDlg.cpp : implementation file
//
#include "stdafx.h"
#include "ShowByGUI.h"
#include "ShowByGUIDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#include "List.cpp"

/////////////////////////////////////////////////////////////////////////////
//enum{list,stack,queue,tree,binTree,graph,search,sort,numOfStruc};
CString CShowByGUIDlg::typeStrOfStruct[]={"线性表","堆栈","队列","树","二叉树","图","查找","排序"};
//enum{seqList,linkList,withHeadLinkList,staticLinkList,cycleLinkList,numOfList};
CString CShowByGUIDlg::typeStrOfList[]={"顺序表","链表","专用头结点链表","静态链表","循环链表"};
//enum{seqStack,linkStack,numOfStack};
CString CShowByGUIDlg::typeStrOfStack[]={"顺序栈","链栈"};
//enum{childSibTree,numOfTree};
CString CShowByGUIDlg::typeStrOfTree[]={"孩子兄弟树"};
//enum{binTreeLink,numOfBinTree};
CString CShowByGUIDlg::typeStrOfBinTree[]={"链式二叉树"};
//enum{nonDirGraph,dirGraph,nonDirNet,dirNet,numOfGraph};
CString CShowByGUIDlg::typeStrOfGraph[]={"无向图","有向图","无向网","有向网"};


//int  CShowByGUIDlg::childrenNum[]={numOfList};
/////////////////////////////////////////////////////////////////////////////
// CShowByGUIDlg dialog

CShowByGUIDlg::CShowByGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowByGUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowByGUIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShowByGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowByGUIDlg)
	DDX_Control(pDX, IDC_STATIC_value, m_ValueLabel);
	DDX_Control(pDX, IDC_STATIC_location, m_LocationLabel);
	DDX_Control(pDX, IDC_EDIT_endLocation, m_EndLocationTextField);
	DDX_Control(pDX, IDC_EDIT_location, m_LocationTextField);
	DDX_Control(pDX, IDC_EDIT_value, m_ValueTextField);
	DDX_Control(pDX, IDC_TREE_choice, m_TestChoiceTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowByGUIDlg, CDialog)
	//{{AFX_MSG_MAP(CShowByGUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_choice, OnDblClickTreeChoice)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_sure, OnClickButtonSure)
	ON_COMMAND(ID_MENUITEM_insertArc, OnMenuInsertGraphArc)
	ON_COMMAND(ID_MENUITEM_insertVex, OnOnMenuInsertGraphVex)
	ON_COMMAND(ID_MENUITEM_searchVex, OnMenuSearchGraphVex)
	ON_COMMAND(ID_MENUITEM_updateVex, OnMenuUpdateGraphVex)
	ON_COMMAND(ID_MENUITEM_deleteVex, OnMenuDeleteGraphVex)
	ON_COMMAND(ID_MENUITEM_searchArc, OnMenusearchGraphArc)
	ON_COMMAND(ID_MENUITEM_updateWeight, OnMenuUpdateGraphWeight)
	ON_COMMAND(ID_MENUITEM_deleteArc, OnMenuDeleteGraphArc)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_OnMenuInsertList, OnMenuInsertList)
	ON_COMMAND(ID_OnMenuUpdatatList, OnMenuUpdatatList)
	ON_COMMAND(ID_OnMenuSearchList, OnMenuSearchList)
	ON_COMMAND(ID_OnMenuDeleteList, OnMenuDeleteList)
	ON_COMMAND(ID_MENUITEM_insertRightChild, OnMEenuInsertRightChild)
	ON_COMMAND(ID_MENUITEM_insertLeftChild, OnMenuInsertLeftChild)
	ON_COMMAND(ID_MENUITEM_exit, OnMenuExit)
	ON_COMMAND(ID_MENUITEM_about, OnMenuAbout)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowByGUIDlg message handlers

BOOL CShowByGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	this->SetWindowText("图形界面数据结构测试");
	
	InitTestChoiceTree();
	pDataStructure=NULL;	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShowByGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		AboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShowByGUIDlg::OnPaint() 
{
	CPaintDC dc(this);
	if (IsIconic())
	{
		//CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	Refresh(dc);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShowByGUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/************************************************以下为自定义方法**********************************************************/
//释放内存
void CShowByGUIDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	if(pDataStructure!=NULL)
		delete pDataStructure;	
}
//初始化选择列表
void CShowByGUIDlg::InitTestChoiceTree()
{
	imgList.Create(16,16,ILC_COLOR,2,2);//?
	imgList.Add( AfxGetApp()->LoadIcon(IDI_ICON_structImg1) );
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_structImg2));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_leaf));
	m_TestChoiceTree.SetImageList(&imgList,TVSIL_NORMAL);
	for(int i=0;i<numOfStruct;i++)
	{
		treeItemOfStruct[i]=this->m_TestChoiceTree.InsertItem(typeStrOfStruct[i],1,1);//TVSIL_STATE	TVSIL_NORMAL
		m_TestChoiceTree.SetItemData(treeItemOfStruct[i],i);
	}
	int k;
	//线性表
	for(k=0;k<numOfList;k++)
	{
		treeItemOfList[k]=this->m_TestChoiceTree.InsertItem(typeStrOfList[k],2,2,treeItemOfStruct[list]);
		m_TestChoiceTree.SetItemData(treeItemOfList[k],k);
	}
	//堆栈
	for(k=0;k<numOfStack;k++)
	{
		treeItemOfStack[k]=this->m_TestChoiceTree.InsertItem(typeStrOfStack[k],2,2,treeItemOfStruct[stack]);
		m_TestChoiceTree.SetItemData(treeItemOfStack[k],k);
	}
	//树
	for(k=0;k<numOfTree;k++)
	{
		treeItemOfTree[k]=this->m_TestChoiceTree.InsertItem(typeStrOfTree[k],2,2,treeItemOfStruct[tree]);
		m_TestChoiceTree.SetItemData(treeItemOfTree[k],k);
	}
	//二叉树
	for(k=0;k<numOfBinTree;k++)
	{
		treeItemOfBinTree[k]=this->m_TestChoiceTree.InsertItem(typeStrOfBinTree[k],2,2,treeItemOfStruct[binTree]);
		m_TestChoiceTree.SetItemData(treeItemOfBinTree[k],k);
	}
	//图
	for(k=0;k<numOfGraph;k++)
	{
		treeItemOfGraph[k]=this->m_TestChoiceTree.InsertItem(typeStrOfGraph[k],2,2,treeItemOfStruct[graph]);
		m_TestChoiceTree.SetItemData(treeItemOfGraph[k],k);
	}
	controlType=0;
}
//双击监听
void CShowByGUIDlg::OnDblClickTreeChoice(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	HTREEITEM item=m_TestChoiceTree.GetSelectedItem();		
	//CString str;str.Format("%d",m_TestChoiceTree.ItemHasChildren(item));  AfxMessageBox(str,100,100);
	//无孩子,即为叶子节点
	if(m_TestChoiceTree.ItemHasChildren(item)==0)
	{
		HTREEITEM parentItem=m_TestChoiceTree.GetParentItem(item);
		if(parentItem==NULL)
			return;
		structureType=m_TestChoiceTree.GetItemData(parentItem);
		itemType=m_TestChoiceTree.GetItemData(item);
		if(pDataStructure!=NULL)
			delete pDataStructure;
		DataStructureTest<CString> *pTest;
		pTest=new DataStructureTest<CString>();
		pDataStructure=pTest->Test(structureType,itemType);
		delete pTest;
		if(pDataStructure)
		{
			Invalidate();
			AfxMessageBox("初始化成功!",100,100);
		}
		else
			AfxMessageBox("初始化失败!",100,100);
		/*
		HTREEITEM childItem;
		//获取父节点索引
		for(int i=0;i<numOfStruct;i++)
		{			
			if(m_TestChoiceTree.GetParentItem(item)==treeItemOfStruct[i])
			{
				//AfxMessageBox(m_TestChoiceTree.GetItemText(item),100,100);
				//获取叶子节点索引
				for(int k=0;k<childrenNum[i];k++)
				{
					childItem=m_TestChoiceTree.GetChildItem(treeItemOfStruct[i]);						
					if(item==childItem)
					{
						pTest->Test(i,k);
						break;
					}
					childItem=m_TestChoiceTree.GetNextItem(childItem,TVGN_NEXT);
				}
			}
		}
		*/
	}
	*pResult = 0;
}

//确定按钮监听
void CShowByGUIDlg::OnClickButtonSure() 
{
	if(pDataStructure==NULL)
	{
		AfxMessageBox("您尚未选择测试类型!",100,100);
		return;
	}	
	CString locationStr,valueStr;
	int location,returnValue;
	this->m_LocationTextField.GetWindowText(locationStr);	
	this->m_ValueTextField.GetWindowText(valueStr);	
		
	CString str;
	
	//查询
	if(controlType==2)		
	{
		Invalidate();
		return;
	}
	switch(structureType)
	{//list,stack,queue,tree,binTree,graph,search,sort
		case list:
			location=atoi(locationStr.GetBuffer(locationStr.GetLength()+1));
			//插入
			if(controlType==0)
			{				
				pDataStructure->Insert(location,valueStr);//不应该根据位置来查找吧???
			}
			//修改
			else if(controlType==1)
			{
				pDataStructure->Delete(location,locationStr);//修改某位置的值
				pDataStructure->Insert(location,valueStr);

			}
			//删除
			else if(controlType==3)
			{
				pDataStructure->Delete(location,valueStr);//
			}
			break;
		case stack:			
			if(controlType==0)
			{
				pDataStructure->Push(valueStr);//压栈
			}
			break;
		case tree:
			//插入
			if(controlType==0)
			{
				returnValue=pDataStructure->Insert(locationStr,valueStr); 
				//	str.Format("返回值%d!",returnValue);	AfxMessageBox(str,100,100);
			
				switch(returnValue)
				{
					case 0:
						::AfxMessageBox("内存不足!",100,100);
						return;
					case -1:
						AfxMessageBox("插入值重复!!",100,100);
						return;
					default:
						break;
				}
				InitPosition(valueStr);//为刚插入节点初始化该显示的坐标
			}			
			break;
		case binTree:
			//插入左孩子
			if(controlType==20)
			{
				returnValue=pDataStructure->InsertL(locationStr,valueStr);
			}
			//插入又孩子
			else if(controlType==21)
			{
				returnValue=pDataStructure->InsertR(locationStr,valueStr);
			}
			InitPosition(valueStr);
			break;
		case graph:
		{
			//returnValue=pDataStructure->InsertVex(valueStr.GetBuffer(locationStr.GetLength()+1),location);
			
			//插入边
			if(controlType==15)
			{
				CString locationEndStr;
				this->m_EndLocationTextField.GetWindowText(locationEndStr);
				location=atoi(locationStr.GetBuffer(locationStr.GetLength()+1));
				int locationEnd=atoi(locationEndStr.GetBuffer(locationEndStr.GetLength()+1));
				int value=0;
				if(valueStr!="")
					value=atoi(valueStr.GetBuffer(valueStr.GetLength()+1));
				returnValue=pDataStructure->InsertArc(location,locationEnd,value);
				InitPosition(location,locationEnd);//为刚插入节点初始化该显示的坐标
			}	
			//插入顶点
			else
				returnValue=pDataStructure->InsertVex(valueStr,location);
			
				//str.Format("返回值:%d ",location);	AfxMessageBox(str,100,100);		
			break;
		}
		default:
			break;
	}	
	
	//UpdateWindow();//??
	//Invalidate();
	pThread=AfxBeginThread(PaintThread,	this);//调用线程函数
	/*
	int k,max=0,line=0,width=20,height=30,hOffset=30,vOffset=20,textOffset=3,base=240;
	CClientDC dc(this);
	dc.SetTextAlign(TA_CENTER|TA_TOP);	
	//this->ValidateRect(&rect);
	dc.Rectangle(&rect);
	for(int i=1; pDataStructure->Get(i,locationStr)>0;i++)//((LIST<CString>*)pDataStructure)
	{	
		k=4*(i-1);
		k-=max;
		//换行
		if(base+width*k+hOffset>m_nWidth-5)
		{
			line++;
			max=k*line;
			k=k-max;
			height+=30;
		}		
		dc.Rectangle(base+width*k-hOffset,height,base+width*k+hOffset,height+vOffset);
		dc.TextOut(base+width*k,height+textOffset,locationStr);
	}	
	*/
}
//界面刷新,画图
void CShowByGUIDlg::Refresh(CPaintDC &dc)
{
	if(pDataStructure==NULL)
		return;
	CString returnValue;
	int k=0,max=0,line=0,width=20,realHeight=30,height=30,hOffset=30,vOffset=20,textOffset=3;

	dc.SetTextAlign(TA_CENTER|TA_TOP);
	dc.SetBkColor(RGB(255,255,255));
	CRect rect(base-50,10,m_nWidth-5,m_nHeight-5);
	//this->ValidateRect(&rect);
	dc.Rectangle(&rect);	
	
	int i=0,level;	
	int x,y;
	CString queueForTree[100];
	int head=-1,rear=0;
	switch(structureType)
	{
		//list,stack,queue,tree,binTree,graph,search,sort
		//线性表
	case list:
		//查询
		if(controlType==2)
		{
			CString locationStr,valueStr;
			this->m_LocationTextField.GetWindowText(locationStr);	
			this->m_ValueTextField.GetWindowText(valueStr);
			int position=atoi(locationStr.GetBuffer(locationStr.GetLength()+1));
			pDataStructure->Get(position,returnValue);
			CString str;
			str="您查询位置的值是："+returnValue;
			dc.TextOut(270,13,str);
		}
		else
		{
			switch(itemType)
				{
				case seqList:
				{
					hOffset=40;	
					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)
					{	
						k=4*(i-1);
						k-=max;
						//换行
						if(base+width*k+hOffset>m_nWidth-5)
						{
							line++;
							max=k*line;
							k=k-max;
							realHeight+=60;							
							/*
							if(height>m_nHeight)
							{
								m_nTotalHeight=height;
								m_nScrollHeight=m_nTotalHeight-m_nHeight;
								SetScrollHeight(m_nScrollHeight);
							}*/
							if(realHeight+vOffset+20>m_nHeight)
							{
								SetTotalHeight(realHeight+vOffset+25);								
							}							
						}
						height=realHeight-offset;
						if(height < 30 || height+vOffset+20>m_nHeight)								
						{
							continue;
						}
						dc.Rectangle(base+width*k-hOffset,height,base+width*k+hOffset,height+vOffset);
						dc.SetBkColor(RGB(255,255,255));
						dc.TextOut(base+width*k,height+textOffset,returnValue);	
						//打印下标	
						char s[40];
						wsprintf(s,"%d",i-1);
						dc.TextOut(base+width*k,height+textOffset+20,s);
					}
				break;
				}
				case withHeadLinkList:
				{
					hOffset=30;	
					//头结点
					dc.Rectangle(base-hOffset,height,base+10,height+vOffset);
					dc.Rectangle(base+10,height,base+hOffset,height+vOffset);
					dc.TextOut(base-10,height+textOffset,"first");
					dc.TextOut(base,height+textOffset+20,"0");
/*					//开始状态链表为空

					dc.MoveTo(base+18,height+5);
					dc.LineTo(base+14,height+15);
					dc.MoveTo(base+18,height+5);
					dc.LineTo(base+22,height+15);
*/
					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)//((LIST<CString>*)pDataStructure)
					{	
						k=4*(i-1);
						k-=max;
						//换行
						if(base+width*k+hOffset>m_nWidth-5)
						{
							line++;
							max=k*line;
							k=k-max;
							realHeight+=60;						
							
							if(realHeight+vOffset+20>m_nHeight)
							{
								SetTotalHeight(realHeight+vOffset+25);								
							}							
						}
						height=realHeight-offset;
						if(height < 30 || height+vOffset+20>m_nHeight)								
						{
							continue;
						}
						dc.Rectangle(base+width*(k+4)-hOffset,height,base+width*(k+4)+10,height+vOffset);
						dc.Rectangle(base+width*(k+4)+10,height,base+width*(k+4)+hOffset,height+vOffset);
						dc.SetBkColor(RGB(255,255,255));
						dc.TextOut(base+width*(k+4),height+textOffset,returnValue);	

						//打印下标
						char s[40];
						wsprintf(s,"%d",i);
						dc.TextOut(base+width*(k+4),height+textOffset+20,s);

						//打印箭头
						dc.MoveTo(base+width*k+hOffset,height+10);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
						dc.MoveTo(base+width*k+hOffset+8,height+8);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
						dc.MoveTo(base+width*k+hOffset+8,height+12);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
					}
					if(i!=1)
					{
						dc.MoveTo(base+width*(k+4)+18,height+5);
						dc.LineTo(base+width*(k+4)+14,height+15);
						dc.MoveTo(base+width*(k+4)+18,height+5);
						dc.LineTo(base+width*(k+4)+22,height+15);					
					}
					else
					{
						dc.MoveTo(base+18,height+5);
						dc.LineTo(base+14,height+15);
						dc.MoveTo(base+18,height+5);
						dc.LineTo(base+22,height+15);
					}
				}				
				break;
				case cycleLinkList:
				{
					hOffset=30;	
					//头结点
					dc.Rectangle(base-hOffset,height,base+10,height+vOffset);
					dc.Rectangle(base+10,height,base+hOffset,height+vOffset);
					dc.TextOut(base-10,height+textOffset,"first");
					dc.TextOut(base,height+textOffset+20,"0");

					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)//((LIST<CString>*)pDataStructure)
					{	
						k=4*(i-1);
						k-=max;
						//换行
						if(base+width*k+hOffset>m_nWidth-5)
						{
							line++;
							max=k*line;
							k=k-max;
							realHeight+=60;						
							
							if(realHeight+vOffset+20>m_nHeight)
							{
								SetTotalHeight(realHeight+vOffset+25);								
							}							
						}
						height=realHeight-offset;
						if(height < 30 || height+vOffset+20>m_nHeight)								
						{
							continue;
						}
						dc.Rectangle(base+width*(k+4)-hOffset,height,base+width*(k+4)+10,height+vOffset);
						dc.Rectangle(base+width*(k+4)+10,height,base+width*(k+4)+hOffset,height+vOffset);
						dc.SetBkColor(RGB(255,255,255));
						dc.TextOut(base+width*(k+4),height+textOffset,returnValue);	

						//打印下标
						char s[40];
						wsprintf(s,"%d",i);
						dc.TextOut(base+width*(k+4),height+textOffset+20,s);

						//打印箭头
						dc.MoveTo(base+width*k+hOffset,height+10);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
						dc.MoveTo(base+width*k+hOffset+8,height+8);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
						dc.MoveTo(base+width*k+hOffset+8,height+12);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
					}

					//指向头结点
					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)//((LIST<CString>*)pDataStructure)
					{	
						k=4*(i-1);
						k-=max;
						//换行
						if(base+width*k+hOffset>m_nWidth-5)
						{
							line++;
							max=k*line;
							k=k-max;
							realHeight+=60;							
							
							if(realHeight+vOffset+20>m_nHeight)
							{
								SetTotalHeight(realHeight+vOffset+25);								
							}							
						}
						height=realHeight-offset;
						if(height < 30 || height+vOffset+20>m_nHeight)								
						{
							continue;
						}
					}
					if(i!=1)
					{
						dc.MoveTo(base+width*(k+4)+hOffset-10,height+vOffset);
						dc.LineTo(base+width*(k+4)+hOffset-10,height+vOffset+20);
						dc.MoveTo(base+width*(k+4)+hOffset-10,height+vOffset+20);
						dc.LineTo(base-25,height+vOffset+20);
						dc.MoveTo(base-25,height+vOffset+20);
						dc.LineTo(base-25,50);
						//箭头
						dc.MoveTo(base-30,55);
						dc.LineTo(base-25,50);
						dc.MoveTo(base-20,55);
						dc.LineTo(base-25,50);
						dc.LineTo(base-25,50);
					}
					else
					{
						//链表为空是 的指针指向
						dc.MoveTo(base+15,height+20);
						dc.LineTo(base+15,height+40);
						dc.MoveTo(base+15,height+40);
						dc.LineTo(base-15,height+40);
						dc.MoveTo(base-15,height+40);
						dc.LineTo(base-15,height+20);
						dc.MoveTo(base-15,height+20);
						dc.LineTo(base-10,height+25);
						dc.MoveTo(base-15,height+20);
						dc.LineTo(base-20,height+25);
					}
				}				
				break;				

				default:
				{			
					hOffset=30;
					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)//((LIST<CString>*)pDataStructure)
					{	
						k=4*(i-1);
						k-=max;
						//换行
						if(base+width*k+hOffset>m_nWidth-5)
						{
							line++;
							max=k*line;
							k=k-max;
							realHeight+=60;							
							
							if(realHeight+vOffset+20>m_nHeight)
							{
								SetTotalHeight(realHeight+vOffset+25);								
							}												
						}
						height=realHeight-offset;
						if(height < 30 || height+vOffset+20>m_nHeight)								
						{
							//returnValue.Format("height=%d,m_nHeight=%d",height,m_nHeight); dc.TextOut(400,130,returnValue);
							continue;
						}	
						dc.Rectangle(base+width*k-hOffset,height,base+width*k+10,height+vOffset);
						dc.Rectangle(base+width*k+10,height,base+width*k+hOffset,height+vOffset);
						dc.SetBkColor(RGB(255,255,255));
						dc.TextOut(base+width*k,height+textOffset,returnValue);
						//打印箭头
						if(i!=1)
						{
							dc.MoveTo(base+width*(k-4)+hOffset,height+10);
							dc.LineTo(base+width*k-hOffset,height+10);
							dc.MoveTo(base+width*(k-4)+hOffset+8,height+8);
							dc.LineTo(base+width*k-hOffset,height+10);
							dc.MoveTo(base+width*(k-4)+hOffset+8,height+12);
							dc.LineTo(base+width*k-hOffset,height+10);
						}
					}	
					if(i!=1)//尾指针为空
					{
						dc.MoveTo(base+width*k+18,height+5);
						dc.LineTo(base+width*k+14,height+15);
						dc.MoveTo(base+width*k+18,height+5);
						dc.LineTo(base+width*k+22,height+15);	
					}
				}				
				break;
			}
			break;//end of switch(itemType) 	
		}
		break;//end of  case list	
		
		//堆栈
		case stack:				
			for(i=1; pDataStructure->GetElement(i,returnValue) >0 ;i++)
			{	
				//换行
				realHeight=30*(15-i);
				height=realHeight-offset;
					
				if(realHeight+vOffset+20>m_nHeight)
				{
					SetTotalHeight(realHeight+vOffset+25);								
				}
				if(height < 30 || height+vOffset+20>m_nHeight)								
				{
					continue;
				}
					
				dc.Rectangle(base+width-hOffset,height,base+width+hOffset,height+vOffset);
				dc.TextOut(base+width,height+textOffset,returnValue);
			}
			break;
		//树
		case tree:
			//根节点值
			if(pDataStructure->Root(returnValue,x,y)!=1)
				return;				
			dc.Ellipse(x-18,y-10,x+21,y+25);
			dc.TextOut(x,y,returnValue);		
			//入队
			queueForTree[rear++]=returnValue;
			//层序遍历,与用指针相比的优缺点?
			while(1)
			{
				/*
				//第一个孩子值
				if(pDataStructure->GetFirstChildOf(returnValue,returnValue,x,y)==0)
				{
					if(head==rear)
						break;
					returnValue=queueForTree[++head];
					continue;
				}
				level=pDataStructure->GetLevelOf(returnValue);//获取该值的层号				
				if(x==0 && y==0)
				{
					pDataStructure->SetPosition(returnValue,base+width*k,height*level+textOffset);
					dc.TextOut(base+width*k,height*level+textOffset,returnValue);	
				}
				else
					dc.TextOut(x,y,returnValue);
				queueForTree[rear++]=returnValue;
				//兄弟值
				for(i=1; pDataStructure->GetNextSibOf(returnValue,returnValue,x,y)>0;i++)
				{
					k=4*i;
					//dc.TextOut(base+width*k,height*level+textOffset,returnValue);
					//设置坐标
					if(x==0 && y==0)
					{
						pDataStructure->SetPosition(returnValue,base+width*k,height*level+textOffset);
						dc.TextOut(base+width*k,height*level+textOffset,returnValue);	
					}
					//按x,y画图
					else
						dc.TextOut(x,y,returnValue);
					//入队
					queueForTree[rear++]=returnValue;
				}
				//出队
				returnValue=queueForTree[++head];
				/*/
				//保存将父亲节点坐标
				pDataStructure->GetPositionOf(returnValue,startPositionX,startPositionY);
				startPositionY+=20;
				//判断是否有第一个孩子值
				if(pDataStructure->GetFirstChildOf(returnValue,returnValue,x,y)==0)
				{
					if(head==rear)//队空
						break;
					returnValue=queueForTree[++head];//没有孩子时,出队
					continue;
				}
				dc.MoveTo(startPositionX,startPositionY);
				dc.LineTo(x,y);
				dc.Ellipse(x-18,y-10,x+21,y+25);
				dc.TextOut(x,y,returnValue);
				/*
				height=y-offset;
				if(y+25>m_nHeight)
				{
					SetTotalHeight(y+30);
				}				
				if(height < 30 || height+vOffset+20>m_nHeight)								
				{
					return;
				}*/
				queueForTree[rear++]=returnValue;
				//兄弟值
				for(i=1; pDataStructure->GetNextSibOf(returnValue,returnValue,x,y)>0;i++)
				{
					dc.MoveTo(startPositionX,startPositionY);
					dc.LineTo(x,y);
					dc.Ellipse(x-18,y-10,x+21,y+25);
					dc.TextOut(x,y,returnValue);
					//入队
					queueForTree[rear++]=returnValue;
				}
				//出队
				returnValue=queueForTree[++head];
				//*/
			}
			break;
		//二叉树
		case binTree:			
		{			
			if(pDataStructure->Root(returnValue,x,y)!=1)
				return;	
			CString parentValue=returnValue;
		    dc.Ellipse(x-18,y-10,x+21,y+25);
			dc.TextOut(x,y,returnValue);		
			while(rear!=head)
			{ 
				pDataStructure->GetPositionOf(parentValue,startPositionX,startPositionY);
				startPositionY+=20;
				if(pDataStructure->GetLeftChildOf(parentValue,returnValue,x,y))
				{
					//入队
					queueForTree[rear++]=returnValue;
					dc.MoveTo(startPositionX,startPositionY);
					dc.LineTo(x,y);
					dc.Ellipse(x-18,y-10,x+21,y+25);
					dc.TextOut(x,y,returnValue);
					/*
					height=y-offset;
					if(y+25>m_nHeight)
					{
						SetTotalHeight(y+30);
					}				
					if(height < 30 || height+vOffset+20>m_nHeight)								
					{
						return;
					}*/
				}
				if(pDataStructure->GetRightChildOf(parentValue,returnValue,x,y))
				{
					queueForTree[rear++]=returnValue;
					dc.MoveTo(startPositionX,startPositionY);
					dc.LineTo(x,y);
					dc.Ellipse(x-18,y-10,x+21,y+25);
					dc.TextOut(x,y,returnValue);
					/*
					height=y-offset;
					if(y+25>m_nHeight)
					{
						SetTotalHeight(y+30);
					}				
					if(height < 30 || height+vOffset+20>m_nHeight)								
					{
						return;
					}*/
				}
				parentValue=queueForTree[++head];
			}				 
		}
		break;
		//图,超过20崩溃?
		case graph:	
			i=1;
			while(pDataStructure->GetVex(i,returnValue))
			{
				pDataStructure->GetPositionOf(i,x,y);				
				//画边
				PositionStruct *pPositions;
				pDataStructure->GetNeighborPositionOf(returnValue,pPositions);
				while(pPositions)
				{
					dc.MoveTo(x,y);
					dc.LineTo(pPositions->x,pPositions->y);
					pPositions=pPositions->pNext;
				}
				//画顶点
				dc.Ellipse(x-18,y-10,x+21,y+25);
				dc.TextOut(x,y,returnValue);
				i++;
			}
			break;
		default:
			break;
	}	
}
//动画演示
void CShowByGUIDlg::PaintLine()
{
	temp_startPositionX=startPositionX+temp_endOffsetX;
	//temp_startPositionY = k * temp_startPositionX + temp_startPositionX;
	temp_startPositionY=startPositionY+temp_endOffsetY;
	
	bool isLarger=(endPositionX>startPositionX);
	if(isLarger)
	{
		temp_endOffsetX++;//相对于startPositionX的偏移量		
	}
	else 
	{
		temp_endOffsetX--;		
	}
	temp_endOffsetY = slope * temp_endOffsetX;	

	int temp_endPositionX= startPositionX+temp_endOffsetX;
	int temp_endPositionY= startPositionY+temp_endOffsetY;
	if(isLarger)
	{
		if(temp_endPositionX-endPositionX >0)//abs()
			isFinished=true;
	}
	else
	{
		if(temp_endPositionX-endPositionX <0)
			isFinished=true;
	}
	//测试画线
	CClientDC dc(this);
	dc.MoveTo(temp_startPositionX ,temp_startPositionY);
	//dc.MoveTo(240 ,30);
	dc.LineTo(temp_endPositionX,temp_endPositionY);
	//	CString str;str.Format("k=%f",k);dc.TextOut(400,100,str);
	//Invalidate();
}
//初始化 树/二叉树 节点位置
void CShowByGUIDlg::InitPosition(CString locationStr)
{
	CString parentValue;
	if(pDataStructure->Parent(locationStr,parentValue)==2)
	{
		//为第一个节点
		pDataStructure->SetPositionOf(locationStr,540,20,800);
		isFinished=true;
		return;
	}
	//获取父亲节点坐标
	pDataStructure->GetPositionOf(parentValue,startPositionX,startPositionY);
	startPositionY+=20;
	//获取本节点坐标
	pDataStructure->GetPositionOf(locationStr,endPositionX,endPositionY);

	SetSlope();

	isFinished=false;
}
//初始化图节点位置
void CShowByGUIDlg::InitPosition(int locationStartVex,int locationEndVex)
{	
	//if(pDataStructure->GetPositionOf(location-1,startPositionX,startPositionY)!=1)//先的找到相邻节点(location-1作为测试)
	if(pDataStructure->GetPositionOf(locationStartVex,startPositionX,startPositionY)!=1)
	{
		isFinished=true;//location为第一个节点
		return;
	}
	if(pDataStructure->GetPositionOf(locationEndVex,endPositionX,endPositionY)!=1)
		return;

	SetSlope();
	
	isFinished=false;//未画完时若继续添加则会出现安全问题?
}
//设置斜率
void CShowByGUIDlg::SetSlope()
{
	temp_startPositionX=startPositionX;
	temp_startPositionY=startPositionY;	
	
	temp_endOffsetX=0;
	temp_endOffsetY=0;
	
	double a=1;
	slope=(endPositionY*a-startPositionY) / (endPositionX-startPositionX);
}
//启动线程
void CShowByGUIDlg::Run()
{	
	while(! isFinished)
	{	
		Sleep(10);//休眠一段时间
		PaintLine();
		//AfxMessageBox("线程...",100,100);
	}
	Invalidate();	
}

//画图线程
UINT PaintThread(LPVOID pParam) 
{
	CShowByGUIDlg* pDlg=(CShowByGUIDlg*)pParam;
	pDlg->Run();
	return 0;
}




//设置操作类型
void CShowByGUIDlg::SetControlType()
{
	m_EndLocationTextField.ShowWindow(SW_HIDE);
	switch(controlType)
	{
	case 0:
		m_LocationLabel.SetWindowText("插入位置:");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("插入值:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	
	case 1:
		m_LocationLabel.SetWindowText("修改位置:");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("修改为:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	case 2:
		m_LocationLabel.SetWindowText("查询位置");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("");
		m_ValueTextField.ShowWindow(SW_HIDE);	
		break;
	case 3:
		m_LocationLabel.SetWindowText("删除位置:");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("");
		m_ValueTextField.ShowWindow(SW_HIDE);
			
		break;
    //图的操作
	//插入顶点
	case 11:
		m_LocationLabel.SetWindowText("");
		m_ValueLabel.SetWindowText("插入顶点的值");
		m_LocationTextField.ShowWindow(SW_HIDE);
		break;
	//查询顶点
	case 12:
		m_LocationLabel.SetWindowText("");
		m_ValueLabel.SetWindowText("要查寻值");
		m_LocationTextField.ShowWindow(SW_HIDE);
		break;
	//修改顶点的值
	case 13:
		m_LocationLabel.SetWindowText("待修改顶点");
		m_ValueLabel.SetWindowText("修改后的值");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//删除顶点的值
	case 14:
		m_LocationLabel.SetWindowText("");
		m_ValueLabel.SetWindowText("待删除顶点");
		m_LocationTextField.ShowWindow(SW_HIDE);
		break;
	//插入边
	case 15:
		m_LocationLabel.SetWindowText("边始末节点");				
		m_ValueLabel.SetWindowText("边的权值");
		m_LocationTextField.ShowWindow(SW_SHOW);
		m_EndLocationTextField.ShowWindow(SW_SHOW);
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//查询边
	case 16:
		m_LocationLabel.SetWindowText("边的始节点");
		m_ValueLabel.SetWindowText("边的末节点");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//修改边权值
	case 18:
		m_LocationLabel.SetWindowText("边的始节点");
		m_ValueLabel.SetWindowText("边的末节点");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//删除边
	case 19:
		m_LocationLabel.SetWindowText("边的始节点");
		m_ValueLabel.SetWindowText("边的末节点");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//二叉树
	case 20:
		m_LocationLabel.SetWindowText("插入根位置:");
		m_ValueLabel.SetWindowText("插入左孩子:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	case 21:
		m_LocationLabel.SetWindowText("插入根位置:");
		m_ValueLabel.SetWindowText("插入右孩子:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	default:
		break;

	}	
}

//菜单监听,选择操作类型

void CShowByGUIDlg::OnMenuInsertList() 
{
	// TODO: Add your command handler code here
	controlType=0;
	SetControlType();
}

void CShowByGUIDlg::OnMenuUpdatatList() 
{
	// TODO: Add your command handler code here
	controlType=1;
	SetControlType();
	
}

void CShowByGUIDlg::OnMenuSearchList() 
{
	// TODO: Add your command handler code here
	controlType=2;
	SetControlType();
	
}

void CShowByGUIDlg::OnMenuDeleteList() 
{
	// TODO: Add your command handler code here
	controlType=3;
	SetControlType();
	
}
void CShowByGUIDlg::OnOnMenuInsertGraphVex() 
{
	// TODO: Add your command handler code here
	controlType=11;
	SetControlType();
}

void CShowByGUIDlg::OnMenuSearchGraphVex() 
{
	// TODO: Add your command handler code here
	controlType=12;
	SetControlType();
}

void CShowByGUIDlg::OnMenuUpdateGraphVex() 
{
	// TODO: Add your command handler code here
	controlType=13;
	SetControlType();
}
void CShowByGUIDlg::OnMenuDeleteGraphVex() 
{
	// TODO: Add your command handler code here
	controlType=14;
	SetControlType();
}
void CShowByGUIDlg::OnMenuInsertGraphArc() 
{
	// TODO: Add your command handler code here
	controlType=15;
	SetControlType();
}
/////////////////////////////////////////////////
/*
void CShowByGUIDlg::OnMenuInsertArc() 
{
	CRect rect;
	m_LocationTextField.GetRect(&rect);
	CRect tmp_rect(rect.left,rect.top,rect.right/2,rect.bottom);
	rect=tmp_rect;
	this->m_LocationTextField.SetRect(&rect);
	controlType=15;
}
*/
void CShowByGUIDlg::OnMenusearchGraphArc() 
{
	// TODO: Add your command handler code here
	controlType=16;
	SetControlType();
}

void CShowByGUIDlg::OnMenuUpdateGraphWeight() 
{
	// TODO: Add your command handler code here
	controlType=18;
	SetControlType();
}

void CShowByGUIDlg::OnMenuDeleteGraphArc() 
{
	// TODO: Add your command handler code here
	controlType=19;
	SetControlType();
}
void CShowByGUIDlg::OnMEenuInsertRightChild() 
{
	// TODO: Add your command handler code here
	controlType=21;
    SetControlType();
}

void CShowByGUIDlg::OnMenuInsertLeftChild() 
{
	// TODO: Add your command handler code here
	controlType=20;
	SetControlType();    

}
void CShowByGUIDlg::OnMenuExit() 
{
	// TODO: Add your command handler code here
	this->OnCancel();
}
void CShowByGUIDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	AboutDlg dlg;
	dlg.DoModal();
}
//弹出菜单
void CShowByGUIDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here	

}
//响应滚动条
void CShowByGUIDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int prePosition,distance;	
	CRect rc(base-50,0,m_nWidth,m_nHeight);
	/*
	SCROLLINFO scroll;
	GetScrollInfo(SB_VERT,&scroll,SIF_ALL);	
	*/
	prePosition=GetScrollPos(SB_VERT);	
	//CString str;str.Format("nPos%d,m_nHeight%d",nPos,m_nHeight);CClientDC dc(this);dc.TextOut(300,100,str);
	switch(nSBCode)
	{
	case SB_THUMBTRACK:
		SetScrollPos(SB_VERT,nPos,true);
		distance=prePosition-nPos;
		offset=nPos;
		//ScrollWindow(0, m_nScrollHeight * offset/m_nScrollHeight,&rc);
		//ScrollWindow(0,  distance ,&rc);//????????????
		Invalidate();
		break;	
	default:
		break;
	}
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
//监听窗口尺寸改变
void CShowByGUIDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	base=240;
	offset=0;
	CRect rc;
	/*GetClientRect(&rc);
	m_nWidth=rc.Width();
	m_nHeight=rc.Height();
	*/
	m_nWidth=cx;
	m_nHeight=cy;
	if(m_nTotalHeight<m_nHeight)
	{
		m_nTotalHeight=m_nHeight;
		m_nScrollHeight=0;
	}
	else
		m_nScrollHeight=m_nTotalHeight-m_nHeight;
	
	SetScrollHeight(m_nScrollHeight);
	Invalidate();
}
//设置滚动条高度
void CShowByGUIDlg::SetScrollHeight(int scrollHeight)
{
	SCROLLINFO scroll;
	GetScrollInfo(SB_VERT,&scroll,SIF_ALL);	
	scroll.nMax=scrollHeight+1;
	//scroll.fMask=SIF_ALL;
	//scroll.nMin=0;
	SetScrollInfo(SB_VERT,&scroll);		
}
//设置整个画布高度
void CShowByGUIDlg::SetTotalHeight(int height)
{
	m_nTotalHeight=height;
	m_nScrollHeight=m_nTotalHeight-m_nHeight;
	SetScrollHeight(m_nScrollHeight);
}

void CShowByGUIDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	menu.LoadMenu(IDR_MENU_tool);
	CMenu* pPopuuMenu=menu.GetSubMenu(1);
	CPoint tmp_point;
	::GetCursorPos(&tmp_point);
	pPopuuMenu->TrackPopupMenu(TPM_LEFTALIGN,tmp_point.x,tmp_point.y,this);
	CDialog::OnRButtonDown(nFlags, point);
}
