#include "occview.h"
#include <QMouseEvent>
#include <QSurfaceFormat>

#ifdef _WIN32
#include <WNT_Window.hxx>
#endif

OCCView::OCCView(QWidget* parent)
    : QOpenGLWidget(parent),
    myXmin(0),
    myYmin(0),
    myXmax(0),
    myYmax(0),
    myCurrentButton(Qt::NoButton)
{
    // Set focus policy to enable keyboard input
    setFocusPolicy(Qt::StrongFocus);
    
    // Enable mouse tracking
    setMouseTracking(true);
}

OCCView::~OCCView()
{
    // Clean up OpenCASCADE objects
    if (!myContext.IsNull()) {
        myContext->RemoveAll(Standard_False);
    }
}

void OCCView::initializeGL()
{
    // Initialize OpenGL functions
    initializeOpenGLFunctions();

    try {
        // Create OpenCASCADE graphics driver
        Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
        Handle(OpenGl_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(displayConnection, false);

        // Create Viewer and View
        myViewer = new V3d_Viewer(graphicDriver);
        myViewer->SetDefaultLights();
        myViewer->SetLightOn();
        
        myView = myViewer->CreateView();

        // Create interactive context
        myContext = new AIS_InteractiveContext(myViewer);

        // Set up the view
        myView->SetBackgroundColor(Quantity_NOC_BLACK);
        myView->MustBeResized();
        
        // Map the window
        WId window_handle = (WId)winId();
        Handle(WNT_Window) window = new WNT_Window((Aspect_Handle)window_handle);
        myView->SetWindow(window);
        
        if (!window->IsMapped()) {
            window->Map();
        }

        // Create and initialize view cube
        initViewCube();

        // Create a test shape (yellow sphere)
        Handle(AIS_Shape) sphere = new AIS_Shape(BRepPrimAPI_MakeSphere(100.0));
        myContext->SetColor(sphere, Quantity_NOC_YELLOW, Standard_False);
        myContext->SetMaterial(sphere, Graphic3d_NOM_PLASTIC, Standard_False);
        myContext->SetDisplayMode(sphere, AIS_Shaded, Standard_True);  // Set display mode to shaded
        myContext->Display(sphere, Standard_False);

        // Set the view to fit all objects
        myView->FitAll();
        myView->ZFitAll();
    }
    catch (const Standard_Failure& ex) {
        qDebug() << "OpenCASCADE exception during initialization:" << ex.GetMessageString();
    }
    catch (const std::exception& ex) {
        qDebug() << "Standard exception during initialization:" << ex.what();
    }
    catch (...) {
        qDebug() << "Unknown exception during initialization";
    }
}

void OCCView::paintGL()
{
    if (!myView.IsNull())
    {
        myView->Redraw();
    }
}

void OCCView::resizeGL(int width, int height)
{
    if (!myView.IsNull())
    {
        myView->Window()->DoResize();
        myView->MustBeResized();
        myView->Redraw();
    }
}

void OCCView::fitAll()
{
    if (!myView.IsNull())
    {
        myView->FitAll();
        myView->ZFitAll();
        update();
    }
}

void OCCView::initViewCube()
{
    if (!myContext.IsNull())
    {
        // Create and customize the view cube
        myViewCube = new AIS_ViewCube();
        
        // Set size and position (reduced by 75%)
        myViewCube->SetSize(17.5);  // Reduced from 70 to 17.5
        myViewCube->SetBoxColor(Quantity_NOC_GRAY75);
        myViewCube->SetFixedAnimationLoop(false);
        myViewCube->SetTransformPersistence(
            new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers, 
                                      Aspect_TOTP_LEFT_LOWER,
                                      Graphic3d_Vec2i(25, 25)));  // Reduced offset for smaller cube
        
        // Set text properties
        myViewCube->SetTextColor(Quantity_NOC_WHITE);
        myViewCube->SetAxesLabels("X", "Y", "Z");
        
        // Set up view camera animation
        Handle(AIS_AnimationCamera) aCamera = new AIS_AnimationCamera("ViewCubeCamera", myView);
        myViewCube->SetViewAnimation(aCamera);
        myViewCube->SetDuration(0.2);  // Faster animation for better responsiveness
        
        // Enable selection for interaction
        myContext->Display(myViewCube, Standard_True);
        myContext->SetDisplayMode(myViewCube, AIS_Shaded, Standard_True);
        myContext->Activate(myViewCube, 0);  // Use default selection mode
    }
}

void OCCView::mousePressEvent(QMouseEvent* event)
{
    if (!myView.IsNull())
    {
        myLastPos = event->pos();
        myCurrentButton = event->button();

        if (event->button() == Qt::LeftButton)
        {
            // Convert mouse position to view coordinates
            myContext->MoveTo(event->pos().x(), event->pos().y(), myView, Standard_True);
            
            // Check if view cube was clicked
            if (myContext->HasDetected())
            {
                Handle(AIS_InteractiveObject) detected = myContext->DetectedInteractive();
                if (detected == myViewCube)
                {
                    myContext->Select(Standard_True);
                    myView->Redraw();
                    return;
                }
            }
            
            // If not clicking view cube, start rotation
            myView->StartRotation(event->pos().x(), event->pos().y());
        }
    }
}

void OCCView::mouseReleaseEvent(QMouseEvent* event)
{
    myCurrentButton = Qt::NoButton;
    
    // Handle view cube click completion
    if (!myContext.IsNull() && myContext->HasDetected())
    {
        Handle(AIS_InteractiveObject) selected = myContext->DetectedInteractive();
        if (selected == myViewCube)
        {
            myContext->UpdateCurrentViewer();
        }
    }
}

void OCCView::mouseMoveEvent(QMouseEvent* event)
{
    if (!myView.IsNull())
    {
        if (myCurrentButton == Qt::LeftButton)
        {
            // Move detector to current mouse position
            myContext->MoveTo(event->pos().x(), event->pos().y(), myView, Standard_True);
            
            // Only rotate if not interacting with view cube
            if (!myContext->HasDetected() || myContext->DetectedInteractive() != myViewCube)
            {
                myView->Rotation(event->pos().x(), event->pos().y());
            }
        }
        else if (myCurrentButton == Qt::MiddleButton)
        {
            myView->Pan(event->pos().x() - myLastPos.x(), 
                       myLastPos.y() - event->pos().y());
        }
        else
        {
            // Update detection when mouse moves without buttons
            myContext->MoveTo(event->pos().x(), event->pos().y(), myView, Standard_True);
        }

        myLastPos = event->pos();
    }
}
