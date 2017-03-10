; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDlgLocation
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "skin.h"
LastPage=0
CDK=Y

ClassCount=20
Class1=CDlgAlarms
Class2=CDlgLocation
Class3=CDlgLocationDetails
Class4=CDlgMember
Class5=CDlgMemberAdd
Class6=CLabel
Class7=COptionsDlg
Class8=CPrefLocationPropPage
Class9=CPrefMainPropPage
Class10=CPrefMapPropPage
Class11=CPrefPropSheet
Class12=CPrefSoundsPropPage
Class13=CPrefTemplatePropPage
Class14=CPrefTimePropPage
Class15=CSkinApp
Class16=CAboutDlg
Class17=CSkinDlg

ResourceCount=16
Resource1=IDD_SKIN_DIALOG (English (U.S.))
Resource2=IDD_PREFERENCES_TIME (English (U.S.))
Resource3=IDD_PREFERENCES_TEMPLATE (English (U.S.))
Resource4=IDD_OPTIONS (English (U.S.))
Resource5=IDD_LOCATION_DETAILS (English (U.S.))
Resource6=IDD_LOCATIONS (English (U.S.))
Resource7=IDD_PREFERENCES_SOUNDS (English (U.S.))
Resource8=IDD_UPDATER (English (U.S.))
Resource9=IDD_ABOUTBOX (English (U.S.))
Resource10=IDD_PREFERENCES_LOCATIONS (English (U.S.))
Resource11=IDD_MEMBER_ADD (English (U.S.))
Resource12=IDD_ALARM_MESSAGE (English (U.S.))
Resource13=IDD_ALARMS (English (U.S.))
Class18=CDlgAlarmDetails
Class19=CDlgAlarmMessage
Resource14=IDD_MEMBERS (English (U.S.))
Resource15=IDD_ALARM (English (U.S.))
Class20=CDlgUpdater
Resource16=IDR_SYSTEMTRAY

[CLS:CDlgAlarms]
Type=0
BaseClass=CDialog
HeaderFile=DlgAlarms.h
ImplementationFile=DlgAlarms.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST

[CLS:CDlgLocation]
Type=0
BaseClass=CDialog
HeaderFile=DlgLocation.h
ImplementationFile=DlgLocation.cpp
LastObject=CDlgLocation

[CLS:CDlgLocationDetails]
Type=0
BaseClass=CDialog
HeaderFile=DlgLocationDetails.h
ImplementationFile=DlgLocationDetails.cpp

[CLS:CDlgMember]
Type=0
BaseClass=CDialog
HeaderFile=DlgMember.h
ImplementationFile=DlgMember.cpp
LastObject=IDC_MEMBER_ADD
Filter=D
VirtualFilter=dWC

[CLS:CDlgMemberAdd]
Type=0
BaseClass=CDialog
HeaderFile=DlgMemberAdd.h
ImplementationFile=DlgMemberAdd.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgMemberAdd

[CLS:CLabel]
Type=0
BaseClass=CStatic
HeaderFile=Label.h
ImplementationFile=Label.cpp

[CLS:COptionsDlg]
Type=0
BaseClass=CDialog
HeaderFile=OptionsDlg.h
ImplementationFile=OptionsDlg.cpp

