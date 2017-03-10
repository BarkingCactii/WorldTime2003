// DlgLocationDetails.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "DlgLocationDetails.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLocationDetails dialog


CDlgLocationDetails::CDlgLocationDetails(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocationDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLocationDetails)
	m_country = _T("");
	m_dsEnable = FALSE;
	m_latitude = 0.0f;
	m_longitude = 0.0f;
	m_city = _T("");
	m_areaCode = 0;
	m_countryCode = 0;
	m_ew = _T("");
	m_ns = _T("");
	m_hours = _T("");
	//}}AFX_DATA_INIT
}


void CDlgLocationDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocationDetails)
	DDX_Control(pDX, IDC_LOC_DETAILS_NAME, m_nameCtrl);
	DDX_Control(pDX, IDC_LOC_DETAILS_START_DAY, m_dsStartDay);
	DDX_Control(pDX, IDC_LOC_DETAILS_START_FIRSTLAST, m_dsStartWeek);
	DDX_Control(pDX, IDC_LOC_DETAILS_START_MONTH, m_dsStartMonth);
	DDX_Control(pDX, IDC_LOC_DETAILS_END_MONTH, m_dsEndMonth);
	DDX_Control(pDX, IDC_LOC_DETAILS_END_FIRSTLAST, m_dsEndWeek);
	DDX_Control(pDX, IDC_LOC_DETAILS_END_DAY, m_dsEndDay);
	DDX_Control(pDX, IDC_LOC_DETAILS_DSTOFFSET, m_sliderCtrl);
	DDX_Text(pDX, IDC_LOC_DETAILS_COUNTRY, m_country);
	DDX_Check(pDX, IDC_LOC_DETAILS_DST, m_dsEnable);
	DDX_Text(pDX, IDC_LOC_DETAILS_LATDEGREES, m_latitude);
	DDV_MinMaxFloat(pDX, m_latitude, 0.f, 180.f);
	DDX_Text(pDX, IDC_LOC_DETAILS_LONGDEGREES, m_longitude);
	DDX_Text(pDX, IDC_LOC_DETAILS_NAME, m_city);
	DDX_Text(pDX, IDC_LOC_DETAILS_AREACODE, m_areaCode);
	DDX_Text(pDX, IDC_LOC_DETAILS_COUNTRYCODE, m_countryCode);
	DDX_Text(pDX, IDC_LOC_DETAILS_LONGNS, m_ew);
	DDV_MaxChars(pDX, m_ew, 1);
	DDX_Text(pDX, IDC_LOC_DETAILS_LATNS, m_ns);
	DDX_Text(pDX, IDC_ADD_HOURS, m_hours);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLocationDetails, CDialog)
	//{{AFX_MSG_MAP(CDlgLocationDetails)
	ON_BN_CLICKED(IDC_LOC_DETAILS_DST, OnLocDetailsDst)
	ON_BN_CLICKED(IDC_ADD_HOURS, OnAddHours)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LOC_DETAILS_DSTOFFSET, OnCustomdrawLocDetailsDstoffset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLocationDetails message handlers

void CDlgLocationDetails::OnLocDetailsDst() 
{
    UpdateData();
	// TODO: Add your control notification handler code here
    if ( !m_dsEnable )
    {
        GetDlgItem ( IDC_LOC_DETAILS_START_FIRSTLAST )->ShowWindow ( SW_HIDE );
        GetDlgItem ( IDC_LOC_DETAILS_START_DAY )->ShowWindow ( SW_HIDE );
        GetDlgItem ( IDC_LOC_DETAILS_START_MONTH )->ShowWindow ( SW_HIDE );
        GetDlgItem ( IDC_LOC_DETAILS_END_FIRSTLAST )->ShowWindow ( SW_HIDE );
        GetDlgItem ( IDC_LOC_DETAILS_END_DAY )->ShowWindow ( SW_HIDE );
        GetDlgItem ( IDC_LOC_DETAILS_END_MONTH )->ShowWindow ( SW_HIDE );
    }
    else
    {
        GetDlgItem ( IDC_LOC_DETAILS_START_FIRSTLAST )->ShowWindow ( SW_SHOW );
        GetDlgItem ( IDC_LOC_DETAILS_START_DAY )->ShowWindow ( SW_SHOW );
        GetDlgItem ( IDC_LOC_DETAILS_START_MONTH )->ShowWindow ( SW_SHOW );
        GetDlgItem ( IDC_LOC_DETAILS_END_FIRSTLAST )->ShowWindow ( SW_SHOW );
        GetDlgItem ( IDC_LOC_DETAILS_END_DAY )->ShowWindow ( SW_SHOW );
        GetDlgItem ( IDC_LOC_DETAILS_END_MONTH )->ShowWindow ( SW_SHOW );
    }
    
}

