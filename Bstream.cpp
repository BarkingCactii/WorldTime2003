 //
//
//   BSTREAM.CPP
//
//   Binary File I/O via manipulators
//
//	Developed by:  Jeff Hill of PCM Computer Systems Pty Ltd
//                  for Reoforce Systems Pty Ltd
//
//

#include "stdafx.h"
//#include <stdio.h>
//#include "globals.h"
//#include "units.h"
#include "bstream.h"
//#include "bardbase.h"

#define BYTESZ	8
#define WORDSZ	16

#undef LOBYTE
#undef HIBYTE
#undef LOWORD
#undef HIWORD

#define LOBYTE	0x00ff
#define HIBYTE	0xff00
#define LOWORD	0x0000ffff
#define HIWORD	0xffff0000
/*
static unsigned short SSwap ( unsigned short arg)
{
     if ( bDB->ForeignFile ())
          return(((arg & LOBYTE) << BYTESZ) | ((arg & HIBYTE) >> BYTESZ));

     return arg;
}
*/
/*
static unsigned long LSwap ( unsigned long arg )
{
     if ( bDB->ForeignFile ())
     {
          unsigned  short     hiword;
          unsigned  short     loword;

          hiword = SSwap(( unsigned short ) ((arg & HIWORD) >> WORDSZ ));
          loword = SSwap(( unsigned short ) ( arg & LOWORD ));

          return(hiword | (loword << WORDSZ));
     }

     return arg;
}

static double RSwap ( double rnum )
{
     if ( bDB->ForeignFile ())
     {
     	char	res1[sizeof(double) / 2];
     	char	res2[sizeof(double) / 2];
     	char	*src;
     	char	*dest;
     	double	result;
     	long	*tmp;
     
     	src = (char *)&rnum;
     	dest = (char *)&result;
     
     	memcpy(res1, src, sizeof(res1));
     	memcpy(res2, src + (sizeof(double) / 2), sizeof(double) / 2);
     
     	tmp = (long *)res1;
     	*tmp = LSwap(*tmp);
     
     	tmp = (long *)res2;
     	*tmp = LSwap(*tmp);
     
     	memcpy(dest, res2, sizeof(res2));
     	memcpy(dest + (sizeof(double) / 2), res1, sizeof(double) / 2);
     
     	return(result);
     }
     
     return rnum;
}

*/
/*-------------------------------------------------------------------------
|	IEEEtoReal
|
|	Purpose: Converts an IEEE float to a double
|
*/
/*
double IEEEToReal ( double * rp )
{
	double    *num;

	num = rp;
     return(RSwap(*num));
}
*/
/*-------------------------------------------------------------------------
|	RealtoIEEE
|
|	Purpose: Converts a double to IEEE format
|
*/
/*
void RealToIEEE ( double r, double * result )
{
	double    *num;

	num = result;
	*num = RSwap(r);
}

void bofstream::Convert ( void *p, DataType type )
{
     if ( type == TChar )
     {
          // do nothing
     }
     else
     if ( type == TShort || type == TUShort )
     {
     }
     else
     if ( type == TLong || type == TULong )
     {
     }
     else
     if ( type == TFloat )
     {
     }
     else
     if ( type == TDouble || type == TUDouble )
     {
          double * val = ( double * ) p;
          RealToIEEE ( *val, val );
     }
     else
     if ( type == TBoolean || type == TColor || type == TBarType ||
          type == TSide || type == TFormats || type == TUnits || type == TShape )
     {
          // defined as char, so do nothing
     }
     else
     if ( type == TString || type == TCharPtr )
     {
          // do nothing
     }
     else
          *err << Error << "Unknown data type " << ( short ) type << " on ofstream" << endl;
}

  */
