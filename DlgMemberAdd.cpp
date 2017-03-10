// DlgMemberAdd.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "DlgMemberAdd.h"
#include "location.h"
#include "member.h"
#include <strstream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMemberAdd dialog


CDlgMemberAdd::CDlgMemberAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMemberAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMemberAdd)
	m_email = _T("");
	m_name = _T("");
	m_phone = _T("");
	m_location = TRUE;
	//}}AFX_DATA_INIT
    m_locRef = 0;
}


void CDlgMemberAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMemberAdd)
	DDX_Control(pDX, IDC_MEMBER_ADD_LOCATION, m_listOld);
	DDX_Control(pDX, IDC_LOCATION_PERSONICON, m_personIcon);
	DDX_Control(pDX, IDC_LOCATION_LOCATIONICON, m_locationIcon);
	DDX_Control(pDX, IDC_LOCATION_LIST, m_list);
	DDX_Control(pDX, IDC_MEMBER_ADD_NAME, m_nameCtrl);
	DDX_Text(pDX, IDC_MEMBER_ADD_EMAIL, m_email);
	DDX_Text(pDX, IDC_MEMBER_ADD_NAME, m_name);
	DDX_Text(pDX, IDC_MEMBER_ADD_PHONE, m_phone);
	DDX_Check(pDX, IDC_MEMBER_ADD_LOCONLY, m_location);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMemberAdd, CDialog)
	//{{AFX_MSG_MAP(CDlgMemberAdd)
	ON_CBN_SELCHANGE(IDC_MEMBER_ADD_LOCATION, OnSelchangeMemberAddLocation)
	ON_BN_CLICKED(IDC_MEMBER_ADD_LOCONLY, OnMemberAddLoconly)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LOCATION_LIST, OnColumnclickLocationList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMemberAdd message handlers

extern int sortBy[3];

extern int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort );

int sortBy1[3] = { 1, 1, 1 };

int CALLBACK CompareFunc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
//     LPLVITEM l1, l2;
/*
     if ( lParam1 < 0 || lParam1 > l.lastTag )
     {
          MessageBox( NULL, "Param1 bad in sort", "Error", MB_ICONSTOP | MB_OK
);
          return 0;
     }

     if ( lParam2 < 0 || lParam2 > l.lastTag )
     {
          MessageBox( NULL, "Param2 bad in sort", "Error", MB_ICONSTOP | MB_OK
);
          return 0;
     }
  */
     LocationItem *i1 = l.GetLocationbyTag ( lParam1 );
     //     LocationItem *i1 = l.GetLocation ( lParam1 );
     if ( i1 == 0 )
          return 0;
     LocationItem *i2 = l.GetLocationbyTag ( lParam2 );
     //     LocationItem *i2 = l.GetLocation ( lParam2 );
     if ( i2 == 0 )
          return 0;

     if ( lParamSort == 0 )
     {
          if ( sortBy[lParamSort] == 1 )
               return stricmp ( i1->city.c_str(), i2->city.c_str() );
          else
               return stricmp ( i2->city.c_str(), i1->city.c_str() );
     }

          if ( lParamSort == 1 )
     {
          if ( sortBy[lParamSort] == 1 )
               return stricmp ( i1->country.c_str(), i2->country.c_str() );
          else
               return stricmp ( i2->country.c_str(), i1->country.c_str() );
     }

     if ( lParamSort == 2 )
     {
          float result;
          if ( sortBy[lParamSort] == 1 )
          {
               result = i2->offset - i1->offset;
               result = ceil ( result );
               return ( int ) result;
          }
          else
          {
               result = i1->offset - i2->offset;
               result = ceil ( result );
//               return ( int ) ( i1->offset - i2->offset );
               return ( int ) result;
          }
     }

     return 0;
}


