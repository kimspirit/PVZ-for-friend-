#include "AppDelegate.h"
#include "./mainscene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

//将文件复制到可读写路径
void FileCopy(const char* pFileName)
{
    //查看文件是否存在于可读写路径
    std::string strWritablePath = FileUtils::getInstance()->getWritablePath();
    strWritablePath+=pFileName;
    FILE* pFile = NULL;
    /************************************************************************/
    /* w：以只写权限创建一个空文件  覆盖原文件
    	w+：以读写权限创建一个空文件  覆盖原文件
    	r：以只读权限打开一个文件，如果文件不存在  返回NULL
    	r+：以读写权限打开一个文件，如果文件不存在  返回NULL
    	a：只写追加打开一个文件，如果文件不存在，返回NULL
    	a+：读写追加打开一个文件，如果文件不存在，返回NULL*/
    /************************************************************************/
    pFile = fopen(strWritablePath.c_str(),"r");
    //如果文件存在于可读写路径，则不再复制
    if (pFile!=NULL)
    {
        fclose(pFile);
        return;
    }
    //复制文件
    //获得文件完整路径
    unsigned char* pData = NULL;
    ssize_t uLen = 0;
    //获得文件中数据
    pData = FileUtils::getInstance()->getFileData(pFileName,"r",&uLen);

    pFile = fopen(strWritablePath.c_str(),"w");
    fwrite(pData,sizeof(char),uLen,pFile);
    delete[] pData;
    //fread(void*,int,int,FILE*)
    //fwrite(void* SRC,int SIZE,int COUNT,FILE*);
    fclose(pFile);
}


bool AppDelegate::applicationDidFinishLaunching() {
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
    FileCopy("pvz.db");
#endif
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);
    glview->setDesignResolutionSize(1280,720,ResolutionPolicy::EXACT_FIT);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
