; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShowByGUIDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ShowByGUI.h"

ClassCount=3
Class1=CShowByGUIApp
Class2=CShowByGUIDlg

ResourceCount=5
Resource1=IDD_SHOWBYGUI_DIALOG
Resource2=IDR_MAINFRAME
Class3=AboutDlg
Resource3=IDR_MENU_tool
Resource4=IDD_ABOUTBOX
Resource5="IDR_MENU_TOOLOLD"

[CLS:CShowByGUIApp]
Type=0
HeaderFile=ShowByGUI.h
ImplementationFile=ShowByGUI.cpp
Filter=N
LastObject=CShowByGUIApp

[CLS:CShowByGUIDlg]
Type=0
HeaderFile=ShowByGUIDlg.h
ImplementationFile=ShowByGUIDlg.cpp
Filter=D
LastObject=CShowByGUIDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=AboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_SHOWBYGUI_DIALOG]
Type=1
Class=CShowByGUIDlg
ControlCount=8
Control1=IDC_TREE_choice,SysTreeView32,1350631426
Control2=IDC_STATIC_location,static,1342308352
Control3=IDC_EDIT_location,edit,1350631552
Control4=IDC_STATIC_value,static,1342308352
Control5=IDC_EDIT_value,edit,1350631552
Control6=IDC_BUTTON_sure,button,1342242816
Control7=IDC_BUTTON_cancel,button,1342242816
Control8=IDC_EDIT_endLocation,edit,1082196096

[CLS:AboutDlg]
Type=0
HeaderFile=AboutDlg.h
ImplementationFile=AboutDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=AboutDlg

[MNU:IDR_MENU_tool]
Type=1
Class=?
Command1=ID_MENUITEM_open
Command2=ID_MENUITEM_save
Command3=ID_MENUITEM_exit
Command4=ID_OnMenuInsertList
Command5=ID_OnMenuUpdatatList
Command6=ID_OnMenuSearchList
Command7=ID_OnMenuDeleteList
Command8=ID_MENUITEM32793
Command9=ID_MENUITEM32798
Command10=ID_MENUITEM_insertLeftChild
Command11=ID_MENUITEM_insertRightChild
Command12=ID_MENUITEM_deleteLeftChild
Command13=ID_MENUITEM_deleteRightChild
Command14=ID_MENUITEM_insertVex
Command15=ID_MENUITEM_searchVex
Command16=ID_MENUITEM_updateVex
Command17=ID_MENUITEM_deleteVex
Command18=ID_MENUITEM_insertArc
Command19=ID_MENUITEM_searchArc
Command20=ID_MENUITEM_
Command21=ID_MENUITEM_updateWeight
Command22=ID_MENUITEM_deleteArc
Command23=ID_MENUITEM32800
Command24=ID_MENUITEM32801
Command25=ID_MENUITEM_about
CommandCount=25

[MNU:"IDR_MENU_TOOLOLD"]
Type=1
Class=?
Command1=ID_MENUITEM_open
Command2=ID_MENUITEM_save
Command3=ID_MENUITEM_exit
Command4=ID_MENUITEM_insert
Command5=ID_MENUITEM_update
Command6=ID_MENUITEM_search
Command7=ID_MENUITEM_delete
Command8=ID_MENUITEM_insertArc
Command9=ID_MENUITEM_about
CommandCount=9

