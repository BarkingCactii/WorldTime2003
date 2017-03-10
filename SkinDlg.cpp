// SkinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Skin.h"
#include "SkinDlg.h"

#include "location.h"
#include "member.h"
#include "regdata.h"

#include "optionsdlg.h"
#include "displaylocation.h"
#include <strstream>

#include "dlglocation.h"
#include "dlglocationdetails.h"
#include "dlgmember.h"
#include "dlgmemberadd.h"
#include "dlgAlarms.h"
#include "dlgUpdater.h"
#include "prefpropsheet.h"

#include "alarms.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int itemsPerPage = 5;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_registeredTo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_registeredTo = _T("");
	//}}AFX_DATA_INIT

    char regStr[100];
    memset ( regStr, 0, sizeof ( regStr ));
    GetEnvironmentVariable ( "USERNAME", regStr, sizeof ( regStr ));

    char daysLeft[20];
    memset ( daysLeft, 0, sizeof ( daysLeft ));
    GetEnvironmentVariable ( "DAYSLEFT", daysLeft, sizeof ( daysLeft ));


//    You have %DAYSLEFT% day(s) remaining before this trail version expires.

    if ( stricmp ( regStr, "DEFAULT" ))
    {
        // registered
//        m_details.SetWindowText ( "This product is registered to:" );
        m_registeredTo = regStr;
    }
    else
    {
        // shareware
        char message[50];
        sprintf ( message,  "Evaluation Version ( %s days left )", daysLeft );
        m_registeredTo = message;
    }

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_REGISTERED_TO, m_registeredTo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinDlg dialog

CSkinDlg * main;



CSkinDlg::CSkinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSkinDlg::IDD, pParent),  m_trayIcon(IDR_SYSTEMTRAY)

{
	//{{AFX_DATA_INIT(CSkinDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pageNum = 0;
    m_templateStr_col1 = m_templateStr_col2 = m_templateStr_col3 = ""; //%n %t";
    main = this;


}

void CSkinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSkinDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

#define WM_MY_TRAY_NOTIFICATION WM_USER+0

BEGIN_MESSAGE_MAP(CSkinDlg, CDialog)
	//{{AFX_MSG_MAP(CSkinDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
