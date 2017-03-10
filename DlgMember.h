#if !defined(AFX_DLGMEMBER_H__FF241F04_038C_40EC_9D98_79C3C6013D94__INCLUDED_)
#define AFX_DLGMEMBER_H__FF241F04_038C_40EC_9D98_79C3C6013D94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMember.h : header file
//

#include "member.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMember dialog

class CDlgMember : public CDialog
{
// Construction
public:
	CDlgMember(CWnd* pParent = NULL);   // standard constructor
    ~CDlgMember( void ) { delete m_images; }

    void RedrawList ( int = -1 );
    CImageList * m_images;

// Dialog Data
	//{{AFX_DATA(CDlgMember)
	enum { IDD = IDD_MEMBERS };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMember)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
    public:
    bool ShowMemberPropDlg( MemberItem * mItem );
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMember)
	virtual BOOL OnInitDialog();
	afx_msg void OnMemberProperties();
	afx_msg void OnMemberAdd();
	afx_msg void OnMemberRemove();
	afx_msg void OnDblclkMemberList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMEMBER_H__FF241F04_038C_40EC_9D98_79C3C6013D94__INCLUDED_)
