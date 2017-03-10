#if !defined(AFX_DLGALARMDETAILS_H__87B741A5_DA2B_4259_B9F4_22CD72F52B33__INCLUDED_)
#define AFX_DLGALARMDETAILS_H__87B741A5_DA2B_4259_B9F4_22CD72F52B33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmDetails.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmDetails dialog

class CDlgAlarmDetails : public CDialog
{
// Construction
public:
	CDlgAlarmDetails(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmDetails)
	enum { IDD = IDD_ALARM };
	CComboBox	m_recurring;
	CListCtrl	m_list;
	CString	m_appName;
	CTime	m_date;
	CString	m_message;
	BOOL	m_playSound;
	BOOL	m_runApp;
	CTime	m_time;
	//}}AFX_DATA
    int     m_member; // current selection for m_list
    int     m_memberTag; // current selection for m_list's tag
    int     m_recurringVal; // current selection for m_recurring
    bool    m_properties; // true if properties, false if adding an alarm

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void RedrawList ( int = -1 );
    CImageList * m_images;
	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmDetails)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	afx_msg void OnAlarmChooseapp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMDETAILS_H__87B741A5_DA2B_4259_B9F4_22CD72F52B33__INCLUDED_)