[CLS:CPrefLocationPropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=PrefLocationPropPage.h
ImplementationFile=PrefLocationPropPage.cpp

[CLS:CPrefMainPropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=PrefMainPropPage.h
ImplementationFile=PrefMainPropPage.cpp

[CLS:CPrefMapPropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=PrefMapPropPage.h
ImplementationFile=PrefMapPropPage.cpp

[CLS:CPrefPropSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=PrefPropSheet.h
ImplementationFile=PrefPropSheet.cpp

[CLS:CPrefSoundsPropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=PrefSoundsPropPage.h
ImplementationFile=PrefSoundsPropPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=CPrefSoundsPropPage

[CLS:CPrefTemplatePropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=PrefTemplatePropPage.h
ImplementationFile=PrefTemplatePropPage.cpp
LastObject=CPrefTemplatePropPage
Filter=D
VirtualFilter=idWC

[CLS:CPrefTimePropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=PrefTimePropPage.h
ImplementationFile=PrefTimePropPage.cpp
Filter=D
VirtualFilter=idWC
LastObject=CPrefTimePropPage

[CLS:CSkinApp]
Type=0
BaseClass=CWinApp
HeaderFile=Skin.h
ImplementationFile=Skin.cpp
LastObject=CSkinApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SkinDlg.cpp
ImplementationFile=SkinDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_REGISTERED_TO

[CLS:CSkinDlg]
Type=0
BaseClass=CDialog
HeaderFile=SkinDlg.h
ImplementationFile=SkinDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CSkinDlg

[DLG:IDD_ALARMS]
Type=1
Class=CDlgAlarms

[DLG:IDD_OPTIONS]
Type=1
Class=COptionsDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_SKIN_DIALOG]
Type=1
Class=CSkinDlg

[DLG:IDD_ALARM_MESSAGE (English (U.S.))]
Type=1
Class=CDlgAlarmMessage
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_ALARM_DETAILS,static,1342308480
Control3=IDC_ALARMMESSAGE,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_SNOOZE,button,1342373889
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_SKIN_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_SKIN,{BA8C584B-209C-4D54-8BB1-8AB5F1DCA18E},1342242816

[DLG:IDD_OPTIONS (English (U.S.))]
Type=1
Class=?
ControlCount=3
Control1=IDC_LIST,SysListView32,1350682628
Control2=IDC_STATIC,static,1342179331
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_ALARMS (English (U.S.))]
Type=1
Class=?
ControlCount=7
Control1=IDC_LIST,SysListView32,1350664205
Control2=IDC_ALARMS_ADD,button,1342242816
Control3=IDC_ALARMS_PROPERTIES,button,1342242816
Control4=IDC_ALARMS_REMOVE,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342179331
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_REGISTERED_TO,edit,1350633600

[CLS:CDlgAlarmDetails]
Type=0
HeaderFile=DlgAlarmDetails.h
ImplementationFile=DlgAlarmDetails.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgAlarmDetails
VirtualFilter=dWC

[CLS:CDlgAlarmMessage]
Type=0
HeaderFile=DlgAlarmMessage.h
ImplementationFile=DlgAlarmMessage.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgAlarmMessage
VirtualFilter=dWC

[MNU:IDR_SYSTEMTRAY]
Type=1
Class=?
CommandCount=0

[DLG:IDD_ALARM (English (U.S.))]
Type=1
Class=CDlgAlarmDetails
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ALARM_MESSAGE,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_STATIC,button,1342177287
Control6=IDC_ALARM_CHOOSEAPP,button,1342242816
Control7=IDC_ALARM_RUNAPP,button,1342245891
Control8=IDC_ALARM_TIME,SysDateTimePick32,1342242873
Control9=IDC_ALARM_DATE,SysDateTimePick32,1342242852
Control10=IDC_ALARM_RECURRING,combobox,1344339970
Control11=IDC_MEMBER_LIST,SysListView32,1350631711
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_ALARM_PLAYSOUND,button,1342242819
Control15=IDC_STATIC,static,1342308352
Control16=IDC_ALARM_APPNAME,edit,1350633600
Control17=IDC_STATIC,static,1342179331

[DLG:IDD_LOCATION_DETAILS (English (U.S.))]
Type=1
Class=CDlgLocationDetails
ControlCount=32
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342179331
Control4=IDC_STATIC,static,1342308864
Control5=IDC_LOC_DETAILS_NAME,edit,1350631552
Control6=IDC_LOC_DETAILS_DSTOFFSET,msctls_trackbar32,1342242816
Control7=IDC_ADD_HOURS,static,1342308865
Control8=IDC_STATIC,button,1342177287
Control9=IDC_LOC_DETAILS_START_DAY,combobox,1344339970
Control10=IDC_LOC_DETAILS_START_FIRSTLAST,combobox,1344340994
Control11=IDC_LOC_DETAILS_START_MONTH,combobox,1344339970
Control12=IDC_STATIC,static,1342308864
Control13=IDC_LOC_DETAILS_END_DAY,combobox,1344339970
Control14=IDC_LOC_DETAILS_END_FIRSTLAST,combobox,1344339970
Control15=IDC_LOC_DETAILS_END_MONTH,combobox,1344339970
Control16=IDC_STATIC,static,1342308864
Control17=IDC_LOC_DETAILS_DST,button,1342242819
Control18=IDC_LOC_DETAILS_COUNTRY,edit,1350631552
Control19=IDC_STATIC,static,1342308864
Control20=IDC_LOC_DETAILS_COUNTRYCODE,edit,1350631552
Control21=IDC_STATIC,static,1342308864
Control22=IDC_LOC_DETAILS_AREACODE,edit,1350631552
Control23=IDC_STATIC,static,1342308864
Control24=IDC_STATIC,button,1342177287
Control25=IDC_LOC_DETAILS_LATDEGREES,edit,1350631552
Control26=IDC_LOC_DETAILS_LATNS,edit,1350631552
Control27=IDC_LOC_DETAILS_LONGNS,edit,1350631552
Control28=IDC_LOC_DETAILS_LONGDEGREES,edit,1350631552
Control29=IDC_STATIC,button,1342177287
Control30=IDC_STATIC,static,1342308864
Control31=IDC_STATIC,static,1342308864
Control32=IDC_STATIC,button,1342177287

[DLG:IDD_LOCATIONS (English (U.S.))]
Type=1
Class=CDlgLocation
ControlCount=7
Control1=IDC_LOCATION_ADD,button,1342242816
Control2=IDC_LOCATION_PROPERTIES,button,1342242816
Control3=IDC_LOCATION_REMOVE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342179331
Control6=IDC_LOCATION_LIST,SysListView32,1350631693
Control7=IDCANCEL,button,1342242816

[DLG:IDD_MEMBER_ADD (English (U.S.))]
Type=1
Class=CDlgMemberAdd
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_MEMBER_ADD_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308864
Control5=IDC_MEMBER_ADD_EMAIL,edit,1350631552
Control6=IDC_STATIC,static,1342308864
Control7=IDC_MEMBER_ADD_PHONE,edit,1350631552
Control8=IDC_STATIC,static,1342308864
Control9=IDC_MEMBER_ADD_LOCATION,combobox,1075904770
Control10=IDC_MEMBER_ADD_LOCONLY,button,1342242819
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342179331
Control13=IDC_STATIC,button,1342177287
Control14=IDC_LOCATION_LIST,SysListView32,1350631693
Control15=IDC_LOCATION_LOCATIONICON,static,1342179331
Control16=IDC_LOCATION_PERSONICON,static,1342179331
Control17=IDC_STATIC,static,1342308864

[DLG:IDD_MEMBERS (English (U.S.))]
Type=1
Class=CDlgMember
ControlCount=7
Control1=IDC_MEMBER_ADD,button,1342242816
Control2=IDC_MEMBER_PROPERTIES,button,1342242816
Control3=IDC_MEMBER_REMOVE,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342179331
Control6=IDC_MEMBER_LIST,SysListView32,1350631711
Control7=IDCANCEL,button,1342242816

[DLG:IDD_PREFERENCES_SOUNDS (English (U.S.))]
Type=1
Class=CPrefSoundsPropPage
ControlCount=15
Control1=IDC_STATIC,static,1342179331
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_SOUNDALARM,button,1342242816
Control5=IDC_SOUNDHOUR,button,1342242816
Control6=IDC_SOUNDQUARTER,button,1342242816
Control7=IDC_SOUNDALARMON,button,1342242819
Control8=IDC_SOUNDHOURON,button,1342242819
Control9=IDC_SOUNDQUARTERON,button,1342242819
Control10=IDC_ALARMSOUND_FILE,static,1342312448
Control11=IDC_HOURSOUND_FILE,static,1342312448
Control12=IDC_QUARTERSOUND_FILE,static,1342312448
Control13=IDC_ALARM_TEST,button,1342242816
Control14=IDC_HOUR_TEST,button,1342242816
Control15=IDC_QUARTER_TEST,button,1342242816

[DLG:IDD_PREFERENCES_LOCATIONS (English (U.S.))]
Type=1
Class=CPrefLocationPropPage
ControlCount=7
Control1=IDC_STATIC,static,1342179331
Control2=IDC_MESSAGE,static,1342308352
Control3=IDC_PREFERENCES_USETEMPLATE,button,1342242819
Control4=IDC_STATIC,button,1342177287
Control5=IDC_PREFERENCES_SHOWALL,button,1342242819
Control6=IDC_PREFERENCES_LOCBACKGROUND,combobox,1344339970
Control7=IDC_STATIC,static,1342308864

[DLG:IDD_PREFERENCES_TEMPLATE (English (U.S.))]
Type=1
Class=CPrefTemplatePropPage
ControlCount=10
Control1=IDC_STATIC,static,1342179331
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PROPERTIES_TEMPLATE,edit,1350631556
Control5=IDC_PROPERTIES_USETEMPLATE,button,1342242819
Control6=IDC_PROPERTIES_TEMPLATE2,edit,1350631556
Control7=IDC_PROPERTIES_TEMPLATE3,edit,1350631556
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_PREFERENCES_TIME (English (U.S.))]
Type=1
Class=CPrefTimePropPage
ControlCount=12
Control1=IDC_STATIC,static,1342179331
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PREFERENCES_SHOWAM,button,1342242819
Control5=IDC_PREFERENCES_24HOUR,button,1342242819
Control6=IDC_PREFERENCES_DETAILED,button,1342251011
Control7=IDC_STATIC,button,1342177287
Control8=IDC_UPDATE,button,1342242816
Control9=IDC_STATIC,static,1342308864
Control10=IDC_STATIC,static,1342179331
Control11=IDC_PREFERENCES_TOPMOST,button,1342242819
Control12=IDC_STATIC,button,1342177287

[DLG:IDD_UPDATER (English (U.S.))]
Type=1
Class=CDlgUpdater
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342179331
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CONNECT_STATUS,listbox,1353793793
Control5=IDC_UPDATER_START,button,1342242816

[CLS:CDlgUpdater]
Type=0
HeaderFile=DlgUpdater.h
ImplementationFile=DlgUpdater.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_UPDATER_START
VirtualFilter=dWC