void CDlgMemberAdd::RedrawList ( int selection )
{
//    GroupItem * group = g.groups.Nth ( m_group );

    m_list.DeleteAllItems ();


    for ( int i = 0; i < l.Size (); i++ )
    {
//        int tag = m.Tag ( i );
//        MemberItem * member = m.GetMemberbyTag ( tag );

//        MemberItem * member = m.GetMemberbyTag ( m.Tag ( i ));
//        int * ref = group->members.Nth ( i );
//        MemberItem * member = m.GetMemberbyTag ( *ref ); //group->members.Nth ( i );
        LVITEM lvitem;
        lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM; // | LVIF_STATE; // |
        lvitem.iItem = i;
        lvitem.iSubItem = 0;

        lvitem.iImage = 0;
        int tag = l.Tag ( i );
        lvitem.lParam = tag;

        LocationItem * lItem = l.GetLocationbyTag ( tag );
        if ( lItem )
            lvitem.pszText = ( char * ) lItem->city.c_str(); //( char * ) group->Name ().c_str();
        else
          lvitem.pszText = "Error - Unknown";

        m_list.InsertItem ( &lvitem );
//        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );

            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = i;
            lvitem.iSubItem = 1;
            lvitem.iImage = 0;
            lvitem.pszText = ( char * ) lItem->country.c_str(); //( char * ) group->Name ().c_str();
            lvitem.lParam = tag;
        m_list.SetItem ( &lvitem );
//        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );

            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = i;
            lvitem.iSubItem = 2;
            lvitem.iImage = 0;

             strstream sout;

//             float mins = lItem->offset - ( float )floor ( offset );

             sout << lItem->offset << ends;

// offset = ( float ) fabs ( floor ( offset ));

//          sout << offset << " hrs" << ends; // << ":";

            lvitem.pszText = ( char * ) sout.str(); //( char * ) group->Name ().c_str();
            lvitem.lParam = tag;
        m_list.SetItem ( &lvitem );


    }


//    m_list.SetFocus();
//    m_list.EnsureVisible ( 40, FALSE );
//    m_list.SetItemState ( 40, LVIS_SELECTED, -1 ); //0xffff, LVIS_SELECTED );

    /*
    LVITEM lvitem;
    lvitem.mask = LVIF_STATE; // |
    lvitem.iItem = 4;
    lvitem.iSubItem = 0;

    lvitem.state = LVIS_SELECTED | LVIS_FOCUSED | LVIS_DROPHILITED;
    lvitem.stateMask = LVIS_SELECTED | LVIS_FOCUSED | LVIS_DROPHILITED;
    m_list.SetItem ( &lvitem );

  
      */

    m_list.SortItems ( CompareFunc, 0 );

//    m_list.EnsureVisible ( 2, FALSE );
    if ( selection != -1 )
    {

        int idx = 0;
        int itemData;
        while (( itemData = m_list.GetItemData ( idx )) != LB_ERR )
        {
            if ( selection == itemData )
            {
                m_list.EnsureVisible ( idx, FALSE );
                m_list.SetItemState ( idx, LVIS_SELECTED | LVIS_FOCUSED, 0xffff ); ///1 ); //0xffff, LVIS_SELECTED );
//                m_list.SetCheck ( idx );
                break;
            }
            idx++;
        }
//        selection = m_list.GetItemData ( selection );

//        m_list.EnsureVisible ( selection, FALSE );
//        m_list.SetItemState ( selection, LVIS_SELECTED | LVIS_FOCUSED, -1 ); //0xffff, LVIS_SELECTED );
    }

}



