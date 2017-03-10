// onLineTimeView.cpp : implementation of the COnLineTimeView class
//

#include "stdafx.h"
#include <math.h>
#include "skin.h"
#include "displaylocation.h"

#include "location.h"
#include "member.h"
#include "regData.h"

#include "Sounds.h"

#include "dlgMember.h"
//#include "DlgAlarm.h"

//#include "DlgPreferences.h"
#include "PrefPropSheet.h"

//#include "cisbitmap.h"
#include "wingdi.h"
//#include "TimeSync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int whichLoc = 0;
static int whichGroup = 0;
//bool showAll = false;
float homeDST = 0.0f;
static bool destroy = false;
static bool processNow = false;

// Actual size of map
static const int bitmapActualWidth = 595;
static const int bitmapActualHeight = 287; // + 13;

//static int bitmapWidth = 595;
//static int bitmapHeight = 287; // + 13;

DisplayCollection displayData;

/////////////////////////////////////////////////////////////////////////////
// COnLineTimeView construction/destruction

HICON alarmIcon;
HICON dstIcon;
//HICON dstOnIcon;
//HICON dstOffIcon;
HICON currLocIcon;
HICON currMemberIcon;

COnLineTimeView * mainView;

COnLineTimeView::COnLineTimeView()
{
	// TODO: add construction code here
//    dstOnIcon = theApp.LoadIcon ( IDI_DSTON );
    alarmIcon = AfxGetApp()->LoadIcon ( IDR_MAINFRAME );
    dstIcon = AfxGetApp()->LoadIcon ( IDR_MAINFRAME );
//    dstOffIcon = theApp.LoadIcon ( IDI_DSTOFF );
    currLocIcon = AfxGetApp()->LoadIcon ( IDI_LOCATION );
    currMemberIcon = AfxGetApp()->LoadIcon ( IDI_MEMBER );
    mainView = this;
//    mainView = r.MainView();
}

COnLineTimeView::~COnLineTimeView()
{
    CloseHandle ( alarmIcon );
    CloseHandle ( dstIcon );
//    CloseHandle ( dstOnIcon );
//    CloseHandle ( dstOffIcon );
    CloseHandle ( currLocIcon );
    CloseHandle ( currMemberIcon );
}


float HomeDST ( void )
{
    struct tm *newtime;
    time_t long_time;

    time( &long_time );                /* Get time as long integer. */
    newtime = localtime( &long_time ); /* Convert to local time. */

    if ( newtime->tm_isdst )
        return 1.0f;

    return 0.0f;
}

static int monthLimit[12] = 
{
     31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};


