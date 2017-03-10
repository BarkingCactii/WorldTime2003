// Skin.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Skin.h"
#include "SkinDlg.h"
#include "regdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinApp

BEGIN_MESSAGE_MAP(CSkinApp, CWinApp)
	//{{AFX_MSG_MAP(CSkinApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinApp construction

CSkinApp::CSkinApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSkinApp object

CSkinApp theApp;

RegistryCollection r ( "software\\WorldTime2003" );

/////////////////////////////////////////////////////////////////////////////
// CSkinApp initialization

BOOL CSkinApp::InitInstance()
{
  //  AfxOleInit(); //added

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CSkinDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

#include "member.h"

BOOL CSkinApp::SaveAllModified()
{
//    m.Save();

    return TRUE;
}


int CSkinApp::ExitInstance()
{
//    m.Save();
    return CWinApp::ExitInstance();
}
