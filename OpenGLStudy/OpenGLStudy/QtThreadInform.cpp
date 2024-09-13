#include "QtThreadInform.h"
#include "stdio.h"
#include "iostream"



string CommunicationThread::executeLogicInThread()
{
    std::string result;
    // 使用C++的线程来执行逻辑
    //std::thread logicThread([&result]() 
    //    {
    //    // 在逻辑线程中执行一些操作
    //    result = "逻辑线程执行的结果";
    //    });

    //ref() 指定是引用传值，对应要写上 &
    std::thread logicThread(&MyClass::ThreadClassDeal, &m_MyClass, std::ref(result));

    logicThread.join();  // 等待逻辑线程完成

    return result;
}


void CommunicationThread::run() 
{
    // 创建逻辑线程
    std::string result = executeLogicInThread();
    // 发送结果到主线程UI
    emit resultReady(QString::fromStdString(result));
}

