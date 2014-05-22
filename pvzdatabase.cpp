/*
 *android必备  将数据库文件copy到可读写路径
 */
#include "pvzdatabase.h"
#include "cocos2d.h"

std::string GetWritablePath( const char* pFileName )
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    std::string strWriteablePath = cocos2d::FileUtils::getInstance()->getWritablePath();
    strWriteablePath+=pFileName;
    return strWriteablePath;
#else
    return pFileName;
#endif
}

static pvzdatabase *g_datamanager = nullptr;   //创建但列模式数据库
pvzdatabase* pvzdatabase::getinstance()
{
    do {
        if(g_datamanager == nullptr) {
            g_datamanager = new pvzdatabase;
            if(g_datamanager->initdatabase() == false) {
                delete g_datamanager;
                g_datamanager = nullptr;
                break;
            }
        }
        return g_datamanager;
    } while(false);
    cocos2d::log("pvzdatabase* pvzdatabase::getinstance() error !!!");
    return nullptr;
}

/*
 * 初始化数据库
 */
bool pvzdatabase::initdatabase()
{
    if(getcharacterinfo() == false) {
        cocos2d::log("pvzdatabase::initdatabase() getcharacterinfo() error");
        return false;
    }
    return true;
}

void pvzdatabase::release()
{
    g_datamanager->vecCaracter.clear();

    delete g_datamanager;
    g_datamanager = nullptr;
}

/**
 * 数据库的连接
 */
bool pvzdatabase::getcharacterinfo()
{

    do
    {
        sqlite3 *pDB = nullptr;
        char *pErrorMSG = nullptr;
	std::string strFileName = GetWritablePath("pvz.db");
        CC_BREAK_IF(sqlite3_open(strFileName.c_str(),&pDB) != SQLITE_OK);
        CC_BREAK_IF(sqlite3_exec(pDB,"select BackGroundName,Name,CDTime,Cost from character where isBuied='true'",readcharacterinfo,nullptr,&pErrorMSG) != SQLITE_OK);
        sqlite3_close(pDB);
        return true;
    } while (false);
    cocos2d::log("pvzdatabase::getcharacterinfo() error !!!");
    return false;
}

/**
 * 将读取的数据存放到容器中
 */
int pvzdatabase::readcharacterinfo(void* pArg, int nColumns, char** pColumn_Values, char** pColumn_Names)
{
    characterInfo tempInfo;
    tempInfo.strbgname = pColumn_Values[0];
    tempInfo.strname = pColumn_Values[1];
    tempInfo.fCdTime = atof(pColumn_Values[2]);
    tempInfo.nCost = atoi(pColumn_Values[3]);

    g_datamanager->vecCaracter.push_back(tempInfo);
    return 0;
}

/**
 * 将读取的数据发送给调用者
 */
void pvzdatabase::writecharacterinfo(std::vector<characterInfo> **info)
{
    do
    {
        if(vecCaracter.size() == 0 ) {
            break;
        }
        *info = &vecCaracter;
        return;
    } while (false);
    cocos2d::log("pvzdatabase::writecharacterinfo() error !!!");
}
