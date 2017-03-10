// PrefLocationPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "PrefLocationPropPage.h"
#include "regdata.h"
//#include "OnLineTimeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefLocationPropPage property page

IMPLEMENT_DYNCREATE(CPrefLocationPropPage, CPropertyPage)

CPrefLocationPropPage::CPrefLocationPropPage() : CPropertyPage(CPrefLocationPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPrefLocationPropPage)
	m_showAll = r.ShowAll();
	m_useTemplate = r.UseTemplate();
	//}}AFX_DATA_INIT
}

CPrefLocationPropPage::~CPrefLocationPropPage()
{
}

void CPrefLocationPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefLocationPropPage)
	DDX_Control(pDX, IDC_PREFERENCES_LOCBACKGROUND, m_locBackgroundType);
	DDX_Control(pDX, IDC_MESSAGE, m_message);
	DDX_Check(pDX, IDC_PREFERENCES_SHOWALL, m_showAll);
	DDX_Check(pDX, IDC_PREFERENCES_USETEMPLATE, m_useTemplate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefLocationPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefLocationPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefLocationPropPage message handlers


BOOL CPrefLocationPropPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    SetModified ( TRUE );

	// TODO: Add extra initialization here

//    m_manualUpdate = r.ManualView ();
    int controlID = ( m_manualUpdate ) ? IDC_PREFERENCES_MANUALUPDATE : IDC_PREFERENCES_AUTOUPDATE;
    CheckRadioButton ( IDC_PREFERENCES_AUTOUPDATE, IDC_PREFERENCES_MANUALUPDATE, controlID );

    m_message.SetFontItalic ( TRUE );


//    m_locBackgroundType.SetCurSel ( r.LocBackgroundType());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefLocationPropPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class

//     r.ManualView ( m_manualUpdate );

	r.ShowAll( m_showAll);
	r.UseTemplate(m_useTemplate);
//	r.UpdateInterval ( m_updateInterval);

//     r.LocBackgroundType ( m_locBackgroundType.GetCurSel ());

//     mainView->Invalidate ( FALSE );
	CPropertyPage::OnOK();
}


BOOL CPrefLocationPropPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
    SetModified ( TRUE );
	
	return CPropertyPage::OnSetActive();
}

