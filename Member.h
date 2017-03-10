#ifndef _Member_H
#define _Member_H

#include "bstream.h"
#include "list.h"

#define VERSION 0.90f

/*
class DisplayItem
{
public:
    virtual int  Tag ( void ) = 0;
//    virtual bool Type ( void ) = 0;
    DisplayItem ( void ) { }
};
  */

enum Recurring { Once = 0, Daily = 1, Weekly = 2, Fortnightly = 3, Monthly = 4 };

class AlarmItem
{
    friend class MemberItem;
    friend bifstream & operator >> ( bifstream & fin,  AlarmItem & data );
    friend bofstream & operator << ( bofstream & fout, AlarmItem & data );

private:
//    int  hour;
//    int  minute;

//    int  day;
//    int  month;
//    int  year;


    CTime time;
    Recurring occurence;
    bool playSound;

    string messageText;

    bool   appRun;
    string appRunText;

    // working variables
    bool messageDisplayed;


public:
//    void Time ( CTime & t ) { time = t; }
    CTime & Time ( void ) { return time; }
    string & Message ( void ) { return messageText; }
    Recurring Occurence ( void ) { return occurence; }
    bool PlaySound ( void ) { return playSound; }
    bool RunApp ( void ) { return appRun; }
    string & AppName ( void ) { return appRunText; }
    void SetDisplayStatus ( bool status ) { messageDisplayed = status; }
    bool GetDisplayStatus ( void ) { return messageDisplayed; }

     void Reset ( CTime & newDate, CTime & newTime, Recurring newRecurring,
         bool newPlaySound, CString & newMessageText, bool newAppRun, CString & newAppRunText )
     {
         CTime tmp ( newDate.GetYear(), newDate.GetMonth(), newDate.GetDay(), 0, 0, 0);
         time = tmp;
         time += CTimeSpan (0, newTime.GetHour(), newTime.GetMinute(), 0);
         occurence = newRecurring;
         playSound = newPlaySound;
         messageText = newMessageText;
         appRun = newAppRun;
         appRunText = newAppRunText;

         messageDisplayed = false;
     }


     AlarmItem ( CTime & newDate, CTime & newTime, Recurring newRecurring,
         bool newPlaySound, CString & newMessageText, bool newAppRun, CString & newAppRunText )
     {
         Reset ( newDate, newTime, newRecurring, newPlaySound, newMessageText
             , newAppRun, newAppRunText );

//         CTime tmp ( newDate.GetYear(), newDate.GetMonth(), newDate.GetDay(), 0, 0, 0);
//         time = tmp;
//         time += CTimeSpan (0, newTime.GetHour(), newTime.GetSecond(), 0);
//         occurence = newRecurring;
//         playSound = newPlaySound;
//         messageText = newMessageText;
//         appRun = newAppRun;
//         appRunText = newAppRunText;

     }


     AlarmItem ( void )
     {
//         hour = minute = 0;
//         day = month = 0;
//         year = 2003;

         playSound = true;
        
         messageText = appRunText = "";

         appRun = false;
     }
};

class MemberItem //: public virtual DisplayItem
{
    friend class Members;
    friend bifstream & operator >> ( bifstream & fin,  MemberItem & data );
    friend bofstream & operator << ( bofstream & fout, MemberItem & data );

private:
    LinkedList<AlarmItem *> ll;
    int    tag;
           
    int    locRef;

    bool   location;

    // make this a virtual class pointer to member and location
    // if location, below is irrelevant
    string name;
    string email;
    string phone;


//     int  alarmEnable;
//     int  alarmHour;
//     int  alarmMinute;
//     string alarmMessage;
//     string alarmRunApp;

//     int alarmRunEnable;
//     int offsetX;
//     int offsetY;
     

     //
     //   throw in some extra fields
     //
//     int    spare[3];

     //
     // not saved to database
//    bool alarmActive;
//    bool alarmReset;
//    bool alarmAppExec;  // flag to tell us if the application has been run on an alarm
public:

    // get
    //
    bool Location ( void ) { return location; }
    int LocRef ( void ) { return locRef; }
    int Tag ( void ) { return tag; }
    string & Name ( void ) { return name; }
    string & Email ( void ) { return email; }
    string & Phone ( void ) { return phone; }

