#include "DrawTestGL.h"
#include <QDebug>

FBOItem::FBOItem(QQuickItem* parent)
    : QQuickFramebufferObject(parent)
{
    //���·�ת�������ͺ�OpenGL������ϵһ����
    qDebug() << "init ";
    setMirrorVertically(true);
}

QQuickFramebufferObject::Renderer* FBOItem::createRenderer() const
{
    qDebug() << "init ";
    //Renderer �� FBO �����ڲ�������ڴ�
    return new FBORenderer();
}


FBORenderer::FBORenderer()
{
    qDebug() << "FBO Render";
    //Ϊ��ǰ�����ĳ�ʼ��OpenGL��������
    initializeOpenGLFunctions();

    //��ɫ������
    //in���룬out���,uniform��cpu��gpu����
    const char* vertex_str = R"(#version 330 core
                           layout (location = 0) in vec3 vertices;
                           void main() {
                           gl_Position = vec4(vertices,1.0);
                           })";
    const char* fragment_str = R"(#version 330 core
                             uniform vec3 myColor;
                             void main() {
                             gl_FragColor = vec4(myColor,1.0);
                             })";

    //��source����Ϊָ�����͵���ɫ��������ӵ�����ɫ������
    if (!program.addCacheableShaderFromSourceCode(
        QOpenGLShader::Vertex, vertex_str)) {
        qDebug() << "compiler vertex error";
        exit(0);
    }
    if (!program.addCacheableShaderFromSourceCode(
        QOpenGLShader::Fragment, fragment_str)) {
        qDebug() << "compiler fragment error";
        exit(0);
    }
    //ʹ��addShader()����ӵ��ó������ɫ��������һ��
    program.link();

    //���������ư󶨵�ָ��λ��(����location=0)
    program.bindAttributeLocation("vertices", 0);

    qDebug() << "init ";
}

void FBORenderer::render()
{
    glClearColor(1.0f, 1.0f, 0.3f, 1.0f);
    //create FBO ʱ��������Ȼ���
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //������ɫ������󶨵����QOpenGLContext����ʹ���Ϊ��ǰ����ɫ������
    //ͬ�ڵ���glUseProgram(programid)
    program.bind();
    //����ֵ
    program.setUniformValue("myColor", QVector3D(0, 1, 0));

    //QtĬ���Ǻ�OpenGL��ߵ������ģ��ϸ�������
    //���ǿ�����QQuickFramebufferObject����setMirrorVertically(true);
    float vertices[] = {
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f,-0.5f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f   // top
    };
    //�ڴ���ɫ�������е�λ�ô����ö������飬
    //�Ա���ɫ������ʹ����λ������setAttributeArray()���õ�ֵ��
    program.enableAttributeArray(0);
    //����Ӧλ�����ö�������
    program.setAttributeArray(0, GL_FLOAT, vertices, 3);
    //������������ȾͼԪ(render primitives from array data)
    glDrawArrays(GL_TRIANGLES, 0, 3);
    program.disableAttributeArray(0);

    //�ӵ�ǰQOpenGLContext�ͷŻ����ɫ������
    //�൱�ڵ���glUseProgram(0)
    program.release();
}

QOpenGLFramebufferObject* FBORenderer::createFramebufferObject(const QSize& size)
{
    QOpenGLFramebufferObjectFormat format;
    //attach����Ҫ����GL_DEPTH_TEST
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}