bool DaylightSavings ( LocationItem * li, CTime * t )
{
     // daylight savings not enabled
     if ( ! li->dsEnable )
          return 0;
     
     const int month = t->GetMonth () - 1;
     const int day = t->GetDay () - 1;
     const int dayofweek = t->GetDayOfWeek () - 1;
     
     // set array of months in dst
     char dstMonths[12];
     
     if ( li->dsEndMonth < li->dsStartMonth )
     {
          memset ( dstMonths, 1, sizeof ( dstMonths ));
          for ( int i = li->dsEndMonth + 1; i < li->dsStartMonth; i++ )
               dstMonths[i] = 0;
     }
     else
     {
          memset ( dstMonths, 0, sizeof ( dstMonths ));
          for ( int i = li->dsStartMonth; i <= li->dsEndMonth; i++ )
               dstMonths[i] = 1;
     }
     
     // month not in daylight savings period
     if ( !dstMonths[month] )
          return false;
     
     // month is not in extreme boundary of dst, so must be dst
     if ( month != li->dsStartMonth && month != li->dsEndMonth )
          return true;
     
     // if we get here, we still have determined that dst either starts or ends in
     // the current month. We must now be more specific and check the weeks and days
     
     CTime startMonth ( t->GetYear(), t->GetMonth(), 1, t->GetHour(), t->GetMinute(), t->GetSecond());
     const int startMonthDay = startMonth.GetDayOfWeek() - 1;
     
     //	startMonth -= CTimeSpan( 0, 1, 0, 0 );
     // work out what day the 1st of the month is
     /*	int startMonthDay;
     startMonthDay = ( day % 7 );
     if ( dayofweek - startMonthDay < 0 ) 
     startMonthDay -= abs ( 7 - dayofweek);
     else
     startMonthDay -= abs ( dayofweek );
     */
     // now work out what day to actually start from
     short	dsWeek;
     short	dsDay;
     
     if ( month == li->dsStartMonth )
     {
          dsWeek = li->dsStartWeek;
          dsDay = li->dsStartDay;
          
          int weekOffset = ( 7 * dsWeek );
          if ( dsDay < startMonthDay )
               dsDay += 7;
          int dayOffset = abs ( dsDay - startMonthDay );
          
          // week is LAST, not fourth so see if LAST is in fact the 5th week
          if ( dsWeek == 4 )
          {
               if ( weekOffset + dayOffset < monthLimit[month] - 7 )
                    weekOffset += 7;
               else
               // our calculations exceed the number of days for this month, so crop back
               if ( weekOffset + dayOffset > monthLimit[month] )
                    weekOffset -= 7;

          }
          
          if ( day >= weekOffset + dayOffset )
               return 1;
     }
     else
     {
          dsWeek = li->dsEndWeek;
          dsDay = li->dsEndDay;
          
          int weekOffset = ( 7 * dsWeek );
          if ( dsDay < startMonthDay )
               dsDay += 7;
          int dayOffset = abs ( dsDay - startMonthDay );
          
          // week is LAST, not fourth so see if LAST is in fact the 5th week
          if ( dsWeek == 4 )
          {
               if ( weekOffset + dayOffset < monthLimit[month] - 7 )
                    weekOffset += 7;
               else
               // our calculations exceed the number of days for this month, so crop back
               if ( weekOffset + dayOffset > monthLimit[month] )
                    weekOffset -= 7;

          }
          
          
          
          if ( day <= weekOffset + dayOffset )
               return true;
     }
     
     
     return false;
}


float MemberTime ( LocationItem * li, CTime & ti )
{
    int gmtOffset = -( _timezone / 3600 );
//    double fTimeZone = ( float ) _timezone;
//    float gmtMinOffset = ( float ) -( floor (( float ) _timezone / 3600.0f ) - (( float ) _timezone / 3600.0f ));
//    double tmp = fTimeZone / 3600.0f;
//    double gmtMinOffset = ( double ) -( floor ( tmp ) - tmp );
    double gmtMinOffset = -( floor (( double ) _timezone / 3600.0f ) - (( double ) _timezone / 3600.0f ));
    gmtMinOffset *= 60.0f;
    gmtMinOffset = floor ( gmtMinOffset );


    float dst = 0.0;
    if ( DaylightSavings ( li, &ti ))
    {
//         DrawIconEx(  memDC, (int)(( XHour * ratio )  - 15), YPOS + 2, theApp.dstOnIcon[dstIdx], 12, 12, 0, NULL, DI_NORMAL );
         //                        DrawIconEx(  memDC, (int)(( XHour * ratio )  - 15), Y + ( n * YStep ) + 2, theApp.dstOnIcon, 12, 12, 0, NULL, DI_NORMAL );
         ti += CTimeSpan( 0, 1, 0, 0 );
         dst = 1.0;
    }
//    else
//         if ( DaylightSavingsZone ( li ))
//              DrawIconEx(  memDC, (int)(( XHour * ratio ) - 15), YPOS + 2, theApp.dstOffIcon, 12, 12, 0, NULL, DI_NORMAL );

    float mins = li->offset - ( float ) floor ( li->offset );
    mins *= 60.0f;
    mins = floor ( mins );
//    if ( mins ) mins = 30.0f;
    
        ti += CTimeSpan( 0, ( int ) (( int ) li->offset - gmtOffset - HomeDST() ), ( int ) mins - ( int ) gmtMinOffset, 0 ); // 1 hour exactly


//    char buf[255];

//    sprintf ( buf, "%d %f %f %f %f", gmtOffset, gmtMinOffset, dst, mins, li->offset );
//    ::MessageBox ( NULL, buf, "", MB_OK );
    return dst;
}



bool IsNight ( float hour )
{
    if ( hour > 21.f || hour < 5.f )
        return true;

    return false;
}

bool IsTransition ( float hour )
{
    if ( hour > 19.f && hour <= 21.f )
        return true;

    if ( hour > 5.f && hour <= 7.f )
        return true;

    return false;
}

