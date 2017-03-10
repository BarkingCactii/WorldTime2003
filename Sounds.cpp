// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "skin.h"
#include <mmsystem.h>    // Multimedia functions and structures
#include <direct.h>        // DirectX defines (many of dsound structures)
#include <dsound.h>        // Direct sound Header
//#include "mainfrm.h"

//static LPDIRECTSOUND pDirectSoundAPI = NULL;
//static LPDIRECTSOUNDBUFFER pGrunt = NULL;

BOOL bSetupBufferFromWave(LPDIRECTSOUNDBUFFER& pDSBuffer, const char *szWaveFile, LPDIRECTSOUND pDirectSoundAPI )
{
     	
     HMMIO	hmfr;
     MMCKINFO parent,child;
     WAVEFORMATEX wfmtx;

     // Open the wave file with the Multimedia I/O routines
     hmfr = mmioOpen(( char * )szWaveFile,NULL, MMIO_READ | MMIO_ALLOCBUF);
     if(hmfr == NULL)
     {
		  static int errCount = 0;

		  if ( !errCount )
	          MessageBox(NULL,"Could not Open Wave File",NULL,MB_OK);
		  errCount++;

          return FALSE;
     }

     parent.ckid = (FOURCC)0;
     parent.cksize = 0;
     parent.fccType = (FOURCC)0;
     parent.dwDataOffset = 0;
     parent.dwFlags = 0;
     child = parent;

     parent.fccType = mmioFOURCC('W','A','V','E');
     if(mmioDescend(hmfr,&parent,NULL,MMIO_FINDRIFF))
     {
          mmioClose(hmfr,0);

		  static int errCount = 0;

		  if ( !errCount )
		      MessageBox(NULL,"Could not Descend into Wave File",NULL,MB_OK);
		  errCount = 1;
          return FALSE;
     }

     child.ckid = mmioFOURCC('f','m','t',' ');
     if(mmioDescend(hmfr,&child,&parent,0))
     {
          mmioClose(hmfr,0);

		  static int errCount = 0;
		  if ( !errCount )
			MessageBox(NULL,"Could not Descend into format of Wave File",NULL,MB_OK);
		  errCount = 1;
          return FALSE;
     }

     // Read the wave format
     if(mmioRead(hmfr, (char *)&wfmtx, sizeof(wfmtx)) != sizeof(wfmtx))
     {
          mmioClose(hmfr,0);
		  static int errCount = 0;
		  if ( !errCount )
			MessageBox(NULL,"Error reading Wave Format",NULL,MB_OK);
		  errCount = 1;
          return FALSE;
     }

     // Double check to make sure this is a wave file
     if(wfmtx.wFormatTag != WAVE_FORMAT_PCM )
     {
          mmioClose(hmfr,0);
		  static int errCount = 0;
		  if ( !errCount )
	          MessageBox(NULL,"Not a valid Wave Format",NULL,MB_OK);
		  errCount = 1;
          return FALSE;
     }
  
     if(mmioAscend(hmfr, &child, 0))
     {
          mmioClose(hmfr,0);
		  static int errCount = 0;
		  if ( !errCount )
			  MessageBox(NULL,"Unable to Ascend",NULL,MB_OK);

		  errCount = 1;
          return FALSE;
     }

     // Read the chunk right into the structure
     child.ckid = mmioFOURCC('d','a','t','a');
     if(mmioDescend(hmfr,&child, &parent, MMIO_FINDCHUNK))
     {
          mmioClose(hmfr,0);
		  static int errCount = 0;
		  if ( !errCount )
	          MessageBox(NULL,"Wave file has no data",NULL,MB_OK);
		  errCount = 1;
          return FALSE;
     }

     // Allocate space and read in the data
     BYTE *pBuffer= new BYTE[child.cksize];
     if((DWORD)mmioRead(hmfr, (char *)pBuffer, child.cksize) != child.cksize)
     {
          mmioClose(hmfr,0);
		  static int errCount = 0;
		  if ( !errCount )
          MessageBox(NULL,"Could not read Wave Data",NULL,MB_OK);
		  errCount = 1;
          return FALSE;
     }

     // Close the wave file
     mmioClose(hmfr,0);


     // Create Direct Sound Buffer
     DSBUFFERDESC dsbdesc;
     PCMWAVEFORMAT pcmwf;

     memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
     pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM; //wfmtx.wFormatTag
     pcmwf.wf.nChannels	= wfmtx.nChannels;
     pcmwf.wf.nSamplesPerSec	= wfmtx.nSamplesPerSec;
     pcmwf.wf.nBlockAlign = wfmtx.nBlockAlign;
     pcmwf.wf.nAvgBytesPerSec = wfmtx.nAvgBytesPerSec;
     pcmwf.wBitsPerSample = wfmtx.wBitsPerSample;


     memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
     dsbdesc.dwSize = sizeof(DSBUFFERDESC);
     dsbdesc.dwFlags = DSBCAPS_GLOBALFOCUS; //CTRLDEFAULT;
     dsbdesc.dwBufferBytes = child.cksize;			
     dsbdesc.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;

     if(pDirectSoundAPI->CreateSoundBuffer(&dsbdesc, &pDSBuffer, NULL) != DS_OK)
     {
		  static int errCount = 0;
		  if ( !errCount )
          MessageBox(NULL,"Could not Create Sound Buffer.",NULL,MB_OK);
		  errCount = 1;
          delete [] pBuffer;
     }


     // Fill buffer with the wave file data
     LPVOID written1, written2;
     DWORD length1,length2;
     if(pDSBuffer->Lock(0, child.cksize, &written1, &length1, &written2, &length2, 0) == DSERR_BUFFERLOST)
     {
          pDSBuffer->Restore();
          pDSBuffer->Lock(0, child.cksize, &written1, &length1, &written2, &length2, 0);
     }

     CopyMemory(written1, pBuffer, length1);

     if(written2 != NULL)
          CopyMemory(written2, pBuffer+length1, length2);

     pDSBuffer->Unlock(written1, length1, written2, length2);

     // Free the temporary buffer
     delete [] pBuffer;

     return TRUE;
}


