// SkinDlg.h : header file
//

#if !defined(AFX_SKINDLG_H__AA01751D_6FF8_4937_A17E_521DE0153461__INCLUDED_)
#define AFX_SKINDLG_H__AA01751D_6FF8_4937_A17E_521DE0153461__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "trayicon.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinDlg dialog

class CSkinDlg : public CDialog
{
// Construction
public:
	CSkinDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSkinDlg)
	enum { IDD = IDD_SKIN_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
    public:
	CComPtr<ISkinObject> m_pMainWnd; // A reference to the root SkinObject of the form
    void ApplySkin ( char * );
    void InitData ( void );
    void DrawLocalTime ( CTime & );
	CComQIPtr<ISkin> m_pSkin; // Holds a reference to the Skin control, that is placed into the form
    int m_pageNum;
    string m_templateStr_col1;
protected:
    bool SetField ( CTime &, char * , int, int );
	HICON m_hIcon;
    string m_templateStr_col2;
    string m_templateStr_col3;
    CTrayIcon m_trayIcon;

    



	// Generated message map functions
	//{{AFX_MSG(CSkinDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickSkin(LPUNKNOWN Source);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
     afx_msg LRESULT OnTrayNotification(WPARAM wp, LPARAM lp);
	afx_msg void OnClose();
	afx_msg void OnDblClickSkin(LPUNKNOWN Source);
	afx_msg void OnMouseDownSkin(LPUNKNOWN Source, long Button, long x, long y);
    afx_msg void OnTrayRestore();
    afx_msg void OnTrayExit();
    afx_msg void OnTrayAbout();
    afx_msg void OnTrayOptions();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSkinDlg * main;
extern int itemsPerPage;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINDLG_H__AA01751D_6FF8_4937_A17E_521DE0153461__INCLUDED_)
