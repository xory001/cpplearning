#include "pch.h"
#include <iostream>
#include <io.h>
#include <string.h>
#include <iomanip>
#include "CXLog.h"
#include <process.h>
//for _beginthreadex & _endthreadex & CloseHandle
//https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/beginthread-beginthreadex?view=msvc-170

#define DAY_MILLISECONDS  (24*60*60*1000)
#define XLOG_EXTENSION_NAME   ".log"
#define XLOG_BACKUP_EXTENSION_NAME   ".bak"

xlog::CLogMgr* xlog::CLogMgr::m_pInst = new xlog::CLogMgr;

xlog::CLogMgr::CLogMgr()
{
    ::setlocale(LC_ALL, "zh-CN");
    Init();
}

xlog::CLogMgr::~CLogMgr()
{
    //https://learn.microsoft.com/zh-cn/cpp/c-runtime-library/reference/beginthread-beginthreadex?view=msvc-170
    m_bThradExit = true;
    SetEvent(m_hEvent);
    WaitForSingleObject( m_hThreadWrite, 500 );
    CloseHandle(m_hThreadWrite);
    CloseHandle(m_hEvent);
    m_hEvent = INVALID_HANDLE_VALUE;
    m_hThreadWrite = NULL;
    DeleteCriticalSection( &m_cs );
}

void xlog::CLogMgr::Init()
{
     ClearHistoryLogFile();
    InitializeCriticalSection(&m_cs);
    m_hThreadWrite = INVALID_HANDLE_VALUE;
    m_bThradExit = false;
    m_hEvent = CreateEventW(NULL, FALSE, FALSE, L"");

    time_t timeVal = time(NULL);
    struct tm* tmVar = localtime(&timeVal);

    for (int i = 0; i < X_LOG_LEVEL_MAX; i++)
    {
        m_arrLogCfg[i].logLevel = (X_LOG_LEVEL)i;
        m_arrLogCfg[i].nCurrentDay = tmVar->tm_mday;
#ifdef _DEBUG
        m_arrLogCfg[i].bToStdOut = TRUE;
#endif
    }

#ifndef _DEBUG
    m_arrLogCfg[X_LOG_LEVEL_DEBUG].bToFile = FALSE;
#endif
    m_hThreadWrite = (HANDLE)_beginthreadex( NULL, 0, ThreadWrite, this, 0, NULL );
}

void xlog::CLogMgr::SetConfig(const std::string& strConfigFileName)
{
    EnterCriticalSection(&m_cs);

    char szBuf[32] = { 0 };
    std::string strSection;
    for ( int i = 0; i < X_LOG_LEVEL_MAX; i++ )
    {
        strSection = Get_X_LOG_LEVEL_String( (X_LOG_LEVEL)i );
        int nSize = GetPrivateProfileSectionA( strSection.c_str(), szBuf, 31, strConfigFileName.c_str() );
        if ( nSize > 0 )
        {
            int nVal = GetPrivateProfileIntA( strSection.c_str(), "ToStdOut", -1, strConfigFileName.c_str());
            if ( nVal >= 0 )
            {
                m_arrLogCfg[i].bToStdOut = nVal;
            }

            nVal = GetPrivateProfileIntA(strSection.c_str(), "ToFile", -1, strConfigFileName.c_str());
            if ( nVal >= 0 )
            {
                m_arrLogCfg[i].bToFile = nVal;
            }

            nVal = GetPrivateProfileIntA(strSection.c_str(), "SeparateFile", -1, strConfigFileName.c_str());
            if ( nVal >= 0 )
            {
                m_arrLogCfg[i].bSeparateFile = nVal;
            }

            nVal = GetPrivateProfileIntA(strSection.c_str(), "MaxFileSize", -1, strConfigFileName.c_str());
            if ( nVal > 0 )
            {
                m_arrLogCfg[i].nMaxFileSize = 1024 * 1024 * nVal;
            }

            nVal = GetPrivateProfileIntA(strSection.c_str(), "MaxIndex", -1, strConfigFileName.c_str());
            if ( nVal >= 0 )
            {
                m_arrLogCfg[i].nMaxIndex = nVal;
            }

            nVal = GetPrivateProfileIntA(strSection.c_str(), "KeepDays", -1, strConfigFileName.c_str());
            if ( nVal > 0 )
            {
                m_arrLogCfg[i].nKeepDays = nVal;
            }
        }
    }

    LeaveCriticalSection(&m_cs);
}

 void xlog::CLogMgr::SetGenerateFileNameCallBack(X_LOG_LEVEL level, lpfnGenerateFileName fn)
{

}

