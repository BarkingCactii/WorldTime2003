// PrefTimePropPage.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "PrefTimePropPage.h"
#include "regdata.h"
#include "DlgUpdater.h"
#include "skinDlg.h"
#include "htmlhelp.h"

//#include "OnLineTimeView.h"
#include <strstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "label.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefTimePropPage property page

IMPLEMENT_DYNCREATE(CPrefTimePropPage, CPropertyPage)

CPrefTimePropPage::CPrefTimePropPage() : CPropertyPage(CPrefTimePropPage::IDD)
{
	//{{AFX_DATA_INIT(CPrefTimePropPage)
	m_24Hour = r.Show24Hour();
	m_showAM = r.ShowAM();
    m_detailed = r.ShowDetailed();
	m_alwaysOnTop = r.AlwaysOnTop();
	//}}AFX_DATA_INIT
}

CPrefTimePropPage::~CPrefTimePropPage()
{
}

void CPrefTimePropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefTimePropPage)
	DDX_Check(pDX, IDC_PREFERENCES_24HOUR, m_24Hour);
	DDX_Check(pDX, IDC_PREFERENCES_SHOWAM, m_showAM);
	DDX_Check(pDX, IDC_PREFERENCES_DETAILED, m_detailed);
	DDX_Check(pDX, IDC_PREFERENCES_TOPMOST, m_alwaysOnTop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefTimePropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefTimePropPage)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefTimePropPage message handlers

BOOL CPrefTimePropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    SetModified ( TRUE );

	// TODO: Add extra initialization here

    strstream sout;

    sout << r.FontName().c_str() << " " 
         << ( int ) (r.FontSize() / 10) 
         << ( r.FontItalic() ? " Italic" : "" )
         << ( r.FontBold() ? " Bold" : "" )
         << ends << flush;


//    m_message.SetFontItalic ( TRUE );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefTimePropPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
//    r.BackgroundColor ( m_backgroundColor );

	r.Show24Hour( m_24Hour );
//	r.ShowSeconds( m_showSeconds );
	r.ShowAM( m_showAM );

    r.ShowDetailed ( m_detailed );

    r.AlwaysOnTop ( m_alwaysOnTop );
//     mainView->Invalidate ( FALSE );

        if ( m_alwaysOnTop )
            main->SetWindowPos ( &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
        else
            main->SetWindowPos ( &wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );

	CPropertyPage::OnOK();
}

BOOL CPrefTimePropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
    SetModified ( TRUE );
	
	return CPropertyPage::OnSetActive();
}

void CPrefTimePropPage::OnUpdate() 
{
	// TODO: Add your control notification handler code here
    CDlgUpdater dlg;
    dlg.DoModal ();
	
}

BOOL CPrefTimePropPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
    NMHDR* phdr = (NMHDR*)lParam;

    switch(phdr->code)
    {
        case PSN_HELP:
        {
// fix            HtmlHelp(NULL, "WorldTIme2003.chm::/preferences_time.htm", HH_DISPLAY_TOPIC, 0);
            return TRUE;
        break;
        }
    }

	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}
