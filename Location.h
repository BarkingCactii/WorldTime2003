#ifndef _LOCATION_H
#define _LOCATION_H

#include "bstream.h"
#include "list.h"

#define VERSION 0.90f

class LocationItem
{
     friend bifstream & operator >> ( bifstream & fin,  LocationItem & data );
     friend bofstream & operator << ( bofstream & fout, LocationItem & data );

public:
     int    tag;

     string	country;
     string	city;
     int    countryCode;
     int    areaCode;

     float  offset;

     int    dsEnable;

     int	dsStartWeek;
     int	dsStartDay;
     int	dsStartMonth;

     int	dsEndWeek;
     int	dsEndDay;
     int	dsEndMonth;

     
     // alarm info
/*     int  alarmEnable;
     int  alarmHour;
     int  alarmMinute;
     string alarmMessage;
     string alarmRunApp;
     int alarmRunEnable;
  */
     float latitude;
     char  ns;
     float longitude;
     char  ew;


     //
     //   throw in some extra fields
     //
     int    spare[5];

     LocationItem ( void )
     {
          tag = 0;

          country = city = "";
          offset = 0.0f;
          countryCode = 0;
          areaCode = 0;
          dsEnable = 0;

          dsStartWeek = 0;
          dsStartDay = 0;
          dsStartMonth = 0;
          dsEndWeek = 0;
          dsEndDay = 0;
          dsEndMonth = 0;
    /*
            alarmEnable = 0;
            alarmHour = 0;
            alarmMinute = 0;
            alarmMessage = "";
            alarmRunApp = "";
            alarmRunEnable = 1;
      */

          latitude = longitude = 0.0f;
          ns = 'N'; ew = 'E';

          for ( int i = 0; i < sizeof ( spare ) / sizeof ( int ); i++ )
              spare[i] = 0;
     }
};



class Locations
{
private:                    
    string fileName;

     LinkedList<LocationItem *> ll;

     float version;
     int  lastTag;

public:
     float Version ( void ) { return version; }
     int Size ( void ) { return ll.Size(); }

     int Tag ( int idx ) { if ( idx < ll.Size()) return ll.Nth ( idx )->tag; else return -1; }
     string CountryList ( int idx ) { if ( idx < ll.Size()) return ll.Nth ( idx )->country; else return ""; }
     string CityList ( int idx ) { if ( idx < ll.Size()) return ll.Nth ( idx )->city; else return ""; }

     float GMTOffset ( int idx );
     float OffsetList ( int idx );
     int OffsetDisplay ( int idx );

     LocationItem * GetLocationbyTag ( int tag )
     {
         ListIterator<LocationItem *> it(ll);
         LocationItem * li;
         while ( li = it++ )
         {
             if ( li->tag == tag )
                 return li;
         }


//         MessageBox( NULL, "Location tag not found. Abortion not necessary", "Error", MB_ICONSTOP | MB_OK );

         return 0;
     }

     void DeleteList ( int tag )
     {

        ListIterator<LocationItem *> it(ll);
        LocationItem * li;
        while ( li = it++ )
        {
            if ( li->tag == tag )
            {
                ll.Delete ( li );
                break;
            }
        }
     }

     void Add ( LocationItem * aItem )
     {
         lastTag++;
         aItem->tag = lastTag;
         ll.Add ( aItem );
     }

     int DaylightSavings ( LocationItem * li, CTime * t );

     // class persistence
     void Save ( void ); //string & );
     void Open ( string & );
     void Create ( string & );

     Locations ( void );
    ~Locations ( void );
};

extern Locations l;

#endif
