#pragma once
#include <sstream>
#include <windows.h>
#include <sys/timeb.h>
#include <time.h>
#include <iostream>
#include <map>
#include <vector>


#ifdef XLOG_EXPORTS
#define XLOG_EXPORT_API __declspec(dllexport)
#else
#define XLOG_EXPORT_API __declspec(dllimport)
#endif

/*  config file content
; section: ALL, VERBOSE, DEBUG, INFO, WARN, ERROR, FATAL
[ALL]
; ToStdOut=1 or 0, default value: debug mode for console app set to 1, otherwise set to 0
;ToStdOut=0
; ToFile=1 or 0, default value: 1, but DEBUG info dropped in release mode
ToFile=1
; SeparateFile=1 or 0, default value: 0, set to 1 will create separate log file
;SeparateFile=0
; MaxFileSize=10, default value: 10, means 10MB
;MaxFileSize=10
;MaxIndex=0 or n; default value: 0, if > 0, the log file will from xx_0.log to xx_n.logand loop
MaxIndex=1
;KeepDays=1 or n; default value: 7
KeepDays=7

[DEBUG]
; ToFile=1 or 0, default value: 1, but DEBUG info dropped in release mode
ToFile=1
*/

namespace xlog
{
    //#define GET_ENUM_NAME(value) case value:return (#value);

    typedef enum tagX_LOG_LEVEL
    {
        X_LOG_LEVEL_ALL = 0,
        X_LOG_LEVEL_VERBOSE,
        X_LOG_LEVEL_DEBUG,
        X_LOG_LEVEL_INFO,
        X_LOG_LEVEL_WARN,
        X_LOG_LEVEL_ERROR,
        X_LOG_LEVEL_FATAL,
        X_LOG_LEVEL_MAX,
    }X_LOG_LEVEL;

    inline std::string Get_X_LOG_LEVEL_String(X_LOG_LEVEL val)
    {
        switch (val)
        {
        case X_LOG_LEVEL_ALL:
            return "ALL";

        case X_LOG_LEVEL_VERBOSE:
            return "VERBOSE";

        case X_LOG_LEVEL_DEBUG:
            return "DEBUG";

        case X_LOG_LEVEL_INFO:
            return "INFO";

        case X_LOG_LEVEL_WARN:
            return "WARN";

        case X_LOG_LEVEL_ERROR:
            return "ERROR";

        case X_LOG_LEVEL_FATAL:
            return "FATAL";

        default:
            return "UNKNOWN";
        }
    }

    typedef std::string(*lpfnGenerateFileName)( X_LOG_LEVEL logLevel, BOOL bSeparateFile );

    class CLogCfg
    {
    public:
        CLogCfg()
        {
            logLevel = X_LOG_LEVEL_DEBUG;
            bToStdOut = FALSE;
            bToFile = TRUE;
            bSeparateFile = FALSE;  //if bSeparateFile == FALSE, write file to X_LOG_LEVEL_ALL.pFile
            nMaxFileSize = 1024 * 1024 * 10; //10MB
            nCurrentFileSize = 0;
            nMaxIndex = 1;
            nCurrentIndex  = 0;
            pFile = NULL;
            nCurrentDay = 0;
            nKeepDays = 7;  //default, 7 days
        }
        virtual ~CLogCfg() {}

    public:
        X_LOG_LEVEL logLevel;
        BOOL bToStdOut;
        BOOL bToFile;
        BOOL bSeparateFile;
        int nMaxFileSize;
        size_t nCurrentFileSize;
        int nMaxIndex;
        int nCurrentIndex;
        int nCurrentDay;
        int nKeepDays;      //keep log days
        
        //lpfnGenerateFileName fnGenFileName;
        //std::string strFmt;
        std::string strFileName;
        FILE* pFile;
    };

    typedef std::map< X_LOG_LEVEL, CLogCfg > CMapLogCfg;
    typedef CMapLogCfg::iterator CMapLogCfgIter;
    typedef CMapLogCfg::const_iterator CMapLogCfgCIter;

