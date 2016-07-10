# Microsoft Developer Studio Project File - Name="ShowByGUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ShowByGUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ShowByGUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ShowByGUI.mak" CFG="ShowByGUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ShowByGUI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ShowByGUI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ShowByGUI - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ShowByGUI - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ShowByGUI - Win32 Release"
# Name "ShowByGUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BinTree.cpp
# End Source File
# Begin Source File

SOURCE=.\BinTreeLink.cpp
# End Source File
# Begin Source File

SOURCE=.\BST.CPP
# End Source File
# Begin Source File

SOURCE=.\Common.cpp
# End Source File
# Begin Source File

SOURCE=.\CycleLinkList.cpp
# End Source File
# Begin Source File

SOURCE=.\DataStructure.cpp
# End Source File
# Begin Source File

SOURCE=.\DataStructureTest.cpp
# End Source File
# Begin Source File

SOURCE=.\Graph.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphAM.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkList.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkList2.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkStack.cpp
# End Source File
# Begin Source File

SOURCE=.\List.cpp
# End Source File
# Begin Source File

SOURCE=.\Queue.cpp
# End Source File
# Begin Source File

SOURCE=.\SeqList.cpp
# End Source File
# Begin Source File

SOURCE=.\SeqQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\SeqSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\SeqStack.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowByGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowByGUI.rc
# End Source File
# Begin Source File

SOURCE=.\ShowByGUIDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Stack.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticList.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tree.cpp
# End Source File
# Begin Source File

SOURCE=.\TreeChildSib.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\BST.H
# End Source File
# Begin Source File

SOURCE=.\DataStructure.h
# End Source File
# Begin Source File

SOURCE=.\DataStructureTest.h
# End Source File
# Begin Source File

SOURCE=.\Graph.h
# End Source File
# Begin Source File

SOURCE=.\GraphAM.H
# End Source File
# Begin Source File

SOURCE=.\Node.h
# End Source File
# Begin Source File

SOURCE=.\Position.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShowByGUI.h
# End Source File
# Begin Source File

SOURCE=.\ShowByGUIDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\dataStruct1.ico
# End Source File
# Begin Source File

SOURCE=.\res\dataStruct2.ico
# End Source File
# Begin Source File

SOURCE=.\res\leaf.ico
# End Source File
# Begin Source File

SOURCE=.\res\ShowByGUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\ShowByGUI.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
