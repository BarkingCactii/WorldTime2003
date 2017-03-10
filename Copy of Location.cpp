// Location.cpp
//

#include "stdafx.h"
#include "location.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Locations l;

bifstream & operator >> ( bifstream & fin, LocationItem & data )
{
    fin >> data.tag >> data.country >> data.city >> data.countryCode >> data.areaCode;
    fin >> data.offset >> data.dsEnable;
    fin >> data.dsStartWeek >> data.dsStartDay >> data.dsStartMonth;
    fin >> data.dsEndWeek >> data.dsEndDay >> data.dsEndMonth;

    fin >> data.latitude >> data.ns >> data.longitude >> data.ew;

    for ( int i = 0; i < sizeof ( data.spare ) / sizeof ( int ); i++ )
        fin >> data.spare[i];

    return fin;
}

bofstream & operator << ( bofstream & fout, LocationItem & data )
{
    fout << data.tag << data.country << data.city << data.countryCode << data.areaCode;
    fout << data.offset << data.dsEnable;
    fout << data.dsStartWeek << data.dsStartDay << data.dsStartMonth;
    fout << data.dsEndWeek << data.dsEndDay << data.dsEndMonth;

    fout << data.latitude << data.ns << data.longitude << data.ew;

    for ( int i = 0; i < sizeof ( data.spare ) / sizeof ( int ); i++ )
        fout << data.spare[i];

    return fout;
}

float Locations::GMTOffset ( int idx )
{ 
    if ( idx < ll.Size()) 
        return ll.Nth ( idx )->offset;
    else 
        return 0.0f; 
}

float Locations::OffsetList ( int idx )
{ 
    DEBUGLINE
    if ( idx < ll.Size()) 
    {
        LocationItem * li = GetLocationbyTag ( idx );
        if ( li )
        {
            float dst = 0.0;
            CTime ti = CTime::GetCurrentTime();
            if ( DaylightSavings ( li, &ti ))
                dst = 1.0;

            return li->offset + dst; 
        }
    }
    return 0.0f; 
}


Locations::Locations ( void  )
{
    lastTag = 0;
    version = VERSION;
}

