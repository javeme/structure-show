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
CString CShowByGUIDlg::typeStrOfStruct[]={"���Ա�","��ջ","����","��","������","ͼ","����","����"};
//enum{seqList,linkList,withHeadLinkList,staticLinkList,cycleLinkList,numOfList};
CString CShowByGUIDlg::typeStrOfList[]={"˳���","����","ר��ͷ�������","��̬����","ѭ������"};
//enum{seqStack,linkStack,numOfStack};
CString CShowByGUIDlg::typeStrOfStack[]={"˳��ջ","��ջ"};
//enum{childSibTree,numOfTree};
CString CShowByGUIDlg::typeStrOfTree[]={"�����ֵ���"};
//enum{binTreeLink,numOfBinTree};
CString CShowByGUIDlg::typeStrOfBinTree[]={"��ʽ������"};
//enum{nonDirGraph,dirGraph,nonDirNet,dirNet,numOfGraph};
CString CShowByGUIDlg::typeStrOfGraph[]={"����ͼ","����ͼ","������","������"};


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
	
	this->SetWindowText("ͼ�ν������ݽṹ����");
	
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
/************************************************����Ϊ�Զ��巽��**********************************************************/
//�ͷ��ڴ�
void CShowByGUIDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	if(pDataStructure!=NULL)
		delete pDataStructure;	
}
//��ʼ��ѡ���б�
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
	//���Ա�
	for(k=0;k<numOfList;k++)
	{
		treeItemOfList[k]=this->m_TestChoiceTree.InsertItem(typeStrOfList[k],2,2,treeItemOfStruct[list]);
		m_TestChoiceTree.SetItemData(treeItemOfList[k],k);
	}
	//��ջ
	for(k=0;k<numOfStack;k++)
	{
		treeItemOfStack[k]=this->m_TestChoiceTree.InsertItem(typeStrOfStack[k],2,2,treeItemOfStruct[stack]);
		m_TestChoiceTree.SetItemData(treeItemOfStack[k],k);
	}
	//��
	for(k=0;k<numOfTree;k++)
	{
		treeItemOfTree[k]=this->m_TestChoiceTree.InsertItem(typeStrOfTree[k],2,2,treeItemOfStruct[tree]);
		m_TestChoiceTree.SetItemData(treeItemOfTree[k],k);
	}
	//������
	for(k=0;k<numOfBinTree;k++)
	{
		treeItemOfBinTree[k]=this->m_TestChoiceTree.InsertItem(typeStrOfBinTree[k],2,2,treeItemOfStruct[binTree]);
		m_TestChoiceTree.SetItemData(treeItemOfBinTree[k],k);
	}
	//ͼ
	for(k=0;k<numOfGraph;k++)
	{
		treeItemOfGraph[k]=this->m_TestChoiceTree.InsertItem(typeStrOfGraph[k],2,2,treeItemOfStruct[graph]);
		m_TestChoiceTree.SetItemData(treeItemOfGraph[k],k);
	}
	controlType=0;
}
//˫������
void CShowByGUIDlg::OnDblClickTreeChoice(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	HTREEITEM item=m_TestChoiceTree.GetSelectedItem();		
	//CString str;str.Format("%d",m_TestChoiceTree.ItemHasChildren(item));  AfxMessageBox(str,100,100);
	//�޺���,��ΪҶ�ӽڵ�
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
			AfxMessageBox("��ʼ���ɹ�!",100,100);
		}
		else
			AfxMessageBox("��ʼ��ʧ��!",100,100);
		/*
		HTREEITEM childItem;
		//��ȡ���ڵ�����
		for(int i=0;i<numOfStruct;i++)
		{			
			if(m_TestChoiceTree.GetParentItem(item)==treeItemOfStruct[i])
			{
				//AfxMessageBox(m_TestChoiceTree.GetItemText(item),100,100);
				//��ȡҶ�ӽڵ�����
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

//ȷ����ť����
void CShowByGUIDlg::OnClickButtonSure() 
{
	if(pDataStructure==NULL)
	{
		AfxMessageBox("����δѡ���������!",100,100);
		return;
	}	
	CString locationStr,valueStr;
	int location,returnValue;
	this->m_LocationTextField.GetWindowText(locationStr);	
	this->m_ValueTextField.GetWindowText(valueStr);	
		
	CString str;
	
	//��ѯ
	if(controlType==2)		
	{
		Invalidate();
		return;
	}
	switch(structureType)
	{//list,stack,queue,tree,binTree,graph,search,sort
		case list:
			location=atoi(locationStr.GetBuffer(locationStr.GetLength()+1));
			//����
			if(controlType==0)
			{				
				pDataStructure->Insert(location,valueStr);//��Ӧ�ø���λ�������Ұ�???
			}
			//�޸�
			else if(controlType==1)
			{
				pDataStructure->Delete(location,locationStr);//�޸�ĳλ�õ�ֵ
				pDataStructure->Insert(location,valueStr);

			}
			//ɾ��
			else if(controlType==3)
			{
				pDataStructure->Delete(location,valueStr);//
			}
			break;
		case stack:			
			if(controlType==0)
			{
				pDataStructure->Push(valueStr);//ѹջ
			}
			break;
		case tree:
			//����
			if(controlType==0)
			{
				returnValue=pDataStructure->Insert(locationStr,valueStr); 
				//	str.Format("����ֵ%d!",returnValue);	AfxMessageBox(str,100,100);
			
				switch(returnValue)
				{
					case 0:
						::AfxMessageBox("�ڴ治��!",100,100);
						return;
					case -1:
						AfxMessageBox("����ֵ�ظ�!!",100,100);
						return;
					default:
						break;
				}
				InitPosition(valueStr);//Ϊ�ղ���ڵ��ʼ������ʾ������
			}			
			break;
		case binTree:
			//��������
			if(controlType==20)
			{
				returnValue=pDataStructure->InsertL(locationStr,valueStr);
			}
			//�����ֺ���
			else if(controlType==21)
			{
				returnValue=pDataStructure->InsertR(locationStr,valueStr);
			}
			InitPosition(valueStr);
			break;
		case graph:
		{
			//returnValue=pDataStructure->InsertVex(valueStr.GetBuffer(locationStr.GetLength()+1),location);
			
			//�����
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
				InitPosition(location,locationEnd);//Ϊ�ղ���ڵ��ʼ������ʾ������
			}	
			//���붥��
			else
				returnValue=pDataStructure->InsertVex(valueStr,location);
			
				//str.Format("����ֵ:%d ",location);	AfxMessageBox(str,100,100);		
			break;
		}
		default:
			break;
	}	
	
	//UpdateWindow();//??
	//Invalidate();
	pThread=AfxBeginThread(PaintThread,	this);//�����̺߳���
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
		//����
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
//����ˢ��,��ͼ
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
		//���Ա�
	case list:
		//��ѯ
		if(controlType==2)
		{
			CString locationStr,valueStr;
			this->m_LocationTextField.GetWindowText(locationStr);	
			this->m_ValueTextField.GetWindowText(valueStr);
			int position=atoi(locationStr.GetBuffer(locationStr.GetLength()+1));
			pDataStructure->Get(position,returnValue);
			CString str;
			str="����ѯλ�õ�ֵ�ǣ�"+returnValue;
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
						//����
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
						//��ӡ�±�	
						char s[40];
						wsprintf(s,"%d",i-1);
						dc.TextOut(base+width*k,height+textOffset+20,s);
					}
				break;
				}
				case withHeadLinkList:
				{
					hOffset=30;	
					//ͷ���
					dc.Rectangle(base-hOffset,height,base+10,height+vOffset);
					dc.Rectangle(base+10,height,base+hOffset,height+vOffset);
					dc.TextOut(base-10,height+textOffset,"first");
					dc.TextOut(base,height+textOffset+20,"0");
/*					//��ʼ״̬����Ϊ��

					dc.MoveTo(base+18,height+5);
					dc.LineTo(base+14,height+15);
					dc.MoveTo(base+18,height+5);
					dc.LineTo(base+22,height+15);
*/
					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)//((LIST<CString>*)pDataStructure)
					{	
						k=4*(i-1);
						k-=max;
						//����
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

						//��ӡ�±�
						char s[40];
						wsprintf(s,"%d",i);
						dc.TextOut(base+width*(k+4),height+textOffset+20,s);

						//��ӡ��ͷ
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
					//ͷ���
					dc.Rectangle(base-hOffset,height,base+10,height+vOffset);
					dc.Rectangle(base+10,height,base+hOffset,height+vOffset);
					dc.TextOut(base-10,height+textOffset,"first");
					dc.TextOut(base,height+textOffset+20,"0");

					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)//((LIST<CString>*)pDataStructure)
					{	
						k=4*(i-1);
						k-=max;
						//����
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

						//��ӡ�±�
						char s[40];
						wsprintf(s,"%d",i);
						dc.TextOut(base+width*(k+4),height+textOffset+20,s);

						//��ӡ��ͷ
						dc.MoveTo(base+width*k+hOffset,height+10);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
						dc.MoveTo(base+width*k+hOffset+8,height+8);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
						dc.MoveTo(base+width*k+hOffset+8,height+12);
						dc.LineTo(base+width*(k+4)-hOffset,height+10);
					}

					//ָ��ͷ���
					for(i=1; pDataStructure->Get(i,returnValue)>0;i++)//((LIST<CString>*)pDataStructure)
					{	
						k=4*(i-1);
						k-=max;
						//����
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
						//��ͷ
						dc.MoveTo(base-30,55);
						dc.LineTo(base-25,50);
						dc.MoveTo(base-20,55);
						dc.LineTo(base-25,50);
						dc.LineTo(base-25,50);
					}
					else
					{
						//����Ϊ���� ��ָ��ָ��
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
						//����
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
						//��ӡ��ͷ
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
					if(i!=1)//βָ��Ϊ��
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
		
		//��ջ
		case stack:				
			for(i=1; pDataStructure->GetElement(i,returnValue) >0 ;i++)
			{	
				//����
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
		//��
		case tree:
			//���ڵ�ֵ
			if(pDataStructure->Root(returnValue,x,y)!=1)
				return;				
			dc.Ellipse(x-18,y-10,x+21,y+25);
			dc.TextOut(x,y,returnValue);		
			//���
			queueForTree[rear++]=returnValue;
			//�������,����ָ����ȵ���ȱ��?
			while(1)
			{
				/*
				//��һ������ֵ
				if(pDataStructure->GetFirstChildOf(returnValue,returnValue,x,y)==0)
				{
					if(head==rear)
						break;
					returnValue=queueForTree[++head];
					continue;
				}
				level=pDataStructure->GetLevelOf(returnValue);//��ȡ��ֵ�Ĳ��				
				if(x==0 && y==0)
				{
					pDataStructure->SetPosition(returnValue,base+width*k,height*level+textOffset);
					dc.TextOut(base+width*k,height*level+textOffset,returnValue);	
				}
				else
					dc.TextOut(x,y,returnValue);
				queueForTree[rear++]=returnValue;
				//�ֵ�ֵ
				for(i=1; pDataStructure->GetNextSibOf(returnValue,returnValue,x,y)>0;i++)
				{
					k=4*i;
					//dc.TextOut(base+width*k,height*level+textOffset,returnValue);
					//��������
					if(x==0 && y==0)
					{
						pDataStructure->SetPosition(returnValue,base+width*k,height*level+textOffset);
						dc.TextOut(base+width*k,height*level+textOffset,returnValue);	
					}
					//��x,y��ͼ
					else
						dc.TextOut(x,y,returnValue);
					//���
					queueForTree[rear++]=returnValue;
				}
				//����
				returnValue=queueForTree[++head];
				/*/
				//���潫���׽ڵ�����
				pDataStructure->GetPositionOf(returnValue,startPositionX,startPositionY);
				startPositionY+=20;
				//�ж��Ƿ��е�һ������ֵ
				if(pDataStructure->GetFirstChildOf(returnValue,returnValue,x,y)==0)
				{
					if(head==rear)//�ӿ�
						break;
					returnValue=queueForTree[++head];//û�к���ʱ,����
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
				//�ֵ�ֵ
				for(i=1; pDataStructure->GetNextSibOf(returnValue,returnValue,x,y)>0;i++)
				{
					dc.MoveTo(startPositionX,startPositionY);
					dc.LineTo(x,y);
					dc.Ellipse(x-18,y-10,x+21,y+25);
					dc.TextOut(x,y,returnValue);
					//���
					queueForTree[rear++]=returnValue;
				}
				//����
				returnValue=queueForTree[++head];
				//*/
			}
			break;
		//������
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
					//���
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
		//ͼ,����20����?
		case graph:	
			i=1;
			while(pDataStructure->GetVex(i,returnValue))
			{
				pDataStructure->GetPositionOf(i,x,y);				
				//����
				PositionStruct *pPositions;
				pDataStructure->GetNeighborPositionOf(returnValue,pPositions);
				while(pPositions)
				{
					dc.MoveTo(x,y);
					dc.LineTo(pPositions->x,pPositions->y);
					pPositions=pPositions->pNext;
				}
				//������
				dc.Ellipse(x-18,y-10,x+21,y+25);
				dc.TextOut(x,y,returnValue);
				i++;
			}
			break;
		default:
			break;
	}	
}
//������ʾ
void CShowByGUIDlg::PaintLine()
{
	temp_startPositionX=startPositionX+temp_endOffsetX;
	//temp_startPositionY = k * temp_startPositionX + temp_startPositionX;
	temp_startPositionY=startPositionY+temp_endOffsetY;
	
	bool isLarger=(endPositionX>startPositionX);
	if(isLarger)
	{
		temp_endOffsetX++;//�����startPositionX��ƫ����		
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
	//���Ի���
	CClientDC dc(this);
	dc.MoveTo(temp_startPositionX ,temp_startPositionY);
	//dc.MoveTo(240 ,30);
	dc.LineTo(temp_endPositionX,temp_endPositionY);
	//	CString str;str.Format("k=%f",k);dc.TextOut(400,100,str);
	//Invalidate();
}
//��ʼ�� ��/������ �ڵ�λ��
void CShowByGUIDlg::InitPosition(CString locationStr)
{
	CString parentValue;
	if(pDataStructure->Parent(locationStr,parentValue)==2)
	{
		//Ϊ��һ���ڵ�
		pDataStructure->SetPositionOf(locationStr,540,20,800);
		isFinished=true;
		return;
	}
	//��ȡ���׽ڵ�����
	pDataStructure->GetPositionOf(parentValue,startPositionX,startPositionY);
	startPositionY+=20;
	//��ȡ���ڵ�����
	pDataStructure->GetPositionOf(locationStr,endPositionX,endPositionY);

	SetSlope();

	isFinished=false;
}
//��ʼ��ͼ�ڵ�λ��
void CShowByGUIDlg::InitPosition(int locationStartVex,int locationEndVex)
{	
	//if(pDataStructure->GetPositionOf(location-1,startPositionX,startPositionY)!=1)//�ȵ��ҵ����ڽڵ�(location-1��Ϊ����)
	if(pDataStructure->GetPositionOf(locationStartVex,startPositionX,startPositionY)!=1)
	{
		isFinished=true;//locationΪ��һ���ڵ�
		return;
	}
	if(pDataStructure->GetPositionOf(locationEndVex,endPositionX,endPositionY)!=1)
		return;

	SetSlope();
	
	isFinished=false;//δ����ʱ��������������ְ�ȫ����?
}
//����б��
void CShowByGUIDlg::SetSlope()
{
	temp_startPositionX=startPositionX;
	temp_startPositionY=startPositionY;	
	
	temp_endOffsetX=0;
	temp_endOffsetY=0;
	
	double a=1;
	slope=(endPositionY*a-startPositionY) / (endPositionX-startPositionX);
}
//�����߳�
void CShowByGUIDlg::Run()
{	
	while(! isFinished)
	{	
		Sleep(10);//����һ��ʱ��
		PaintLine();
		//AfxMessageBox("�߳�...",100,100);
	}
	Invalidate();	
}

//��ͼ�߳�
UINT PaintThread(LPVOID pParam) 
{
	CShowByGUIDlg* pDlg=(CShowByGUIDlg*)pParam;
	pDlg->Run();
	return 0;
}




//���ò�������
void CShowByGUIDlg::SetControlType()
{
	m_EndLocationTextField.ShowWindow(SW_HIDE);
	switch(controlType)
	{
	case 0:
		m_LocationLabel.SetWindowText("����λ��:");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("����ֵ:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	
	case 1:
		m_LocationLabel.SetWindowText("�޸�λ��:");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("�޸�Ϊ:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	case 2:
		m_LocationLabel.SetWindowText("��ѯλ��");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("");
		m_ValueTextField.ShowWindow(SW_HIDE);	
		break;
	case 3:
		m_LocationLabel.SetWindowText("ɾ��λ��:");
		m_LocationLabel.ShowWindow(SW_SHOW);
		m_ValueLabel.SetWindowText("");
		m_ValueTextField.ShowWindow(SW_HIDE);
			
		break;
    //ͼ�Ĳ���
	//���붥��
	case 11:
		m_LocationLabel.SetWindowText("");
		m_ValueLabel.SetWindowText("���붥���ֵ");
		m_LocationTextField.ShowWindow(SW_HIDE);
		break;
	//��ѯ����
	case 12:
		m_LocationLabel.SetWindowText("");
		m_ValueLabel.SetWindowText("Ҫ��Ѱֵ");
		m_LocationTextField.ShowWindow(SW_HIDE);
		break;
	//�޸Ķ����ֵ
	case 13:
		m_LocationLabel.SetWindowText("���޸Ķ���");
		m_ValueLabel.SetWindowText("�޸ĺ��ֵ");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//ɾ�������ֵ
	case 14:
		m_LocationLabel.SetWindowText("");
		m_ValueLabel.SetWindowText("��ɾ������");
		m_LocationTextField.ShowWindow(SW_HIDE);
		break;
	//�����
	case 15:
		m_LocationLabel.SetWindowText("��ʼĩ�ڵ�");				
		m_ValueLabel.SetWindowText("�ߵ�Ȩֵ");
		m_LocationTextField.ShowWindow(SW_SHOW);
		m_EndLocationTextField.ShowWindow(SW_SHOW);
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//��ѯ��
	case 16:
		m_LocationLabel.SetWindowText("�ߵ�ʼ�ڵ�");
		m_ValueLabel.SetWindowText("�ߵ�ĩ�ڵ�");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//�޸ı�Ȩֵ
	case 18:
		m_LocationLabel.SetWindowText("�ߵ�ʼ�ڵ�");
		m_ValueLabel.SetWindowText("�ߵ�ĩ�ڵ�");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//ɾ����
	case 19:
		m_LocationLabel.SetWindowText("�ߵ�ʼ�ڵ�");
		m_ValueLabel.SetWindowText("�ߵ�ĩ�ڵ�");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	//������
	case 20:
		m_LocationLabel.SetWindowText("�����λ��:");
		m_ValueLabel.SetWindowText("��������:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	case 21:
		m_LocationLabel.SetWindowText("�����λ��:");
		m_ValueLabel.SetWindowText("�����Һ���:");
		m_ValueTextField.ShowWindow(SW_SHOW);
		break;
	default:
		break;

	}	
}

//�˵�����,ѡ���������

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
//�����˵�
void CShowByGUIDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here	

}
//��Ӧ������
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
//�������ڳߴ�ı�
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
//���ù������߶�
void CShowByGUIDlg::SetScrollHeight(int scrollHeight)
{
	SCROLLINFO scroll;
	GetScrollInfo(SB_VERT,&scroll,SIF_ALL);	
	scroll.nMax=scrollHeight+1;
	//scroll.fMask=SIF_ALL;
	//scroll.nMin=0;
	SetScrollInfo(SB_VERT,&scroll);		
}
//�������������߶�
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
