#if !defined(AFX_DLGLOCATIONDETAILS_H__19C31085_004E_415D_8A3F_7A4043DDEAE1__INCLUDED_)
#define AFX_DLGLOCATIONDETAILS_H__19C31085_004E_415D_8A3F_7A4043DDEAE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLocationDetails.h : header file
//

#include "location.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgLocationDetails dialog

class CDlgLocationDetails : public CDialog
{
// Construction
public:
	CDlgLocationDetails(CWnd* pParent = NULL);   // standard constructor
    LocationItem * m_lItem;

// Dialog Data
	//{{AFX_DATA(CDlgLocationDetails)
	enum { IDD = IDD_LOCATION_DETAILS };
	CEdit	m_nameCtrl;
	CComboBox	m_dsStartDay;
	CComboBox	m_dsStartWeek;
	CComboBox	m_dsStartMonth;
	CComboBox	m_dsEndMonth;
	CComboBox	m_dsEndWeek;
	CComboBox	m_dsEndDay;
	CSliderCtrl	m_sliderCtrl;
	CString	m_country;
	BOOL	m_dsEnable;
	float	m_latitude;
	float	m_longitude;
	CString	m_city;
	UINT	m_areaCode;
	UINT	m_countryCode;
	CString	m_ew;
	CString	m_ns;
	CString	m_hours;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLocationDetails)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLocationDetails)
	afx_msg void OnLocDetailsDst();
	virtual BOOL OnInitDialog();
	afx_msg void OnAddHours();
	afx_msg void OnCustomdrawLocDetailsDstoffset(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOCATIONDETAILS_H__19C31085_004E_415D_8A3F_7A4043DDEAE1__INCLUDED_)
