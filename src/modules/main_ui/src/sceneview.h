#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <vw/entity.h>

class SceneView :
        public QOpenGLWidget,
        public QOpenGLFunctions_4_0_Core
{
    Q_OBJECT
public:
    explicit SceneView(QWidget *parent = nullptr);
    ~SceneView();

    void setScene(vw::Entity *scene);

signals:

public slots:

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;

    // QOpenGLWidget interface
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;

private:
    void drawGrid();

    QMatrix4x4 current_matrix_;
    vw::Entity *scene_;

    QPoint last_pos_;
};

#endif // SCENEVIEW_H