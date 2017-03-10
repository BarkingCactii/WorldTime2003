//
//
//   BSTREAM.H
//
//   Binary File I/O via manipulators
//
//	Developed by:  Jeff Hill of PCM Computer Systems Pty Ltd
//                  for Reoforce Systems Pty Ltd
//
//

#ifndef _BSTREAM_H
#define _BSTREAM_H

#include <iostream>
#include <fstream>
//#include "units.h"
//#include "str.h"
#include <string>
using namespace std;

const int MaxLineSz = 128;

//enum Boolean { False = 0, True = 1 };
// Binary output file stream

enum DataType   { TChar, TShort, TInt, TUShort, TLong, TULong, TFloat, TDouble,
                  TBoolean, TColor, TBarType, TSide, TString, TCharPtr,
                  TFormats, TUnits, TShape, TUDouble };

class bofstream: public ofstream 
{
private:
public:
  bofstream ( const char *fn ) : ofstream ( fn, ios::out | ios::binary ) { }
  void WriteBytes ( void *, int, DataType );

  friend bofstream & operator << ( bofstream &, char );
  friend bofstream & operator << ( bofstream &, short );
  friend bofstream & operator << ( bofstream &, int );
  friend bofstream & operator << ( bofstream &, unsigned short );
  friend bofstream & operator << ( bofstream &, long );
  friend bofstream & operator << ( bofstream &, unsigned long );
  friend bofstream & operator << ( bofstream &, float );
  friend bofstream & operator << ( bofstream &, bool );
  friend bofstream & operator << ( bofstream &, string & );
  friend bofstream & operator << ( bofstream &, const char * );
  friend bofstream & operator << ( bofstream &, char * );
//  friend bofstream & operator << ( bofstream &, UDouble & );
};


// Binary input file stream

class bifstream: public ifstream {
private:
public:
    bifstream ( const char * fn ) : ifstream ( fn, ios::in | ios::binary ) { } //ios::nocreate ) { }
  void ReadBytes ( void *, int, DataType );

  friend bifstream & operator >> ( bifstream &, char & );
  friend bifstream & operator >> ( bifstream &, short & );
  friend bifstream & operator >> ( bifstream &, int & );
  friend bifstream & operator >> ( bifstream &, unsigned short & );
  friend bifstream & operator >> ( bifstream &, long & );
  friend bifstream & operator >> ( bifstream &, unsigned long & );
  friend bifstream & operator >> ( bifstream &, float & );
  friend bifstream & operator >> ( bifstream &, bool & );
  friend bifstream & operator >> ( bifstream &, string & );
//  friend bifstream & operator >> ( bifstream &, UDouble & );
};                            

// Binary file output friends

inline bofstream & operator << ( bofstream &fout, char val )
{
     fout.WriteBytes (( void *)&val, sizeof ( char ), TChar );
     return fout;
}

inline bofstream & operator << ( bofstream &fout, short val )
{
     fout.WriteBytes (( void *)&val, sizeof ( short ), TShort );
     return fout;
}


inline bofstream & operator << ( bofstream &fout, int val )
{
     fout.WriteBytes (( void *)&val, sizeof ( int ), TInt );
     return fout;
}

inline bofstream & operator << ( bofstream &fout, unsigned short val )
{
     fout.WriteBytes (( void *)&val, sizeof ( unsigned short ), TUShort );
     return fout;
}

inline bofstream & operator << ( bofstream &fout, long val )
{
     fout.WriteBytes (( void *)&val, sizeof ( long ), TLong );
     return fout;
}

inline bofstream & operator << ( bofstream &fout, unsigned long val )
{
     fout.WriteBytes (( void *)&val, sizeof ( unsigned long ), TULong );
     return fout;
}

inline bofstream & operator << ( bofstream &fout, float val )
{
//     FileUnit  u;
//     u = val;
//     u.Set ( Output );
//     val = u;

     fout.WriteBytes (( void *)&val, sizeof ( float ), TFloat );
     return fout;
}
/*
inline bofstream & operator << ( bofstream &fout, UDouble & val )
{
     double tmp = val.Val();
     fout.WriteBytes (( void *)&tmp, sizeof ( double ), TUDouble );
     return fout;
}
*/
inline bofstream & operator << ( bofstream &fout, bool val )
{
     char ch = ( char ) val;
     fout.WriteBytes (( void *)&val, sizeof ( char ), TChar );
     return fout;
}

