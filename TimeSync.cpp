#include "stdafx.h"
#include "skin.h"
#include <afxinet.h>
#include <strstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif






// LocalZoneTime function calculate Local time using Universal time.
// Time zone information is gotten from Windows using 
// GetTimeZoneInformation API function (see MSDN for more information).
// The function support DST time.
// Created by Alex.
void LocalZoneTime(const SYSTEMTIME& tmUniversal, SYSTEMTIME& tmLocal)
{
     long nZoneCorrection = _timezone / 60.0f;

//     float gmtHours = -_timezone / 3600.0f;
/*
TIME_ZONE_INFORMATION TZI;
DWORD retCode = GetTimeZoneInformation(&TZI);

int iStandardMonth = TZI.StandardDate.wMonth;
int iDaylightMonth = TZI.DaylightDate.wMonth;

long nZoneCorrection = TZI.Bias;

if( retCode == TIME_ZONE_ID_STANDARD){
     nZoneCorrection = nZoneCorrection + TZI.StandardBias;
}
else if( retCode == TIME_ZONE_ID_DAYLIGHT){
     nZoneCorrection = nZoneCorrection + TZI.DaylightBias;
}
else{
     ASSERT(0);
}

  */
nZoneCorrection = -nZoneCorrection;
int nTotalMinutes = tmUniversal.wHour * 60 + tmUniversal.wMinute + nZoneCorrection;
if(nTotalMinutes < 0){
     nTotalMinutes+=24*60;
}
if(nTotalMinutes>24*60){
     nTotalMinutes-=24*60;
}

tmLocal.wHour = nTotalMinutes /60;
tmLocal.wMinute = nTotalMinutes - tmLocal.wHour*60;
tmLocal.wSecond = tmUniversal.wSecond;

}

                                       /*
void TimeSync( void ) 
{

    // Open Internet connection.
    HINTERNET hInternet = ::InternetOpen("BSAtomicEdu", INTERNET_OPEN_TYPE_PRECONFIG , NULL, NULL, 0);
    if(!hInternet)
    {
        AfxMessageBox( "Internet open error! Test your system and try again.", MB_OK | MB_ICONERROR );
         return;
    }

    ofstream fout ( "test.html" );
    for ( int i = 1; i < 1017; i++ )
    {
        strstream sout;

        sout << "http://www.timeanddate.com/worldclock/city.html?n=" << i << endl << flush;
    
        // Open site of U.S. Naval Observatory. 
        unsigned long Context = 777;
        //http://www.timeanddate.com/worldclock/city.html?n=1000 n = 0 to n = 1016
        HINTERNET hHttp;
        do
        {
            hHttp = ::InternetOpenUrl(hInternet, sout.str(), //www.timeanddate.com/worldclock/city.html?n=1000",
        //HINTERNET hHttp = ::InternetOpenUrl(hInternet, "http://tycho.usno.navy.mil/cgi-bin/timer.pl",
        NULL, -1L, INTERNET_FLAG_RELOAD, Context);


        }
         while ( !hHttp );
        // Read the time from site
        //CString buff(' ',1024); 
        CString buff(' ',10024); 
        unsigned long NumberOfBytesRead = 0;
        BOOL bRet = ::InternetReadFile(hHttp, (void *)((LPCTSTR)buff), 10024L, &NumberOfBytesRead);

        // Close Internet connection.
        if(hHttp)
        {
             InternetCloseHandle(hHttp);
        }

        fout << buff.GetBuffer ( 0 );
    }

    fout.close();
    if(hInternet){
         InternetCloseHandle(hInternet);
    }

    AfxMessageBox("Done reading sites", MB_OK | MB_ICONERROR );

    return;
}

  */
// OnSyncro is called after ID_SYNCRO dialog button pressing.
// It opens Internet connection, receives Universal Time,
// calculates Local Time and set it in Windows.
// Created by Alex.


