// DlgAlarmMessage.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "DlgAlarmMessage.h"
#include "sounds.h"
#include "regdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmMessage dialog


CDlgAlarmMessage::CDlgAlarmMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmMessage)
	m_location = _T("");
	m_message = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAlarmMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmMessage)
	DDX_Text(pDX, IDC_ALARM_DETAILS, m_location);
	DDX_Text(pDX, IDC_ALARMMESSAGE, m_message);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmMessage, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmMessage)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmMessage message handlers

void CDlgAlarmMessage::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    CTime t = CTime::GetCurrentTime();


    if ((t.GetSecond() % 10 ) == 0 )
        // play a sound
        Playsound ( r.SoundAlarmFile().c_str(), m_aItem->PlaySound() ? ( r.SoundAlarm() ? true : false) : false ); //r.SoundAlarm() ? true : false);


	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgAlarmMessage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    SetTimer ( 101, 1000, NULL );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
