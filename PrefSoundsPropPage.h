#if !defined(AFX_PREFSOUNDSPROPPAGE_H__553DA0B0_1A4B_41EA_9B60_40AC0177D2EC__INCLUDED_)
#define AFX_PREFSOUNDSPROPPAGE_H__553DA0B0_1A4B_41EA_9B60_40AC0177D2EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefSoundsPropPage.h : header file
//

#include "label.h"

/////////////////////////////////////////////////////////////////////////////
// CPrefSoundsPropPage dialog

class CPrefSoundsPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefSoundsPropPage)

// Construction
public:
	CPrefSoundsPropPage();
	~CPrefSoundsPropPage();

// Dialog Data
	//{{AFX_DATA(CPrefSoundsPropPage)
	enum { IDD = IDD_PREFERENCES_SOUNDS };
	CLabel	m_alarmFileCtrl;
	CLabel	m_hourFileCtrl;
	CLabel	m_quarterFileCtrl;
	BOOL	m_alarm;
	BOOL	m_hour;
	BOOL	m_quarter;
	CString	m_quarterFile;
	CString	m_hourFile;
	CString	m_alarmFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefSoundsPropPage)
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
	//{{AFX_MSG(CPrefSoundsPropPage)
	afx_msg void OnSoundalarm();
	afx_msg void OnSoundhour();
	afx_msg void OnSoundquarter();
	virtual BOOL OnInitDialog();
	afx_msg void OnAlarmTest();
	afx_msg void OnHourTest();
	afx_msg void OnQuarterTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSOUNDSPROPPAGE_H__553DA0B0_1A4B_41EA_9B60_40AC0177D2EC__INCLUDED_)
