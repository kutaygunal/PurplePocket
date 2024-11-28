#ifndef OCCVIEW_H
#define OCCVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QDebug>

// OpenCASCADE includes
#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_Shape.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_AnimationCamera.hxx>
#include <Graphic3d_GraphicDriver.hxx>

class OCCView : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OCCView(QWidget* parent = nullptr);
    ~OCCView();

    Handle(AIS_InteractiveContext) getContext() const { return myContext; }
    void fitAll();
    Handle(V3d_View) getView() const { return myView; }

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
    void initViewCube();

    Handle(AIS_InteractiveContext) myContext;
    Handle(V3d_View) myView;
    Handle(V3d_Viewer) myViewer;
    Handle(AIS_ViewCube) myViewCube;

    Standard_Integer myXmin;
    Standard_Integer myYmin;
    Standard_Integer myXmax;
    Standard_Integer myYmax;
    Qt::MouseButton myCurrentButton;
    QPoint myLastPos;
};

#endif // OCCVIEW_H
