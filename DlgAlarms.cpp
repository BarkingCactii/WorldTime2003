// DlgAlarms.cpp : implementation file
//

#include "stdafx.h"
#include "Skin.h"
#include "DlgAlarms.h"
#include "location.h"
#include "member.h"
#include "DlgAlarmDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarms dialog


CDlgAlarms::CDlgAlarms(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarms::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarms)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_images = new CImageList;

}


void CDlgAlarms::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarms)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarms, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarms)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_ALARMS_ADD, OnAlarmsAdd)
	ON_BN_CLICKED(IDC_ALARMS_PROPERTIES, OnAlarmsProperties)
	ON_BN_CLICKED(IDC_ALARMS_REMOVE, OnAlarmsRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarms message handlers

void  CDlgAlarms::RedrawList( int selection ) 
{
//    m_list.SetBkColor ( 0x00d0d0d0 );
//    m_list.SetTextBkColor ( 0x00e0e0e0 );
    m_list.DeleteAllItems ();


    MemberItem * member;
    for ( int i = 0; member = m.GetMemberByIdx ( i ); i++ )
    {
//        int tag = m.Tag ( i );
//        MemberItem * member = m.GetMemberbyTag ( tag );
//        MemberItem * member = m.GetMemberByIdx ( i );
        int tag = member->Tag();

        // JH NEW
//        if ( member == 0 )
//            continue;

//        if ( !member->alarmActive )
//            continue;

        int actualItem = 0;

        for ( int j = 0; j < member->NumAlarms(); j++ )
        {
            AlarmItem * ai = member->GetAlarm ( j );
            if ( !ai )
                continue;
            // alarm is set for this member
            LVITEM lvitem;
            lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM; // | LVIF_STATE; // |
            lvitem.iItem = i;
            lvitem.iSubItem = 0;

            if ( member->Location() )
                lvitem.iImage = 1;
            else
                lvitem.iImage = 0;
//        int tag = 0;
//        int tag = l.Tag ( i );
            int tagMask = tag + (j << 16 );

            lvitem.lParam = tagMask;
            LocationItem * lItem = l.GetLocationbyTag ( member->LocRef() );

//            CString str;
            if ( lItem )
            {
                if ( member->Location() )
                {
//                    str = lItem->city.c_str();
//                    lvitem.pszText = str.GetBuffer ( 0 );
                    lvitem.pszText = ( char * )lItem->city.c_str();
                }
                else
                    lvitem.pszText = ( char * )member->Name().c_str();
            }
            else
                    lvitem.pszText = ( char * )"Unknown";
            


//            int tagMask = tag + (j << 16 );
//            m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tagMask);

            actualItem = m_list.InsertItem ( &lvitem );
                                              
            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = actualItem;
//            lvitem.iItem = i;
            lvitem.iSubItem = 1;
            lvitem.pszText = ( char * )lItem->country.c_str();
            lvitem.lParam = tagMask;
            lvitem.iImage = 0;
//            m_list.InsertItem ( &lvitem );
//            if ( m_list.InsertItem ( &lvitem ) == -1 )
//              MessageBox ( "Error Setting List item", "" );
            m_list.SetItem ( &lvitem );

            
            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = actualItem;
        //    lvitem.iItem = i;
            lvitem.iSubItem = 2;
            CString s = ai->Time().Format( "%I:%M %p - %b %d, %Y" );

//            lvitem.pszText = (char *)( const char * )s; 
            lvitem.pszText = s.GetBuffer(0); 
//            if ( m_list.InsertItem ( &lvitem ) == -1 )
//              MessageBox ( "Error Setting Insert Item", "" );
          m_list.SetItem ( &lvitem );
//              MessageBox ( "Error Setting List item", "" );
            
            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = actualItem;
          //  lvitem.iItem = i;
            lvitem.iSubItem = 3;
            switch ( ai->Occurence ())
            {
            case Once:
                lvitem.pszText = "Once";
                break;
            case Daily:
                lvitem.pszText = "Daily";
                break;
            case Weekly:
                lvitem.pszText = "Weekly";
                break;
            case Fortnightly:
                lvitem.pszText = "Fortnightly";
                break;
            case Monthly:
                lvitem.pszText = "Monthly";
                break;
            }
//            m_list.InsertItem ( &lvitem );
          m_list.SetItem ( &lvitem );


            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = actualItem;
            //lvitem.iItem = i;
            lvitem.iSubItem = 4;
            lvitem.pszText = ( char * )ai->Message().c_str();
//            m_list.InsertItem ( &lvitem );
          m_list.SetItem ( &lvitem );
              
//            int tagMask = tag + (j << 16 );
//            m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tagMask);
//        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );
            
        }

    }
    if ( selection != -1 )
    {
        m_list.EnsureVisible ( selection, FALSE );
        m_list.SetItemState ( selection, LVIS_SELECTED | LVIS_FOCUSED, -1 ); //0xffff, LVIS_SELECTED );
    }


//    m_list.Update ( 0 );
}

BOOL CDlgAlarms::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_images->Create(16, 16, ILC_COLOR16 | ILC_MASK, 2, 2 );
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_MEMBER ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_LOCATION ));
    m_list.SetImageList ( m_images, LVSIL_SMALL );

    m_list.InsertColumn(0, "Location", LVCFMT_LEFT, 130, 0);
    m_list.InsertColumn(1, "Country", LVCFMT_LEFT, 130, 1);
    m_list.InsertColumn(2, "Time", LVCFMT_LEFT, 160, 2);
    m_list.InsertColumn(3, "Occurs", LVCFMT_LEFT, 90, 3);
    m_list.InsertColumn(4, "Action", LVCFMT_LEFT, 220, 4);


    RedrawList();
