#pragma once
#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLContext>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>


class FBORenderer;
//QML UI ����߼��ŵ� QQuickFramebufferObject ����
//��Ⱦ��طŵ� QQuickFramebufferObject::Renderer ����
//������� Qt Quick ͨ�� OpenGL ��Ⱦʱ��������
class FBOItem : public QQuickFramebufferObject
{
    Q_OBJECT
    //QML_NAMED_ELEMENT(Renderer)
public:
    FBOItem(QQuickItem* parent = nullptr);
    //Renderer ʵ���Ǵ� createRenderer() ���ص�
    QQuickFramebufferObject::Renderer* createRenderer() const override;
};

//��Ⱦ��طŵ� QQuickFramebufferObject::Renderer ����
class FBORenderer : public QQuickFramebufferObject::Renderer,
    protected QOpenGLFunctions_3_3_Core
{
public:
    FBORenderer();
    //Ҫ��Ⱦ�� FBO����Ҫ�̳� Renderer �ಢ����ʵ���� render() ����
    void render() override;
    //�����µ� FBO ʱ���ã��� resize ʱ
    QOpenGLFramebufferObject* createFramebufferObject(const QSize& size) override;

private:
    //��ɫ������
    QOpenGLShaderProgram program;
};