bool IsDay ( float hour )
{
    if ( hour > 7.f && hour < 17.f )
        return true;

    return false;
}

//const int mapWidth = 600;
//const int widthPerHour = mapWidth / 24;


// bitmap is 600 x 270 this
// 1 degree = 600 / 360 EW pixels and 270/180 NS pixels
// 
// TopLeft of map is 90N 180E
//
//


//%n name
//%t time
//%d date
//%o country code
//%l latitude / longitude
//%c country
//%s daylight savings mode
//%e email
//%p phone number

//extern int CalcSun( double latit, double longit, double tzone, double &sunriseHours, double & sunsetHours);

void SunHours ( string & output, LocationItem * lItem )
{
    double sunriseHours, sunsetHours;
    double latit, longit;

    latit = floor ( lItem->latitude );
    latit += (( lItem->latitude - latit ) * 10.0f ) / 6.0f;

    longit = floor ( lItem->longitude );
    longit += (( lItem->longitude - longit ) * 10.0f ) / 6.0f;


    if ( lItem->ew == 'W' )
        longit *= -1.0f;
    if ( lItem->ns == 'S' )
        latit *= -1.0f;

//    CalcSun( latit, longit, lItem->offset, sunriseHours, sunsetHours);

    char hourBuf[15];
    double hr, mn;
    mn = modf ( sunriseHours, &hr );
    sprintf ( hourBuf, "Sunrise %02d:%02d ", ( int ) sunriseHours, ( int ) (modf ( sunriseHours, &hr ) * 60.0f ));
    output += hourBuf;
    sprintf ( hourBuf, "Sunset %02d:%02d", ( int ) sunsetHours, ( int ) (modf ( sunsetHours, &hr ) * 60.0f ));
    output += hourBuf;

}

void Name ( string & output, MemberItem * mItem, LocationItem * lItem )
{
    if ( mItem->Location() )
        output += lItem->city;
    else
    {
        if ( mItem->Name().size())
            output += mItem->Name();
        else
            output += lItem->city;
    }
}


void Date ( string & output, CTime & t )
{
    CString s = t.Format( "%d %b" );
    output += s;
}

void Time ( string & output, CTime & t, LocationItem * lItem )
{
     CTime ti = t;
     if ( lItem )
         float dst = MemberTime ( lItem, ti );

     int hour = ti.GetHour();
     int minute = ti.GetMinute();
     int second = ti.GetSecond();
     
     char * pm = "";
     
     
     if ( !r.Show24Hour ())
     {
          if ( hour < 12 )
          {
               if ( r.ShowAM ())
                  pm = "am";
          }
          else
          if ( hour == 12 )
               pm = "pm";
          else
          if ( hour >= 12 )
          {
               hour -= 12;
               pm = "pm";
          }

     }
     

     // display the hours, minutes & seconds
     char hourBuf[15];
     
//     if ( hourFlicker )
//          sprintf ( hourBuf, "%02d:%02d", hour, minute );
//     else
//     if ( r.ShowSeconds ())
//          sprintf ( hourBuf, "%02d:%02d:%02d %s", hour, minute, second, pm );
//     else
          sprintf ( hourBuf, "%02d:%02d %s", hour, minute, pm );
//     CString s = hourBuf;

//     memDC->TextOut ( x, y, s );
//     CSize hourSize = memDC->GetTextExtent ( hourBuf, strlen ( hourBuf ));
//     dl.Add ( x, y, hourSize, string ( hourBuf ), 0 );
    output += hourBuf;

}

void CountryCode ( string & output, LocationItem * lItem )
{
    char buf[20];

    output += itoa ( lItem->countryCode, buf, 10 );
}

void Country ( string & output, LocationItem * lItem )
{
    output += lItem->country;
}

void LatLong ( string & output, LocationItem * lItem )
{
    char buf[30];
//    int decimal, sign;
    sprintf ( buf, "%.2f%c-%.2f%c", lItem->latitude, lItem->ns, lItem->longitude, lItem->ew );
    output += buf;
}


void EMail ( string & output, MemberItem * mItem )
{
    output += mItem->Email();
}

void Phone ( string & output, MemberItem * mItem )
{
    output += mItem->Phone();
}

