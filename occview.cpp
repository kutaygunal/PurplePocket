#include "occview.h"
#include <QMouseEvent>
#include <QSurfaceFormat>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <BRepPrimAPI_MakeBox.hxx>
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
    setAcceptDrops(true);
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
    qDebug() << "Initializing OpenGL context";
    
    // Initialize OpenGL functions
    initializeOpenGLFunctions();

    try {
        // Create the OpenCascade viewer
        Handle(Aspect_DisplayConnection) displayConnection = new Aspect_DisplayConnection();
        Handle(OpenGl_GraphicDriver) graphicDriver = new OpenGl_GraphicDriver(displayConnection, false);
        
        myViewer = new V3d_Viewer(graphicDriver);
        myViewer->SetDefaultLights();
        myViewer->SetLightOn();
        
        // Set up the view
        myView = myViewer->CreateView();
        myView->SetBackgroundColor(Quantity_NOC_BLACK);
        myView->MustBeResized();
        
        // Create the interactive context
        myContext = new AIS_InteractiveContext(myViewer);
        myContext->SetDisplayMode(AIS_Shaded, Standard_True);
        
        // Initialize the view cube
        initViewCube();
        
        // Map the window
        WId window_handle = (WId)winId();
        Handle(WNT_Window) window = new WNT_Window((Aspect_Handle)window_handle);
        myView->SetWindow(window);
        
        if (!window->IsMapped()) {
            window->Map();
        }
        
        // Initial view setup
        myView->FitAll();
        myView->ZFitAll();
        
        qDebug() << "OpenGL initialization completed";
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

        myContext->Display(myViewCube, Standard_False);
      
        // Set size and position
        myViewCube->SetBoxColor(Quantity_NOC_GRAY75);
        myViewCube->SetFixedAnimationLoop(false);
        myViewCube->SetTransformPersistence(
            new Graphic3d_TransformPers(
                Graphic3d_TMF_TriedronPers,
                Aspect_TOTP_LEFT_LOWER,
                Graphic3d_Vec2i(85, 85)));

        myViewCube->SetAutoStartAnimation(Standard_True);
        myViewCube->SetSize(60);
        myViewCube->SetFontHeight(13);
        
        // Set text properties
        myViewCube->SetTextColor(Quantity_NOC_WHITE);
        myViewCube->SetAxesLabels("X", "Y", "Z");
        
        // Set up view camera animation
        Handle(AIS_AnimationCamera) aCamera = new AIS_AnimationCamera("ViewCubeCamera", myView);
        myViewCube->SetViewAnimation(aCamera);
        myViewCube->SetDuration(0.2);
        
        // Enable selection for interaction
        myContext->Display(myViewCube, Standard_True);
        myContext->SetDisplayMode(myViewCube, AIS_Shaded, Standard_True);
        myContext->Activate(myViewCube, 0);
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

void OCCView::wheelEvent(QWheelEvent* event)
{
    if (!myView.IsNull()) {
        // Get the number of degrees scrolled
        const int delta = event->angleDelta().y();
        
        // Current scale
        Standard_Real currentScale = myView->Scale();
        
        // Zoom factor (adjust this value to change zoom sensitivity)
        Standard_Real zoomFactor = 1.1;
        
        if (delta > 0) {
            // Zoom in
            myView->SetZoom(currentScale * zoomFactor);
        } else {
            // Zoom out
            myView->SetZoom(currentScale / zoomFactor);
        }
        
        myView->Redraw();
    }
    event->accept();
}

void OCCView::dragEnterEvent(QDragEnterEvent* event)
{
    qDebug() << "Drag Enter Event - MIME formats:" << event->mimeData()->formats();
    if (event->mimeData()->hasText()) {
        qDebug() << "Text content:" << event->mimeData()->text();
    }
    event->acceptProposedAction();
}

void OCCView::dropEvent(QDropEvent* event)
{
    qDebug() << "Drop Event received at:" << event->pos();

    // Get drop position
    gp_Pnt dropPoint = convertClickToPoint(event->pos());
    qDebug() << "Drop point calculated:" << dropPoint.X() << dropPoint.Y() << dropPoint.Z();
    
    // Create and display the cube
    createCubeAt(dropPoint);
    
    // Ensure proper view update
    myContext->UpdateCurrentViewer();
    myView->Redraw();
    
    event->acceptProposedAction();
    qDebug() << "Drop event processed successfully";
}

void OCCView::createCubeAt(const gp_Pnt& position)
{
    qDebug() << "Creating cube at position:" << position.X() << position.Y() << position.Z();
    
    try {
        // Create a larger cube (100x100x100) for better visibility
        Standard_Real size = 10.0;
        // Calculate the corner position by offsetting half the size in each direction
        gp_Pnt cornerPos(
            position.X() - size/2,
            position.Y() - size/2,
            position.Z() - size/2
        );
        TopoDS_Shape cube = BRepPrimAPI_MakeBox(cornerPos, size, size, size).Shape();
        
        Handle(AIS_Shape) aisBox = new AIS_Shape(cube);
        aisBox->SetColor(Quantity_NOC_BLUE);
        myContext->SetDisplayMode(aisBox, 1, Standard_True); // 1 = shaded mode in OpenCASCADE 7.8
        myContext->SetMaterial(aisBox, Graphic3d_NOM_GOLD, Standard_True);
        myContext->Display(aisBox, Standard_True);
        
        // Update the view
        myView->Redraw();
        
        qDebug() << "Cube creation completed";
    }
    catch (const Standard_Failure& ex) {
        qDebug() << "Error creating cube:" << ex.GetMessageString();
    }
}

gp_Pnt OCCView::convertClickToPoint(const QPoint& pos)
{
    try {
        // Get the view parameters
        Standard_Real X, Y, Z;
        Standard_Real XEye, YEye, ZEye;
        Standard_Real XAt, YAt, ZAt;
        
        myView->Eye(XEye, YEye, ZEye);
        myView->At(XAt, YAt, ZAt);
        
        // Convert click position to 3D point
        myView->Convert(pos.x(), height() - pos.y(), X, Y, Z);
        
        // Create point with some offset from camera
        gp_Pnt worldPos(X, Y, Z);
        qDebug() << "Click converted to:" << X << Y << Z;
        
        return worldPos;
    }
    catch (const Standard_Failure& ex) {
        qDebug() << "Error converting point:" << ex.GetMessageString();
        return gp_Pnt(0, 0, 0);
    }
}
