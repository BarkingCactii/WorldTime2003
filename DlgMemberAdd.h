#if !defined(AFX_DLGMEMBERADD_H__F8933BF3_DB46_4611_BB80_4213E957D49D__INCLUDED_)
#define AFX_DLGMEMBERADD_H__F8933BF3_DB46_4611_BB80_4213E957D49D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMemberAdd.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDlgMemberAdd dialog

class CDlgMemberAdd : public CDialog
{
// Construction
public:
	CDlgMemberAdd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMemberAdd)
	enum { IDD = IDD_MEMBER_ADD };
	CComboBox	m_listOld;
	CStatic	m_personIcon;
	CStatic	m_locationIcon;
	CListCtrl	m_list;
	CEdit	m_nameCtrl;
	CString	m_email;
	CString	m_name;
	CString	m_phone;
	BOOL	m_location;
	//}}AFX_DATA
    int m_locRef;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMemberAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    void RedrawList ( int = -1 );

	// Generated message map functions
	//{{AFX_MSG(CDlgMemberAdd)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMemberAddLocation();
	afx_msg void OnMemberAddLoconly();
	virtual void OnOK();
	afx_msg void OnColumnclickLocationList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMEMBERADD_H__F8933BF3_DB46_4611_BB80_4213E957D49D__INCLUDED_)