//void DST ( HICON & icon, CTime * t, LocationItem * lItem )
bool DST ( string & output, CTime * t, LocationItem * lItem )
{
     CTime ti = *t;
     float dst = MemberTime ( lItem, ti );

     if ( DaylightSavings ( lItem, &ti ))
         return true;

     return false;
/*
         output += "DST";
     else
         output += "ST";

  */




//         icon = dstOnIcon;
//         dl.Add ( x + nameSize.cx + 5, y, dstOnIcon );
     /*
     else
     if ( lItem->dsEnable )
         output += "DST Off";
         */
  //       icon = dstOffIcon;
//         dl.Add ( x + nameSize.cx + 5, y, dstOffIcon );
    
//     icon = 0;

}

LocationItem * GetLocData ( int whichLoc, MemberItem* &mItem )
{
    /*
    GroupItem * aGroup = g.groups.Nth ( whichGroup );
    if ( aGroup == 0 )
        return 0;

    // ensure current member is drawn last
    int * aMemberTag;
    if (( aMemberTag = aGroup->members.Nth ( whichLoc )) == 0 )
        return 0;

    mItem = m.GetMemberbyTag ( *aMemberTag );
    
    if ( mItem == 0 )
    {
        // remove member from group
        aGroup->members.Delete ( aMemberTag );
        return 0;
    }
      */
    mItem = m.GetMemberByIdx ( whichLoc );
    if ( mItem == 0 )
        return 0;

    LocationItem * lItem = l.GetLocationbyTag ( mItem->LocRef() );
    if ( lItem == 0 )
    {
        // remove member from group with bad location reference
//        aGroup->DeleteList ( *aMemberTag ); //members.Delete ( mItem ); //aMemberTag );
        return 0;
    }

    return lItem;
}

bool IsAlarmSet ( int whichLoc )
{
    MemberItem * mItem = 0;
    LocationItem * lItem = GetLocData ( whichLoc, mItem );
    if ( !lItem )
       return false;

    if ( mItem->NumAlarms())
        return true;

    return false;
}


bool IsPerson ( int whichLoc )
{
        MemberItem * mItem = 0;
        LocationItem * lItem = GetLocData ( whichLoc, mItem );
        if ( !lItem )
            return false;

    if ( mItem->Location() )
        return false;

    return true;
}


bool IsDaylightSavings ( int whichLoc, CTime & t )
{
        MemberItem * mItem = 0;
        LocationItem * lItem = GetLocData ( whichLoc, mItem );
        if ( !lItem )
            return false;

    return DaylightSavings ( lItem, &t );
}

void GetLocationText ( int whichLoc, CTime & t, string & result, string & templateStr )
{

//    string templateStr;

//    if ( r.UseTemplate())
//        templateStr = r.MemberTemplate();
//    else
//        templateStr = templateStrArg;
//	m_template = r.MemberTemplate().c_str(); //_T("");
//	m_overrideTemplate = r.UseTemplate();
//	m_template2 = r.MemberTemplate2().c_str(); //_T("");
//	m_template3 = r.MemberTemplate3().c_str(); //_T("");

        MemberItem * mItem = 0;
        LocationItem * lItem = GetLocData ( whichLoc, mItem );
        
        if ( lItem == 0 )
        {
            result = "";
            return;
        }


        
            string output = "";

            string m_template = templateStr;//.GetBuffer( 0 );
//            string m_template = "%n, %c %d %t";
//            string m_template = r.MemberTemplate();

            // move starting point a little down to the right
             bool firstLine = true;

            for ( int c = 0;; c++ )
            {

                // For the case of the time which is not the current selected member/location
                // ignore the rules and just display the time only
                // OR
                // if the user displays not to display the template
                //

                /*
                if ( i != whichLoc || !r.UseTemplate() )
                {

                    Time ( output, t, lItem );

                    if ( mItem->alarmEnable )
                    {
                        dl.Add ( cursor.cx, cursor.cy, alarmIcon );
  //                      labelSz.cx += 15;
                          cursor.cx += 13;
                    }

                    if ( DaylightSavings ( lItem, &t ))
                    {
                        dl.Add ( cursor.cx, cursor.cy, dstIcon );
                          cursor.cx += 13;
                    }

                    dl.Add ( cursor.cx, cursor.cy, labelSz, output, &font );


                    break;
                }
                  */


                if ( m_template[c] == 0x0a || m_template[c] == 0x0d || m_template[c] == 0 )
                    break;


                if ( m_template[c] == '%' )
                {
                    // get next char and increment c
                    c++;
                    char var = m_template[c];
                    if ( tolower ( var ) == 'n' )
                        Name ( output, mItem, lItem );
                    if ( tolower ( var ) == 'd' )
                    {
                        // adjust time, so date is correct
                        CTime ti = t;
                        if ( lItem )
                            MemberTime ( lItem, ti );


                        Date ( output, ti );
                    }
                    if ( tolower ( var ) == 't' )
                        Time ( output, t, lItem );
                    if ( tolower ( var ) == 'o' )
                        CountryCode ( output, lItem );
                    if ( tolower ( var ) == 'l' )
                        LatLong ( output, lItem );
                    if ( tolower ( var ) == 'c' )
                        Country ( output, lItem );
                    if ( tolower ( var ) == 'e' )
                        EMail ( output, mItem );
                    if ( tolower ( var ) == 'p' )
                        Phone ( output, mItem );
                    if ( tolower ( var ) == 's' )
                        DST ( output, &t, lItem );
                    if ( tolower ( var ) == 'u' )
                        SunHours ( output, lItem );

                }
                else
                    output += m_template[c];
            }




//        dl.Render ( this, memDC, clientRect, mItem->alarmActive, false, x, y ); //( i == whichLoc ) ? true : false );

  //  }

    displayData.numDisplayLists = m.Size(); //i;

    result = output;

}




