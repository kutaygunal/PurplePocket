#include "occview.h"

#include <QMouseEvent>
#include <QWheelEvent>

#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <AIS_Shape.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepTools.hxx>

#ifdef _WIN32
#include <WNT_Window.hxx>
#endif

OCCView::OCCView(QWidget *parent)
    : QOpenGLWidget(parent)
    , myCurrentButton(Qt::NoButton)
{
    // Enable mouse tracking for smooth navigation
    setMouseTracking(true);

    // Accept keyboard focus
    setFocusPolicy(Qt::StrongFocus);
}

OCCView::~OCCView()
{
    if (!myContext.IsNull()) {
        myContext->RemoveAll(false);
    }
}

void OCCView::initContext()
{
    if (myContext.IsNull())
    {
        // Create graphic driver
        Handle(Aspect_DisplayConnection) aDisplay = new Aspect_DisplayConnection();
        myDriver = new OpenGl_GraphicDriver(aDisplay);

        // Create viewer
        myViewer = new V3d_Viewer(myDriver);
        myViewer->SetDefaultLights();
        myViewer->SetLightOn();

        // Create view
        myView = myViewer->CreateView();
        myView->SetBackgroundColor(Quantity_NOC_BLACK);
        myView->MustBeResized();
        myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_WHITE, 0.1);

        // Create interactive context
        myContext = new AIS_InteractiveContext(myViewer);
        myContext->SetDisplayMode(AIS_Shaded, Standard_True);

        // Map the window
        WId window_handle = (WId)winId();
        Handle(WNT_Window) window = new WNT_Window((Aspect_Handle)window_handle);
        myView->SetWindow(window);
        
        if (!window->IsMapped()) {
            window->Map();
        }

        // Initialize demo scene
        initDemoScene();
    }
}

void OCCView::initDemoScene()
{
    // Create a sphere with radius 50
    BRepPrimAPI_MakeSphere sphereMaker(50.0);
    Handle(AIS_Shape) aisSphere = new AIS_Shape(sphereMaker.Shape());
    
    // Set display properties - yellow color
    aisSphere->SetColor(Quantity_NOC_YELLOW);
    aisSphere->SetDisplayMode(AIS_Shaded);
    
    // Display the sphere
    myContext->Display(aisSphere, Standard_True);
    
    // Fit all objects in view
    fitAll();
}

void OCCView::fitAll()
{
    if (!myView.IsNull()) {
        myView->FitAll();
        myView->ZFitAll();
        update();
    }
}

void OCCView::initializeGL()
{
    initContext();
}

void OCCView::paintGL()
{
    if (!myView.IsNull()) {
        myView->Redraw();
    }
}

void OCCView::resizeGL(int width, int height)
{
    if (!myView.IsNull()) {
        myView->Window()->DoResize();
        myView->MustBeResized();
        myView->Redraw();
    }
}

void OCCView::mousePressEvent(QMouseEvent* event)
{
    myLastPos = event->pos();
    myCurrentButton = event->button();

    if (event->button() == Qt::LeftButton) {
        myView->StartRotation(event->pos().x(), event->pos().y());
    }
}

void OCCView::mouseReleaseEvent(QMouseEvent* event)
{
    myCurrentButton = Qt::NoButton;
}

void OCCView::mouseMoveEvent(QMouseEvent* event)
{
    if (myCurrentButton == Qt::LeftButton) {
        myView->Rotation(event->pos().x(), event->pos().y());
    }
    else if (myCurrentButton == Qt::MiddleButton) {
        myView->Pan(event->pos().x() - myLastPos.x(), 
                   myLastPos.y() - event->pos().y());
    }

    myLastPos = event->pos();
}

void OCCView::wheelEvent(QWheelEvent* event)
{
    if (!myView.IsNull()) {
        Standard_Real currentScale = myView->Scale();
        Standard_Real newScale = event->angleDelta().y() < 0 ? currentScale * 0.9 : currentScale * 1.1;
        myView->SetScale(newScale);
    }
}
