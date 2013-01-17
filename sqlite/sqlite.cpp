#include "SQLite.h"

static const int BUSYTIMEOUTMS  = 60000;
static const int SLEEPTIME      = 100;
static const int LIMITNUM       = 200;

static const char * STRSYNCHRONOUS_ON  = "PRAGMA SYNCHRONOUS = ON";
static const char * STRSYNCHRONOUS_OFF = "PRAGMA SYNCHRONOUS = OFF";

//static const char * STRPAGESIZE  = "PRAGMA PAGE_SIZE = 8192";
static const char * STRCACHESIZE = "PRAGMA CACHE_SIZE = 8000";
//static const char * STRDEFAULTCACHESIZE = "PRAGMA DEFAULT_CACHE_SIZE = 8000";

const char * STRBEGINTRANS  = "BEGIN TRANSACTION";
const char * STRCOMMITTRANS = "COMMIT TRANSACTION";
const char * STRROLLBACK    = "ROLLBACK TRANSACTION";

CSQLite::CSQLite( void )
    : m_pDb(NULL)
    , m_pStmt(NULL)
    , m_nState(-1)
    , m_nTimeoutMs(BUSYTIMEOUTMS)
    , m_nCurFieldNum(0)
    , m_nLimitNum( LIMITNUM )
    , m_bIsOpen( false )
{
}

CSQLite::~CSQLite( void )
{
    if (NULL != m_pStmt)
    {
        sqlite3_finalize(m_pStmt);
        m_pStmt = NULL;
    }
    Close();
}

bool CSQLite::Open( const char * inDbName , bool inSynFlag )
{
    //数据库名检查
    if ( NULL == inDbName )
    {
        m_strErrInfo = "数据库文件名为空";
        return false;
    }

    //打开数据库
    m_strFileName = inDbName;
    m_nState = sqlite3_open(inDbName, &m_pDb);
    if ( SQLITE_OK != m_nState )
    {
        m_strErrInfo = sqlite3_errmsg(m_pDb);
        return false;
    }

    //设置超时
    SetBusyTimeout( m_nTimeoutMs );

    //打开同步开关标志
    const char * pTmp = NULL;
    if ( inSynFlag )
    {
        pTmp = STRSYNCHRONOUS_ON;
    }
    else
    {
        pTmp = STRSYNCHRONOUS_OFF;
    }
    ExecDML ( pTmp );
    if ( SQLITE_OK != m_nState )
    {
        m_strErrInfo = sqlite3_errmsg(m_pDb);
        m_strErrInfo.append(" . So database had been closed .");
        Close();
        return false;
    }
    //设置最大缓存
    ExecDML ( STRCACHESIZE );
    if ( SQLITE_OK != m_nState )
    {
        m_strErrInfo = sqlite3_errmsg(m_pDb);
        m_strErrInfo.append(" . So database had been closed .");
        Close();
        return false;
    }

    m_bIsOpen = true;
    return true;
}

bool CSQLite::Reopen( bool inSynFlag )
{
    Close();
    return Open( m_strFileName.c_str(), inSynFlag );
}

void CSQLite::Close( void )
{
    if ( NULL != m_pDb)
    {
       m_nState = sqlite3_close( m_pDb );
       m_pDb = NULL;
    }
    m_bIsOpen = false;
}

int CSQLite::SetBusyTimeout( unsigned int inMS )
{
    m_nTimeoutMs = inMS;

    m_nState = sqlite3_busy_timeout( m_pDb, m_nTimeoutMs );
    if ( SQLITE_OK != m_nState )
    {
        m_strErrInfo = sqlite3_errmsg(m_pDb);
    }
    return  m_nState;
}

int CSQLite::ExecDML( const char * inSql )
{
    if (NULL == inSql)
    {
       m_strErrInfo = "The inputed SQL sentence is empty .";
       return  DEF_INPUTISNULL;
    }
    for( unsigned int m = 0; m < m_nLimitNum; m++ )
    {
        m_nState = sqlite3_exec( m_pDb, inSql, NULL, NULL, NULL );
        if ( SQLITE_OK == m_nState )
        {
            break;
        }
        else if ( SQLITE_BUSY == m_nState )
        {
            if ( m_nLimitNum == m+1 )
            {
                m_strErrInfo = sqlite3_errmsg( m_pDb );
                break;
            }
            sqlite3_busy_handler( m_pDb, NULL,NULL );
            sleep( SLEEPTIME );
            continue;
        }
        else
        {
            m_strErrInfo = sqlite3_errmsg( m_pDb );
            break;
        }
    }
    return m_nState;
}

