#include "OpenGLStudy.h"
#include "QtThreadInform.h"
OpenGLStudy::OpenGLStudy(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.BtnCreateGL, SIGNAL(clicked()), this, SLOT(TestOpenGL()));
    connect(ui.BtnCreateThread, SIGNAL(clicked()), this, SLOT(TestThread()));
}

OpenGLStudy::~OpenGLStudy()
{
    
}


void OpenGLStudy::TestOpenGL()
{
    if (m_DrawCircle == nullptr)
    {
        m_DrawCircle = new C_DrawCircle();
    }
    if (m_DrawRect == nullptr)
    {
        m_DrawRect = new C_DrawRectangle();
    }
    if (m_DrawText == nullptr)
    {
        m_DrawText = new C_DrawText();
    }
    //m_DrawCircle->DrawCircle_Vertices();

    //m_DrawCircle->DrawCircleSingle_GLSL();   //使用glsl进行绘图
    //m_DrawCircle->DrawCircleGrid_GLSL();
    //m_DrawCircle->DrawCircleGridPixel_GLSL();
    //m_DrawRect->DrawRectangle_Vertices();
    m_DrawText->DrawText_Vertices();
}

void OpenGLStudy::TestThread()
{
    ui.textEdit->setText("");
    CommunicationThread* commThread = new CommunicationThread();
    //connect(commThread, &CommunicationThread::resultReady, this, [](const QString& result) {
    //    // 更新UI界面文本
    //    qDebug() << "收到的结果：" << result;
    //    // 可以使用类似的方式将结果显示到QML界面上
    //    // QML界面可以通过绑定属性或直接调用C++方法来更新
    //    });
    connect(commThread, &CommunicationThread::resultReady, this, &OpenGLStudy::UpdataRunResult);

    commThread->start();  // 启动通信
   
}


void OpenGLStudy::UpdataRunResult(const QString& result)
{
    ui.textEdit->setText(result);

}
