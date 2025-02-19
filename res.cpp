/* ========================================================================= */
/* RESOLUTION CHANGER                                © MHATXOTIC DESIGN 2009 */
/* ========================================================================= */
#define VS_MAJOR                     1 // Major version of application
#define VS_MINOR                     0 // Minor version of application
#define VS_BUILD                     0 // Build of application
#define VS_REVISION                  0 // Revision of application
/* ========================================================================= */
#ifndef RC_INVOKED                     // If not using resource compiler
/* ========================================================================= */
#define WIN32_LEAN_AND_MEAN            // Faster compilation of headers
#define _WIN32_WINNT            0x0500 // Windows XP or Later required
/* ========================================================================= */
#include <Windows.H>                   // Windows API
#include <Assert.H>                    // Assertation functions
#include <StdIO.H>                     // Standard IO functions
#include <StdLib.H>                    // Standard library functions
/* ========================================================================= */
#pragma comment(lib, "Gdi32.Lib")      // Want functions from GDI32.DLL
#pragma comment(lib, "User32.Lib")     // Want functions from USER32.DLL
#pragma comment(lib, "AdvApi32")       // Want functions from ADVAPI32.DLL
/* ========================================================================= */
INT    iVerMajor = VS_MAJOR;           // Major version of application
INT    iVerMinor = VS_MINOR;           // Minor version of application
INT    iVerBits  = sizeof(PVOID) << 3; // Bits version of program (32/64)
INT    iWinVer   = GetVersion();       // Windows version
INT    iCompVer  = _MSC_VER;           // Visual C++ version
PCHAR  cpVerDate = __TIMESTAMP__;      // Date program was compiled
/* ========================================================================= */
INT MessageBoxF(HWND H, LPCSTR T, INT FL, LPCSTR F, ...)
{
  CHAR FB[1025];
  _vsnprintf_s(FB, sizeof(FB), F, (PCHAR)(&F + 1));
  return MessageBox(H, FB, T, FL);
}
/* ========================================================================= */
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
  if(__argc < 3)
  {
    MessageBoxF(NULL, NULL, MB_ICONINFORMATION,
      "Desktop Resolution Changer, Version %u.%02u (%u-Bit).\n"
      "Compiled %s using Visual C++ %d.\n"
      "Copyright © MhatXotic Design, 2010. All Rights Reserved.\n"
      "Visit http://github.com/mhatxotic for more information and updates.\n"
      "\n"
      "Usage: RES <Width> <Height> [Depth] [Refresh].\n"
      "\n"
      "Procedures:-\n"
      "1. Test the resolution, fail if not available.\n"
      "2. Try to write new resolution to local machine registry.\n"
      "3. (If 2 fails) Try to write new resolution to user profile registry.\n"
      "4. Set the new resolution.\n"
      "5. (If reboot required) Ask user to reboot and do it for them.\n"
      "6. Done.",
      iVerMajor, iVerMinor, iVerBits, cpVerDate, iCompVer);
    return 1;
  }

  DEVMODE dmMode;
  memset(&dmMode, 0, sizeof(dmMode));
  dmMode.dmSize = sizeof(dmMode);
  dmMode.dmPelsWidth = atoi(__argv[1]);
  dmMode.dmPelsHeight = atoi(__argv[2]);
  dmMode.dmBitsPerPel = __argc >= 4 ? atoi(__argv[3]) : 32;
  dmMode.dmDisplayFrequency = __argc >= 5 ? atoi(__argv[4]) : 60;
  dmMode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT|DM_DISPLAYFREQUENCY;

  DWORD dwFlags = CDS_GLOBAL|CDS_UPDATEREGISTRY;
  while(dwFlags != 0)
  {
    switch(ChangeDisplaySettings(&dmMode, dwFlags))
    {
      case DISP_CHANGE_SUCCESSFUL:
      {
        dwFlags = 0;
        break;
      }
      case DISP_CHANGE_BADFLAGS:
      {
        MessageBoxF(NULL, NULL, MB_ICONSTOP, "An invalid set of flags was passed in.");
        return 3;
      }
      case DISP_CHANGE_BADMODE:
      {
        MessageBoxF(NULL, NULL, MB_ICONSTOP, "The graphics mode is not supported.");
        return 4;
      }
      case DISP_CHANGE_BADPARAM:
      {
        MessageBoxF(NULL, NULL, MB_ICONSTOP, "An invalid parameter was passed in. This can include an invalid flag or combination of flags.");
        return 5;
      }
      case DISP_CHANGE_FAILED:
      {
        MessageBoxF(NULL, NULL, MB_ICONSTOP, "The display driver failed the specified graphics mode.");
        return 6;
      }
      case DISP_CHANGE_NOTUPDATED:
      {
        if(dwFlags & CDS_GLOBAL)
          dwFlags &= ~CDS_GLOBAL;
        else if(dwFlags & CDS_UPDATEREGISTRY)
          dwFlags &= ~CDS_UPDATEREGISTRY;
        else
        {
          MessageBoxF(NULL, NULL, MB_ICONSTOP, "Unable to write settings to the registry.");
          return 7;
        }
        break;
      }
      case DISP_CHANGE_RESTART:
      {
        if(MessageBoxF(NULL, NULL, MB_ICONQUESTION|MB_OKCANCEL, "You have to restart Windows to complete the resolution change.") == IDOK)
        {
          if(InitiateSystemShutdown(NULL, "Resolution Change", 0, FALSE, TRUE) == 0)
          {
            MessageBoxF(NULL, NULL, MB_ICONSTOP, "Failed to restart the computer!");
            return 8;
          }
        }
        break;
      }
      default:
      {
        MessageBoxF(NULL, NULL, MB_ICONSTOP, "An unknown error has occured.");
        return 9;
      }
    }
  }
  return 0;
}
/* ========================================================================= */
#endif                                 // !RC_INVOKED
/* ========================================================================= */
/* EOF                                                                   EOF */
/* ========================================================================= */
