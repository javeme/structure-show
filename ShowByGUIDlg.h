// ShowByGUIDlg.h : header file
//

#if !defined(AFX_SHOWBYGUIDLG_H__64D83024_6768_4FCD_A773_641A11C645B4__INCLUDED_)
#define AFX_SHOWBYGUIDLG_H__64D83024_6768_4FCD_A773_641A11C645B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataStructureTest.cpp"//必须cpp!!!

/////////////////////////////////////////////////////////////////////////////
// CShowByGUIDlg dialog

class CShowByGUIDlg : public CDialog
{
// Construction
public:
	CShowByGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShowByGUIDlg)
	enum { IDD = IDD_SHOWBYGUI_DIALOG };
	CStatic	m_ValueLabel;
	CStatic	m_LocationLabel;
	CEdit	m_EndLocationTextField;
	CEdit	m_LocationTextField;
	CEdit	m_ValueTextField;
	CTreeCtrl	m_TestChoiceTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowByGUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShowByGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblClickTreeChoice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnClickButtonSure();
	afx_msg void OnMenuInsertGraphArc();
	afx_msg void OnOnMenuInsertGraphVex();
	afx_msg void OnMenuSearchGraphVex();
	afx_msg void OnMenuUpdateGraphVex();
	afx_msg void OnMenuDeleteGraphVex();
	afx_msg void OnMenusearchGraphArc();
	afx_msg void OnMenuUpdateGraphWeight();
	afx_msg void OnMenuDeleteGraphArc();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuInsertList();
	afx_msg void OnMenuUpdatatList();
	afx_msg void OnMenuSearchList();
	afx_msg void OnMenuDeleteList();
	afx_msg void OnMEenuInsertRightChild();
	afx_msg void OnMenuInsertLeftChild();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuAbout();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	//选择测试枚举
	static enum{list,stack,queue,tree,binTree,graph,search,sort,numOfStruct};
	//选择测试字符串
	static CString typeStrOfStruct[numOfStruct];
	//选择测试项
	HTREEITEM treeItemOfStruct[numOfStruct];
	
	//顺序表
	static enum{seqList,linkList,withHeadLinkList,staticLinkList,cycleLinkList,numOfList};
	static CString typeStrOfList[numOfList];
	HTREEITEM treeItemOfList[numOfList];
	//堆栈
	static enum{seqStack,linkStack,numOfStack};
	static CString typeStrOfStack[numOfStack];
	HTREEITEM treeItemOfStack[numOfStack];
	//树
	static enum{childSibTree,numOfTree};
	static CString typeStrOfTree[numOfTree];
	HTREEITEM treeItemOfTree[numOfTree];
	//二叉树
	static enum{binTreeLink,numOfBinTree};
	static CString typeStrOfBinTree[numOfBinTree];
	HTREEITEM treeItemOfBinTree[numOfBinTree];
	//图
	enum{nonDirGraph,dirGraph,nonDirNet,dirNet,numOfGraph};
	static  CString typeStrOfGraph[numOfGraph];//"无向图","有向图","无向网","有向网"
	HTREEITEM treeItemOfGraph[numOfGraph];
public:	
	void Run();
	//孩子数
	//static int childrenNum[numOfStruct];
private:
	CImageList imgList;
	DataStructure<CString> *pDataStructure;
	int structureType,itemType;

	CWinThread *pThread;
	int startPositionX,	startPositionY,	endPositionX,endPositionY;
	int temp_startPositionX,temp_startPositionY,	temp_endOffsetX,temp_endOffsetY;
	double slope;//斜率
	bool isFinished;
	
	int controlType;

	int m_nHeight,m_nWidth,base,m_nTotalHeight,m_nScrollHeight,offset;
private:
	void InitTestChoiceTree();
	void Refresh(CPaintDC& dc);
	
	void SetControlType();
	//void InitPosition(int location);
	void InitPosition(int,int);
	void InitPosition(CString locationStr);
	
	void SetSlope();
	
	void PaintLine();

	void SetScrollHeight(int height);
	void SetTotalHeight(int height);
};
UINT PaintThread(LPVOID pParam);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWBYGUIDLG_H__64D83024_6768_4FCD_A773_641A11C645B4__INCLUDED_)