inline bofstream & operator<< (bofstream &bofs, char * str)
{
     bofs.write ( str, ( int ) strlen ( str ) + 1 );
     return bofs;
}

inline bofstream & operator<< (bofstream &bofs, const char * str)
{
     bofs.write ( str, ( int ) strlen ( str ) + 1 );
     return bofs;
}

inline bofstream & operator << (bofstream &bofs, string & str)
{
//     const char * text = str;
     bofs.write ( str.c_str(), ( int ) str.size() + 1 );
     return bofs;
}

// Binary file input friends

inline bifstream & operator >> (bifstream &bifs, char& val )
{
     bifs.ReadBytes( ( void * ) &val, sizeof ( char ), TChar );
     return bifs;
}

inline bifstream & operator >> (bifstream &bifs, short& val )
{
     bifs.ReadBytes( ( void * ) &val, sizeof ( short ), TShort );
     return bifs;
}

inline bifstream & operator >> (bifstream &bifs, int& val )
{
     bifs.ReadBytes( ( void * ) &val, sizeof ( int ), TInt );
     return bifs;
}

inline bifstream & operator >> (bifstream &bifs, unsigned short& val )
{
     bifs.ReadBytes( ( void * ) &val, sizeof ( unsigned short ), TUShort );
     return bifs;
}

inline bifstream & operator >> (bifstream &bifs, long& val )
{
     bifs.ReadBytes( ( void * ) &val, sizeof ( long ), TLong );
     return bifs;
}

inline bifstream & operator >> (bifstream &bifs, unsigned long& val )
{
     bifs.ReadBytes( ( void * ) &val, sizeof ( unsigned long ), TULong );
     return bifs;
}


inline bifstream & operator >> (bifstream &bifs, float& val )
{
     bifs.ReadBytes( ( void * ) &val, sizeof ( float ), TFloat );

     // to fix 
//     FileUnit  u ( val );
//     val = u;

     return bifs;
}
/*
inline bifstream & operator >> (bifstream &bifs, UDouble & val )
{
     double tmp = val.Val ();
     bifs.ReadBytes( ( void * ) &tmp, sizeof ( double ), TUDouble );
     return bifs;
}
*/
inline bifstream & operator >> (bifstream &bifs, bool& val )
{
     char ch;
     bifs.ReadBytes( ( void * ) &ch, sizeof ( char ), TChar );
     ch ? val = true : val = false;

//     val = ( bool ) ch;
     return bifs;
}

inline bifstream & operator >> (bifstream &bifs, string & str)
{
     char tmpBuf[MaxLineSz];

     int i = 0;
     while (( tmpBuf[i++] = bifs.get()) != 0 )
     {
         if ( i >= MaxLineSz - 1 )
             break;
     }
     tmpBuf[i] = 0;

     str = tmpBuf;
     return bifs;
}

/*
#ifndef __WATCOMC__

inline bifstream & operator >> (bifstream &bifs, char * & str )
{
     char tmpBuf[MaxLineSz];

     int i = 0;
     while (( tmpBuf[i++] = bifs.get()) != 0 )
          ;
     tmpBuf[i] = 0;

     strcpy ( str, tmpBuf );     
     return bifs;
}

#endif

#ifdef WIN32

inline bifstream & operator >> (bifstream &bifs, char * str )
{
     char tmpBuf[MaxLineSz];

     int i = 0;
     while (( tmpBuf[i++] = bifs.get()) != 0 )
          ;
     tmpBuf[i] = 0;

     strcpy ( str, tmpBuf );     
     return bifs;
}

#endif

#ifdef __WATCOMC__

inline bifstream & operator >> (bifstream &bifs, char * str )
{
     char tmpBuf[MaxLineSz];

     int i = 0;
     while (( tmpBuf[i++] = bifs.get()) != 0 )
          ;
     tmpBuf[i] = 0;

     strcpy ( str, tmpBuf );     
     return bifs;
}

#endif

*/
#endif
