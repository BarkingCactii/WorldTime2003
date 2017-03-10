////////////////////////////////////////////////////////////////
// CTrayIcon Copyright 1996 Microsoft Systems Journal.
//
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.

#include "stdafx.h"
#include "trayicon.h"
#include <afxpriv.h>		// for AfxLoadString
#include <strstream>
#include "skin.h"
#include "skindlg.h"

//#include "onlinetime.h"
#include "resource.h"
#include "location.h"
#include "member.h"
#include "displaylocation.h"
#include "regdata.h"

IMPLEMENT_DYNAMIC(CTrayIcon, CCmdTarget)

UINT jeff;

CTrayIcon::CTrayIcon(UINT uID)
{
	// Initialize NOTIFYICONDATA
	memset(&m_nid, 0 , sizeof(m_nid));
	m_nid.cbSize = sizeof(m_nid);
	m_nid.uID = uID;	// never changes after construction

	// Use resource string as tip if there is one
	AfxLoadString(uID, m_nid.szTip, sizeof(m_nid.szTip));
//    sprintf ( m_nid.szTip, "JEFFY" );
        jeff=uID;
}

CTrayIcon::~CTrayIcon()
{
	SetIcon(0); // remove icon from system tray
}

//////////////////
// Set notification window. It must created already.
//
void CTrayIcon::SetNotificationWnd(CWnd* pNotifyWnd, UINT uCbMsg)
{
	// If the following assert fails, you're probably
	// calling me before you created your window. Oops.
	ASSERT(pNotifyWnd==NULL || ::IsWindow(pNotifyWnd->GetSafeHwnd()));
	m_nid.hWnd = pNotifyWnd->GetSafeHwnd();

	ASSERT(uCbMsg==0 || uCbMsg>=WM_USER);
	m_nid.uCallbackMessage = uCbMsg;
}


//////////////////
// This is the main variant for setting the icon.
// Sets both the icon and tooltip from resource ID
// To remove the icon, call SetIcon(0)
//
BOOL CTrayIcon::SetIcon(UINT uID, char *tip)
{ 
	HICON hicon=NULL;
	if (uID) {
		AfxLoadString(uID, m_nid.szTip, sizeof(m_nid.szTip));
		hicon = AfxGetApp()->LoadIcon(uID);
	}
	return SetIcon(hicon, tip ); //NULL ); //tip ); //NULL);
}

//////////////////
// Common SetIcon for all overloads. 
//
BOOL CTrayIcon::SetIcon(HICON hicon, LPCSTR lpTip) 
{
	UINT msg;
	m_nid.uFlags = 0;

	// Set the icon
	if (hicon) {
		// Add or replace icon in system tray
		msg = m_nid.hIcon ? NIM_MODIFY : NIM_ADD;
		m_nid.hIcon = hicon;
		m_nid.uFlags |= NIF_ICON;
	} else { // remove icon from tray
		if (m_nid.hIcon==NULL)
			return TRUE;		// already deleted
		msg = NIM_DELETE;
	}

	// Use the tip, if any
	if (lpTip)
		strncpy(m_nid.szTip, lpTip, sizeof(m_nid.szTip));
	if (m_nid.szTip[0])
		m_nid.uFlags |= NIF_TIP;

	// Use callback if any
	if (m_nid.uCallbackMessage && m_nid.hWnd)
		m_nid.uFlags |= NIF_MESSAGE;

	// Do it
	BOOL bRet = Shell_NotifyIcon(msg, &m_nid);
	if (msg==NIM_DELETE || !bRet)
		m_nid.hIcon = NULL;	// failed
	return bRet;
}


int DST ( void )
{
     struct tm *newtime;
     time_t long_time;

     time( &long_time );                /* Get time as long integer. */
     newtime = localtime( &long_time ); /* Convert to local time. */

     if ( newtime->tm_isdst )
          return 1;
     return 0;
}

/////////////////
// Default event handler handles right-menu and doubleclick.
// Call this function from your own notification handler.
//

