// PrefTemplatePropPage.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "PrefTemplatePropPage.h"
#include "RegData.h"
//#include "OnLineTimeView.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefTemplatePropPage property page

IMPLEMENT_DYNCREATE(CPrefTemplatePropPage, CPropertyPage)

CPrefTemplatePropPage::CPrefTemplatePropPage() : CPropertyPage(CPrefTemplatePropPage::IDD)
{
	//{{AFX_DATA_INIT(CPrefTemplatePropPage)
	m_template = r.MemberTemplate().c_str(); //_T("");
	m_overrideTemplate = r.UseTemplate();
	m_template2 = r.MemberTemplate2().c_str(); //_T("");
	m_template3 = r.MemberTemplate3().c_str(); //_T("");
	//}}AFX_DATA_INIT
}

CPrefTemplatePropPage::~CPrefTemplatePropPage()
{
}

void CPrefTemplatePropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefTemplatePropPage)
	DDX_Text(pDX, IDC_PROPERTIES_TEMPLATE, m_template);
	DDX_Check(pDX, IDC_PROPERTIES_USETEMPLATE, m_overrideTemplate);
	DDX_Text(pDX, IDC_PROPERTIES_TEMPLATE2, m_template2);
	DDX_Text(pDX, IDC_PROPERTIES_TEMPLATE3, m_template3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefTemplatePropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefTemplatePropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefTemplatePropPage message handlers

BOOL CPrefTemplatePropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
//    m_message.SetFontItalic ( TRUE );


	// TODO: Add extra initialization here

    /*
    m_variablesCtrl.AddString ( "%n Name" );
    m_variablesCtrl.AddString ( "%t Time" );
    m_variablesCtrl.AddString ( "%d Date" );
    m_variablesCtrl.AddString ( "%o Country Code" );
    m_variablesCtrl.AddString ( "%l Latitude/Longitude" );
    m_variablesCtrl.AddString ( "%s Daylight Savings ?" );
    m_variablesCtrl.AddString ( "%e Email" );
    m_variablesCtrl.AddString ( "%p Phone Number" );
    m_variablesCtrl.AddString ( "%c Country" );
    m_variablesCtrl.AddString ( "%u Sunrise/Sunset" );
      */
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPrefTemplatePropPage::OnSetActive() 
{
    // force the apply button to show
    SetModified ( TRUE );
	
	return CPropertyPage::OnSetActive();
}

void CPrefTemplatePropPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
    r.MemberTemplate ( ( string ) m_template );
    r.MemberTemplate2 ( ( string ) m_template2 );
    r.MemberTemplate3 ( ( string ) m_template3 );
    r.UseTemplate( m_overrideTemplate );

//    r.ListTemplate ( ( string ) m_listTemplate );
//    r.ShowMarquee ( m_showMarquee );
    
//     mainView->Invalidate ( FALSE );

	CPropertyPage::OnOK();
}

BOOL CPrefTemplatePropPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
    NMHDR* phdr = (NMHDR*)lParam;

    switch(phdr->code)
    {
        case PSN_HELP:
        {
// fix            HtmlHelp(NULL, "WorldTIme2003.chm::/preferences_template.htm", HH_DISPLAY_TOPIC, 0);
            return TRUE;
        break;
        }
    }

	
	return CPropertyPage::OnNotify(wParam, lParam, pResult);
}