int CSQLite::ExecDML(const vector<string> &inTransaction)
{
    unsigned int nStrNum = (unsigned int)inTransaction.size();
    if ( 0 ==  nStrNum )
    {
        return SQLITE_OK;
    }

    //以下是事务执行，事务必须成功或者回滚
    for( unsigned int m = 0; m < m_nLimitNum; m++ )
    {
        m_nState = sqlite3_exec( m_pDb, STRBEGINTRANS, NULL, NULL, NULL );
        if ( SQLITE_OK == m_nState )
        {
            break;
        }
        else if ( SQLITE_BUSY == m_nState )
        {
            if ( m_nLimitNum == m+1 )
            {
                m_strErrInfo = sqlite3_errmsg( m_pDb );
                return m_nState;
            }
            //等待指定时间间隔继续执行
            sqlite3_busy_handler( m_pDb, NULL,NULL );
            sleep( SLEEPTIME );
        }
        else
        {
            m_strErrInfo = sqlite3_errmsg(m_pDb);
            return m_nState;
        }
    }

    //执行相关SQL语句
    for ( unsigned int i = 0; i < nStrNum; i++ )
    {
        for( unsigned int m = 0; m < m_nLimitNum; m++ )
        {
            m_nState = sqlite3_exec( m_pDb, inTransaction[i].c_str(), NULL, NULL, NULL );
            if ( SQLITE_OK == m_nState )
            {
                break;
            }
            else if( SQLITE_BUSY == m_nState )
            {
                if ( m_nLimitNum == m+1 )
                {
                    m_strErrInfo = sqlite3_errmsg( m_pDb );
                    sqlite3_exec( m_pDb, STRROLLBACK, NULL, NULL, NULL );
                    return m_nState;
                }
                //等待指定时间间隔继续执行
                sqlite3_busy_handler( m_pDb, NULL,NULL );
                sleep( SLEEPTIME );
            }
            else
            {
                m_strErrInfo = sqlite3_errmsg( m_pDb );
                sqlite3_exec( m_pDb, STRROLLBACK, NULL, NULL, NULL );
                return m_nState;
            }
        }
    }

    //提交事务
    for( unsigned int m = 0; m < m_nLimitNum; m++ )
    {
        m_nState = sqlite3_exec( m_pDb, STRCOMMITTRANS, NULL, NULL, NULL );
        if ( SQLITE_OK == m_nState )
        {
            break;
        }
        else if( SQLITE_BUSY == m_nState )
        {
            if ( m_nLimitNum == m+1 )
            {
                m_strErrInfo = sqlite3_errmsg( m_pDb );
                return m_nState;
            }
            //等待指定时间间隔继续执行
            sqlite3_busy_handler( m_pDb, NULL,NULL );
            sleep( SLEEPTIME );
        }
        else
        {
            m_strErrInfo = sqlite3_errmsg( m_pDb );                   //调整执行顺序
            sqlite3_exec( m_pDb, STRROLLBACK, NULL, NULL, NULL );
            return m_nState;
        }
    }

    return m_nState;
}

int CSQLite::ExecQuery(const char * inSql)
{
   //检查输入查询语句
   if ( NULL == inSql )
   {
      m_strErrInfo = "The inputed SQL is empty.";
      return  DEF_INPUTISNULL;
   }
   for( unsigned int m = 0; m < m_nLimitNum; m++ )
   {
       //执行查询语句
       m_nState = sqlite3_prepare( m_pDb, inSql, -1, &m_pStmt, NULL );
       if ( SQLITE_OK == m_nState )
       {
          //获取查询的字段个数
           m_nCurFieldNum = sqlite3_column_count( m_pStmt );
           break;
       }
       else if( SQLITE_BUSY == m_nState )
       {
           if ( m_nLimitNum == m+1 )
           {
               m_strErrInfo = sqlite3_errmsg( m_pDb );
               sqlite3_finalize(m_pStmt);
               m_pStmt = NULL;
               break;
           }
           //等待指定时间间隔继续执行
           sqlite3_busy_handler( m_pDb, NULL,NULL );
           sleep( SLEEPTIME );
           continue;
       }
       else
       {
           m_strErrInfo = sqlite3_errmsg( m_pDb );
           sqlite3_finalize(m_pStmt);
           m_pStmt = NULL;
           break;
       }
    }
    return m_nState;
}

