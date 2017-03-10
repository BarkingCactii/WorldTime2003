#if !defined(AFX_PREFMAINPROPPAGE_H__5AA8D738_CFC2_442F_8589_0AA477B42C75__INCLUDED_)
#define AFX_PREFMAINPROPPAGE_H__5AA8D738_CFC2_442F_8589_0AA477B42C75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefMainPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrefMainPropPage dialog

class CPrefMainPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefMainPropPage)

// Construction
public:
	CPrefMainPropPage();
	~CPrefMainPropPage();

// Dialog Data
	//{{AFX_DATA(CPrefMainPropPage)
	enum { IDD = IDD_PREFERENCES };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefMainPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefMainPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFMAINPROPPAGE_H__5AA8D738_CFC2_442F_8589_0AA477B42C75__INCLUDED_)
