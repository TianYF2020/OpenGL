#pragma once
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>


class FBORenderer;
//QML UI 相关逻辑放到 QQuickFramebufferObject 子类
//渲染相关放到 QQuickFramebufferObject::Renderer 子类
//该类仅在 Qt Quick 通过 OpenGL 渲染时才起作用
class FBOItem : public QQuickFramebufferObject
{
    Q_OBJECT
    //QML_NAMED_ELEMENT(Renderer)
public:
    FBOItem(QQuickItem* parent = nullptr);
    //Renderer 实例是从 createRenderer() 返回的
    QQuickFramebufferObject::Renderer* createRenderer() const override;
};

//渲染相关放到 QQuickFramebufferObject::Renderer 子类
class FBORenderer : public QQuickFramebufferObject::Renderer,
    protected QOpenGLFunctions_3_3_Core
{
public:
    FBORenderer();
    //要渲染到 FBO，需要继承 Renderer 类并重新实现其 render() 函数
    void render() override;
    //创建新的 FBO 时调用，如 resize 时
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;

private:
    //着色器程序
    QOpenGLShaderProgram program;
};