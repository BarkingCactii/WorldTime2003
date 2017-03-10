// PrefPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "PrefPropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefPropSheet

IMPLEMENT_DYNAMIC(CPrefPropSheet, CPropertySheet)

CPrefPropSheet::CPrefPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPrefPropSheet::CPrefPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
//    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//    m_psh.dwFlags |= PSP_USEHICON;
//    m_psh.hIcon = m_hIcon;
//    m_psh.dwFlags |= PSH_NOAPPLYNOW;    // Lose the Apply Now button
    m_psh.dwFlags &= ~PSH_HASHELP;  // Lose the Help button

//    m_psh.dwFlags = PSH_DEFAULT;
//    AddPage(&m_page1);
//    AddPage(&m_page2);
    AddPage(&m_page3);
    AddPage(&m_page4);
    AddPage(&m_page5);
}

CPrefPropSheet::~CPrefPropSheet()
{
}


BEGIN_MESSAGE_MAP(CPrefPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CPrefPropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefPropSheet message handlers
