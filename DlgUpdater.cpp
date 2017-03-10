// DlgUpdater.cpp : implementation file
//

#include "stdafx.h"
#include "skin.h"
#include "DlgUpdater.h"
#include <afxinet.h>
#include <strstream>

#include <fcntl.h>
            #include <sys/types.h>
            #include <sys/stat.h>
#include <io.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUpdater dialog


CDlgUpdater::CDlgUpdater(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUpdater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUpdater)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUpdater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUpdater)
	DDX_Control(pDX, IDC_CONNECT_STATUS, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUpdater, CDialog)
	//{{AFX_MSG_MAP(CDlgUpdater)
	ON_BN_CLICKED(IDC_UPDATER_START, OnUpdaterStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUpdater message handlers

void CDlgUpdater::OnUpdaterStart() 
{
	// TODO: Add your control notification handler code here
    // Open Internet connection.

    HINTERNET hInternet = NULL;
    HINTERNET hHttp = NULL;
#ifdef _DEBUG
    string baseURL = "http://users.tpg.com.au/adsld842/wt2003/";
//    string baseURL = "http://jeff/updates/";
#else
    string baseURL = "http://users.tpg.com.au/adsld842/wt2003/";
//    string baseURL = "http://jeffs-software/updates/";
#endif
    try
    {
        m_list.AddString ( "Opening connection..." );
        m_list.RedrawWindow ();
        hInternet = ::InternetOpen("AvailableSkins", INTERNET_OPEN_TYPE_PRECONFIG , NULL, NULL, 0);
        if( !hInternet )
            throw ( "Internet open error! Test your system and try again." );

        // Open site of U.S. Naval Observatory. 
        m_list.AddString ( "Connecting to host..." );
        m_list.RedrawWindow ();
//        m_list.AddString ( baseURL.c_str() );
//        m_list.RedrawWindow ();


        unsigned long Context = 777;
//#ifdef _DEBUG
//        hHttp = ::InternetOpenUrl(hInternet, "http://users.tpg.com.au/adsld842/wt2003/wt2003 update list.txt", NULL, -1L, INTERNET_FLAG_RELOAD, Context);
//        hHttp = ::InternetOpenUrl(hInternet, "http://jeff/updates/wt2003 update list.txt", NULL, -1L, INTERNET_FLAG_RELOAD, Context);
//#else
        string masterFile = baseURL;
        masterFile += "wt2003 update list.txt";
        hHttp = ::InternetOpenUrl(hInternet, masterFile.c_str(), NULL, -1L, INTERNET_FLAG_RELOAD, Context);
//        hHttp = ::InternetOpenUrl(hInternet, "http://users.tpg.com.au/adsld842/wt2003/wt2003 update list.txt", NULL, -1L, INTERNET_FLAG_RELOAD, Context);
//        hHttp = ::InternetOpenUrl(hInternet, "http://jeffs-software/updates/wt2003 update list.txt", NULL, -1L, INTERNET_FLAG_RELOAD, Context);
//#endif
        if(!hHttp)
            throw ( "Failed to connect to host. Please try again later." );

        // Read the time from site
        m_list.AddString ( "Building list of files to be updated." );
        m_list.RedrawWindow ();

        CString buff('\0',1024); 
        unsigned long NumberOfBytesRead = 0;
        BOOL bRet = ::InternetReadFile(hHttp, (void *)((LPCTSTR)buff), 1024L, &NumberOfBytesRead);
//        char buff[1024];
//        BOOL bRet = ::InternetReadFile(hHttp, (void *)((LPCTSTR)buff), 1024L, &NumberOfBytesRead);

        if (!bRet || !strncmp ( buff, "<!DOCTYPE", 9 ))
            throw ( "Failed to read master update file. Please contact us if this problem persists." );

        string tempStr = buff;

        strstream sout (( char * ) tempStr.c_str(), tempStr.length() );

        while ( !sout.eof() )
        {
            string fileName, date;

            sout >> fileName >> date;

            //
            // get file date on local machine
            //

            // check if file is current
            struct _stat buf;
            int fh, result;
            long fileLength;
            string localFileTimeStr;
            if( (fh = _open( fileName.c_str(), _O_RDONLY )) !=  -1 )
            {
            /* Get data associated with "fh": */
                result = _fstat( fh, &buf );
                fileLength = _filelength ( fh );
                _close( fh );

                // get time
                struct tm * localFileTime;
                localFileTime = localtime ( &buf.st_mtime );

                strstream sout;
                sout.fill ( '0' );
                sout.width ( 4 );
                sout << localFileTime->tm_year + 1900;
                sout.width ( 2 );
                sout << localFileTime->tm_mon + 1;
                sout << localFileTime->tm_mday << ends << flush;
                localFileTimeStr = sout.str();
            }
            else
                localFileTimeStr = "00000000";
//            string localFileTimeStr;

            if ( fileName.length () > 2 )
            {
                string message;
                if ( localFileTimeStr >= date )
                {
                     message = fileName.c_str();
                     message += " ( No update necessary )";
                //     m_list.AddString ( message.c_str());
                //     m_list.RedrawWindow ();

                }
                else
                {


                message = fileName.c_str();

                string fileURL = baseURL;
                fileURL += fileName.c_str();

                char * fileBuf = new char[1024000L];

                if ( hHttp )
                    InternetCloseHandle(hHttp);

//                hHttp = ::InternetOpenUrl(hInternet, "http://jeff/skin1.skn", NULL, -1L, INTERNET_FLAG_RELOAD, Context);
                hHttp = ::InternetOpenUrl(hInternet, fileURL.c_str(), NULL, -1L, INTERNET_FLAG_RELOAD, Context);
                DWORD error = GetLastError();
                if(!hHttp)
                    message += " ( File not found on server )";
//                    throw ( "Failed to find an update file. Please try again later." );
                bRet = ::InternetReadFile(hHttp, fileBuf, 1024000L, &NumberOfBytesRead);
                if (!bRet || !strncmp ( fileBuf, "<!DOCTYPE", 9 ))
                    message += " ( Read operation on server file failed )";
//                    throw ( "Failed to read a file on the host. Please contact us if this problem persists." );
                else
                {
                    FILE * fp = fopen ( fileName.c_str(), "wb" );
                    if ( fp )
                    {
                        fwrite ( fileBuf, NumberOfBytesRead, 1, fp );
                        fclose ( fp );

                        char messBuf[40];
                        sprintf ( messBuf, " ( Updated successfully %ld bytes )", NumberOfBytesRead );
                        message += messBuf;//" ( Updated successfully ";
                    }
                }


                delete [] fileBuf;

                }

                m_list.AddString ( message.c_str());
                m_list.RedrawWindow ();


            }
//            sout.getline ( buf, sizeof ( buf ));
//            if ( strlen ( buf ) <= 2 )
//                    break;

//            m_list.AddString ( buf );
//            m_list.RedrawWindow ();

        }

/*
        InternetCloseHandle(hHttp);
        hHttp = ::InternetOpenUrl(hInternet, "http://jeff/default.htm", NULL, -1L, INTERNET_FLAG_RELOAD, Context);

    bRet = ::InternetReadFile(hHttp, (void *)((LPCTSTR)buff), 1024L, &NumberOfBytesRead);
    tempStr = buff;

    AfxMessageBox( tempStr.c_str(), MB_OK | MB_ICONINFORMATION );
*/


    }

    catch ( char * message )
    {
        m_list.AddString ( message );
        m_list.RedrawWindow ();
    }


    m_list.AddString ( "Operation Complete" );
    m_list.RedrawWindow ();


    if(hHttp)
        InternetCloseHandle(hHttp);

    if(hInternet)
        InternetCloseHandle(hInternet);

    return; 

}

