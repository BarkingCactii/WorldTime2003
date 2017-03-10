#if !defined(AFX_PREFLocationPropPAGE_H__B5FC0940_178C_4C03_9BDE_C125B8E064E4__INCLUDED_)
#define AFX_PREFLocationPropPAGE_H__B5FC0940_178C_4C03_9BDE_C125B8E064E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefLocationPropPage.h : header file
//

#include "label.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefLocationPropPage dialog

class CPrefLocationPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefLocationPropPage)

// Construction
public:
	CPrefLocationPropPage();
	~CPrefLocationPropPage();

// Dialog Data
	//{{AFX_DATA(CPrefLocationPropPage)
	enum { IDD = IDD_PREFERENCES_LOCATIONS };
	CComboBox	m_locBackgroundType;
	CLabel	m_message;
	BOOL	m_showAll;
	BOOL	m_useTemplate;
	//}}AFX_DATA
    int m_manualUpdate;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefLocationPropPage)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefLocationPropPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFLocationPropPAGE_H__B5FC0940_178C_4C03_9BDE_C125B8E064E4__INCLUDED_)