void SkinList ( void )
{
    // Open Internet connection.
    HINTERNET hInternet = ::InternetOpen("AvailableSkins", INTERNET_OPEN_TYPE_PRECONFIG , NULL, NULL, 0);
    if(!hInternet)
    {
        AfxMessageBox( "Internet open error! Test your system and try again.", MB_OK | MB_ICONERROR );
        return;
    }

    // Open site of U.S. Naval Observatory. 
    unsigned long Context = 777;
    HINTERNET hHttp = ::InternetOpenUrl(hInternet, "http://jeff/skins.txt",
        NULL, -1L, INTERNET_FLAG_RELOAD, Context);

    if(!hHttp)
    {
        AfxMessageBox("Time Synchronise Failed!\nCheck your internet connection", MB_OK | MB_ICONERROR );

        if(hInternet)
            InternetCloseHandle(hInternet);

        return;

    }

    // Read the time from site
    CString buff(' ',1024); 
    unsigned long NumberOfBytesRead = 0;
    BOOL bRet = ::InternetReadFile(hHttp, (void *)((LPCTSTR)buff), 1024L, &NumberOfBytesRead);

    string tempStr = buff;

    AfxMessageBox( tempStr.c_str(), MB_OK | MB_ICONINFORMATION );

    // Close Internet connection.
    if(hHttp)
        InternetCloseHandle(hHttp);


    hHttp = ::InternetOpenUrl(hInternet, "http://jeff/default.htm",
        NULL, -1L, INTERNET_FLAG_RELOAD, Context);

    bRet = ::InternetReadFile(hHttp, (void *)((LPCTSTR)buff), 1024L, &NumberOfBytesRead);
    tempStr = buff;

    AfxMessageBox( tempStr.c_str(), MB_OK | MB_ICONINFORMATION );


    if(hHttp)
        InternetCloseHandle(hHttp);

    if(hInternet)
        InternetCloseHandle(hInternet);

    // Is received information correct?
    if(!bRet)
    { 
        AfxMessageBox( "URL reading error! Test internet connection and try again.", MB_OK | MB_ICONERROR );
        return;
    }

//    if(NumberOfBytesRead != 610 )
//    { //603){
//        AfxMessageBox( "The time server has changed its format. Please download the latest version of WhenOnEarth or notify us of this problem", MB_OK | MB_ICONERROR );
//        return;
//    }


    return; 

}

void TimeSync( void ) 
{

    // Open Internet connection.
    HINTERNET hInternet = ::InternetOpen("BSAtomicEdu", INTERNET_OPEN_TYPE_PRECONFIG , NULL, NULL, 0);
    if(!hInternet)
    {
        AfxMessageBox( "Internet open error! Test your system and try again.", MB_OK | MB_ICONERROR );
        return;
    }

    // Open site of U.S. Naval Observatory. 
    unsigned long Context = 777;
    HINTERNET hHttp = ::InternetOpenUrl(hInternet, "http://tycho.usno.navy.mil/cgi-bin/timer.pl",
        NULL, -1L, INTERNET_FLAG_RELOAD, Context);

    if(!hHttp)
    {
        AfxMessageBox("Time Synchronise Failed!\nCheck your internet connection", MB_OK | MB_ICONERROR );

        if(hInternet)
            InternetCloseHandle(hInternet);

        return;

    }

    // Read the time from site
    CString buff(' ',1024); 
    unsigned long NumberOfBytesRead = 0;
    BOOL bRet = ::InternetReadFile(hHttp, (void *)((LPCTSTR)buff), 1024L, &NumberOfBytesRead);

    // Close Internet connection.
    if(hHttp)
        InternetCloseHandle(hHttp);

    if(hInternet)
        InternetCloseHandle(hInternet);

    // Is received information correct?
    if(!bRet)
    { 
        AfxMessageBox( "URL reading error! Test internet connection and try again.", MB_OK | MB_ICONERROR );
        return;
    }

//    if(NumberOfBytesRead != 610 )
//    { //603){
//        AfxMessageBox( "The time server has changed its format. Please download the latest version of WhenOnEarth or notify us of this problem", MB_OK | MB_ICONERROR );
//        return;
//    }


    // Parse Universal time from string buffer to SYSTEMTIME struct.
    SYSTEMTIME tmUniversal, tmLocal, dtOldTime;
    ZeroMemory(&tmUniversal,sizeof(tmUniversal));
    GetLocalTime(&tmLocal);
    dtOldTime = tmLocal;

    string tempStr = buff;
    int hour = tempStr.find ( ":" ) - 2;
    if ( hour < 0 )
    {
        AfxMessageBox( "Unable to locate Universal Time. Please download the latest version of WhenOnEarth or notify us of this problem", MB_OK | MB_ICONERROR );
        return;
    }
    tmUniversal.wHour = atoi((LPCTSTR)buff.Mid(hour,2));
    tmUniversal.wMinute = atoi((LPCTSTR)buff.Mid(hour + 3,2));
    tmUniversal.wSecond = atoi((LPCTSTR)buff.Mid(hour + 6,2));

    // Calculate Local Time using received Universal Time.
    LocalZoneTime(tmUniversal, tmLocal);

    // Make Windows time correction.
    // Show report dialog box.
    CString sReport;
    sReport.Format( "Your Time is: %02d:%02d:%02d.\n Time on Server is: %02d:%02d:%02d.\n\nUpdate time now ?",
    dtOldTime.wHour, dtOldTime.wMinute, dtOldTime.wSecond, tmLocal.wHour, tmLocal.wMinute, tmLocal.wSecond);

    if ( AfxMessageBox( sReport, MB_YESNO | MB_ICONINFORMATION ) == IDYES )
    {
        if ( SetLocalTime(&tmLocal) == 0 )
        {
            AfxMessageBox ( "Failed to set time on local computer!", MB_OK | MB_ICONERROR );
            return;
        }
    }
    return; 

}