void Locations::Create ( string & locationsFile  )
{
        fileName = locationsFile;

        class List
        {
        public:
            int index;
            char * name;
        };

        List dayList[] = { 
            { 0, "Sunday" },
            { 1, "Monday" },
            { 2, "Tuesday" },
            { 3, "Wednesday" },
            { 4, "Thursday" },
            { 5, "Friday" },
            { 6, "Saturday" },
        };

        List weekList[] = { 
            { 0, "First" },
            { 1, "Second" },
            { 2, "Third" },
            { 3, "Fourth" },
            { 4, "Last" },
        };

        List monthList[] = { 
            { 0, "January" },
            { 1, "February" },
            { 2, "March" },
            { 3, "April" },
            { 4, "May" },
            { 5, "June" },
            { 6, "July" },
            { 7, "August" },
            { 8, "September" },
            { 9, "October" },
            { 10, "November" },
            { 11, "December" },
        };

        ifstream fin ( "data\\newdefault.txt" );
        short locationTag = 0;

        bool newLocation = true;

        int lineNum = 0;
        LocationItem * aItem = 0;
        while ( !fin.eof() )
        {
            char buf[255];
            fin.getline ( buf, sizeof ( buf ));
            lineNum++;
            if ( strlen ( buf ) <= 4 )
                    continue;

            
            char city[150];
            char state[150];
            char country[150];
            if ( newLocation )
            {
                aItem = new LocationItem;


                lastTag = aItem->tag = locationTag++;

                // parse cities
                // count commas, if 2, then skip state name

                char * ptr = strchr ( buf, ',' );
                char * ptr2;
                bool stateExists = false;
                if ( ptr )
                {
                    ptr++;
                    if (( ptr2 = strchr ( ptr, ',' )))
                    {
                        ptr2++;
                        stateExists = true;
                    }
                }
            
                strcpy ( city, buf );
                city[(ptr - buf) - 1] = 0;
                if ( stateExists )
                {
                    while ( *ptr == ' ' )
                        ptr++;
                    strcpy ( state, ptr );
                    state[(ptr2 - buf) - 1] = 0;

                    while ( *ptr2 == ' ' )
                        ptr2++;
                    strcpy ( country, ptr2 );

                }
                else
                {
                    while ( *ptr == ' ' )
                        ptr++;
                    strcpy ( country, ptr );
//                    state[(ptr2 - buf) - 1] = 0;

                }

                aItem->city = city;
                aItem->country = country;
                newLocation = false;
            }

            char * tmp;
            if (( tmp = strstr ( buf, "UTC/GMT" )))
            {
                // hours from GMT
                tmp = strstr ( tmp + 8, "UTC/GMT" );

                if ( tmp )
                {
                    tmp += 8;
                    int hour = 0;
                    int minute = 0;
                    sscanf ( tmp, "%d:%d", &hour, &minute );//&aItem->offset );
                    aItem->offset = hour;
                    aItem->offset += (( float ) minute / 60.0f );
                }

            }

            if (( tmp = strstr ( buf, "International country code" )))
            {

                tmp += strlen ( "International country code" );
                tmp += 4;
                sscanf ( tmp, "%d", &aItem->countryCode );

            }


            if (( tmp = strstr ( buf, "Coordinates Latitude:" )))
            {

                tmp += strlen ( "Coordinates Latitude:" );

                int hour, minute;
                sscanf ( tmp, "%d", &hour );
                while ( *tmp != '°' )
                    tmp++;

                tmp+=2;
                sscanf ( tmp, "%d", &minute );

                aItem->latitude = hour;
                aItem->latitude += (( float ) minute / 100.0f );

                while ( *tmp != ' ' )
                    tmp++;

                tmp++;
                aItem->ns = *tmp;

            }

            if (( tmp = strstr ( buf, "Longitude:" )))
            {

                tmp += strlen ( "Longitude:" );

                int hour, minute;
                sscanf ( tmp, "%d", &hour );
                while ( *tmp != '°' )
                    tmp++;

                tmp+=2;
                sscanf ( tmp, "%d", &minute );

                aItem->longitude = hour;
                aItem->longitude += (( float ) minute / 100.0f );

                while ( *tmp != ' ' )
                    tmp++;

                tmp++;
                aItem->ew = *tmp;


                newLocation = true;
                ll.Add ( aItem );

            }

            if (( tmp = strstr ( buf, "Area code:" )))
            {

                tmp += strlen ( "Area code:" );
                sscanf ( tmp, "%d", &aItem->areaCode );
            }


            if (( tmp = strstr ( buf, "No known DST" )))
            {
                // no DST
                aItem->dsEnable = 0;
            }

            class DSTList
            {
            public:
                int index;
                char * name;
                int weekday;
                int weekNum;
                int monthNum;
            };


            if (( tmp = strstr ( buf, "DST starts" )))
            {
                aItem->dsEnable = 1;

                for ( int i = 0; i < sizeof ( dayList ) / sizeof ( List ); i++ )
                {
                    if ( strstr ( buf, dayList[i].name ))
                    {
                        aItem->dsStartDay = i;
                        break;
                    }
                }

                for ( i = 0; i < sizeof ( monthList ) / sizeof ( List ); i++ )
                {
                    if (( tmp = strstr ( buf, monthList[i].name )))
                    {
                        aItem->dsStartMonth = i;
                        tmp += strlen ( monthList[i].name );
                        break;
                    }
                }

                // now to work out the what day in the month ie 1st, 2nd 3rd etc
                int day;
                sscanf ( tmp, "%d", &day );
                day = day / 7;
                aItem->dsStartWeek = day;
            }


            if (( tmp = strstr ( buf, "DST ends" )))
            {
                aItem->dsEnable = 1;

                for ( int i = 0; i < sizeof ( dayList ) / sizeof ( List ); i++ )
                {
                    if ( strstr ( buf, dayList[i].name ))
                    {
                        aItem->dsEndDay = i;
                        break;
                    }
                }

                for ( i = 0; i < sizeof ( monthList ) / sizeof ( List ); i++ )
                {
                    if (( tmp = strstr ( buf, monthList[i].name )))
                    {
                        aItem->dsEndMonth = i;
                        tmp += strlen ( monthList[i].name );
                        break;
                    }
                }

                // now to work out the what day in the month ie 1st, 2nd 3rd etc
                int day;
                sscanf ( tmp, "%d", &day );
                day = day / 7;
                aItem->dsEndWeek = day;
            }


//Daylight Saving Time DST starts
//Daylight Saving Time DST ends                    
//DST starts
//DST ends
        }
        /*
            char dst[255];
            city[0] = country[0] = dst[0] = 0;
            LocationItem * aItem = new LocationItem;

            lastTag = aItem->tag = locationTag++;

            sscanf ( buf, "%32[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz `'-.] %26[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz `'-.] %f %d %f %c %f %c %[^\n]", 
                city, country, &aItem->offset, &aItem->countryCode, &aItem->latitude, &aItem->ns, &aItem->longitude, &aItem->ew, dst );

            // remove trailing spaces
            for ( int i = strlen ( city ) - 1; city[i] == ' '; i-- )
                    city[i] = 0;
            for ( i = strlen ( country ) - 1; country[i] == ' '; i-- )
                    country[i] = 0;

            aItem->city = city;
            aItem->country = country;

            aItem->dsStartWeek = -1;
            aItem->dsStartDay = -1;
            aItem->dsStartMonth = -1;
            aItem->dsEndWeek = -1;
            aItem->dsEndDay = -1;
            aItem->dsEndMonth = -1;
            aItem->dsEnable = 1;


            char timeStr[4][255];
            sscanf ( dst, "%s %s %s %s", timeStr[0], timeStr[1], timeStr[2], timeStr[3] );

            if ( timeStr[0][0] == '<' )
            {
                aItem->dsEnable = 0;
                ll.Add ( aItem );
                continue;
            }

            for ( i = 0; i < sizeof ( weekList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[0], weekList[i].name ))
                {
                    aItem->dsStartWeek = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( dayList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[1], dayList[i].name ))
                {
                    aItem->dsStartDay = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( monthList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[3], monthList[i].name ))
                {
                    aItem->dsStartMonth = i;
                    break;
                }
            }

            sscanf ( &dst[34], "%s %s %s %s", timeStr[0], timeStr[1], timeStr[2], timeStr[3] );

            for ( i = 0; i < sizeof ( weekList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[0], weekList[i].name ))
                {
                    aItem->dsEndWeek = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( dayList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[1], dayList[i].name ))
                {
                    aItem->dsEndDay = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( monthList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[3], monthList[i].name ))
                {
                    aItem->dsEndMonth = i;
                    break;
                }
            }


            if ( aItem->dsStartWeek == -1 ||
                 aItem->dsStartDay == -1 ||
                 aItem->dsStartMonth == -1 ||
                 aItem->dsEndWeek == -1 ||
                 aItem->dsEndDay == -1 ||
                 aItem->dsEndMonth == -1 )
                MessageBox ( NULL, "Unknown dst option", NULL, MB_ICONEXCLAMATION );

            ll.Add ( aItem );
       }
          */
       fin.close ();


       // save the data back in binary form
       Save ();

       // clear the list out
       LocationItem * lItem;
        while ( lItem = ll.Nth ( 0 ))
            ll.Delete ( lItem );
//    }
}

