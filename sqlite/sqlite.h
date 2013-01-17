#ifndef __CSQLITE__H__
#define __CSQLITE__H__

#include <stdio.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <unistd.h>

using namespace std;

//补充一些错误码
#define  DEF_INPUTISNULL -1
#define  DEF_TABLEEXIST -2
#define  DEF_TABLENOTEXIST -3

extern const char * STRBEGINTRANS;
extern const char * STRCOMMITTRANS;
extern const char * STRROLLBACK;

class CSQLite
{
public:
    CSQLite( void );
    virtual ~CSQLite( void );

private:
    sqlite3 * m_pDb; //SQLite 对象指针
    sqlite3_stmt * m_pStmt; //执行SQL 的句柄
    int m_nState; //当前SQLite 状态
    string m_strFileName; //SQLite的库文件名
    string m_strErrInfo; //错误信息
    unsigned long m_nTimeoutMs; //设置超时毫秒数

    unsigned int m_nCurFieldNum; //当前查询的表中字段的总个数
    unsigned int m_nLimitNum; //执行SQL忙时最大的尝试次数
    bool m_bIsOpen; //数据库是否打开

public:
    // 打开SQLite
    bool Open( const char * inDbName, bool inSynFlag = false );

    // 重新打开SQLite
    bool Reopen( bool inSynFlag = false );

    //关闭SQLite
    void Close( void );

    // 设置超时时间
    int SetBusyTimeout( unsigned int inMS ) ;

    // 获取超时时间
    unsigned int GetBusyTimeout( void ) const { return m_nTimeoutMs; }

    //获取当前SQLite 的状态
    inline int GetState( void ) const { return m_nState; }

    //获取最后一次的错误信息
    inline const char * GetLastError( void ) const { return m_strErrInfo.c_str(); }

    //获取执行忙时的最大尝试次数
    inline unsigned int GetLimitNum( void ) const { return m_nLimitNum; }

    //设置执行忙时的最大尝试次数
    inline void SetLimitNum( unsigned int inLimitNum ) { m_nLimitNum = inLimitNum; }

    //判断数据库是否打开
    inline bool IsOpen( void ) { return m_bIsOpen; }

    //转换错误码为字符串
    const char *  ErrCodeAsString( int inErrCode );

    // 事务方式执行一批SQL语句
    int ExecDML( const char * inSql );
    int ExecDML(const vector<string>  & inTransation);

    // 执行SQL查询语句
    int ExecQuery(const char * inSql);

    // 取一条查询记录
    int Fetch( vector<string> & ioValues );
    int Fetch( vector<string> & ioValues, vector<int>& ioNull );  //增加空值记录

    // 检查指定的表是否存在
    int TableExists( const char * inTabName );

    // 启动一个事务
    inline int BeginTrans( void ) { return ExecDML( STRBEGINTRANS );  }

    // 结束一个事务
    inline int CommitTrnas( void )   { return ExecDML( STRCOMMITTRANS ); }

    // 回滚一个事务
    inline int RollbackTrans( void ) { return ExecDML( STRROLLBACK ); }

    //默认释放类成员
   void FreeStmt( void );

private:
    CSQLite( const CSQLite & inSqlite );
    CSQLite & operator = ( const CSQLite & inSqlite );
};

#endif