    /// <summary>
    /// CWriterSink
    /// </summary>
     class CWriterSink
     {
     public:
          virtual ~CWriterSink(){}

     public:
         XLOG_EXPORT_API virtual void Write(X_LOG_LEVEL level, const std::string& strLog) = 0;
    };
    
    /// <summary>
    /// CLogMgr
    /// </summary>
    class   CLogMgr : public CWriterSink
    {
    public:
        ~CLogMgr();
        XLOG_EXPORT_API static CLogMgr* Inst() { return m_pInst; }
        XLOG_EXPORT_API static void Release() { delete m_pInst; m_pInst = NULL;}

    public:
        XLOG_EXPORT_API virtual void Write(X_LOG_LEVEL level, const std::string& strLog);

    public:
        XLOG_EXPORT_API void SetConfig( const std::string& strConfigFileName );  //ansi format
        XLOG_EXPORT_API void SetGenerateFileNameCallBack(X_LOG_LEVEL level, lpfnGenerateFileName fn );


    private:
        CLogMgr();
        CLogMgr(const CLogMgr&);
        CLogMgr& operator = (const CLogMgr&);

    private:
        class CLogItem{
        public:
            X_LOG_LEVEL level;
            std::string strLog;
        };
    
    private:
        void Init();
        void Write2File(X_LOG_LEVEL level, const std::string& strLog);
        std::string GenerateFileName( X_LOG_LEVEL level, int nCurrentIndex, int nMaxIndex, BOOL bSeparateFile );
        void CheckLogFile(X_LOG_LEVEL level);
        void OpenLogFile(X_LOG_LEVEL level);
        void ClearHistoryLogFile();
        static UINT _stdcall ThreadWrite( void* pVoid );
        std::vector<CLogItem*> m_vecLogItem;

    private:
        static CLogMgr* m_pInst;
        CRITICAL_SECTION m_cs;
        CMapLogCfg m_mapLogCfg;
        CLogCfg m_arrLogCfg[X_LOG_LEVEL_MAX];
        HANDLE m_hThreadWrite;
        bool    m_bThradExit;
        HANDLE  m_hEvent;
    };


    /// <summary>
    /// CWriter
    /// </summary>
    class CWriter
    {
    public:
        CWriter( CWriterSink* pSink, X_LOG_LEVEL logLevel)
        {
            m_pSink = pSink;
            ::setlocale(LC_ALL, "zh-CN");
            BuildTime();
            m_logLevel = logLevel;
            m_ostream << "\t" << Get_X_LOG_LEVEL_String(logLevel) << "\t";
        }

        virtual ~CWriter()
        {
            m_ostream << std::endl;
            if ( NULL != m_pSink )
            {
                m_pSink->Write( m_logLevel, m_ostream.str() );
            }
        }

        template < typename T >
        inline CWriter& operator << (const T& t)
        {
            m_ostream << t;
            return *this;
        }

        template < typename T >
        inline CWriter& operator << (T* t) {
            m_ostream << "0x" << t;
            return *this;
        }

        template <>
        inline CWriter& operator << (char* lpInfo)
        {
            return operator << ((const char*)lpInfo);
        }

        template <>
        inline CWriter& operator << (const char* lpInfo)
        {
            m_ostream << lpInfo;
            return *this;
        }

        template <>
        inline CWriter& operator << (const std::wstring& strInfo)
        {
            return operator << (strInfo.c_str());
        }

        template <>
        inline CWriter& operator << (const wchar_t* lpwInfo)
        {
            int nLen = (int)wcslen(lpwInfo) + 1;
            int nBytes = ::WideCharToMultiByte(CP_ACP, 0, lpwInfo, nLen, NULL, 0, NULL, NULL);
            char* szBuf = new char[nBytes];
            memset(szBuf, 0, nBytes);
            ::WideCharToMultiByte(CP_ACP, 0, lpwInfo, nLen, szBuf, nBytes, NULL, NULL);
            m_ostream << szBuf;
            delete[]szBuf;
            return *this;
        }