int CSQLite::Fetch( vector<string> & ioValues )
{
    //清空数组
    ioValues.clear();
    bool bRelease = true; //是否释放游标

    for( unsigned int m = 0; m < m_nLimitNum; m++ )
    {
        m_nState = sqlite3_step( m_pStmt );

        if ( SQLITE_DONE  == m_nState )
        {
            // no rows
            m_strErrInfo = sqlite3_errmsg( m_pDb );
            goto __Exit;
        }
        else if ( SQLITE_ROW == m_nState )
        {
            //循环获取字段的内容
            for ( unsigned int i = 0; i < m_nCurFieldNum; i++ )
            {
                const char* pTmp = NULL;   //防止空值
                pTmp = (const char*)( sqlite3_column_text( m_pStmt, i ) );
                if ( NULL == pTmp )
                {
                    ioValues.push_back( "" );
                 }
                else
                {
                    ioValues.push_back( pTmp );
                }
            }
            bRelease = false;
            goto __Exit;
        }
        else if ( SQLITE_BUSY == m_nState )
        {
           if ( m_nLimitNum == m+1 )
           {
               m_strErrInfo = sqlite3_errmsg( m_pDb );
               goto __Exit;
           }
           sqlite3_busy_handler( m_pDb,NULL,NULL);
           sleep( SLEEPTIME );
           continue;
        }
        else
        {
            //other exceptions
            m_strErrInfo = sqlite3_errmsg( m_pDb );
            goto __Exit;
        }
    }
__Exit:
    if ( NULL != m_pStmt && bRelease )
    {
        sqlite3_finalize( m_pStmt );
        m_pStmt = NULL;
    }
    return m_nState;
}

int CSQLite::Fetch( vector<string> & ioValues, vector<int>& ioNull )
{
    //清空数组
    ioValues.clear();
    ioNull.clear();
    bool bRelease = true; //是否释放游标

    for( unsigned int m = 0; m < m_nLimitNum; m++ )
    {
        m_nState = sqlite3_step( m_pStmt );

        if ( SQLITE_DONE  == m_nState )
        {
            // no rows
            m_strErrInfo = sqlite3_errmsg( m_pDb );
            goto __Exit;
        }
        else if ( SQLITE_ROW == m_nState )
        {
            //循环获取字段的内容
            for ( unsigned int i = 0; i < m_nCurFieldNum; i++ )
            {
                const char* pTmp = NULL;   //防止空值
                pTmp = (const char*)( sqlite3_column_text( m_pStmt, i ) );
                 //有空值
                if ( NULL == pTmp )
                {
                    ioValues.push_back( "" );
                    ioNull.push_back(0);
                 }
                else
                {
                    ioValues.push_back( pTmp );
                    ioNull.push_back(1);
                }
            }
            bRelease = false;
            goto __Exit;
        }
        else if ( SQLITE_BUSY == m_nState )
        {
           if ( m_nLimitNum == m+1 )
           {
               m_strErrInfo = sqlite3_errmsg( m_pDb );
               goto __Exit;
           }
           sqlite3_busy_handler( m_pDb,NULL,NULL);
           sleep( SLEEPTIME );
           continue;
        }
        else
        {
            //other exceptions
            m_strErrInfo = sqlite3_errmsg( m_pDb );
            goto __Exit;
        }
    }
__Exit:
    if ( NULL != m_pStmt && bRelease )
    {
        sqlite3_finalize( m_pStmt );
        m_pStmt = NULL;
    }
    return m_nState;
}