ON_MESSAGE(WM_MY_TRAY_NOTIFICATION, OnTrayNotification)
	ON_WM_CLOSE()
    ON_COMMAND(ID_TRAY_RESTORE, OnTrayRestore)
    ON_COMMAND(ID_TRAY_EXIT, OnTrayExit)
    ON_COMMAND(ID_TRAY_ABOUT, OnTrayAbout)
    ON_COMMAND(ID_TRAY_OPTIONS, OnTrayOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSkinDlg::OnTrayRestore()
{
        ShowWindow(SW_NORMAL);
        SetForegroundWindow();
}

void CSkinDlg::OnTrayAbout()
{
    CAboutDlg dlg;
    dlg.DoModal();
}

void CSkinDlg::OnTrayExit()
{
    SendMessage ( WM_CLOSE );
}

void CSkinDlg::OnTrayOptions()
{
    COptionsDlg dlg;
    dlg.DoModal();
}


LRESULT CSkinDlg::OnTrayNotification(WPARAM wp, LPARAM lp)
{                    
	// display message
	return m_trayIcon.OnTrayNotification(wp, lp);
}

                   
void CSkinDlg::InitData ( void )
{
    static bool init = false;

    if ( init == false )
    {
        // get the command line
        char * appPath = GetCommandLine();

        // set the data path ( same as application path )
        string dataPath;
        dataPath = appPath + 1; // jump past quote
        dataPath.resize ( dataPath.find_last_of ( "\\" ));
        dataPath += "\\";

        string locationsFile;
        locationsFile = dataPath + "locations.dat";

        string membersFile;
        membersFile = dataPath + "members.dat";

        // fix this
        

        if ( strstr ( AfxGetApp()->m_lpCmdLine, "recreate" ))
        {
            MessageBox ( "Recreating Locations.dat", "OnlineTime", MB_ICONEXCLAMATION );
            l.Create ( locationsFile );
        }
          

    // open locations.dat file
//    MessageBox ( "Opening files", "OnLineTime", MB_OK );

        l.Open ( locationsFile );
        m.Open ( membersFile );
//        g.Open ( dataPath );
#ifdef TEST
         
        // create some dummy members
        MemberItem * newItem;
        newItem = new MemberItem;
        newItem->name = "Jeff";
        m.Add ( newItem );
        newItem = new MemberItem;
        newItem->name = "Hunter";
        m.Add ( newItem );
          
#endif
//    g.Open ( dataPath );

        if (! r.ReadRegistry())
            ::MessageBox ( NULL, "There was a problem reading onlineTime\'s settings from the registry", "Error", MB_OK );


        if ( r.AlwaysOnTop())
            SetWindowPos ( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

         SetWindowPos ( NULL, r.WinLeft(), r.WinTop(), r.WinRight() - r.WinLeft (),
            r.WinBottom() - r.WinTop(), SWP_NOZORDER );

        init = true;

    }
}

/////////////////////////////////////////////////////////////////////////////
// CSkinDlg message handlers

BOOL CSkinDlg::OnInitDialog()
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
	

    // registry and data initialization

    InitData();
	// TODO: Add extra initialization here


    CComQIPtr<ISkin> pSkin = GetDlgItem(IDC_SKIN)->GetControlUnknown();
    m_pSkin = pSkin;
    ApplySkin (( char *) r.SkinName().c_str());

//    ShellExecute( AfxGetMainWnd()->m_hWnd, NULL, "regsvr32.exe", "actskn43.ocx", NULL, SW_SHOWNORMAL );
/*
    CComQIPtr<ISkin> pSkin = GetDlgItem(IDC_SKIN)->GetControlUnknown();
    char * name;
    if ( !name )
        name = "default.skn";
    else
        name = ( char * ) r.SkinName().c_str();

    pSkin->LoadSkin ( (_bstr_t) name );

//    ApplySkin ( "skin1.skn" );
    pSkin->ApplySkinByName((long)m_hWnd, L"Main") ;// code. 



	m_pSkin = GetDlgItem(IDC_SKIN)->GetControlUnknown();
	m_pSkin->GetSkinnedWindow((long)m_hWnd, &m_pMainWnd);
*/

    // save the template string

	CComPtr<ISkinObject> pTemplate;
    
	m_pMainWnd->FindObject(L"template_col1", &pTemplate);
        if ( pTemplate )
        {
        	CComQIPtr<ISkinStatic> pStaticTemplate(pTemplate);
            CComBSTR bstrName;

//            CString str;
            pStaticTemplate->GetCaption ( &bstrName );
//            string str = ( _bstr_t )bstrName;

            m_templateStr_col1 = (_bstr_t)bstrName;
//            m_templateStr = bstrName;
        }

        {
	CComPtr<ISkinObject> pTemplate;
	m_pMainWnd->FindObject(L"template_col2", &pTemplate);
        if ( pTemplate )
        {
        	CComQIPtr<ISkinStatic> pStaticTemplate(pTemplate);
            CComBSTR bstrName;

//            CString str;
            pStaticTemplate->GetCaption ( &bstrName );
//            string str = ( _bstr_t )bstrName;

            m_templateStr_col2 = (_bstr_t)bstrName;
//            m_templateStr = bstrName;
        }
        }
        {
	CComPtr<ISkinObject> pTemplate;
	m_pMainWnd->FindObject(L"template_col3", &pTemplate);
        if ( pTemplate )
        {
        	CComQIPtr<ISkinStatic> pStaticTemplate(pTemplate);
            CComBSTR bstrName;

//            CString str;
            pStaticTemplate->GetCaption ( &bstrName );
//            string str = ( _bstr_t )bstrName;

            m_templateStr_col3 = (_bstr_t)bstrName;
//            m_templateStr = bstrName;
        }
        }
      
    SetTimer ( 101, 1000, NULL );
//    AfxBeginThread ( Pulsate, this, THREAD_PRIORITY_IDLE );


    	// Notify me, please
	m_trayIcon.SetNotificationWnd(this, WM_MY_TRAY_NOTIFICATION); 
	//      m_trayIcon.SetIcon(IDI_MYICON);  
	m_trayIcon.SetIcon(IDR_MAINFRAME, " ");         //resource ID


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSkinDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
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

void CSkinDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSkinDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CSkinDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CSkinDlg)
	ON_EVENT(CSkinDlg, IDC_SKIN, 20 /* Click */, OnClickSkin, VTS_UNKNOWN)
	ON_EVENT(CSkinDlg, IDC_SKIN, 21 /* DblClick */, OnDblClickSkin, VTS_UNKNOWN)
	ON_EVENT(CSkinDlg, IDC_SKIN, 22 /* MouseDown */, OnMouseDownSkin, VTS_UNKNOWN VTS_I4 VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSkinDlg::OnClickSkin(LPUNKNOWN Source) 

	// TODO: Add your control notification handler code here
{
    USES_CONVERSION;
    CComBSTR bstrName; // Name of the SkinObject that has generated Click event
    CComQIPtr<ISkinObject> pSkinObject = Source; // Get this SkinObject
    pSkinObject->GetName(&bstrName); // Get its name
                                                       
    if ( bstrName == "Options" )
    {
        COptionsDlg dlg;

        dlg.DoModal();

//        ApplySkin ( "skin1.skn" );

    }

    if ( bstrName == "Next Page" )
    {
        if ((( m.Size() - 1 ) / itemsPerPage ) > m_pageNum )
            m_pageNum++;
        else
            m_pageNum = 0;

        /*
        static int flag = 1;
        if ( flag )
        {
        SetWindowPos ( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
        flag = 0;
        }
        else
        SetWindowPos ( &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
        */
    }

    if ( bstrName == "Previous Page" )
    {
        if ( m_pageNum )
            m_pageNum--;
        else
            m_pageNum = (( m.Size() - 1) / itemsPerPage );
    }


    if ( bstrName == "Display" )
            {
            CDlgMember dlg;
            dlg.DoModal ();
            }

    if ( bstrName == "Locations" )
            {
            CDlgLocation dlg;
            dlg.DoModal ();
            }
    if ( bstrName == "Alarms" )
            {
            CDlgAlarms dlg;
            dlg.DoModal ();
            m.SetModified ();
            }
    if ( bstrName == "Settings" )
            {
            CPrefPropSheet   allcontrolssheet(_T("Preferences"));
            allcontrolssheet.DoModal();
//            if ( allcontrolssheet.DoModal() == IDOK )
//            {
                //         SetWindowPos ( NULL, r.WinLeft(), r.WinTop(), r.WinRight() -
//                r.WinLeft (), r.WinBottom() - r.WinTop(), SWP_NOZORDER );
//                Invalidate ( FALSE );

//            }
//    return;
            }
    if ( bstrName == "Skins" )

            {
            // TODO: Add your command handler code here
          char * filterBuf= "WorldTime2003 Skins\0*.skn;*.cmo\0\0\0";
          CFileDialog openD ( TRUE );

          openD.m_ofn.lpstrFilter = filterBuf;
          openD.m_ofn.lpstrInitialDir = ".\\";
          openD.m_ofn.lpstrTitle = "Select a Skin";

         if ( openD.DoModal () == IDOK )
         {
              //
              // open file and read data
            //

//             CComQIPtr<ISkin> pSkin = AfxGetMainWnd()->GetDlgItem(IDC_SKIN)->GetControlUnknown();
//             main->pSkin->LoadSkin ( (_bstr_t) openD.m_ofn.lpstrFile );



             main->ApplySkin ( openD.m_ofn.lpstrFile );

             
//            CComQIPtr<ISkin> pSkin = AfxGetMainWnd()->GetDlgItem(IDC_SKIN)->GetControlUnknown();
//    pSkin->LoadSkin ( L"skin1.skn" );
//            pSkin->ApplySkinByName((long)AfxGetMainWnd(), (_bstr_t)openD.m_ofn.lpstrFile) ;// code. 
//            pSkin->ApplySkinByName((long)m_hWnd, (_bstr_t)openD.m_ofn.lpstrFile) ;// code. 


//            l.p.wallpaperName = openD.m_ofn.lpstrFile;

          }
            }
    if ( bstrName == "Help" )
    {
   //  HtmlHelp(NULL, "WorldTIme2003.chm::/release notes.htm", HH_DISPLAY_TOPIC, 0);
//        MessageBox ( "Help not implemented in beta", "Information" );
  //      ShowWindow ( SW_HIDE );
    }

    if ( bstrName == "min" )
    {
        // hide window, icon is in taskbar
      ShowWindow ( SW_HIDE );
    }

//    if ( bstrName == "Close" )
//    {
//        ShowWindow ( SW_HIDE );
//        }

//    if ( bstrName == "alarm1" )
//    {
//        MessageBox ( "Alarm!", "Information" );
//    }

    
//    ApplySkin ( "skin1.skn" );
//    USES_CONVERSION; 
//    MessageBox(W2T(bstrName)); // Convert its name to multibyte and display it in message box.

    m.Save();
}


void CSkinDlg::DrawLocalTime ( CTime & t )
{

    char buf[255];

    CString s = t.Format( "%I:%M:%S %p on %b %d" );
//    CString s = t.Format( "%I:%M:%S %p on %b %d" );
//    CString s = t.Format( "%I:%M:%S %p on %b %d, %Y" );

//    sprintf ( buf, "%s", ( const char * )s );
    if ( r.ShowDetailed())
        sprintf ( buf, "%s [%.1lf hrs GMT] %s", ( const char * )s, -_timezone / 3600.0f, ( _daylight ) ? _tzname[0] : _tzname[1] );
    else
        sprintf ( buf, "%s", ( const char * )s );

	CComPtr<ISkinObject> pLocalTime;
	m_pMainWnd->FindObject(L"localtime", &pLocalTime);
    if ( pLocalTime )
    {
    	CComQIPtr<ISkinStatic> pStatic(pLocalTime);
        pStatic->SetCaption ( (_bstr_t)buf );
    }


	CComPtr<ISkinObject> pLocalTime_time;
	m_pMainWnd->FindObject(L"localtime_time", &pLocalTime_time);
    if ( pLocalTime_time )
    {
        s = t.Format( "%I:%M:%S %p" );
    	CComQIPtr<ISkinStatic> pStatic(pLocalTime_time);
        pStatic->SetCaption ( (_bstr_t)(const char *) s );
    }

	CComPtr<ISkinObject> pLocalTime_date;
	m_pMainWnd->FindObject(L"localtime_date", &pLocalTime_date);
    if ( pLocalTime_date )
    {
        s = t.Format( "%b %d" );
    	CComQIPtr<ISkinStatic> pStatic(pLocalTime_date);
        pStatic->SetCaption ( (_bstr_t)(const char *) s );
//        pStatic->SetCaption ( (_bstr_t)buf );
    }



//    CComQIPtr<ISkinVisual>(m_pMainWnd)->Refresh();
}

void CSkinDlg::ApplySkin ( char * skin )
{
//    KillTimer ( 101 );

//    CComQIPtr<ISkin> pSkin = GetDlgItem(IDC_SKIN)->GetControlUnknown();


//    m_pSkin->RemoveSkin((long) m_hWnd );
//	m_pSkin = GetDlgItem(IDC_SKIN)->GetControlUnknown();
//    pSkin->LoadSkin ( L"skin1.skn" );
    m_pSkin->LoadSkin ((_bstr_t)skin) ;// code. 
    m_pSkin->ApplySkinByName((long)m_hWnd, L"main" );// code. 

	CComPtr<ISkinObject> m_pMainWnd2; // A reference to the root SkinObject of the form

	m_pSkin->GetSkinnedWindow((long)m_hWnd, &m_pMainWnd2);
    m_pMainWnd = m_pMainWnd2;



    {
	CComPtr<ISkinObject> pTemplate;
    
	m_pMainWnd->FindObject(L"template_col1", &pTemplate);
        if ( pTemplate )
        {
        	CComQIPtr<ISkinStatic> pStaticTemplate(pTemplate);
            CComBSTR bstrName;

//            CString str;
            pStaticTemplate->GetCaption ( &bstrName );
//            string str = ( _bstr_t )bstrName;

            m_templateStr_col1 = (_bstr_t)bstrName;
//            m_templateStr = bstrName;
            
        }
    }

    {
	CComPtr<ISkinObject> pTemplate;
	m_pMainWnd->FindObject(L"template_col2", &pTemplate);
        if ( pTemplate )
        {
        	CComQIPtr<ISkinStatic> pStaticTemplate(pTemplate);
            CComBSTR bstrName;

//            CString str;
            pStaticTemplate->GetCaption ( &bstrName );
//            string str = ( _bstr_t )bstrName;

            m_templateStr_col2 = (_bstr_t)bstrName;
//            m_templateStr = bstrName;
        }
    }

    {
	CComPtr<ISkinObject> pTemplate;

	m_pMainWnd->FindObject(L"template_col3", &pTemplate);
        if ( pTemplate )
        {
        	CComQIPtr<ISkinStatic> pStaticTemplate(pTemplate);
            CComBSTR bstrName;

//            CString str;
            pStaticTemplate->GetCaption ( &bstrName );
//            string str = ( _bstr_t )bstrName;

            m_templateStr_col3 = (_bstr_t)bstrName;
//            m_templateStr = bstrName;
        }
    }


    // save to registry
    r.SkinName ( string ( skin ));

    // work out how many lines per page

    bool terminate = false;
    for ( int i = 0; !terminate; i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            strstream fieldName;
            fieldName << "text" << i+1 << "_col" << j+1 << ends;

        	CComPtr<ISkinObject> pLabel;
        	m_pMainWnd->FindObject ((_bstr_t)fieldName.str(), &pLabel);
            if ( pLabel )
                itemsPerPage = i + 1;
            else
            {
                terminate = true;
                break;
            }
        }
    }

    // reset page as a skin might have a differing number items per page
    m_pageNum = 0;

}

bool CSkinDlg::SetField ( CTime & t, char * fieldName, int i, int j )
{
    string result;// = "test";
    bool term = false;

    CComPtr<ISkinObject> pText;
    m_pMainWnd->FindObject ((_bstr_t)fieldName, &pText);
    if ( pText )
    {
        CComQIPtr<ISkinStatic> pStatic1(pText);
        GetLocationText ((m_pageNum * itemsPerPage ) + i, t, result, 
            r.UseTemplate() ? r.MemberTemplate() : 
            (( j == 0 ) ? m_templateStr_col1 : 
            (( j == 1 ) ? m_templateStr_col2 : m_templateStr_col3 )));

        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }
    else
    {
        term = true;
    }

    return term;
}

void CSkinDlg::OnTimer(UINT nIDEvent) 
{
    static bool processing = false;

	// TODO: Add your message handler code here and/or call default

    if ( processing )
    {
    	CDialog::OnTimer(nIDEvent);
        return;
    }

    processing = true;

    CTime t = CTime::GetCurrentTime();

    DrawLocalTime( t );


    string result;// = "test";


    // line 1

    // keep looping until a label is missing, signifiying the number of fields per page
        
/*
    
    bool term = false;


    for ( int i = 0; !term; i++ )
    {
        // 
        // location text
        //

        
        for ( int j = 0; j < 3; j++ )
        {
            strstream fieldName;
            fieldName << "text" << i+1 << "_col" << j+1 << ends;
                             
//            if (( term = SetField ( t, fieldName.str(), i, j )) == true )
//                break;

            {
         	CComPtr<ISkinObject> pText;
        	m_pMainWnd->FindObject ((_bstr_t)fieldName.str(), &pText[(i*3)+j]);
            if ( pText[(i*3)+j] )
            {
                CComQIPtr<ISkinStatic> pStatic1(pText[(i*3)+j]);
                GetLocationText ((m_pageNum * itemsPerPage ) + i, t, result, 
                    r.UseTemplate() ? r.MemberTemplate() : 
                    (( j == 0 ) ? m_templateStr_col1 : 
                    (( j == 1 ) ? m_templateStr_col2 : m_templateStr_col3 )));

                pStatic1->SetCaption ( (_bstr_t)result.c_str());
            }
            
            else
            {
                term = true;
                break;
            }
            }
            
        }

        
      
        //
        //  DST
        //

        
        
        {
        strstream fieldName;
        fieldName << "dst" << i+1 << ends;

        CComPtr<ISkinObject> pDst;
	    m_pMainWnd->FindObject((_bstr_t)fieldName.str(), &pDst);
        if ( pDst )
        {
            if ( IsDaylightSavings ((m_pageNum * itemsPerPage ) + i, t ))
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( FALSE );
        }
        }

        //
        // Location type
        //

        {
        strstream fieldName;
        fieldName << "type" << i+1 << ends;

    	CComPtr<ISkinObject> pType;
	    m_pMainWnd->FindObject((_bstr_t)fieldName.str(), &pType);
        if ( pType )
        {
            if ( IsPerson ( (m_pageNum * itemsPerPage ) + i ))
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( FALSE );
        }
        }

        //
        //  Alarm
        //

        {
        strstream fieldName;
        fieldName << "alarm" << i+1 << ends;

        CComPtr<ISkinObject> palarm;
	    m_pMainWnd->FindObject((_bstr_t)fieldName.str(), &palarm);
        if ( palarm )
        {
            if ( IsAlarmSet ( (m_pageNum * itemsPerPage ) + i ))
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( FALSE );
        }
        
        
        }
        
        
          
    }

  */                             
     
	CComPtr<ISkinObject> pText1;
	m_pMainWnd->FindObject(L"text1_col1", &pText1);
    if ( pText1 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText1);
        GetLocationText ((m_pageNum * itemsPerPage ) + 0, t, result, r.UseTemplate() ? r.MemberTemplate() : m_templateStr_col1 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());

//        itemsPerPage = 1;
    }

    
	CComPtr<ISkinObject> pText1_col2;
	m_pMainWnd->FindObject(L"text1_col2", &pText1_col2);
    if ( pText1_col2 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText1_col2);
        GetLocationText ((m_pageNum * itemsPerPage ) + 0, t, result, r.UseTemplate() ? r.MemberTemplate2() : m_templateStr_col2 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }

	CComPtr<ISkinObject> pText1_col3;
	m_pMainWnd->FindObject(L"text1_col3", &pText1_col3);
    if ( pText1_col3 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText1_col3);
        GetLocationText ((m_pageNum * itemsPerPage ) + 0, t, result, r.UseTemplate() ? r.MemberTemplate3() : m_templateStr_col3 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }

      



	CComPtr<ISkinObject> pText2;
	m_pMainWnd->FindObject(L"text2_col1", &pText2);
    if ( pText2 )
    {
    	CComQIPtr<ISkinStatic> pStatic2(pText2);
        GetLocationText ((m_pageNum * itemsPerPage ) + 1, t, result, r.UseTemplate() ? r.MemberTemplate() : m_templateStr_col1 ) ;
        pStatic2->SetCaption ( (_bstr_t)result.c_str());

//        itemsPerPage = 2;
    }

	CComPtr<ISkinObject> pText2_col2;
	m_pMainWnd->FindObject(L"text2_col2", &pText2_col2);
    if ( pText2_col2 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText2_col2);
        GetLocationText ((m_pageNum * itemsPerPage ) + 1, t, result, r.UseTemplate() ? r.MemberTemplate2() : m_templateStr_col2 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }

	CComPtr<ISkinObject> pText2_col3;
	m_pMainWnd->FindObject(L"text2_col3", &pText2_col3);
    if ( pText2_col3 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText2_col3);
        GetLocationText ((m_pageNum * itemsPerPage ) + 1, t, result, r.UseTemplate() ? r.MemberTemplate3() : m_templateStr_col3 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }






	CComPtr<ISkinObject> pText3;
	m_pMainWnd->FindObject(L"text3_col1", &pText3);
    if ( pText3 )
    {
    	CComQIPtr<ISkinStatic> pStatic3(pText3);
        GetLocationText ((m_pageNum * itemsPerPage ) + 2, t, result, r.UseTemplate() ? r.MemberTemplate() : m_templateStr_col1 ) ;
        pStatic3->SetCaption ( (_bstr_t)result.c_str());

  //      itemsPerPage = 3;
    }

	CComPtr<ISkinObject> pText3_col2;
	m_pMainWnd->FindObject(L"text3_col2", &pText3_col2);
    if ( pText3_col2 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText3_col2);
        GetLocationText ((m_pageNum * itemsPerPage ) + 2, t, result, r.UseTemplate() ? r.MemberTemplate2() : m_templateStr_col2 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }

	CComPtr<ISkinObject> pText3_col3;
	m_pMainWnd->FindObject(L"text3_col3", &pText3_col3);
    if ( pText3_col3 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText3_col3);
        GetLocationText ((m_pageNum * itemsPerPage ) + 2, t, result, r.UseTemplate() ? r.MemberTemplate3() : m_templateStr_col3 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }





	CComPtr<ISkinObject> pText4;
	m_pMainWnd->FindObject(L"text4_col1", &pText4);
    if ( pText4 )
    {
    	CComQIPtr<ISkinStatic> pStatic4(pText4);
        GetLocationText ((m_pageNum * itemsPerPage ) + 3, t, result, r.UseTemplate() ? r.MemberTemplate() : m_templateStr_col1 ) ;
        pStatic4->SetCaption ( (_bstr_t)result.c_str());

//        itemsPerPage = 4;
    }

	CComPtr<ISkinObject> pText4_col2;
	m_pMainWnd->FindObject(L"text4_col2", &pText4_col2);
    if ( pText4_col2 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText4_col2);
        GetLocationText ((m_pageNum * itemsPerPage ) + 3, t, result, r.UseTemplate() ? r.MemberTemplate2() : m_templateStr_col2 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }

	CComPtr<ISkinObject> pText4_col3;
	m_pMainWnd->FindObject(L"text4_col3", &pText4_col3);
    if ( pText4_col3 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText4_col3);
        GetLocationText ((m_pageNum * itemsPerPage ) + 3, t, result, r.UseTemplate() ? r.MemberTemplate3() : m_templateStr_col3 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }





	CComPtr<ISkinObject> pText5;
	m_pMainWnd->FindObject(L"text5_col1", &pText5);
    if ( pText5 )
    {
    	CComQIPtr<ISkinStatic> pStatic5(pText5);
        GetLocationText ((m_pageNum * itemsPerPage ) + 4, t, result, r.UseTemplate() ? r.MemberTemplate() : m_templateStr_col1 ) ;
        pStatic5->SetCaption ( (_bstr_t)result.c_str());

  //      itemsPerPage = 5;
    }

	CComPtr<ISkinObject> pText5_col2;
	m_pMainWnd->FindObject(L"text5_col2", &pText5_col2);
    if ( pText5_col2 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText5_col2);
        GetLocationText ((m_pageNum * itemsPerPage ) + 4, t, result, r.UseTemplate() ? r.MemberTemplate2() : m_templateStr_col2 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }

	CComPtr<ISkinObject> pText5_col3;
	m_pMainWnd->FindObject(L"text5_col3", &pText5_col3);
    if ( pText5_col3 )
    {
    	CComQIPtr<ISkinStatic> pStatic1(pText5_col3);
        GetLocationText ((m_pageNum * itemsPerPage ) + 4, t, result, r.UseTemplate() ? r.MemberTemplate3() : m_templateStr_col3 ) ;
        pStatic1->SetCaption ( (_bstr_t)result.c_str());
    }

        
   
     
      
//    CComQIPtr<ISkinVisual>(pText5)->SetVisible ( FALSE );
       
    //
    // set DST visibility
    //
   
    {
    	CComPtr<ISkinObject> pDst;
	    m_pMainWnd->FindObject(L"dst1", &pDst);
        if ( pDst )
        {
            if ( IsDaylightSavings ((m_pageNum * itemsPerPage ) + 0, t ))
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pDst;
	    m_pMainWnd->FindObject(L"dst2", &pDst);
        if ( pDst )
        {
            if ( IsDaylightSavings ( (m_pageNum * itemsPerPage ) + 1, t ))
               CComQIPtr<ISkinVisual>(pDst)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pDst;
	    m_pMainWnd->FindObject(L"dst3", &pDst);
        if ( pDst )
        {
            if ( IsDaylightSavings ( (m_pageNum * itemsPerPage ) + 2, t ))
               CComQIPtr<ISkinVisual>(pDst)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pDst;
	    m_pMainWnd->FindObject(L"dst4", &pDst);
        if ( pDst )
        {
            if ( IsDaylightSavings ( (m_pageNum * itemsPerPage ) + 3, t ))
               CComQIPtr<ISkinVisual>(pDst)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pDst;
	    m_pMainWnd->FindObject(L"dst5", &pDst);
        if ( pDst )
        {
            if ( IsDaylightSavings ( (m_pageNum * itemsPerPage ) + 4, t ))
               CComQIPtr<ISkinVisual>(pDst)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pDst)->SetVisible ( FALSE );
        }
    }
        

    //
    //  If a person, show the image
    //

    {
    	CComPtr<ISkinObject> pType;
	    m_pMainWnd->FindObject(L"type1", &pType);
        if ( pType )
        {
            if ( IsPerson ( (m_pageNum * itemsPerPage ) + 0 ))
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pType;
	    m_pMainWnd->FindObject(L"type2", &pType);
        if ( pType )
        {
            if ( IsPerson ( (m_pageNum * itemsPerPage ) + 1 ))
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pType;
	    m_pMainWnd->FindObject(L"type3", &pType);
        if ( pType )
        {
            if ( IsPerson ( (m_pageNum * itemsPerPage ) + 2 ))
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pType;
	    m_pMainWnd->FindObject(L"type4", &pType);
        if ( pType )
        {
            if ( IsPerson ( (m_pageNum * itemsPerPage ) + 3 ))
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> pType;
	    m_pMainWnd->FindObject(L"type5", &pType);
        if ( pType )
        {
            if ( IsPerson ( (m_pageNum * 5 ) + itemsPerPage ))
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(pType)->SetVisible ( FALSE );
        }
    }



    //
    //  Is alarm enabled
    //

    {
    	CComPtr<ISkinObject> palarm;
	    m_pMainWnd->FindObject(L"alarm1", &palarm);
        if ( palarm )
        {
            if ( IsAlarmSet ( (m_pageNum * itemsPerPage ) + 0 ))
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> palarm;
	    m_pMainWnd->FindObject(L"alarm2", &palarm);
        if ( palarm )
        {
            if ( IsAlarmSet ( (m_pageNum * itemsPerPage ) + 1 ))
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> palarm;
	    m_pMainWnd->FindObject(L"alarm3", &palarm);
        if ( palarm )
        {
            if ( IsAlarmSet ( (m_pageNum * itemsPerPage ) + 2 ))
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> palarm;
	    m_pMainWnd->FindObject(L"alarm4", &palarm);
        if ( palarm )
        {
            if ( IsAlarmSet ( (m_pageNum * itemsPerPage ) + 3 ))
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( FALSE );
        }
    }

    {
    	CComPtr<ISkinObject> palarm;
	    m_pMainWnd->FindObject(L"alarm5", &palarm);
        if ( palarm )
        {
            if ( IsAlarmSet ( (m_pageNum * itemsPerPage ) + 4 ))
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( TRUE );
            else
                CComQIPtr<ISkinVisual>(palarm)->SetVisible ( FALSE );
        }
    }
    

  
    //
    //  page
    //

	CComPtr<ISkinObject> pPage;
	m_pMainWnd->FindObject(L"page", &pPage);
    if ( pPage )
    {

        
    	CComQIPtr<ISkinStatic> pStaticPage(pPage);

//        SkinLogFont font;
//        pStaticPage->GetFont ( &font );
//        strstream sout;
//        sout << "Page " << m_pageNum + 1 << ends;
        static char buf[20];
        sprintf ( buf, "Page %d", m_pageNum + 1 );
        pStaticPage->SetCaption ( (_bstr_t)buf);
//        pStaticPage->SetCaption ( (_bstr_t)sout.str());
    }

    

    CComQIPtr<ISkinVisual>(m_pMainWnd)->Refresh();

    ProcessAlarms ( t );
    
    ProcessChimes ( t );

	CDialog::OnTimer(nIDEvent);

    processing = false;

    return;


    /*
    int whichLoc = 0;
    MemberItem * mItem = m.GetMemberByIdx ( whichLoc );
    if ( mItem )
    {
        LocationItem * lItem = l.GetLocationbyTag ( mItem->locRef );
        if ( lItem == 0 )
        {
        // remove member from group with bad location reference
//        aGroup->DeleteList ( *aMemberTag ); //members.Delete ( mItem ); //aMemberTag );
//        return 0;
        }
    }

  */


	CDialog::OnTimer(nIDEvent);
}

void CSkinDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
    RECT rect;
    GetWindowRect ( &rect );

    if ( rect.left >= 0 && rect.top >= 0 && rect.right >= 0 && rect.bottom >= 0 &&
         rect.right > rect.left && rect.bottom > rect.top )
    {
        // only save screen coords if the look valid
        r.WinLeft( rect.left);
        r.WinTop( rect.top );
        r.WinRight( rect.right );
        r.WinBottom( rect.bottom );
    }

 // TODO: Add your message handler code here
    m.Save ();
//    g.Save ();
    l.Save ();

    r.WriteRegistry ();
}


void CSkinDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
	
    CDialog::OnClose();
//	if (m_bShutdown)
//		CDialog::OnClose();
//	else
		ShowWindow(SW_HIDE);
	
}

//#include "timesync.h"
//#include <afxinet.h>

void CSkinDlg::OnDblClickSkin(LPUNKNOWN Source) 
{
	// TODO: Add your control notification handler code here
    USES_CONVERSION;
    CComBSTR bstrName; // Name of the SkinObject that has generated Click event
    CComQIPtr<ISkinObject> pSkinObject = Source; // Get this SkinObject
    pSkinObject->GetName(&bstrName); // Get its name

    if ( bstrName == "alarm1" ||
         bstrName == "alarm2" ||
         bstrName == "alarm3" ||
         bstrName == "alarm4" ||
         bstrName == "alarm5" 
        )
    {
        CDlgAlarms dlg;
        dlg.DoModal ();

        return;

    }
	
    /*
    if ( bstrName == "text1_col1" ||
         bstrName == "text1_col2" ||
         bstrName == "text1_col3"
       )
    {
        MemberItem * mItem = m.GetMemberByIdx ( 0 );
        if ( mItem == 0 )
            return;

        CDlgMemberAdd dlg;

        dlg.m_locRef = mItem->LocRef();
        dlg.m_name = mItem->Name().c_str();
        dlg.m_email = mItem->Email().c_str();
        dlg.m_phone = mItem->Phone().c_str();
        dlg.m_location = mItem->Location();
  
        if ( dlg.DoModal () != IDOK )
            return;

        mItem->LocRef ( dlg.m_locRef );
        mItem->Name ( dlg.m_name );
        mItem->Email ( dlg.m_email );
        mItem->Phone ( dlg.m_phone );
        mItem->Location ( dlg.m_location ? true : false );

    }

  */
//    const int NumDisplayLines = 5;

    for ( int i = 0; i < itemsPerPage; i++ )
    {
        strstream col1Str;
        col1Str << "text" << i + 1 << "_col1" << ends;
        strstream col2Str;
        col2Str << "text" << i + 1 << "_col2" << ends;
        strstream col3Str;
        col3Str << "text" << i + 1 << "_col3" << ends;
                
        if ( bstrName == col1Str.str() ||
             bstrName == col2Str.str() ||
             bstrName == col3Str.str() )
        {
            MemberItem * mItem = m.GetMemberByIdx (( m_pageNum * itemsPerPage ) + i );
            if ( mItem == 0 )
                return;

            CDlgMemberAdd dlg;

            dlg.m_locRef = mItem->LocRef();
            dlg.m_name = mItem->Name().c_str();
            dlg.m_email = mItem->Email().c_str();
            dlg.m_phone = mItem->Phone().c_str();
            dlg.m_location = mItem->Location();
  
            if ( dlg.DoModal () != IDOK )
                return;

            mItem->LocRef ( dlg.m_locRef );
            mItem->Name ( dlg.m_name );
            mItem->Email ( dlg.m_email );
            mItem->Phone ( dlg.m_phone );
            mItem->Location ( dlg.m_location ? true : false );

            return;
        }
    }

}


void CSkinDlg::OnMouseDownSkin(LPUNKNOWN Source, long Button, long x, long y) 
{
//    USES_CONVERSION;
//    CComBSTR bstrName; // Name of the SkinObject that has generated Click event
//    CComQIPtr<ISkinObject> pSkinObject = Source; // Get this SkinObject
//    pSkinObject->GetName(&bstrName); // Get its name

	// TODO: Add your control notification handler code here

}