    //
    // set
    void Location ( bool newLocation ) { location = newLocation; }
    void LocRef ( int newLocRef ) { locRef = newLocRef; }
    void Name ( CString & newName ) { name = newName; }
    void Email ( CString & newEmail ) { email = newEmail; }
    void Phone ( CString & newPhone ) { phone = newPhone; }


     int NumAlarms ( void ) { return ll.Size(); }
     AlarmItem * GetAlarm ( int idx )
     {
         return ll.Nth ( idx );
     }

     bool DeleteAlarm ( int idx )
     {
         AlarmItem * aItem = GetAlarm ( idx );
         if ( !aItem )
             return false;

         ll.Delete ( aItem );
         return true;
     }

     // add alarm
     void Add ( AlarmItem * aItem )
     {
         ll.Add ( aItem );
     }


     MemberItem ( void )
     {
          tag = 0;

          locRef = 0;
          name = email = phone = "";

          /*
            alarmEnable = 0;
            alarmHour = 0;
            alarmMinute = 0;
            alarmMessage = "";
            alarmRunApp = "";
            alarmRunEnable = 1;

          for ( int i = 0; i < sizeof ( spare ) / sizeof ( int ); i++ )
              spare[i] = 0;

          alarmActive = false;
          alarmReset = false;
          alarmAppExec = false;

          offsetX = 0;
          offsetY = 0;
          */
     }
};



class Members
{
private:                    
    string fileName;

    LinkedList<MemberItem *> ll;

    float version;
    int  lastTag;

    bool modified;

public:
    void SetModified ( void ) { modified = true; }
     float Version ( void ) { return version; }
     int Size ( void ) { return ll.Size(); }

     int Tag ( int idx ) 
     { 
         if ( idx < ll.Size()) 
             return ll.Nth ( idx )->Tag(); 
         else 
             return -1; 
     }

     int OffsetDisplay ( int idx );

     bool Name ( string & s, int idx ) 
     {
         MemberItem * mi = ll.Nth ( idx );
         if ( mi == 0 )
             return false;

         s = mi->Name();
         return true;
     }

     MemberItem * GetMemberbyTag ( int tag )
     {
         ListIterator<MemberItem *> it(ll);
         MemberItem * li;
         while ( li = it++ )
         {
             if ( li->Tag() == tag )
                 return li;
         }


//         MessageBox( NULL, "Member tag not found. Abortion not necessary", "Error", MB_ICONSTOP | MB_OK );

         // delete reference from group, as it no longer exists
         return 0;
     }

     MemberItem * GetMemberbyLocRef ( int ref )
     {
         ListIterator<MemberItem *> it(ll);
         MemberItem * li;
         while ( li = it++ )
         {
             if ( li->LocRef() == ref )
                 return li;
         }

         return 0;
     }


     MemberItem * GetMemberByIdx ( int idx )
     {
         return ll.Nth ( idx );
     }

     
     void DeleteAlarm ( int tag, int alarm )
     {
        ListIterator<MemberItem *> it(ll);
        MemberItem * li;
        while ( li = it++ )
        {
            if ( li->Tag() == tag )
            {
                li->DeleteAlarm ( alarm );
                break;
            }
        }
     }
       

     
     void DeleteList ( int tag )
     {

        MemberItem * mi;
        mi = GetMemberbyTag ( tag );
        if ( mi )
            ll.Delete ( mi );

        return;

        ListIterator<MemberItem *> it(ll);
        MemberItem * li;

        while ( li = it++ )
        {
            if ( li->Tag() == tag )
            {
                ll.Delete ( li );
                break;
            }
        }
     }
  
     void Add ( MemberItem * aItem )
     {
         lastTag++;
         aItem->tag = lastTag;
         ll.Add ( aItem );
     }

     int AlarmsPending ( void )
     {
         int alarms = 0;

         ListIterator<MemberItem *> it(ll);
         MemberItem * mi;
         while ( mi = it++ )
             alarms += mi->NumAlarms(); // accumulate number of alarms for each member

        return alarms;
     }


     // class persistence
     void Save ( void ); //string & );
     void Open ( string & );

     Members ( void );
    ~Members ( void );
};

extern Members m;

#endif