int Playsound ( const char * file, bool playSound )
{
	if ( playSound == false )
		return 1;

//	static int playing = 0;
//	if ( playing )
//		return TRUE;

//	playing = 1;
static LPDIRECTSOUND pDirectSoundAPI = NULL;
static LPDIRECTSOUNDBUFFER pGrunt = NULL;


	if ( pGrunt )
	{
		DWORD result;
		pGrunt->GetStatus ( &result );
			
		if ( result == DSBSTATUS_PLAYING )
			return FALSE;
		else
		{
             if(pGrunt)
		     {
			     pGrunt->Release();
			     pGrunt = NULL;
		     }
			if(pDirectSoundAPI)
		       {
			   pDirectSoundAPI->Release();
				pDirectSoundAPI = NULL;
			}
		}
	}

     const char *szGruntFile = file;

       // If Direct sound fails, just return - no sound effects will be heard
       if(DirectSoundCreate(NULL,&pDirectSoundAPI,NULL) != DS_OK)
       return FALSE;

         if ( pDirectSoundAPI->SetCooperativeLevel( AfxGetMainWnd()->m_hWnd, DSSCL_NORMAL) != DS_OK )
//         if ( pDirectSoundAPI->SetCooperativeLevel( main->m_hWnd, DSSCL_NORMAL) != DS_OK )
		 {
			static int errCount = 0;
			if ( !errCount )
				MessageBox( AfxGetMainWnd()->m_hWnd, "Set Cooperative Level failed",NULL,MB_OK);

			errCount = 1;
		 }
           // Create buffer for grunt sound
           if(!bSetupBufferFromWave(pGrunt,szGruntFile, pDirectSoundAPI))
           {
//           MessageBox( mainFrame->m_hWnd,"Rapt failed",NULL,MB_OK);
           return FALSE;
           }

             if(pGrunt)
             pGrunt->Play(0,0,0);

				   /*
             if(pGrunt)
     {
     pGrunt->Release();
     pGrunt = NULL;
     }
       if(pDirectSoundAPI)
       {
       pDirectSoundAPI->Release();
       pDirectSoundAPI = NULL;
       }
     			   
					 */
//	playing = 0;
			 return TRUE;
}


int PlayAlarm ( char * file, bool playSound )
{
//	static int playing = 0;
//	if ( playing )
//		return TRUE;

//	playing = 1;

	
	if ( playSound == false )
		return 1;

static LPDIRECTSOUND pDirectSoundAPI = NULL;
static LPDIRECTSOUNDBUFFER pGrunt = NULL;


	if ( pGrunt )
	{
		DWORD result;
		pGrunt->GetStatus ( &result );
			
		if ( result == DSBSTATUS_PLAYING )
			return FALSE;
		else
		{
             if(pGrunt)
     {
     pGrunt->Release();
     pGrunt = NULL;
     }
       if(pDirectSoundAPI)
       {
       pDirectSoundAPI->Release();
       pDirectSoundAPI = NULL;
       }
		}
	}

     char *szGruntFile = file;

       // If Direct sound fails, just return - no sound effects will be heard
       if(DirectSoundCreate(NULL,&pDirectSoundAPI,NULL) != DS_OK)
       return FALSE;

         if ( pDirectSoundAPI->SetCooperativeLevel( AfxGetMainWnd()->m_hWnd, DSSCL_NORMAL) != DS_OK )
		 {
			static int errCount = 0;
			if ( !errCount )
				MessageBox( AfxGetMainWnd()->m_hWnd, "Set Cooperative Level failed",NULL,MB_OK);

			errCount = 1;
		 }
           // Create buffer for grunt sound
           if(!bSetupBufferFromWave(pGrunt,szGruntFile, pDirectSoundAPI))
           {
//           MessageBox( mainFrame->m_hWnd,"Rapt failed",NULL,MB_OK);
           return FALSE;
           }

             if(pGrunt)
             pGrunt->Play(0,0,0);

				   /*
             if(pGrunt)
     {
     pGrunt->Release();
     pGrunt = NULL;
     }
       if(pDirectSoundAPI)
       {
       pDirectSoundAPI->Release();
       pDirectSoundAPI = NULL;
       }
     			   
					 */
//	playing = 0;
			 return TRUE;
}

