// onLineTimeView.h : interface of the COnLineTimeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ONLINETIMEVIEW_H__4039EF7E_8CDC_4BEA_8BDC_243FAE9AE001__INCLUDED_)
#define AFX_ONLINETIMEVIEW_H__4039EF7E_8CDC_4BEA_8BDC_243FAE9AE001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//#include "memdc.h"
#include "location.h"

enum DisplayType { DL_Icon, DL_Text };

struct DisplayItem
{
    DisplayType type;

    HICON icon;
    int x, y;
    string text;
    CFont * font;
    COLORREF color;
};

struct DisplayList
{
    CRect       bounds;
    int         numDisplayItems;
    CSize       adj;
    CPoint      offset;
    bool        drag;

    DisplayItem data[20];

    void Reset ( void ) 
    { 
        bounds.left = bounds.top = INT_MAX;
        bounds.right = bounds.bottom = INT_MIN;
        adj.cx = adj.cy = 0;
        numDisplayItems = 0;
        // dont clear the offset to allow dragging
//        offset = CPoint ( 0, 0 );

    }
    CRect & Bounds ( void ) { return bounds; }

    DisplayList ( void );
//    void Render ( CView *, CDC * memDC, CRect & frameRect, bool );
    void Render ( CView *, CDC & memDC, CRect & frameRect, bool, bool, float = 0.0f, float = 0.0f );
    void Add ( int x, int y, HICON icon );
    void Add ( int x, int y, CSize & size, string & text, CFont * font );
};

struct DisplayCollection
{
    int numDisplayLists;

    DisplayList data[100];
    
    DisplayCollection ( void ) { numDisplayLists = 0; }
};

extern DisplayCollection displayData;
//extern string windowText[10];

class COnLineTimeView
{
protected: // create from serialization only
	COnLineTimeView();

// Attributes
public:
    LinkedList<CRect * > rectLL;
//    bool listView;

    void DrawTime ( CDC & memDC, DisplayList & dl, LocationItem * li, CTime * t, int x, int y, float offset );
    void DrawLocation ( CDC & memDC, CTime * t, int x, int y );
//    float MemberTime ( LocationItem * li, CTime & ti );
//    int DaylightSavings ( LocationItem * li, CTime * t );

// Operations
public:
// Overrides

// Implementation
public:
	virtual ~COnLineTimeView();

protected:

// Generated message map functions
protected:
};

extern COnLineTimeView * mainView;
//extern int DaylightSavings ( LocationItem * li, CTime * t );

//#ifndef _DEBUG  // debug version in onLineTimeView.cpp
//inline COnLineTimeDoc* COnLineTimeView::GetDocument()
//   { return (COnLineTimeDoc*)m_pDocument; }
//#endif

extern void GetLocationText ( int whichLoc, CTime & t, string & result, string & templateText );
extern bool IsDaylightSavings ( int whichLoc, CTime & t );
extern bool IsPerson ( int whichLoc );
extern bool IsAlarmSet ( int whichLoc );
float MemberTime ( LocationItem * li, CTime & ti );

extern DisplayCollection displayData;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONLINETIMEVIEW_H__4039EF7E_8CDC_4BEA_8BDC_243FAE9AE001__INCLUDED_)
