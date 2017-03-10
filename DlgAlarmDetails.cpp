// DlgAlarmDetails.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "DlgAlarmDetails.h"
#include "location.h"
#include "member.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmDetails dialog


CDlgAlarmDetails::CDlgAlarmDetails(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmDetails)
	m_appName = _T("");
	m_date = CTime::GetCurrentTime();
	m_message = _T("<no message>");
	m_playSound = TRUE;
	m_runApp = FALSE;
	m_time = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
    m_images = new CImageList;
    m_member = 0;
    m_memberTag = 0;
    m_properties = false;
}


void CDlgAlarmDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmDetails)
	DDX_Control(pDX, IDC_ALARM_RECURRING, m_recurring);
	DDX_Control(pDX, IDC_MEMBER_LIST, m_list);
	DDX_Text(pDX, IDC_ALARM_APPNAME, m_appName);
	DDX_DateTimeCtrl(pDX, IDC_ALARM_DATE, m_date);
	DDX_Text(pDX, IDC_ALARM_MESSAGE, m_message);
	DDX_Check(pDX, IDC_ALARM_PLAYSOUND, m_playSound);
	DDX_Check(pDX, IDC_ALARM_RUNAPP, m_runApp);
	DDX_DateTimeCtrl(pDX, IDC_ALARM_TIME, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmDetails, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmDetails)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_ALARM_CHOOSEAPP, OnAlarmChooseapp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgAlarmDetails::RedrawList ( int selection )
{
//    GroupItem * group = g.groups.Nth ( m_group );

    m_list.DeleteAllItems ();

    for ( int i = 0; i < m.Size (); i++ )
    {
        int tag = m.Tag ( i );
        if ( m_properties )
        {
            // only display item this detail refers to
            if ( tag != m_memberTag )
                continue;
        }

        MemberItem * member = m.GetMemberbyTag ( tag );

        // JH NEW
        if ( member == 0 )
            continue;

//        MemberItem * member = m.GetMemberbyTag ( m.Tag ( i ));
//        int * ref = group->members.Nth ( i );
//        MemberItem * member = m.GetMemberbyTag ( *ref ); //group->members.Nth ( i );
        LVITEM lvitem;
        lvitem.mask = LVIF_TEXT | LVIF_IMAGE; // | LVIF_STATE; // |
        lvitem.iItem = i;
        lvitem.iSubItem = 0;
        if ( member->Location() )
        {
            lvitem.iImage = 1;
            LocationItem * lItem = l.GetLocationbyTag ( member->LocRef() );
            if ( lItem && lItem->city.size())
            {
                string label = lItem->city; //( char * ) group->Name ().c_str();
//                label += ", ";
//
//                label += lItem->country;

                lvitem.pszText = ( char * ) label.c_str(); //( char * ) group->Name ().c_str();
//                lvitem.pszText = ( char * ) lItem->city.c_str(); //( char * ) group->Name ().c_str();
            }
            else
                lvitem.pszText = "???";
        }
        else
        {
            lvitem.iImage = 0;
            lvitem.pszText = ( char * ) member->Name().c_str(); //( char * ) group->Name ().c_str();
        }
        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );
    }

    if ( selection != -1 )
    {
        m_list.EnsureVisible ( selection, FALSE );
        m_list.SetItemState ( selection, LVIS_SELECTED | LVIS_FOCUSED, -1 ); //0xffff, LVIS_SELECTED );
    }


}


/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmDetails message handlers

BOOL CDlgAlarmDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CRect rect;
    m_list.GetWindowRect(&rect);
    m_list.InsertColumn(0, "Member Name", LVCFMT_LEFT, ( rect.Width() / 2 ) - 5, 0);

    m_images->Create(16, 16, ILC_COLOR16 | ILC_MASK, 2, 2);
//    images->Create(32, 32, TRUE, 4, 4);
//    images->Add ( AfxGetApp()->LoadIcon ( IDI_PEOPLE ));
         m_images->Add ( AfxGetApp()->LoadIcon ( IDI_MEMBER ));
         m_images->Add ( AfxGetApp()->LoadIcon ( IDI_LOCATION ));
//         images->Add ( AfxGetApp()->LoadIcon ( IDI_DEFAULT ));
//    images->Create(32, 32, ILC_COLOR4 | ILC_MASK, 4, 4);
    m_list.SetImageList ( m_images, LVSIL_SMALL );


    RedrawList ( );

    m_recurring.SetCurSel ( m_recurringVal );

    if ( m_properties )
    {
        m_list.EnableWindow ( FALSE);
        GetDlgItem ( IDOK )->SetWindowText ( "Change" ); 

    }
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmDetails::OnClose() 
{

	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CDlgAlarmDetails::OnOK() 
{
	// TODO: Add extra validation here
    if ( !m_properties )
    {
        // only if adding a new alarm

        POSITION pos = m_list.GetFirstSelectedItemPosition();
        if (pos == NULL)
        {
            MessageBox ( "No Member selected", "Error", MB_OK | MB_ICONERROR );
            return;
        }
        m_member = m_list.GetNextSelectedItem(pos);
        m_memberTag = m_list.GetItemData ( m_member );
    }

    m_recurringVal = m_recurring.GetCurSel();

	
	CDialog::OnOK();
}

void CDlgAlarmDetails::OnAlarmChooseapp() 
{

	// TODO: Add your control notification handler code here
    string appToRun;
      char * filterBuf= "Applications\0*.exe;*.cmo\0\0\0";
      CFileDialog openD ( TRUE );

      openD.m_ofn.lpstrFilter = filterBuf;
      openD.m_ofn.lpstrInitialDir = ".\\";
      openD.m_ofn.lpstrTitle = "Select Application to run on Alarm";

     if ( openD.DoModal () == IDOK )
     {
          appToRun = openD.m_ofn.lpstrFile;
          SetDlgItemText ( IDC_ALARM_APPNAME, ( char *) appToRun.c_str() );
          //
          // open file and read data
          //
//     wallpaper = LoadImage( 0, openD.m_ofn.lpstrFile, IMAGE_BITMAP, 0, 0,
//LR_LOADFROMFILE | LR_DEFAULTSIZE );

//  if ( wallpaper == NULL )
//   l.p.showWallpaper = 0;

//        l.p.wallpaperName = openD.m_ofn.lpstrFile;
      }
	
}
