#if !defined(AFX_DLGLOCATION_H__0478295C_7C35_43BE_A814_59D7A4C3199F__INCLUDED_)
#define AFX_DLGLOCATION_H__0478295C_7C35_43BE_A814_59D7A4C3199F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLocation.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CDlgLocation dialog

class CDlgLocation : public CDialog
{
// Construction
public:
	CDlgLocation(CWnd* pParent = NULL);   // standard constructor
    ~CDlgLocation( void ) { delete m_images; }

    void RedrawList ( int = -1 );
    CImageList * m_images;

// Dialog Data
	//{{AFX_DATA(CDlgLocation)
	enum { IDD = IDD_LOCATIONS };
	CString 	m_top;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLocation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLocation)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkLocationList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLocationAdd();
	afx_msg void OnLocationProperties();
	afx_msg void OnLocationRemove();
	afx_msg void OnColumnclickLocationList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOCATION_H__0478295C_7C35_43BE_A814_59D7A4C3199F__INCLUDED_)
