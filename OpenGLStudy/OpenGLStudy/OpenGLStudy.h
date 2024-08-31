#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpenGLStudy.h"

class OpenGLStudy : public QMainWindow
{
    Q_OBJECT

public:
    OpenGLStudy(QWidget *parent = nullptr);
    ~OpenGLStudy();

public slots:
    void TestOpenGL();
private:
    Ui::OpenGLStudyClass ui;
};
