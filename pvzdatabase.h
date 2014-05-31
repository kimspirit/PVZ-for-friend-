#ifndef PVZDATABASE_H
#define PVZDATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>

//获得读写路径
std::string GetWritablePath(const char* pFileName);

class characterInfo {
public:
    std::string 	strbgname;
    std::string 	strname;
    float 		fCdTime;
    int 		nCost;
    int         	nTag;
};
class pvzdatabase
{
public:
    //全局数据库链接
    static pvzdatabase *getinstance();

    //释放数据库
    static void release();

    void writecharacterinfo(std::vector<characterInfo> **info);
protected:
  
    bool initdatabase();

    bool getcharacterinfo();

    static int readcharacterinfo(void* pArg,int nColumns,char** pColumn_Values,char** pColumn_Names);

private:
    std::vector<characterInfo>  vecCaracter;
};

#endif // PVZDATABASE_H
