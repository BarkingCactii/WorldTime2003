#if !defined(AFX_PREFPROPSHEET_H__481912CC_ABAE_47D6_8980_8E677316BB07__INCLUDED_)
#define AFX_PREFPROPSHEET_H__481912CC_ABAE_47D6_8980_8E677316BB07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefPropSheet.h : header file
//

#include "PrefMainPropPage.h"
#include "PrefTemplatePropPage.h"
#include "PrefSoundsPropPage.h"
#include "PrefTimePropPage.h"
//#include "PrefMapPropPage.h"
#include "PrefLocationPropPage.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefPropSheet

class CPrefPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CPrefPropSheet)

// Construction
public:
	CPrefPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPrefPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
//    CPrefMainPropPage m_page1;
    CPrefTemplatePropPage m_page5;
    CPrefSoundsPropPage m_page4;
    CPrefTimePropPage m_page3;
    CPrefLocationPropPage m_page2;
//    CPrefMapPropPage m_page1;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrefPropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPrefPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPrefPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFPROPSHEET_H__481912CC_ABAE_47D6_8980_8E677316BB07__INCLUDED_)