/*
void bofstream::WriteBytes ( void *p, int len, DataType type )
{
     if ( !p ) 
     {
          *err << Error << "Writing a NULL pointer" << endl;
          return;
     }

     if ( len <= 0 ) 
     {
          *err << Error << "Writing a <= 0 length data " << len << endl;
          return;
     }
     Convert ( p, type );
     write ((char *) p, len );
     if ( good () == 0 )
          *err << Error << "Failed to write datatype " << ( short )type << " of length " << len << endl;
}

void bifstream::Convert ( void *p, DataType type )
{
     if ( type == TChar )
     {
          // do nothing
     }
     else
     if ( type == TShort || type == TUShort )
     {
          unsigned short * val = ( unsigned short * ) p;
          *val = SSwap ( *val );
     }
     else
     if ( type == TLong || type == TULong )
     {
          unsigned long * val = ( unsigned long * ) p;
          *val = LSwap ( *val );
     }
     else
     if ( type == TFloat )
     {
          float *f = (float *) p;
          double val = (double) *f;
          val = IEEEToReal ( &val );
          *f = ( float )val;
     }
     else
     if ( type == TDouble || type == TUDouble )
     {
          double * val = ( double * ) p;
          *val = IEEEToReal ( val );
     }
     else
     if ( type == TBoolean || type == TColor || type == TBarType ||
          type == TSide || type == TFormats || type == TUnits || type == TShape )
     {
          // defined as char, so do nothing
     }
     else
     if ( type == TString || type == TCharPtr )
     {
          // do nothing
     }
     else
          *err << Error << "Unknown data type " << ( short )type << " on ifstream" << endl;
}
*/
/*
void bifstream::Convert ( void *p, DataType type )
{
     if ( type == TChar )
     {
     }
     else
     if ( type == TShort || type == TUShort )
     {
     }
     else
     if ( type == TLong || type == TULong )
     {
     }
     else
     if ( type == TFloat )
     {
     }
     else
     if ( type == TDouble )
     {
     }
     else
     if ( type == TBoolean || type == TColor || type == TBarType ||
          type == TSide || type == TFormats || type == TUnits || type == TShape )
     {
     }
     else
     if ( type == TString || type == TCharPtr )
     {
     }
     else
          *err << Error << "Unknown data type " << type << " on ifstream" << endl;
}
*/
/*
void bifstream::ReadBytes ( void *p, int len, DataType type )
{
     if ( !p ) 
     {
          *err << Error << "Reading a NULL pointer" << endl;
          return;
     }
     if ( len <= 0 ) 
     {
          *err << Error << "Reading a <= 0 length data " << len << endl;
          return;
     }
//     printf("\nAbout to Read %d bytes",len);
     read ((char *)p, len );
//     if ( type == TFloat )
//     {
//          float *f = (float*)p;
//          printf("\nFloat = %f",*f);
//     }
//     printf ( "good %d fail %d eof %d bar %d", good(), fail(), eof(), bad());
     if ( good () == 0 )
	      *err << Information << "End of File reached after reading " << tellg() << " bytes" << endl;
//          *err << Error << "Failed to read datatype " << ( short )type << " of length " << len << " at pos " << tellg () << endl;
     else
     {
          Convert ( p, type );
//          printf(" - convert OK!!");
     }
}


#include <stdio.h>

void bifstream::SetExistsStatus ( const char * fn )
{

     return;

     FILE * fp;

     fp = fopen ( fn, "rb" );

     // make sure all error status bits are set

     if ( !fp )
          clear ( ios::failbit | ios::badbit | ios::eofbit );
     else
     {
          // make sure file isn't zero size
          char ch;
          ch = fgetc ( fp );

          if ( feof ( fp ))
               clear ( ios::failbit | ios::badbit | ios::eofbit );

          fclose ( fp );
     }
}

#ifdef _VC41

istream& istream::get ( char * arg1, int arg2, int arg3 )
{
	printf ( "Error: In Unresolved library function\n" );
	return *this;
}

#endif
*/

void bifstream::ReadBytes ( void *p, int len, DataType type )
{
     if ( !p ) 
     {
//          *err << Error << "Reading a NULL pointer" << endl;
          return;
     }
     if ( len <= 0 ) 
     {
//          *err << Error << "Reading a <= 0 length data " << len << endl;
          return;
     }

     read (( char * ) p, len );
}

void bofstream::WriteBytes ( void *p, int len, DataType type )
{
     if ( !p ) 
     {
//          *err << Error << "Writing a NULL pointer" << endl;
          return;
     }

     if ( len <= 0 ) 
     {
//          *err << Error << "Writing a <= 0 length data " << len << endl;
          return;
     }
//     Convert ( p, type );
     write (( char * ) p, len );
//     if ( good () == 0 )
//          *err << Error << "Failed to write datatype " << ( short )type << " of length " << len << endl;
}

