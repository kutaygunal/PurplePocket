#ifndef OCCVIEW_H
#define OCCVIEW_H

#include <QWidget>
#include <QOpenGLWidget>

#include <AIS_InteractiveContext.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>

class OCCView : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OCCView(QWidget *parent = nullptr);
    ~OCCView();

    Handle(AIS_InteractiveContext) getContext() const { return myContext; }
    void fitAll();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;

private:
    Handle(OpenGl_GraphicDriver) myDriver;
    Handle(V3d_Viewer) myViewer;
    Handle(V3d_View) myView;
    Handle(AIS_InteractiveContext) myContext;

    // Mouse position
    QPoint myLastPos;
    Qt::MouseButton myCurrentButton;

    void initContext();
    void initViewer();
    void initDemoScene();
};

#endif // OCCVIEW_H
