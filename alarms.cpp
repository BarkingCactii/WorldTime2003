#include "stdafx.h"
#include <math.h>
#include "skin.h"
#include "displaylocation.h"

#include "location.h"
#include "member.h"
#include "regData.h"

#include "DlgAlarmMessage.h"
#include <strstream>
#include "Sounds.h"

//#include "dlgMember.h"
//#include "DlgAlarm.h"

//#include "DlgPreferences.h"
//#include "PrefPropSheet.h"

//#include "cisbitmap.h"
//#include "wingdi.h"
//#include "TimeSync.h"


//  Recurring values
//
//  Once
//  Daily
//  Weekly
//  Fortnightly
//  Monthly

static const float recurringTab[] = {
    0.0f,
    60.0f * 24.0f,
    60.0f * 24.0f * 7.0f,
    60.0f * 24.0f * 14.0f,
    60.0f * 24.0f * 28.0f  // needs to be fixed
};


bool ProcessChimes ( CTime & localTime )
{
    static bool chimeSounded = false;

    if ( localTime.GetMinute() == 0 )
    {
        if ( !chimeSounded )
        {
            chimeSounded = true;    
            Playsound ( r.SoundHourFile().c_str(), r.SoundHour() ? true : false ); //r.SoundAlarm() ? true : false);
        }
    }
    else
    if ((localTime.GetMinute() % 15) == 0 )
    {
        if ( !chimeSounded )
        {
            chimeSounded = true;
            Playsound ( r.SoundQuarterFile().c_str(), r.SoundQuarter() ? true : false ); //r.SoundAlarm() ? true : false);
        }
    }
    else
        chimeSounded = false;

    return true;
}

bool ProcessAlarms ( CTime & localTime )
{
    // loop through the members list

    bool alarmSet = false;

    MemberItem * mItem = 0;
//    LocationItem * lItem = 0;
    
    for ( int i = 0; mItem = m.GetMemberByIdx ( i ); i++ )
    {
        LocationItem * lItem = l.GetLocationbyTag ( mItem->LocRef() );
        if ( !lItem )
            continue;

        CTime t = localTime;

        float dst = MemberTime ( lItem, t );
        AlarmItem * aItem = 0;

        for ( int j = 0; aItem = mItem->GetAlarm ( j ); j++ )
        {
            CTime alarmTime = aItem->Time();

            int h1, h2, m1, m2;

            h1 = alarmTime.GetHour ();
            h2 = alarmTime.GetMinute ();
            m1 = t.GetHour ();
            m2 = t.GetMinute ();

            if ( alarmTime.GetHour() == t.GetHour() && alarmTime.GetMinute() == t.GetMinute())
            {
                // only check if alarm has been reset after checking for the time
                // otherwise the alarm will get reset
//                if ( aItem->alarmReset == false )
//                {
//                    alarmSet = mItem->alarmActive = true;
                    if ( aItem->GetDisplayStatus () == true )
                        continue;

                    aItem->SetDisplayStatus ( true );
                    alarmSet = true;

                    // play a sound
                    Playsound ( r.SoundAlarmFile().c_str(), aItem->PlaySound() ? ( r.SoundAlarm() ? true : false) : false ); //r.SoundAlarm() ? true : false);

                    // run an app
                    if ( aItem->RunApp())
                         ShellExecute( AfxGetMainWnd()->m_hWnd, NULL, aItem->AppName().c_str(), NULL, NULL, SW_SHOWNORMAL );

                    CDlgAlarmMessage dlg;

                    strstream sout;
                    if ( !mItem->Location())
                        sout << mItem->Name() << " @ ";
                    sout << lItem->city << ", " << lItem->country << ends;
                    dlg.m_location = sout.str();

                    dlg.m_message = aItem->Message ().c_str();
                    dlg.m_aItem = aItem;

                    if ( dlg.DoModal () == IDOK )
                    {

                        // rescedule new alarm
                        switch (aItem->Occurence ())
                        {
                        case Once:
                            // remove alarm
                            mItem->DeleteAlarm ( j );
                            break;
                        case Daily:
                            aItem->Time() += CTimeSpan (1, 0, 0, 0);
                            break;
                        case Weekly:
                            aItem->Time() += CTimeSpan (7, 0, 0, 0);
                            break;
                        case Fortnightly:
                            aItem->Time() += CTimeSpan (14, 0, 0, 0);
                            break;
                        case Monthly:
                            CTime tmp ( aItem->Time().GetYear(), 
                                        aItem->Time().GetMonth() + 1,
                                        aItem->Time().GetDay(),
                                        aItem->Time().GetHour(),
                                        aItem->Time().GetMinute(),
                                        0 );

                            aItem->Time() = tmp;
//                            aItem->Time().GetMonth
                            break;
                        }
                    }
                    else
                    {
                        // snooze 5 minutes
                        aItem->Time() += CTimeSpan (0, 0, 5, 0);
                        aItem->SetDisplayStatus ( false );

                    }
                
                    break;
        
                    /*
                    Playsound ( r.SoundAlarmFile().c_str(), r.SoundAlarm() ? true : false);

                    if ( mItem->alarmAppExec == false )
                    {
                    if ( mItem->alarmRunEnable )
                     {
                         ShellExecute( AfxGetMainWnd()->m_hWnd, NULL, mItem->alarmRunApp.c_str(), NULL, NULL, SW_SHOWNORMAL );
                         mItem->alarmAppExec = true;
                     }
                     */
  //              }
            }
        }
    }


    return alarmSet;

//        CTime t = CTime::GetCurrentTime();
//        ti = t;

            /*
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
        */
//    }
//    return alarmSet;
    
}