        template <>
        inline CWriter& operator << (wchar_t* lpwInfo)
        {
            return operator << ((const wchar_t*)lpwInfo);
        }

#ifdef _AFX
        template <>
        inline CWriter& operator << (const CString& strInfo)
        {
            return operator << ((LPCTSTR)strInfo);
        }
#endif

    protected:
        void BuildTime()
        {
            struct _timeb timeb;
            char szTimeBuf[32] = { 0 };
            _ftime_s(&timeb);
            struct tm local;
            localtime_s(&local, &timeb.time);
            sprintf_s(szTimeBuf, "%04d.%02d.%02d %02d:%02d:%02d.%03d", local.tm_year + 1900, local.tm_mon + 1,
                local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec, timeb.millitm);
            m_ostream << szTimeBuf;
        }

    protected:
        std::ostringstream m_ostream;
        X_LOG_LEVEL m_logLevel;
        CWriterSink* m_pSink;
    };
}


#define XWRITE_ALL_THREAD_INFO "[t=" << GetCurrentThreadId() << "]"
#define XWRITE_ALL_LINE_INFO( str )  "[" << __FUNCTION__ << ":" << __LINE__ << "][" << str  << "]"

//use macro to output log
#define XWRITE_VERBOSE xlog::CWriter( xlog::CLogMgr::Inst(), xlog::X_LOG_LEVEL_VERBOSE ) << XWRITE_ALL_THREAD_INFO
#define XWRITE_DEBUG xlog::CWriter( xlog::CLogMgr::Inst(), xlog::X_LOG_LEVEL_DEBUG ) << XWRITE_ALL_THREAD_INFO
#define XWRITE_INFO xlog::CWriter( xlog::CLogMgr::Inst(), xlog::X_LOG_LEVEL_INFO ) << XWRITE_ALL_THREAD_INFO
#define XWRITE_WARNING xlog::CWriter( xlog::CLogMgr::Inst(), xlog::X_LOG_LEVEL_WARN ) << XWRITE_ALL_THREAD_INFO
#define XWRITE_ERROR xlog::CWriter( xlog::CLogMgr::Inst(), xlog::X_LOG_LEVEL_ERROR ) << XWRITE_ALL_THREAD_INFO
#define XWRITE_FATAL xlog::CWriter( xlog::CLogMgr::Inst(), xlog::X_LOG_LEVEL_FATAL ) << XWRITE_ALL_THREAD_INFO

#define TRACE_VERBOSE( str )			XWRITE_VERBOSE << XWRITE_ALL_LINE_INFO( str )
#define TRACE_VERBOSE_THIS( str )		XWRITE_VERBOSE << "[this=" << this <<"]" << XWRITE_ALL_LINE_INFO( str )
#define TRACE_DEBUG( str )				XWRITE_DEBUG << XWRITE_ALL_LINE_INFO( str )
#define TRACE_DEBUG_THIS( str )		XWRITE_DEBUG << "[this=" << this <<"]" << XWRITE_ALL_LINE_INFO( str )
#define TRACE_INFO( str )				XWRITE_INFO << XWRITE_ALL_LINE_INFO( str )
#define TRACE_INFO_THIS( str )		    XWRITE_INFO << "[this=" << this <<"]" << XWRITE_ALL_LINE_INFO( str )
#define TRACE_WARNING( str )			XWRITE_WARNING << XWRITE_ALL_LINE_INFO( str )
#define TRACE_WARNING_THIS( str )		XWRITE_WARNING << "[this=" << this <<"]" << XWRITE_ALL_LINE_INFO( str )
#define TRACE_ERR( str )				XWRITE_ERROR << XWRITE_ALL_LINE_INFO( str )
#define TRACE_ERR_THIS( str )		    XWRITE_ERROR << "[this=" << this <<"]" << XWRITE_ALL_LINE_INFO( str )
#define TRACE_FATAL( str )				XWRITE_FATAL << XWRITE_ALL_LINE_INFO( str )
#define TRACE_FATAL_THIS( str )		XWRITE_FATAL << "[this=" << this <<"]" << XWRITE_ALL_LINE_INFO( str )