BOOL CDlgMemberAdd::OnInitDialog() 
{
    CCmdTarget::BeginWaitCursor();
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//    m_left.SetAngle(270);
//    m_left.UseBevelLine( TRUE) ;
//    m_left.SetAlignment (CNewLabel::HORZ_LEFT | CNewLabel::VERT_CENTER );
//    m_left.SetFontBold ( TRUE );

        for ( int i = 0; i < l.Size (); i++ )
    {
        string name = l.CityList ( i );
        name += ", ";
        name += l.CountryList ( i );
        if ( name.size())
            m_listOld.SetItemData ( m_listOld.AddString ( name.c_str()), l.Tag( i ));;

    }

    for ( i = 0; i < l.Size (); i++ )
    {
        if ( m_listOld.GetItemData ( i ) == m_locRef )
            m_listOld.SetCurSel( i );
    }
      
    OnMemberAddLoconly() ;

     m_list.InsertColumn(0, "Location", LVCFMT_LEFT, 130, 0);
     m_list.InsertColumn(1, "Country", LVCFMT_LEFT, 130, 1);
     m_list.InsertColumn(2, "GMT", LVCFMT_LEFT, 50, 2);


    RedrawList ( m_locRef );

//    m_list.SetCurSel ( m_locRef ); //SelectionMask ( m_locRef ); //CurSel ( m_locRef );


    if ( m_location )
    {
        m_locationIcon.ShowWindow ( SW_SHOW );
        m_personIcon.ShowWindow ( SW_HIDE );    
    }
    else
    {
        m_locationIcon.ShowWindow ( SW_HIDE );
        m_personIcon.ShowWindow ( SW_SHOW );    
    }

    m_list.SetFocus();
    //m_nameCtrl.SetFocus ();

    CCmdTarget::EndWaitCursor();

    return FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMemberAdd::OnSelchangeMemberAddLocation() 
{
	// TODO: Add your control notification handler code here
	int nIndex = m_listOld.GetCurSel();
	if (nIndex == -1)
        return;

    m_locRef = m_listOld.GetItemData ( nIndex );
	
}


void CDlgMemberAdd::OnMemberAddLoconly() 
{
	// TODO: Add your control notification handler code here
    UpdateData();

    if ( m_location )
    {
        GetDlgItem ( IDC_MEMBER_ADD_NAME )->EnableWindow ( FALSE ); 
        GetDlgItem ( IDC_MEMBER_ADD_EMAIL )->EnableWindow ( FALSE ); 
        GetDlgItem ( IDC_MEMBER_ADD_PHONE )->EnableWindow ( FALSE ); 

//        GetDlgItem ( IDC_LOCATION_LOCATIONICON )->EnableWindow ( TRUE ); 
//        GetDlgItem ( IDC_LOCATION_PERSONICON )->EnableWindow ( FALSE ); 
        m_locationIcon.ShowWindow ( SW_SHOW );
        m_personIcon.ShowWindow ( SW_HIDE );    
    }
    else
    {
        GetDlgItem ( IDC_MEMBER_ADD_NAME )->EnableWindow ( TRUE ); 
        GetDlgItem ( IDC_MEMBER_ADD_EMAIL )->EnableWindow ( TRUE ); 
        GetDlgItem ( IDC_MEMBER_ADD_PHONE )->EnableWindow ( TRUE ); 

//        GetDlgItem ( IDC_LOCATION_LOCATIONICON )->EnableWindow ( FALSE ); 
//        GetDlgItem ( IDC_LOCATION_PERSONICON )->EnableWindow ( TRUE ); 
        m_locationIcon.ShowWindow ( SW_HIDE );
        m_personIcon.ShowWindow ( SW_SHOW );    

    }
}

void CDlgMemberAdd::OnOK() 
{
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
    {
        CDialog::OnOK();
        return;
    }

    int nItem = m_list.GetNextSelectedItem(pos);

    m_locRef = m_list.GetItemData ( nItem );
//    LocationItem * lItem = l.GetLocationbyTag ( m_list.GetItemData ( nItem ));
//    if ( lItem == 0 )
//        return;

    if ( m.GetMemberbyLocRef ( m_locRef ))
    {
        // member already in list
         if ( MessageBox ( "This location already exists in the display\n\nDo you still wish to add this location/person ?", "Location Exists", MB_ICONEXCLAMATION | MB_YESNO ) != IDYES )
             return;
    }

	// TODO: Add extra validation here
	CDialog::OnOK();
}


void CDlgMemberAdd::OnColumnclickLocationList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
               if ( pNMListView->iSubItem >= 0 && pNMListView->iSubItem <= 2 )
               {
//                    sortIdx = phdn->iItem;
                    sortBy[pNMListView->iSubItem] *= -1;
                    m_list.SortItems( CompareFunc, pNMListView->iSubItem );
               }


	*pResult = 0;

}