/*
#ifdef MEMDC
void COnLineTimeView::DrawLegend ( CTime & t )
#else
void COnLineTimeView::DrawLegend ( CTime & t )
#endif
{

    char buf[255];
//    string currentTime;
//    Time ( currentTime, t, 0 );

    int alarmCount = 0;
    int i = 0;
    MemberItem * mItem;

    while (( mItem = m.GetMemberByIdx ( i )) != 0 )
    {
        if ( mItem->alarmEnable )
             alarmCount++;
        i++;
    }

//    CString s = t.Format( "%A, %B %d, %Y" );
    CString s = t.Format( "%I:%M %p on %b %d, %Y" );

    sprintf ( buf, "Local time %s | %s | %d Alarms | %.1lf hours GMT", ( const char * )s, ( _daylight ) ? _tzname[0] : _tzname[1], alarmCount, -_timezone / 3600.0f );
//    sprintf ( buf, "Local time %s | Zone: %s | %d Alarms | %.1lf hours GMT", currentTime.c_str(), ( const char * )s, ( _daylight ) ? _tzname[0] : _tzname[1], alarmCount, -_timezone / 3600.0f );
// legend    memDC->TextOut ( 10, rect.top += nameSize.cy + 5, buf );

// legemd   memDC->SelectObject ( saveFont );


//    extern CMainFrame * main;

    main->m_wndStatusBar.SetPaneText ( 0, buf );

     i = 0;
    while (( mItem = m.GetMemberByIdx ( i )) != 0 )
    {
        if ( mItem->alarmActive )
        {
            LocationItem * lItem = GetLocData ( i, mItem );
            sprintf ( buf, "[From %s, %s] %s", lItem->city.c_str(), lItem->country.c_str(), mItem->alarmMessage.c_str() );
            main->m_wndStatusBar.SetPaneText ( 0, buf );
            break;
        }
        i++;
    }
//    m_wndStatusBar.SetPaneText ( 0, "HELLO" );


}

  */


/////////////////////////////////////////////////////////////////////////////
// COnLineTimeView drawing
/*
bool Keypress = false;
void COnLineTimeView::OnDraw(CDC* pDC)
{
    static bool drawing = false;


    if ( drawing )
        return;

    drawing = true;

    if ( Keypress )
        Keypress = false;


    // get current local time
    CTime t = CTime::GetCurrentTime();

    PlotPoints ( memDC, t, windowRect );


    drawing = false;

//    DrawLegend ( t );


}
*/

/////////////////////////////////////////////////////////////////////////////
// COnLineTimeView message handlers