int CSQLite::TableExists( const char * inTabName )
{
    char szSQL[128] = "";
    sprintf( szSQL,"select count(*) from sqlite_master where type='table' and name='%s'",inTabName );

    for( unsigned int m = 0; m < m_nLimitNum; m++ )
    {
        m_nState =  sqlite3_prepare( m_pDb, szSQL, -1, &m_pStmt, NULL );
        if ( SQLITE_OK == m_nState )
        {
            break;
        }
        else if( SQLITE_BUSY == m_nState )
        {
           if ( m_nLimitNum == m+1 )
           {
               m_strErrInfo = sqlite3_errmsg( m_pDb );
               goto __Exit;
           }
           //等待指定时间间隔继续执行
           sqlite3_busy_handler( m_pDb, NULL,NULL );
           sleep( SLEEPTIME );
           continue;
        }
        else
        {
           m_strErrInfo = sqlite3_errmsg( m_pDb );
           goto __Exit;
        }
    }

    for( unsigned int m = 0; m < m_nLimitNum; m++ )
    {
        m_nState = sqlite3_step( m_pStmt );
        if ( SQLITE_ROW == m_nState )
        {
            if ( sqlite3_column_int( m_pStmt, 0 ) > 0 )
            {
                m_nState = DEF_TABLEEXIST;
            }
            else
            {
                m_nState = DEF_TABLENOTEXIST;
            }
            break;
        }
        else if ( SQLITE_BUSY == m_nState )
        {
            if ( m_nLimitNum == m+1 )
            {
                m_strErrInfo = sqlite3_errmsg( m_pDb );
                goto __Exit;
            }
            sqlite3_busy_handler( m_pDb, NULL,NULL );
            sleep( SLEEPTIME );
        }
        else
        {
            m_strErrInfo = sqlite3_errmsg( m_pDb );
            goto __Exit;
        }
    }

__Exit:
    if ( NULL != m_pStmt )
    {
        sqlite3_finalize( m_pStmt );
        m_pStmt = NULL;
    }
    return m_nState;
}

const char* CSQLite::ErrCodeAsString(int inErrCode)
{
  switch (inErrCode)
  {
         case SQLITE_OK           : return "SQLITE_OK";
         case SQLITE_ERROR        : return "SQLITE_ERROR";
         case SQLITE_INTERNAL     : return "SQLITE_INTERNAL";
         case SQLITE_PERM         : return "SQLITE_PERM";
         case SQLITE_ABORT        : return "SQLITE_ABORT";
         case SQLITE_BUSY         : return "SQLITE_BUSY";
         case SQLITE_LOCKED       : return "SQLITE_LOCKED";
         case SQLITE_NOMEM        : return "SQLITE_NOMEM";
         case SQLITE_READONLY     : return "SQLITE_READONLY";
         case SQLITE_INTERRUPT    : return "SQLITE_INTERRUPT";
         case SQLITE_IOERR        : return "SQLITE_IOERR";
         case SQLITE_CORRUPT      : return "SQLITE_CORRUPT";
         case SQLITE_NOTFOUND     : return "SQLITE_NOTFOUND";
         case SQLITE_FULL         : return "SQLITE_FULL";
         case SQLITE_CANTOPEN     : return "SQLITE_CANTOPEN";
         case SQLITE_PROTOCOL     : return "SQLITE_PROTOCOL";
         case SQLITE_EMPTY        : return "SQLITE_EMPTY";
         case SQLITE_SCHEMA       : return "SQLITE_SCHEMA";
         case SQLITE_TOOBIG       : return "SQLITE_TOOBIG";
         case SQLITE_CONSTRAINT   : return "SQLITE_CONSTRAINT";
         case SQLITE_MISMATCH     : return "SQLITE_MISMATCH";
         case SQLITE_MISUSE       : return "SQLITE_MISUSE";
         case SQLITE_NOLFS        : return "SQLITE_NOLFS";
         case SQLITE_AUTH         : return "SQLITE_AUTH";
         case SQLITE_FORMAT       : return "SQLITE_FORMAT";
         case SQLITE_RANGE        : return "SQLITE_RANGE";
         case SQLITE_ROW          : return "SQLITE_ROW";
         case SQLITE_DONE         : return "SQLITE_DONE";
         case DEF_INPUTISNULL     : return "Input string is NULL";
         default                  : return "UNKNOWN_ERROR";
  }
}

void CSQLite::FreeStmt( void )
{
    if ( NULL != m_pStmt )
    {
        sqlite3_finalize( m_pStmt );
        m_pStmt = NULL;
    }
}