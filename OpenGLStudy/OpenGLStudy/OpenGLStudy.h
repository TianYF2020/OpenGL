#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpenGLStudy.h"
#include "DemoVexture.h"
#include "DemoCircle.h"
#include "Common.h"

class OpenGLStudy : public QMainWindow
{
    Q_OBJECT

public:
    OpenGLStudy(QWidget *parent = nullptr);
    ~OpenGLStudy();

    C_DrawCircle* m_DrawCircle = nullptr;
public slots:
    void TestOpenGL();
private:
    Ui::OpenGLStudyClass ui;
};