BOOL CDlgLocationDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    // initialize slider control
    m_sliderCtrl.SetRangeMin ( 0 );
    m_sliderCtrl.SetRangeMax (( int ) 24.0f * 2 );

    for ( int i = 0; i < 24.0f * 2; i+=2 )
         m_sliderCtrl.SetTic ( i );


	// TODO: Add extra initialization here
    OnLocDetailsDst();

    if ( m_lItem )
    {
        float offset;
    offset = m_lItem->offset; //l.GMTOffset ( i );
    m_sliderCtrl.SetPos (( int )(( offset * 2 ) + 24.0f ));

    m_dsStartDay.SetCurSel ( m_lItem->dsStartDay );
    m_dsStartWeek.SetCurSel ( m_lItem->dsStartWeek );
    m_dsStartMonth.SetCurSel ( m_lItem->dsStartMonth );

    m_dsEndDay.SetCurSel ( m_lItem->dsEndDay );
    m_dsEndWeek.SetCurSel ( m_lItem->dsEndWeek );
    m_dsEndMonth.SetCurSel ( m_lItem->dsEndMonth );
//    m_enable.SetCheck ( li->dsEnable );
    }


    m_nameCtrl.SetFocus();
    return FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLocationDetails::OnAddHours() 
{
	// TODO: Add your control notification handler code here
//    int pos = m)GetPos ();	

}

void CDlgLocationDetails::OnCustomdrawLocDetailsDstoffset(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

    static int lastHour = -1;
    static int lastMin = -1;

    int hour = ( m_sliderCtrl.GetPos() - ( int ) 24.0f ) / 2;
    int min = abs ((( m_sliderCtrl.GetPos() - ( int ) 24.0f ) % 2 ) * 30 );
    if ( hour == lastHour && min == lastMin )
         return;

//    strstream sout;

    char buf[50];
    sprintf ( buf, " hrs %d mins %d", hour, min );
//    sout << hour << " hrs " << min << " mins" << ends;
//    CString tmpS = sout.str();
    SetDlgItemText ( IDC_ADD_HOURS, buf ); //tmpS );

	
	*pResult = 0;
}

void CDlgLocationDetails::OnOK() 
{
	// TODO: Add extra validation here
    UpdateData();

    float offset;

    offset = m_sliderCtrl.GetPos () - 24.0f;
     
    m_lItem->offset = offset / 2.0f;

    m_lItem->dsStartDay = m_dsStartDay.GetCurSel ();
    m_lItem->dsStartMonth = m_dsStartMonth.GetCurSel ();
    m_lItem->dsStartWeek = m_dsStartWeek.GetCurSel ();

    m_lItem->dsEndDay = m_dsEndDay.GetCurSel ();
    m_lItem->dsEndMonth = m_dsEndMonth.GetCurSel ();
    m_lItem->dsEndWeek = m_dsEndWeek.GetCurSel ();



/*
    offset = m_lItem->offset; //l.GMTOffset ( i );
    m_sliderCtrl.SetPos (( int )(( offset * 2 ) + 24.0f ));

    m_dsStartDay.GetCurSel ( m_lItem->dsStartDay );
    m_dsStartWeek.GetCurSel ( m_lItem->dsStartWeek );
    m_dsStartMonth.GetCurSel ( m_lItem->dsStartMonth );

    m_dsEndDay.SetCurSel ( m_lItem->dsEndDay );
    m_dsEndWeek.SetCurSel ( m_lItem->dsEndWeek );
    m_dsEndMonth.SetCurSel ( m_lItem->dsEndMonth );
*/    
	CDialog::OnOK();
}
