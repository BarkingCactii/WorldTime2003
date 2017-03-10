#if !defined(AFX_DLGALARMMESSAGE_H__EAAA38F4_97B3_480B_A98E_CA0DEB8C6054__INCLUDED_)
#define AFX_DLGALARMMESSAGE_H__EAAA38F4_97B3_480B_A98E_CA0DEB8C6054__INCLUDED_

#include "member.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmMessage dialog

class CDlgAlarmMessage : public CDialog
{
// Construction
public:
	CDlgAlarmMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    AlarmItem * m_aItem;
	//{{AFX_DATA(CDlgAlarmMessage)
	enum { IDD = IDD_ALARM_MESSAGE };
	CString	m_location;
	CString	m_message;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmMessage)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMMESSAGE_H__EAAA38F4_97B3_480B_A98E_CA0DEB8C6054__INCLUDED_)