/*
    for ( int i = 0; i < 6; i++ )
    {
        LVITEM lvitem;
        lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM; // | LVIF_STATE; // |
        lvitem.iItem = i;
        lvitem.iSubItem = 0;

        lvitem.iImage = i;
        int tag = 0;
//        int tag = l.Tag ( i );
        lvitem.lParam = tag;

        switch ( i )
        {
        case 0:
              lvitem.pszText = "Display";
                break;
        case 1:
              lvitem.pszText = "Edit locations database";
                break;
        case 2:
              lvitem.pszText = "Alarms";
                break;
        case 3:
              lvitem.pszText = "User Settings";
                break;
        case 4:
              lvitem.pszText = "Skins";
                break;
        case 5:
              lvitem.pszText = "Help";
                break;
        }

        m_list.InsertItem ( &lvitem );
//        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );

    }

  */
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarms::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
    delete m_images;
    
	CDialog::OnClose();
}

void CDlgAlarms::OnAlarmsAdd() 
{
	// TODO: Add your control notification handler code here
    CDlgAlarmDetails dlg;

    dlg.m_recurringVal = 0;    
//    dlg.m_properties = false;

    if ( dlg.DoModal () != IDOK )
        return ;

//     AlarmItem ( CTime & newDate, CTime & newTime, Recurring newRecurring,
//         bool newPlaySound, string & newMessageText, bool NewAppRun, string & newAppRunText )

    AlarmItem * aItem = new AlarmItem ( dlg.m_date, dlg.m_time, ( Recurring )dlg.m_recurringVal,
        dlg.m_playSound ? true : false, dlg.m_message,
        dlg.m_runApp ? true : false, dlg.m_appName );

/*    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;
    int nItem = m_list.GetNextSelectedItem(pos);
  */
    MemberItem * mItem = m.GetMemberbyTag ( dlg.m_memberTag );
//    MemberItem * mItem = m.GetMemberByIdx ( dlg.m_member );
    if ( mItem )
        mItem->Add ( aItem );

    RedrawList ();

    /*
    dlg.m_locRef = mItem->LocRef();
    dlg.m_name = mItem->Name().c_str();
    dlg.m_email = mItem->Email().c_str();
    dlg.m_phone = mItem->Phone().c_str();
    dlg.m_location = mItem->Location();
  */
    /*
    mItem->LocRef ( dlg.m_locRef );
    mItem->Name ( dlg.m_name );
    mItem->Email ( dlg.m_email );
    mItem->Phone ( dlg.m_phone );
    mItem->Location ( dlg.m_location ? true : false );

    return true;
*/	
}

void CDlgAlarms::OnAlarmsProperties() 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;
    int nItem = m_list.GetNextSelectedItem(pos);

    int memberTag = m_list.GetItemData ( nItem ) & 0x0000ffff;
    MemberItem * mItem = m.GetMemberbyTag ( memberTag );
    if ( mItem == 0 )
        return;

    int alarmTag = m_list.GetItemData ( nItem ) & 0xffff0000;
    alarmTag >>= 16;

    AlarmItem * aItem;
    aItem = mItem->GetAlarm ( alarmTag );
    if ( !aItem )
        return;

    
    CDlgAlarmDetails dlg;

    dlg.m_date = aItem->Time();
    dlg.m_time = aItem->Time();
    dlg.m_recurringVal = aItem->Occurence();    
    dlg.m_playSound = aItem->PlaySound();
    dlg.m_message = aItem->Message().c_str();
    dlg.m_runApp = aItem->RunApp ();
    dlg.m_appName = aItem->AppName().c_str();

    dlg.m_properties = true;
    dlg.m_memberTag = memberTag;

    if ( dlg.DoModal () != IDOK )
        return ;

    aItem->Reset ( dlg.m_date, dlg.m_time, ( Recurring )dlg.m_recurringVal,
        dlg.m_playSound ? true : false, dlg.m_message,
        dlg.m_runApp ? true : false, dlg.m_appName );


//     AlarmItem ( CTime & newDate, CTime & newTime, Recurring newRecurring,
//         bool newPlaySound, string & newMessageText, bool NewAppRun, string & newAppRunText )

//    AlarmItem * aItem = new AlarmItem ( dlg.m_date, dlg.m_time, ( Recurring )dlg.m_recurringVal,
//        dlg.m_playSound ? true : false, dlg.m_message,
//        dlg.m_runApp ? true : false, dlg.m_appName );


//    if ( ShowMemberPropDlg( mItem ))
//        RedrawList ( nItem );

    RedrawList ( nItem );
	
}

void CDlgAlarms::OnAlarmsRemove() 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;
    int nItem = m_list.GetNextSelectedItem(pos);

    if ( MessageBox ( "Are you sure ?", "Delete Alarm", MB_OKCANCEL | MB_ICONEXCLAMATION ) != IDOK )
        return;

    // also need to remove members from groups, maybe something to do when doing a search
    int memberTag, alarmTag;

//    int test = m_list.GetItemData ( nItem );
    memberTag = m_list.GetItemData ( nItem ) & 0x0000ffff;
    alarmTag = m_list.GetItemData ( nItem ) & 0xffff0000;
    alarmTag >>= 16;

    m.DeleteAlarm ( memberTag, alarmTag );	
//    m_list.DeleteItem ( nItem );
    RedrawList ( nItem );
	
}

void CDlgAlarms::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    OnAlarmsProperties ();
    
	*pResult = 0;
}