/*
void Locations::Create ( string & locationsFile  )
{
        fileName = locationsFile;

        class List
        {
        public:
            int index;
            char * name;
        };

        List dayList[] = { 
            { 0, "Sunday" },
            { 1, "Monday" },
            { 2, "Tuesday" },
            { 3, "Wednesday" },
            { 4, "Thursday" },
            { 5, "Friday" },
            { 6, "Saturday" },
        };

        List weekList[] = { 
            { 0, "First" },
            { 1, "Second" },
            { 2, "Third" },
            { 3, "Fourth" },
            { 4, "Last" },
        };

        List monthList[] = { 
            { 0, "January" },
            { 1, "February" },
            { 2, "March" },
            { 3, "April" },
            { 4, "May" },
            { 5, "June" },
            { 6, "July" },
            { 7, "August" },
            { 8, "September" },
            { 9, "October" },
            { 10, "November" },
            { 11, "December" },
        };

        ifstream fin ( "data\\default.txt" );
        short locationTag = 0;
        while ( !fin.eof() )
        {
            char buf[255];
            fin.getline ( buf, sizeof ( buf ));

            if ( strlen ( buf ) == 0)
                    break;

            if ( buf[0] == '/' )
                // ignore commented lines
                continue;

            char city[150];
            char country[150];
            char dst[255];
            city[0] = country[0] = dst[0] = 0;
            LocationItem * aItem = new LocationItem;

            lastTag = aItem->tag = locationTag++;

            sscanf ( buf, "%32[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz `'-.] %26[ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz `'-.] %f %d %f %c %f %c %[^\n]", 
                city, country, &aItem->offset, &aItem->countryCode, &aItem->latitude, &aItem->ns, &aItem->longitude, &aItem->ew, dst );

            // remove trailing spaces
            for ( int i = strlen ( city ) - 1; city[i] == ' '; i-- )
                    city[i] = 0;
            for ( i = strlen ( country ) - 1; country[i] == ' '; i-- )
                    country[i] = 0;

            aItem->city = city;
            aItem->country = country;

            aItem->dsStartWeek = -1;
            aItem->dsStartDay = -1;
            aItem->dsStartMonth = -1;
            aItem->dsEndWeek = -1;
            aItem->dsEndDay = -1;
            aItem->dsEndMonth = -1;
            aItem->dsEnable = 1;


            char timeStr[4][255];
            sscanf ( dst, "%s %s %s %s", timeStr[0], timeStr[1], timeStr[2], timeStr[3] );

            if ( timeStr[0][0] == '<' )
            {
                aItem->dsEnable = 0;
                ll.Add ( aItem );
                continue;
            }

            for ( i = 0; i < sizeof ( weekList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[0], weekList[i].name ))
                {
                    aItem->dsStartWeek = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( dayList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[1], dayList[i].name ))
                {
                    aItem->dsStartDay = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( monthList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[3], monthList[i].name ))
                {
                    aItem->dsStartMonth = i;
                    break;
                }
            }

            sscanf ( &dst[34], "%s %s %s %s", timeStr[0], timeStr[1], timeStr[2], timeStr[3] );

            for ( i = 0; i < sizeof ( weekList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[0], weekList[i].name ))
                {
                    aItem->dsEndWeek = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( dayList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[1], dayList[i].name ))
                {
                    aItem->dsEndDay = i;
                    break;
                }
            }

            for ( i = 0; i < sizeof ( monthList ) / sizeof ( List ); i++ )
            {
                if ( !stricmp ( timeStr[3], monthList[i].name ))
                {
                    aItem->dsEndMonth = i;
                    break;
                }
            }


            if ( aItem->dsStartWeek == -1 ||
                 aItem->dsStartDay == -1 ||
                 aItem->dsStartMonth == -1 ||
                 aItem->dsEndWeek == -1 ||
                 aItem->dsEndDay == -1 ||
                 aItem->dsEndMonth == -1 )
                MessageBox ( NULL, "Unknown dst option", NULL, MB_ICONEXCLAMATION );

            ll.Add ( aItem );
       }

       fin.close ();


       // save the data back in binary form
       Save ();

       // clear the list out
       LocationItem * lItem;
        while ( lItem = ll.Nth ( 0 ))
            ll.Delete ( lItem );
//    }
}
*/
void Locations::Open ( string & locationsFile  )
{
    fileName = locationsFile;
    bifstream bin ( locationsFile.c_str() );

    if ( bin.fail ())
    {
        bin.close();
        return;
    }

    int	numLocations;
    bin >> version >> lastTag >> numLocations;
    for ( int i = 0; i < numLocations; i++ )
    {
        LocationItem * aItem = new LocationItem;
        bin >> *aItem;
        ll.Add ( aItem );
//        Add ( aItem ); dont increment tags
    }
    bin.close();
}

