#include "OpenGLStudy.h"
#include "DemoVexture.h"
#include "Common.h"

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
    //testmain();
    //testCircle();
    //testCircleBorder();
    testCircleGLSL();
}