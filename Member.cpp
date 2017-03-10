// Member.cpp
//

#include "stdafx.h"
#include "Member.h"
//#include "onlineTimeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

Members m;


bifstream & operator >> ( bifstream & fin, AlarmItem & data )
{
    int year, month, day, hour, minute;

    fin >> hour >> minute;
    fin >> day >> month >> year;
    CTime tmpt ( year, month, day, hour, minute, 0 );
    data.time = tmpt;
    short tmp;
    fin >> tmp;
    data.occurence = ( Recurring )tmp;
    fin >> data.playSound;
    fin >> data.messageText >> data.appRun >> data.appRunText; 

    return fin;
}

bofstream & operator << ( bofstream & fout, AlarmItem & data )
{
    fout << data.time.GetHour() << data.time.GetMinute();
    fout << data.time.GetDay() << data.time.GetMonth() << data.time.GetYear();
    fout << ( short ) data.occurence << data.playSound;
    fout << data.messageText << data.appRun << data.appRunText; 

    return fout;
}


bifstream & operator >> ( bifstream & fin, MemberItem & data )
{
    fin >> data.tag >> data.locRef >> data.location >> data.name >> data.email >> data.phone;

    int numAlarms = 0;
    fin >> numAlarms;

    for ( int i = 0; i < numAlarms; i++ )
    {
        AlarmItem * aItem = new AlarmItem;
        fin >> *aItem;
        data.ll.Add ( aItem );
    }
//    fin >> data.alarmEnable >> data.alarmHour >> data.alarmMinute >> data.alarmMessage >> data.alarmRunApp >> data.alarmRunEnable;

//    fin >> data.offsetX >> data.offsetY;

//    for ( int i = 0; i < sizeof ( data.spare ) / sizeof ( int ); i++ )
//        fin >> data.spare[i];

    return fin;
}

bofstream & operator << ( bofstream & fout, MemberItem & data )
{
    fout << data.tag << data.locRef << data.location << data.name << data.email << data.phone;

    fout << data.NumAlarms();
    for ( int i = 0; i < data.NumAlarms(); i++ )
    {
         AlarmItem * aItem = data.GetAlarm ( i );
         fout << *aItem;
    }


//    fout << data.alarmEnable << data.alarmHour << data.alarmMinute << data.alarmMessage << data.alarmRunApp << data.alarmRunEnable;

//    fout << data.offsetX << data.offsetY;

//    for ( int i = 0; i < sizeof ( data.spare ) / sizeof ( int ); i++ )
//        fout << data.spare[i];

    return fout;
}


Members::Members ( void  )
{
    lastTag = 0;
    version = VERSION;
    modified = false;
}


void Members::Open ( string & MembersFile  )
{
    DEBUGLINE
    fileName = MembersFile;
    bifstream bin ( MembersFile.c_str() );

    if ( bin.eof() )
    {
        bin.close();
        return;
    }

    int	numMembers = 0;
    bin >> version >> lastTag >> numMembers;
    for ( int i = 0; i < numMembers; i++ )
    {
        MemberItem * aItem = new MemberItem;
        bin >> *aItem;

        ll.Add ( aItem );

        // add to the display list
// no no        displayData.data[i].offset.x = aItem->offsetX;
//        displayData.data[i].offset.y = aItem->offsetY;

    }
    bin.close();
}

Members::~Members ( void )
{
    // save the data
//    Save();
}

//void Members::Save ( string & MembersFile )
void Members::Save ( void )
{
    DEBUGLINE

    if ( !modified )
        return;

     version = VERSION;

     // backup data
     CopyFile ( fileName.c_str(), "members_WorkInProgress.wt2003", FALSE );


     bofstream bout ( fileName.c_str() );

    if ( bout.fail ())
        return;

     lastTag = ll.Size();
     bout << version << lastTag << ll.Size();

     for ( int i = 0; i < ll.Size(); i++ )
     {
         MemberItem * aItem = ll.Nth ( i );
         aItem->tag = i;
         bout << *aItem;
     }

     bout.close();

    modified = false;

}



