// DlgMember.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "DlgMember.h"
#include "DlgMemberAdd.h"
#include "location.h"
#include "member.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlgMember dialog


CDlgMember::CDlgMember(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMember::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMember)
	//}}AFX_DATA_INIT
    m_images = new CImageList;
}


void CDlgMember::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMember)
	DDX_Control(pDX, IDC_MEMBER_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMember, CDialog)
	//{{AFX_MSG_MAP(CDlgMember)
	ON_BN_CLICKED(IDC_MEMBER_PROPERTIES, OnMemberProperties)
	ON_BN_CLICKED(IDC_MEMBER_ADD, OnMemberAdd)
	ON_BN_CLICKED(IDC_MEMBER_REMOVE, OnMemberRemove)
	ON_NOTIFY(NM_DBLCLK, IDC_MEMBER_LIST, OnDblclkMemberList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMember message handlers

/*
void CDlgMember::OnDblclkMemberList() 
{
	// TODO: Add your control notification handler code here

    return;

    // ?? CRASHES 
    OnMemberProperties() ;

}
  */
void CDlgMember::RedrawList ( int selection )
{
//    GroupItem * group = g.groups.Nth ( m_group );

    m_list.DeleteAllItems ();

    for ( int i = 0; i < m.Size (); i++ )
    {
        int tag = m.Tag ( i );
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


/*
void CDlgMember::RedrawList ( void )
{
    m_list.ResetContent ();
    for ( int i = 0; i < m.Size(); i++ )
    {
        string name;
        if ( m.Name ( name, i ) == false )
            break;

        m_list.AddString ( name.c_str());
    }
}
  */
BOOL CDlgMember::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

//	VERIFY(m_list.SubclassDlgItem(IDC_GROUP_LIST, this));

    // load regdata into coloritem array

//    RedrawList();

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


    RedrawList ();

    /*
    for ( int i = 0; i < m.Size(); i++ )
    {
        string name;
        if ( m.Name ( name, i ) == false )
            break;

        m_list.AddString ( name.c_str());
    }
	  */
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDlgMember::ShowMemberPropDlg( MemberItem * mItem ) 
{
	// TODO: Add your control notification handler code here
    CDlgMemberAdd dlg;

    dlg.m_locRef = mItem->LocRef();
    dlg.m_name = mItem->Name().c_str();
    dlg.m_email = mItem->Email().c_str();
    dlg.m_phone = mItem->Phone().c_str();
    dlg.m_location = mItem->Location();
  
    if ( dlg.DoModal () != IDOK )
        return false;

    mItem->LocRef ( dlg.m_locRef );
    mItem->Name ( dlg.m_name );
    mItem->Email ( dlg.m_email );
    mItem->Phone ( dlg.m_phone );
    mItem->Location ( dlg.m_location ? true : false );

    m.SetModified();

    return true;
}


void CDlgMember::OnMemberProperties() 
{
	// TODO: Add your control notification handler code here
    
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;
    int nItem = m_list.GetNextSelectedItem(pos);

    MemberItem * mItem = m.GetMemberbyTag ( m_list.GetItemData ( nItem ));
    if ( mItem == 0 )
        return;

    if ( ShowMemberPropDlg( mItem ))
        RedrawList ( nItem );

    RedrawList ( nItem );
}

void CDlgMember::OnMemberAdd() 
{
	// TODO: Add your control notification handler code here
    CDlgMemberAdd dlg;
    if ( dlg.DoModal () != IDOK )
        return;


    MemberItem * mItem = new MemberItem;
    mItem->LocRef ( dlg.m_locRef );
    mItem->Name ( dlg.m_name );
    mItem->Email ( dlg.m_email );
    mItem->Phone ( dlg.m_phone );
    mItem->Location ( dlg.m_location ? true : false );
    m.Add ( mItem );

    RedrawList ();

    m.SetModified();
}

void CDlgMember::OnMemberRemove() 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;
    int nItem = m_list.GetNextSelectedItem(pos);

    if ( MessageBox ( "Are you sure ?", "Delete Member", MB_OKCANCEL | MB_ICONEXCLAMATION ) != IDOK )
        return;

    // also need to remove members from groups, maybe something to do when doing a search
    m.DeleteList ( m_list.GetItemData ( nItem ));	
//    m_list.DeleteItem ( nItem );
    RedrawList ( nItem );

    m.SetModified();

}

void CDlgMember::OnDblclkMemberList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    OnMemberProperties() ;
	
	*pResult = 0;
}
