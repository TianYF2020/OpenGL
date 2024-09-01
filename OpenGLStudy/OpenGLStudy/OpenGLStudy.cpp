#include "OpenGLStudy.h"

OpenGLStudy::OpenGLStudy(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.BtnCreateGL, SIGNAL(clicked()), this, SLOT(TestOpenGL()));
    
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
    //m_DrawCircle->DrawCircle_Vertices();

    //m_DrawCircle->DrawCircleSingle_GLSL();   //使用glsl进行绘图
    //m_DrawCircle->DrawCircleGrid_GLSL();
    m_DrawCircle->DrawCircleGridPixel_GLSL();
}