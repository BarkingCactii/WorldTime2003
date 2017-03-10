// DlgLocation.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "DlgLocation.h"
#include "DlgLocationDetails.h"
#include "member.h"
#include "location.h"
#include <strstream>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLocation dialog


CDlgLocation::CDlgLocation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLocation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_images = new CImageList;
}


void CDlgLocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocation)
	DDX_Control(pDX, IDC_LOCATION_LIST, m_list);
	//}}AFX_DATA_MAP

//	DDX_Control(pDX, IDC_MEMBER_TOPMESSAGE, m_top);

}


BEGIN_MESSAGE_MAP(CDlgLocation, CDialog)
	//{{AFX_MSG_MAP(CDlgLocation)
	ON_NOTIFY(NM_DBLCLK, IDC_LOCATION_LIST, OnDblclkLocationList)
	ON_BN_CLICKED(IDC_LOCATION_ADD, OnLocationAdd)
	ON_BN_CLICKED(IDC_LOCATION_PROPERTIES, OnLocationProperties)
	ON_BN_CLICKED(IDC_LOCATION_REMOVE, OnLocationRemove)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LOCATION_LIST, OnColumnclickLocationList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int sortBy[3] = { 1, 1, 1 };

int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
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

/////////////////////////////////////////////////////////////////////////////
// CDlgLocation message handlers

void CDlgLocation::RedrawList ( int selection )
{
//    GroupItem * group = g.groups.Nth ( m_group );

    m_list.DeleteAllItems ();
    int actualItem;

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

        actualItem = m_list.InsertItem ( &lvitem );
//        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );

            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = actualItem;
            lvitem.iSubItem = 1;
            lvitem.iImage = 0;
            lvitem.pszText = ( char * ) lItem->country.c_str(); //( char * ) group->Name ().c_str();
            lvitem.lParam = tag;
        m_list.SetItem ( &lvitem );
//        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );

            lvitem.mask = LVIF_TEXT; // | LVIF_STATE; // |
            lvitem.iItem = actualItem;
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
        m_list.EnsureVisible ( selection, FALSE );
        m_list.SetItemState ( selection, LVIS_SELECTED | LVIS_FOCUSED, -1 ); //0xffff, LVIS_SELECTED );
    }


}


BOOL CDlgLocation::OnInitDialog() 
{

//    CComQIPtr<ISkin> pSkin = GetDlgItem(IDC_SKIN)->GetControlUnknown();
//    pSkin->ApplySkin((long)m_hWnd);


	CDialog::OnInitDialog();

    
	// TODO: Add extra initialization here
//    CRect rect;
//    m_list.GetWindowRect(&rect);
//    m_list.InsertColumn(0, "Member Name", LVCFMT_LEFT, ( rect.Width() / 2 ) - 5, 0);

    m_images->Create(16, 16, ILC_COLOR16 | ILC_MASK, 2, 2);
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_LOCATION ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_MEMBER ));  // make this a time zone
    m_list.SetImageList ( m_images, LVSIL_SMALL );


    //
    // Initialize locations control
    //

     m_list.InsertColumn(0, "Location", LVCFMT_LEFT, 130, 0);
     m_list.InsertColumn(1, "Country", LVCFMT_LEFT, 130, 1);
     m_list.InsertColumn(2, "GMT", LVCFMT_LEFT, 50, 2);

    RedrawList ();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLocation::OnDblclkLocationList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    OnLocationProperties() ;
	
	*pResult = 0;
}

void CDlgLocation::OnLocationAdd() 
{
	// TODO: Add your control notification handler code here
	CDlgLocationDetails	dlg;

    LocationItem * lItem = new LocationItem;
    dlg.m_lItem = lItem;

    if ( dlg.DoModal () != IDOK )
    {
        delete lItem;
        return;
    }

    lItem->city =  dlg.m_city;
    lItem->country = dlg.m_country;
    lItem->areaCode =        dlg.m_areaCode;
    lItem->countryCode =     dlg.m_countryCode;
    lItem->dsEnable =        dlg.m_dsEnable;
    lItem->latitude =       dlg.m_latitude;
    if ( dlg.m_ns.GetLength ())
        lItem->ns =             dlg.m_ns[0];
    lItem->longitude =      dlg.m_longitude;
    if ( dlg.m_ew.GetLength ())
    lItem->ew =             dlg.m_ew[0];
    l.Add ( lItem );

    RedrawList ();
    
}

void CDlgLocation::OnLocationProperties() 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;

    int nItem = m_list.GetNextSelectedItem(pos);

    LocationItem * lItem = l.GetLocationbyTag ( m_list.GetItemData ( nItem ));
    if ( lItem == 0 )
        return;
      
    CDlgLocationDetails dlg;

    dlg.m_city = lItem->city.c_str();
    dlg.m_country = lItem->country.c_str();
    dlg.m_areaCode = lItem->areaCode;
    dlg.m_countryCode = lItem->countryCode;
    dlg.m_dsEnable = lItem->dsEnable;
    dlg.m_latitude = lItem->latitude;
    dlg.m_ns = lItem->ns;
    dlg.m_longitude = lItem->longitude;
    dlg.m_ew = lItem->ew;

//    dlg.m_startDay = lItem->dsStartDay;
//    dlg.m_dsStartDay.SetCurSel ( lItem->dsStartDay );
//    dlg.m_dsStartWeek.SetCurSel ( lItem->dsStartWeek );
//    dlg.m_dsStartMonth.SetCurSel ( lItem->dsStartMonth );


    dlg.m_lItem = lItem;

/*    dlg.m_locRef = mItem->locRef;
    dlg.m_name = mItem->name.c_str();
    dlg.m_email = mItem->email.c_str();
    dlg.m_phone = mItem->phone.c_str();
    dlg.m_location = mItem->location;
*/  
    if ( dlg.DoModal () != IDOK )
        return;


    lItem->city =  dlg.m_city;
    lItem->country = dlg.m_country;
    lItem->areaCode =        dlg.m_areaCode;
    lItem->countryCode =     dlg.m_countryCode;
    lItem->dsEnable =        dlg.m_dsEnable;
    lItem->latitude =       dlg.m_latitude;
    if ( dlg.m_ns.GetLength ())
        lItem->ns =             dlg.m_ns[0];
    lItem->longitude =      dlg.m_longitude;
    if ( dlg.m_ew.GetLength ())
        lItem->ew =             dlg.m_ew[0];


  /*
    mItem->locRef = dlg.m_locRef;
    mItem->name = dlg.m_name;
    mItem->email = dlg.m_email;
    mItem->phone = dlg.m_phone;
    mItem->location = dlg.m_location;
    */

    RedrawList ( nItem );


//    m_list.SetCurSel(nItem);
    
}

void CDlgLocation::OnLocationRemove() 
{
	// TODO: Add your control notification handler code here
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;
    int nItem = m_list.GetNextSelectedItem(pos);

    if ( MessageBox ( "Are you sure ?", "Delete Location", MB_OKCANCEL | MB_ICONEXCLAMATION ) != IDOK )
        return;

    // also need to remove locations from members list and from groups, maybe something to do when doing a search
    l.DeleteList ( m_list.GetItemData ( nItem ));	
    RedrawList ( nItem );


	
}

void CDlgLocation::OnColumnclickLocationList(NMHDR* pNMHDR, LRESULT* pResult) 
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

