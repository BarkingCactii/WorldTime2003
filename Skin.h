// Skin.h : main header file for the SKIN application
//

#if !defined(AFX_SKIN_H__4BAF6467_B5A6_40BA_9F3A_D041D1631C86__INCLUDED_)
#define AFX_SKIN_H__4BAF6467_B5A6_40BA_9F3A_D041D1631C86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkinApp:
// See Skin.cpp for the implementation of this class
//

class CSkinApp : public CWinApp
{
public:
	CSkinApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinApp)
	public:
	virtual BOOL InitInstance();
    virtual BOOL SaveAllModified();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSkinApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKIN_H__4BAF6467_B5A6_40BA_9F3A_D041D1631C86__INCLUDED_)