void xlog::CLogMgr::Write(X_LOG_LEVEL level, const std::string& strLog)
{
    EnterCriticalSection(&m_cs);
    if ( m_arrLogCfg[level].bToStdOut && m_arrLogCfg[X_LOG_LEVEL_ALL].bToStdOut )
    {
        HWND hWndConsole = GetConsoleWindow();
        if ( NULL != hWndConsole )
        {
            std::cout << strLog << std::endl;
        }
        else
        {
            OutputDebugStringA( strLog.c_str() );
        }
    }
    if ( m_arrLogCfg[level].bToFile && m_arrLogCfg[X_LOG_LEVEL_ALL].bToFile )
    {
        CLogItem *pItem = new CLogItem;
        pItem->level = level;
        pItem->strLog = strLog;
        m_vecLogItem.push_back( pItem );
        SetEvent(m_hEvent);
        //Write2File(level, strLog);
    }
     
    LeaveCriticalSection(&m_cs);
}

void xlog::CLogMgr::Write2File(X_LOG_LEVEL level, const std::string& strLog)
{
    if ( !m_arrLogCfg[level].bSeparateFile )
    {
        level = X_LOG_LEVEL_ALL;
    }

    CheckLogFile(level);

    if ( m_arrLogCfg[level].pFile )
    {
        size_t nBytesWrite = fwrite(strLog.c_str(), 1, strLog.length(), m_arrLogCfg[level].pFile);
        fflush(m_arrLogCfg[level].pFile);
        m_arrLogCfg[level].nCurrentFileSize += nBytesWrite;
        if (m_arrLogCfg[level].nCurrentFileSize > m_arrLogCfg[level].nMaxFileSize )
        {
            fclose(m_arrLogCfg[level].pFile);
            m_arrLogCfg[level].nCurrentFileSize = 0;
            m_arrLogCfg[level].pFile = NULL;
        }
    }
}

std::string xlog::CLogMgr::GenerateFileName(X_LOG_LEVEL level, int nCurrentIndex, int nMaxIndex, BOOL bSeparateFile)
{
    char szBuf[MAX_PATH] = { 0 };
    int nLen = GetModuleFileNameA(NULL, szBuf, MAX_PATH);
    if ( nLen > 4 )
    {
        szBuf[nLen - 4] = 0; //remove ".exe"
    }

    time_t timeVal = time(NULL);
    struct tm* tmVar = localtime(&timeVal);
    std::ostringstream oss;
    oss << szBuf;

    if ( nMaxIndex )
    {
        oss << "_" << GetCurrentProcessId();
    }

    if ( bSeparateFile )
    {
        oss << "_" << Get_X_LOG_LEVEL_String(level);
    }
    oss << "_" << tmVar->tm_year + 1900 << std::setw(2)<< std::setfill('0') <<  tmVar->tm_mon + 1 << std::setw(2) << std::setfill('0') << tmVar->tm_mday;
    if ( nMaxIndex )
    {
        oss << "_" << nCurrentIndex;
    }
    oss << XLOG_EXTENSION_NAME;
   
    return oss.str();
}

void xlog::CLogMgr::CheckLogFile(X_LOG_LEVEL level)
{
    if (NULL == m_arrLogCfg[level].pFile)
    {
        OpenLogFile(level);
    }
    else
    {
        time_t timeVal = time(NULL);
        struct tm* tmVar = localtime(&timeVal);
        if (tmVar->tm_mday != m_arrLogCfg[level].nCurrentDay)
        {
            m_arrLogCfg[level].nCurrentDay = tmVar->tm_mday;
            fclose(m_arrLogCfg[level].pFile);
            m_arrLogCfg[level].pFile = NULL;
            OpenLogFile(level);
        }
    }
}

void xlog::CLogMgr::OpenLogFile(X_LOG_LEVEL level)
{
    m_arrLogCfg[level].strFileName = GenerateFileName(level, m_arrLogCfg[level].nCurrentIndex,
        m_arrLogCfg[level].nMaxIndex, m_arrLogCfg[level].bSeparateFile);

    if ( ( 0 == m_arrLogCfg[level].nMaxIndex ) && ( 0 == _access( m_arrLogCfg[level].strFileName.c_str(), 0 ) ) )
    {
        std::string strBakFileName = m_arrLogCfg[level].strFileName + XLOG_BACKUP_EXTENSION_NAME;
        DeleteFileA(strBakFileName.c_str());
        MoveFileA( m_arrLogCfg[level].strFileName.c_str(), strBakFileName.c_str() );
    }
   
    if (m_arrLogCfg[level].nMaxIndex)
    {
        m_arrLogCfg[level].nCurrentIndex++;
        if (m_arrLogCfg[level].nCurrentIndex > m_arrLogCfg[level].nMaxIndex)
        {
            m_arrLogCfg[level].nCurrentIndex = 0;
        }
    }

    m_arrLogCfg[level].pFile = fopen(m_arrLogCfg[level].strFileName.c_str(), "w+");
}