Locations::~Locations ( void )
{
}

//void Locations::Save ( string & locationsFile )
void Locations::Save ( void )
{
     version = VERSION;

     // backup data
     CopyFile ( fileName.c_str(), "locations_WorkInProgress.woe", FALSE );

     bofstream bout ( fileName.c_str() );
    if ( bout.fail ())
        return;

     bout << version << lastTag << ll.Size();

     for ( int i = 0; i < ll.Size(); i++ )
     {
         LocationItem * aItem = ll.Nth ( i );
         bout << *aItem;
     }

     bout.close();
}


int Locations::DaylightSavings ( LocationItem * li, CTime * t )
{
    int monthLimit[12] =
    {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

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
         return 0;

    // month is not in extreme boundary of dst, so must be dst
    if ( month != li->dsStartMonth && month != li->dsEndMonth )
         return 1;

    // if we get here, we still have determined that dst either starts or ends in
    // the current month. We must now be more specific and check the weeks and days

    CTime startMonth ( t->GetYear(), t->GetMonth(), 1, t->GetHour(), t->GetMinute(), t->GetSecond());
    const int startMonthDay = startMonth.GetDayOfWeek() - 1;

    //	startMonth -= CTimeSpan( 0, 1, 0, 0 );
    // work out what day the 1st of the month is
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
            return 1;
    }


    return 0;
}

