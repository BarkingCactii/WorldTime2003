# Microsoft Developer Studio Project File - Name="Skin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Skin - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Skin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Skin.mak" CFG="Skin - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Skin - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Skin - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Skin - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib dsound.lib htmlhelp.lib msimg32.lib /nologo /subsystem:windows /machine:I386 /out:"release\WorldTime.exe"
# SUBTRACT LINK32 /force

!ELSEIF  "$(CFG)" == "Skin - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib dsound.lib htmlhelp.lib msimg32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"debug\WorldTime.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none /force

!ENDIF 

# Begin Target

# Name "Skin - Win32 Release"
# Name "Skin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\alarms.cpp
# End Source File
# Begin Source File

SOURCE=.\Bstream.cpp
# End Source File
# Begin Source File

SOURCE=.\DisplayLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarms.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocationDetails.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMember.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMemberAdd.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpdater.cpp
# End Source File
# Begin Source File

SOURCE=.\Label.cpp
# End Source File
# Begin Source File

SOURCE=.\List.cpp
# End Source File
# Begin Source File

SOURCE=.\Location.cpp
# End Source File
# Begin Source File

SOURCE=.\Member.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefLocationPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefSoundsPropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefTemplatePropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\PrefTimePropPage.cpp
# End Source File
# Begin Source File

SOURCE=.\Skin.cpp
# End Source File
# Begin Source File

SOURCE=.\Skin.rc
# End Source File
# Begin Source File

SOURCE=.\SkinDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Sounds.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TimeSync.cpp
# End Source File
# Begin Source File

SOURCE=.\TrayIcon.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\alarms.h
# End Source File
# Begin Source File

SOURCE=.\Bstream.h
# End Source File
# Begin Source File

SOURCE=.\DisplayLocation.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmDetails.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmMessage.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarms.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocation.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocationDetails.h
# End Source File
# Begin Source File

SOURCE=.\DlgMember.h
# End Source File
# Begin Source File

SOURCE=.\DlgMemberAdd.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpdater.h
# End Source File
# Begin Source File

SOURCE=.\Label.h
# End Source File
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\Location.h
# End Source File
# Begin Source File

SOURCE=.\Member.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PrefLocationPropPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\PrefSoundsPropPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefTemplatePropPage.h
# End Source File
# Begin Source File

SOURCE=.\PrefTimePropPage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Skin.h
# End Source File
# Begin Source File

SOURCE=.\SkinDlg.h
# End Source File
# Begin Source File

SOURCE=.\Sounds.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TimeSync.h
# End Source File
# Begin Source File

SOURCE=.\TrayIcon.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\adddisplay.ico
# End Source File
# Begin Source File

SOURCE=.\res\addlocation.ico
# End Source File
# Begin Source File

SOURCE=.\res\alarm.ico
# End Source File
# Begin Source File

SOURCE=.\res\display.ico
# End Source File
# Begin Source File

SOURCE=.\res\help.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\location.ico
# End Source File
# Begin Source File

SOURCE=.\res\location_small.ico
# End Source File
# Begin Source File

SOURCE=.\res\locations.ico
# End Source File
# Begin Source File

SOURCE=.\res\member.ico
# End Source File
# Begin Source File

SOURCE=.\res\Member_Small.ico
# End Source File
# Begin Source File

SOURCE=.\res\preferences.ico
# End Source File
# Begin Source File

SOURCE=.\res\Skin.ico
# End Source File
# Begin Source File

SOURCE=.\res\Skin.rc2
# End Source File
# Begin Source File

SOURCE=.\res\skins.ico
# End Source File
# Begin Source File

SOURCE=.\res\template.ico
# End Source File
# Begin Source File

SOURCE=.\res\updater.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
