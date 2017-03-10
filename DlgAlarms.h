#if !defined(AFX_DLGALARMS_H__D885F5BE_CFA6_4C98_8EA5_F3627573CD5F__INCLUDED_)
#define AFX_DLGALARMS_H__D885F5BE_CFA6_4C98_8EA5_F3627573CD5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarms.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarms dialog

class CDlgAlarms : public CDialog
{
// Construction
public:
	CDlgAlarms(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarms)
	enum { IDD = IDD_ALARMS };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarms)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    CImageList * m_images;
    void RedrawList ( int = -1 );
	// Generated message map functions
	//{{AFX_MSG(CDlgAlarms)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnAlarmsAdd();
	afx_msg void OnAlarmsProperties();
	afx_msg void OnAlarmsRemove();
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMS_H__D885F5BE_CFA6_4C98_8EA5_F3627573CD5F__INCLUDED_)
