// PrefMainPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "onlinetime.h"
#include "PrefMainPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrefMainPropPage property page

IMPLEMENT_DYNCREATE(CPrefMainPropPage, CPropertyPage)

CPrefMainPropPage::CPrefMainPropPage() : CPropertyPage(CPrefMainPropPage::IDD)
{
	//{{AFX_DATA_INIT(CPrefMainPropPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPrefMainPropPage::~CPrefMainPropPage()
{
}

void CPrefMainPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefMainPropPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefMainPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefMainPropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrefMainPropPage message handlers