bool ProcessAlarmsOld ( COnLineTimeView * view )
{
    return true;

    /*
    // loop through the members list
     bool alarmSet = false;

//        bool location;
    MemberItem * mItem = 0;
    LocationItem * lItem = 0;
    CTime ti;


    for ( int i = 0; mItem = m.GetMemberByIdx ( i ); i++ )
    {
        if ( !mItem->NumAlarms())
            continue;


        lItem = GetLocData ( i, mItem );

        CTime t = CTime::GetCurrentTime();
        ti = t;

        if ( lItem )
        {
            float dst = MemberTime ( lItem, ti );
            if ( mItem->alarmHour == ti.GetHour() && 
                 mItem->alarmMinute == ti.GetMinute())
            {
                // only check if alarm has been reset after checking for the time
                // otherwise the alarm will get reset
                if ( mItem->alarmReset == false )
                {
                    alarmSet = mItem->alarmActive = true;
                
                    Playsound ( r.SoundAlarmFile().c_str(), r.SoundAlarm() ? true : false);

                    if ( mItem->alarmAppExec == false )
                    {
                         if ( mItem->alarmRunEnable )
                         {
                             ShellExecute( AfxGetMainWnd()->m_hWnd, NULL, mItem->alarmRunApp.c_str(), NULL, NULL, SW_SHOWNORMAL );
                             mItem->alarmAppExec = true;
                         }
                    }
                }
            }
            else
            {
                mItem->alarmReset = false;
                mItem->alarmAppExec = false;
            }
        }
    }
    return alarmSet;
    */
}

void ProcessSounds ( void )
{
    static bool played = false;
    static int numCuckoos = 1;

    CTime t = CTime::GetCurrentTime();

    // play sounds
    if ( t.GetMinute() == 0 )
    {
         if ( !played )
             Playsound ( r.SoundHourFile().c_str(), r.SoundHour() ? true : false);
         
         played = true;
    }
    else
    if ( t.GetMinute() == 15 )
    {
        if ( !played )
            numCuckoos = 1;
         
        if ( numCuckoos )
            if ( Playsound ( r.SoundQuarterFile().c_str(), r.SoundQuarter()  ? true : false))
                numCuckoos--;
              
        played = true;
    }
    else
    if ( t.GetMinute() == 30 )
    {
         if ( !played )
              numCuckoos = 2;
         
         if ( numCuckoos )
            if ( Playsound ( r.SoundQuarterFile().c_str(), r.SoundQuarter() ? true : false))
                   numCuckoos--;
              
         played = true;
    }
    else
    if ( t.GetMinute() == 45 )
    {
         if ( !played )
              numCuckoos = 3;
         
         if ( numCuckoos )
              if ( Playsound ( r.SoundQuarterFile().c_str(), r.SoundQuarter() ? true : false))
                   numCuckoos--;
              
         played = true;
    }
    else
         played = false;

}

static UINT Pulsate ( LPVOID param )
{
    COnLineTimeView * view = ( COnLineTimeView * ) param;
    static bool firstTime = true;

    while ( 1 )
    {
          if ( destroy == true )
               break;

          // only refresh screen once a minute
          CTime t = CTime::GetCurrentTime();
          if ( t.GetSecond() != 0 )
          {

               Sleep ( 200 );


//               if ( !ProcessAlarms ( view ) && firstTime == false)
//                    continue;


               firstTime = false;

    


          }

        ProcessSounds ();

        processNow = false;

    }

    return 0;
}

CSplitterWnd m_wndSplitter;

/*
int COnLineTimeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//    SetTimer ( 101, 2000, NULL );
    
    AfxBeginThread ( Pulsate, this, THREAD_PRIORITY_IDLE );



	return 0;
}

  */



DisplayList::DisplayList ( void ) 
{ 
    Reset();
    offset = CPoint ( 0, 0 );
    drag = false;

//        bounds.left = bounds.top = INT_MAX;
//        bounds.right = bounds.bottom = INT_MIN;
//        bounds.left = bounds.top = INT_MAX;
//        bounds.right = bounds.bottom = INT_MIN;
}

