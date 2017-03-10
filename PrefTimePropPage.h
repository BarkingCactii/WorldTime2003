#if !defined(AFX_PREFTIMEPROPPAGE_H__03927C27_7113_4722_89CB_937565D715C4__INCLUDED_)
#define AFX_PREFTIMEPROPPAGE_H__03927C27_7113_4722_89CB_937565D715C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefTimePropPage.h : header file
//

#include "label.h"

/////////////////////////////////////////////////////////////////////////////
// CPrefTimePropPage dialog

class CPrefTimePropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefTimePropPage)

// Construction
public:
	CPrefTimePropPage();
	~CPrefTimePropPage();

// Dialog Data
	//{{AFX_DATA(CPrefTimePropPage)
	enum { IDD = IDD_PREFERENCES_TIME };
	BOOL	m_24Hour;
	BOOL	m_showAM;
	BOOL	m_detailed;
	BOOL	m_alwaysOnTop;
	//}}AFX_DATA
//    COLORREF m_backgroundColor;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefTimePropPage)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefTimePropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFTIMEPROPPAGE_H__03927C27_7113_4722_89CB_937565D715C4__INCLUDED_)
