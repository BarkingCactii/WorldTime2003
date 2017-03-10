// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Skin.h"
#include "OptionsDlg.h"
#include "location.h"
#include "dlglocation.h"
#include "dlglocationdetails.h"
#include "dlgmember.h"
#include "dlgmemberadd.h"
#include "dlgAlarms.h"
#include "dlgUpdater.h"
#include <strstream>
#include "prefpropsheet.h"
#include "skindlg.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog


COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_images = new CImageList;
}


void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

BOOL COptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	

    m_images->Create(32, 32, ILC_COLOR16 | ILC_MASK, 7, 7 );
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_DISPLAY ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_LOCATIONS ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_ALARM ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_PREFERENCES ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_SKINS ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_UPDATER ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_HELP ));
    m_list.SetImageList ( m_images, LVSIL_NORMAL );


    m_list.DeleteAllItems ();

    for ( int i = 0; i < 7; i++ )
    {
        LVITEM lvitem;
        lvitem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM; // | LVIF_STATE; // |
        lvitem.iItem = i;
        lvitem.iSubItem = 0;

        lvitem.iImage = i;
        int tag = l.Tag ( i );
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
              lvitem.pszText = "Update via Internet";
                break;
        case 6:
              lvitem.pszText = "Help";
                break;
        }

        m_list.InsertItem ( &lvitem );
//        m_list.SetItemData ( m_list.InsertItem ( &lvitem ), tag );

    }


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionsDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();

    delete m_images;
}

void COptionsDlg::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	// TODO: Add your control notification handler code here
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    if (pos == NULL)
        return;
          /*
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_ADDDISPLAY ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_DISPLAY ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_LOCATIONS ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_ADDLOCATION ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_ALARM ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_SOUNDS ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_PREFERENCES ));
    m_images->Add ( AfxGetApp()->LoadIcon ( IDI_TEMPLATE ));
            */

        switch ( (int)pos - 1 )
        {
        case 0:
            {
            CDlgMember dlg;
            dlg.DoModal ();
                break;
            }
        case 1:
            {
            CDlgLocation dlg;
            dlg.DoModal ();
                break;
            }
        case 2:
            {
            CDlgAlarms dlg;
            dlg.DoModal ();
                break;
            }
        case 3:
            {
            CPrefPropSheet   allcontrolssheet(_T("Preferences"));
            allcontrolssheet.DoModal();
//            if ( allcontrolssheet.DoModal() == IDOK )
//            {
                //         SetWindowPos ( NULL, r.WinLeft(), r.WinTop(), r.WinRight() -
//                r.WinLeft (), r.WinBottom() - r.WinTop(), SWP_NOZORDER );
//                Invalidate ( FALSE );

//            }
//    return;
                break;
            }
        case 4:
            {
            // TODO: Add your command handler code here
          char * filterBuf= "WorldTime2003 Skins\0*.skn;*.cmo\0\0\0";
          CFileDialog openD ( TRUE );

          openD.m_ofn.lpstrFilter = filterBuf;
          openD.m_ofn.lpstrInitialDir = ".\\";
          openD.m_ofn.lpstrTitle = "Select a Skin";

         if ( openD.DoModal () == IDOK )
         {
              //
              // open file and read data
            //

//             CComQIPtr<ISkin> pSkin = AfxGetMainWnd()->GetDlgItem(IDC_SKIN)->GetControlUnknown();
//             main->pSkin->LoadSkin ( (_bstr_t) openD.m_ofn.lpstrFile );



             main->ApplySkin ( openD.m_ofn.lpstrFile );

             
//            CComQIPtr<ISkin> pSkin = AfxGetMainWnd()->GetDlgItem(IDC_SKIN)->GetControlUnknown();
//    pSkin->LoadSkin ( L"skin1.skn" );
//            pSkin->ApplySkinByName((long)AfxGetMainWnd(), (_bstr_t)openD.m_ofn.lpstrFile) ;// code. 
//            pSkin->ApplySkinByName((long)m_hWnd, (_bstr_t)openD.m_ofn.lpstrFile) ;// code. 


//            l.p.wallpaperName = openD.m_ofn.lpstrFile;

          }
                break;
            }
        case 5:
            {
            CDlgUpdater dlg;
            dlg.DoModal();
                break;
            }
        case 6:
            {
// fix             HtmlHelp(NULL, "WorldTIme2003.chm::/release notes.htm", HH_DISPLAY_TOPIC, 0);
                break;
        }

        }

}