void DisplayList::Render ( CView * wnd, CDC & memDC, CRect & frameRect, bool alarmActive, bool listView, float x, float y )
{
    if ( numDisplayItems == 0 )
        return;

        for ( int i = 0; i < numDisplayItems; i++ )
        {
            if ( data[i].type == DL_Text )
            {

//                memDC->TextOut ( data[i].x + adj.cx + ( listView ? 0 : offset.x ), data[i].y + adj.cy + ( listView ? 0 : offset.y ), data[i].text.c_str());

            }
//            else
//            if ( data[i].type == DL_Icon )
//                DrawIconEx(  memDC->m_hDC, data[i].x + adj.cx + ( listView ? 0 : offset.x ), data[i].y + adj.cy + ( listView ? 0 : offset.y ), data[i].icon, 12, 12, 0, NULL, DI_NORMAL );
        }



    }
    void DisplayList::Add ( int x, int y, HICON icon )
    {
        if ( x < bounds.left )
            bounds.left = x;
        if ( y < bounds.top )
            bounds.top = y;
        if ( x + 12 > bounds.right )
            bounds.right = x + 12;
        if ( y + 12 > bounds.bottom )
            bounds.bottom = y + 12;


        data[numDisplayItems].type = DL_Icon;
        data[numDisplayItems].icon = icon;
        data[numDisplayItems].x = x;
        data[numDisplayItems].y = y;


        numDisplayItems++;
    }

    void DisplayList::Add ( int x, int y, CSize & size, string & text, CFont * font )
    {
        if ( x < bounds.left )
            bounds.left = x;
        if ( y < bounds.top )
            bounds.top = y;
        if ( x + size.cx > bounds.right )
            bounds.right = x + size.cx;
        if ( y + size.cy > bounds.bottom )
            bounds.bottom = y + size.cy;

        data[numDisplayItems].type = DL_Text;
        data[numDisplayItems].x = x;
        data[numDisplayItems].y = y;

        data[numDisplayItems].text = text;
        data[numDisplayItems].font = font;

        numDisplayItems++;
    }


    /*
static CPoint contextMenuLoc;

void COnLineTimeView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default


    if ( r.MainView())
    {

    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, point ))
        {
            whichLoc = i;
            Invalidate ( FALSE );
        }
    }
    }





    contextMenuLoc = point;
    
    CMenu menu;
    CMenu *submenu;
    // Load the menu.
    menu.LoadMenu( IDR_CONTEXT );
    // Get the pop-up menu.
    submenu = menu.GetSubMenu(0);
    // Convert to screen coordinates.
    ClientToScreen(&point);
    // Post the menu
    submenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, AfxGetApp()->m_pMainWnd,NULL);

	CView::OnRButtonUp(nFlags, point);
}

void COnLineTimeView::OnContextClock() 
{
	// TODO: Add your command handler code here

    // lets  select the clock first, so we know what clock we putting into a window
    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, contextMenuLoc ))
        {
            whichLoc = i;
            break;
        }
    }

    CClockWnd * m_pDlg;
	m_pDlg = new CClockWnd();
	m_pDlg->Create(IDD_CLOCK);
	
}

void COnLineTimeView::OnContextModify() 
{
	// TODO: Add your command handler code here
    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, contextMenuLoc ))
        {
            whichLoc = i;
            break;
        }
    }

    CDlgMember dlg;

    MemberItem * mItem = m.GetMemberByIdx ( whichLoc );
    if ( mItem == 0 )
        return;

    dlg.ShowMemberPropDlg( mItem );

    Invalidate ( FALSE );
}

void COnLineTimeView::OnContextDelete() 
{
	// TODO: Add your command handler code here
    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, contextMenuLoc ))
        {
            whichLoc = i;
            break;
        }
    }

    if ( MessageBox ( "Are you sure ?", "Delete Member", MB_OKCANCEL | MB_ICONEXCLAMATION ) != IDOK )
        return;

    // also need to remove members from groups, maybe something to do when doing a search
    m.DeleteList ( m.Tag ( whichLoc ));	

    Invalidate ( FALSE );
}

        
void COnLineTimeView::OnFileAlarmreset() 
{
    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, contextMenuLoc ))
        {
            whichLoc = i;
            break;
        }
    }

	// TODO: Add your command handler code here
    MemberItem * mItem = m.GetMemberByIdx ( whichLoc );
    if ( mItem )
    {
        if ( mItem->alarmActive )
        {
            mItem->alarmActive = false;
            mItem->alarmReset = true;
        }

        Invalidate ( FALSE );
    }
	
}

void COnLineTimeView::OnFileAlarm() 
{
    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, contextMenuLoc ))
        {
            whichLoc = i;
            break;
        }
    }


	// TODO: Add your command handler code here
    CAlarm dlg;
	
    dlg.m_whichLoc = whichLoc;
    if ( dlg.DoModal() == IDOK )
         Invalidate ( FALSE );
	
}

void COnLineTimeView::OnToolsEmail() 
{
	// TODO: Add your command handler code here
    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, contextMenuLoc ))
        {
            MemberItem * mItem = m.GetMemberByIdx ( i );
            if ( mItem )
            {
                if ( mItem->email.size() == 0 )
                    ::MessageBox ( main->m_hWnd, "No Email for this location!", "Error", MB_OK | MB_ICONEXCLAMATION );
                else
                {
                    string mail = "mailto:" + mItem->email;
                    ShellExecute(NULL,"open",mail.c_str(),NULL,NULL,SW_SHOWNORMAL);
                }
            }
            break;
        }
    }
}


void COnLineTimeView::OnViewPreferences() 
{
    CPrefPropSheet   allcontrolssheet(_T("Preferences"));
    if ( allcontrolssheet.DoModal() == IDOK )
    {
//         SetWindowPos ( NULL, r.WinLeft(), r.WinTop(), r.WinRight() - r.WinLeft (), r.WinBottom() - r.WinTop(), SWP_NOZORDER );
         Invalidate ( FALSE );
    }
    return;
}

void COnLineTimeView::OnSize(UINT nType, int cx, int cy) 
{
     if ( r.ActualSize())
          // don't allow window resize in Actual Map Mode
          return;

	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}


void COnLineTimeView::OnToolsTimesync() 
{
	// TODO: Add your command handler code here
	TimeSync();
     Invalidate ( FALSE );
}


void COnLineTimeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
//    drag = false;
//    if ( dragInitiated )
//        dragInitiated = false;

    DEBUGLINE
	// TODO: Add your message handler code here and/or call default
    // switch to a legend 
    // if selected

    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        if ( PtInRect ( displayData.data[i].bounds, point ))
        {
            whichLoc = i;
            Invalidate ( FALSE );
            processNow = true;
            break;
        }
    }

	CView::OnLButtonUp(nFlags, point);
}


void COnLineTimeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnLButtonDown(nFlags, point);
}

void COnLineTimeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
    static clock_t startTime;
    static CPoint startPoint;
    static CPoint oldOffset;
    static bool startDrag = false;
    static bool drag = false;
    static bool dragInitiated = false;


    if ( r.MainView() != 0 || !( nFlags & MK_LBUTTON ))
    {
        drag = dragInitiated = false;
        startDrag = false;
    	CView::OnMouseMove(nFlags, point);
        return;
    }

    if ( drag == false )
    {
        drag = true;
        startTime = clock ();
        startPoint = point;
    }
    else
    {
        clock_t currentTime = clock ();

        if ( dragInitiated == false )
        {
            float currentTimef, startTimef;
            currentTimef = currentTime;
            startTimef = startTime;
            if ((( currentTimef - startTimef ) / ( float )CLOCKS_PER_SEC ) > 0.1f )
//            if ((( float ) currentTime - ( float ) startTime ) / ( float )CLOCKS_PER_SEC > 1.0f )
            {
                dragInitiated = true;
                startDrag = true;
            }
        }
        else
        {
        for ( int i = 0; i < displayData.numDisplayLists; i++ )
        {
            if ( PtInRect ( displayData.data[i].bounds, point ))
            {
                whichLoc = i;

                if ( startDrag )
                {
                    oldOffset = displayData.data[i].offset;
                    startDrag = false;
                }

                displayData.data[i].offset += ( point - startPoint );
                displayData.data[i].drag = true;

                // save to member data, so it can be persistant
                m.GetMemberByIdx ( i )->offsetX = displayData.data[i].offset.x;
                m.GetMemberByIdx ( i )->offsetY = displayData.data[i].offset.y;

                startPoint = point;

                Invalidate ( FALSE );
                processNow = true;
                break;
            }
        }
        }

    }


    
CView::OnMouseMove(nFlags, point);
}

void COnLineTimeView::OnToolsResetlocations() 
{
	// TODO: Add your command handler code here
    for ( int i = 0; i < displayData.numDisplayLists; i++ )
    {
        displayData.data[i].offset = CPoint ( 0, 0 );
        m.ResetOffsets ();
    }
    Invalidate ( FALSE );
    processNow = true;
	
}
*/