void xlog::CLogMgr::ClearHistoryLogFile()
{
    std::string strLogNamePrefix;
    char szBuf[MAX_PATH] = {0};
    int nSize = GetModuleFileNameA( NULL, szBuf, MAX_PATH  - 1 );
    char* pszTrailingSlash = strrchr( szBuf, '\\' );
    if ( pszTrailingSlash )
    {
        *pszTrailingSlash = 0;
        pszTrailingSlash++;  //{app}.exe
        pszTrailingSlash[strlen(pszTrailingSlash) - 4] = 0;  //remove .exe
        strLogNamePrefix.assign(pszTrailingSlash);
        strLogNamePrefix += "_"; 
    }

    WIN32_FIND_DATAA wfd;
    std::string strFindDir = szBuf;
    strFindDir += "\\";
    HANDLE hFind = FindFirstFileA( (strFindDir + "*").c_str() , &wfd );

    if (INVALID_HANDLE_VALUE == hFind) 
    {
        return;
    } 

    // List all the files in the directory with some info about them.
    UINT64 uDay4FILETIME = DAY_MILLISECONDS;
    uDay4FILETIME *= (1000 * 10 );
    SYSTEMTIME st;
    GetLocalTime( &st );
    FILETIME ftCurrent;
    SystemTimeToFileTime( &st, &ftCurrent );
    ULARGE_INTEGER  uTimeCurrent;
    uTimeCurrent.LowPart = ftCurrent.dwLowDateTime;
    uTimeCurrent.HighPart = ftCurrent.dwHighDateTime;
    
    std::string strBackupLog = XLOG_EXTENSION_NAME;
    strBackupLog += XLOG_BACKUP_EXTENSION_NAME;
    int nSizeExtensionName = strlen(XLOG_EXTENSION_NAME);
    size_t nMinFileName = strLogNamePrefix.length() + nSizeExtensionName;
    do
    {
        if ( !( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
        {
            size_t nLenFileName = strlen( wfd.cFileName );
            if ( nLenFileName >= nMinFileName )
            {
                //{app name without .exe }_date.{XLOG_EXTENSION_NAME}
                //or {app name without .exe }_date.{XLOG_EXTENSION_NAME}{XLOG_BACKUP_EXTENSION_NAME}
                //or {app name without .exe}_tid_date_{index}.{XLOG_EXTENSION_NAME}
                if ( 0 == strLogNamePrefix.compare(0, strLogNamePrefix.length(), wfd.cFileName, strLogNamePrefix.length() ) ) //compare prefix chars
                {
                    BOOL bLogFile = FALSE;
                    //if suffix chars equal XLOG_EXTENSION_NAME
                    if (  ( 0 == strncmp( wfd.cFileName + strlen( wfd.cFileName ) - nSizeExtensionName, XLOG_EXTENSION_NAME, nSizeExtensionName ) )  ) 
                    {
                        bLogFile = TRUE;
                    }
                    else 
                    {
                        if ( nLenFileName >= ( strLogNamePrefix.length() + strBackupLog.length() ) )  
                        {
                            //if suffix chars equal XLOG_EXTENSION_NAME+XLOG_BACKUP_EXTENSION_NAME
                            if (  ( 0 == strncmp( wfd.cFileName + strlen( wfd.cFileName ) - strBackupLog.length(), strBackupLog.c_str(), strBackupLog.length() ) )  )
                            {
                                bLogFile = TRUE;
                            }
                        }
                    }

                    if ( bLogFile )
                    {      
                          ULARGE_INTEGER  uTime;
                            uTime.LowPart = wfd.ftLastWriteTime.dwLowDateTime;
                            uTime.HighPart = wfd.ftLastWriteTime.dwHighDateTime;
                        if ( ( uTime.QuadPart + uDay4FILETIME * m_arrLogCfg[X_LOG_LEVEL_ALL].nKeepDays ) < uTimeCurrent.QuadPart ) // 7 days before
                        {
                            DeleteFileA( (strFindDir + wfd.cFileName  ).c_str() );
                        }
                    }
                }// compare prefix chars
            } //  if ( nLenFileName >= nLenAppName )
        } // if ( !( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) )
    }while ( FindNextFileA( hFind, &wfd ) );

    FindClose(hFind);
}

UINT _stdcall xlog::CLogMgr::ThreadWrite(void* pVoid)
{
    CLogMgr* pThis = (CLogMgr*)pVoid;
    std::vector<CLogItem*> veclogItem;
    while ( !pThis->m_bThradExit )
    {
        WaitForSingleObject(pThis->m_hEvent, INFINITE);
        EnterCriticalSection( &pThis->m_cs );
        if ( !pThis->m_vecLogItem.empty() )
        {
           veclogItem.swap( pThis->m_vecLogItem );
           pThis->m_vecLogItem.clear();
        }
        LeaveCriticalSection( &pThis->m_cs );

        for ( std::vector<CLogItem*>::iterator it = veclogItem.begin(); it != veclogItem.end(); it++ )
        {
             pThis->Write2File( (*it)->level, (*it)->strLog );
             delete *it;
        }
        veclogItem.clear();
    }
    _endthreadex( 0 );
    return 0;
}

