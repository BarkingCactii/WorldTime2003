#if !defined(AFX_PREFTEMPLATEPROPPAGE_H__FEAD3A2E_7693_47A3_AB0C_D37F98483541__INCLUDED_)
#define AFX_PREFTEMPLATEPROPPAGE_H__FEAD3A2E_7693_47A3_AB0C_D37F98483541__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefTemplatePropPage.h : header file
//

#include "label.h"
/////////////////////////////////////////////////////////////////////////////
// CPrefTemplatePropPage dialog

class CPrefTemplatePropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefTemplatePropPage)

// Construction
public:
	CPrefTemplatePropPage();
	~CPrefTemplatePropPage();

// Dialog Data
	//{{AFX_DATA(CPrefTemplatePropPage)
	enum { IDD = IDD_PREFERENCES_TEMPLATE };
	CString	m_template;
	BOOL	m_overrideTemplate;
	CString	m_template2;
	CString	m_template3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefTemplatePropPage)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefTemplatePropPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFTEMPLATEPROPPAGE_H__FEAD3A2E_7693_47A3_AB0C_D37F98483541__INCLUDED_)