long val = 0;
LRESULT CTrayIcon::OnTrayNotification(WPARAM wID, LPARAM lEvent)
{

     // custom change
//     _tzset();
//     sprintf ( m_nid.szTip, "Zone is %s", _tzname[0]);

    string trayStr;// = "test";
    bool term = false;


    for ( int i = 0; i < itemsPerPage; i++ )
    {
        //
        // location text
        //

        CTime t = CTime::GetCurrentTime();

        for ( int j = 0; j < 2; j++ )
        {
            strstream fieldName;
            fieldName << "text" << i+1 << "_col" << j+1 << ends;

//            if (( term = SetField ( t, fieldName.str(), i, j )) == true )
//                break;
            /*
            CComPtr<ISkinObject> pText;
            m_pMainWnd->FindObject ((_bstr_t)fieldName, &pText);
            if ( pText )
            {
                CComQIPtr<ISkinStatic> pStatic1(pText);
                */

                /*
                GetLocationText ((m_pageNum * itemsPerPage ) + i, t, result,
                    r.UseTemplate() ? r.MemberTemplate() :
                    (( j == 0 ) ? m_templateStr_col1 :
                    (( j == 1 ) ? m_templateStr_col2 : m_templateStr_col3 )));
                  */
                string result;
                string templateStr;
                templateStr = (( j == 0 ) ? "%n   " : (( j == 1 ) ? "%t" : " %d" ));

                GetLocationText ((main->m_pageNum * itemsPerPage ) + i, t, result, templateStr );
//                    (( j == 0 ) ? "%n   " :
//                    (( j == 1 ) ? "%t" : " %d" )));

                if ( result == "" )
                    term = true;
                trayStr += result.c_str();
                if ( j == 1 && i < itemsPerPage - 1)
                    trayStr += "\n";
//                else
//                    trayStr += "";
//                pStatic1->SetCaption ( (_bstr_t)result.c_str());
                /*
            }
            else
            {
                term = true;
            }
            */
        }
    }






     sprintf ( m_nid.szTip, "WorldTime2003\n%d alarm(s)\n%s", m.AlarmsPending(), trayStr.c_str());
   //  sprintf ( m_nid.szTip, "WorldTime2003\n%d alarm(s) pending\n%s", m.AlarmsPending(), trayStr.c_str());
//     sprintf ( m_nid.szTip, "WorldTime2003\n%d alarm(s) pending", m.AlarmsPending());
/*
     clock_t currentProcess = clock();
     double duration = (double)(currentProcess - startProcess) / CLOCKS_PER_SEC;

     sprintf ( m_nid.szTip, "Uptime is %.1lf secs\n%d alarm(s) pending\nDST is %s", duration, l.AlarmsPending(), DST()? "on" : "off");
  */
     if ( wID == m_nid.uID && lEvent != WM_RBUTTONUP && lEvent != WM_LBUTTONDBLCLK )
     	Shell_NotifyIcon(NIM_MODIFY, &m_nid);
     // end custom change

	if (wID!=m_nid.uID ||
		(lEvent!=WM_RBUTTONUP && lEvent!=WM_LBUTTONDBLCLK))
		return 0;

	// If there's a resource menu with the same ID as the icon, use it as 
	// the right-button popup menu. CTrayIcon will interprets the first
	// item in the menu as the default command for WM_LBUTTONDBLCLK
	// 
	CMenu menu;
	if (!menu.LoadMenu(m_nid.uID))
		return 0;
	CMenu* pSubMenu = menu.GetSubMenu(0);
	if (!pSubMenu) 
		return 0;

	if (lEvent==WM_RBUTTONUP) {

		// Make first menu item the default (bold font)
		::SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE);

		// Display the menu at the current mouse location. There's a "bug"
		// (Microsoft calls it a feature) in Windows 95 that requires calling
		// SetForegroundWindow. To find out more, search for Q135788 in MSDN.
		//
		CPoint mouse;
		GetCursorPos(&mouse);
		::SetForegroundWindow(m_nid.hWnd);	
		::TrackPopupMenu(pSubMenu->m_hMenu, 0, mouse.x, mouse.y, 0,
			m_nid.hWnd, NULL);

	} else  // double click: execute first menu item
		::SendMessage(m_nid.hWnd, WM_COMMAND, pSubMenu->GetMenuItemID(0), 0);

	return 1; // handled
}
