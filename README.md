# Qt OpenCascade 3D Viewer

A modern desktop application with 3D visualization capabilities using Qt 6.8.0 and OpenCASCADE 7.7.0.

## Features

- 3D visualization using OpenCASCADE
- Interactive view manipulation (rotate, pan, zoom)
- Modern Qt-based user interface
- Demo scene with a red cube
- Coordinate system display (trihedron)

## Prerequisites

- Windows 10/11
- Visual Studio 2022
- CMake 3.20 or higher
- Qt 6.8.0
- OpenCASCADE 7.7.0

### Required Dependencies

1. Qt Components:
   - Qt Core
   - Qt GUI
   - Qt Widgets
   - Qt OpenGL Widgets

2. OpenCASCADE Libraries:
   - TKernel
   - TKMath
   - TKService
   - TKV3d
   - TKOpenGl
   - TKIGES
   - TKG2d
   - TKG3d
   - TKGeomBase
   - TKGeomAlgo

3. Third-Party Libraries:
   - FreeImage
   - FreeType
   - TBB
   - ZLIB
   - OpenVR
   - FFmpeg
   - JEMalloc

## Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/kutaygunal/PurplePocket.git
   cd PurplePocket
   ```

2. Configure environment variables:
   - Set `Qt6_DIR` to your Qt installation (e.g., `C:/Qt/6.8.0/msvc2022_64`)
   - Set `OpenCASCADE_DIR` to your OpenCASCADE installation

3. Create build directory and run CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

4. Build the project:
   ```bash
   cmake --build . --config Debug
   ```

5. Copy required DLLs:
   ```bash
   cd ..
   copy_dlls.bat
   ```

## Usage

1. Launch the application:
   ```bash
   build/Debug/QtProject.exe
   ```

2. View Controls:
   - Left Mouse Button: Rotate view
   - Middle Mouse Button: Pan view
   - Mouse Wheel: Zoom in/out
   - "Fit All" button: Reset view to show all objects

## Development Environment

- IDE: Visual Studio 2022
- Compiler: MSVC 2022 (v143)
- Build System: CMake
- C++ Standard: C++17

## Project Structure

- `main.cpp`: Application entry point
- `mainwindow.h/cpp`: Main application window implementation
- `occview.h/cpp`: OpenCASCADE 3D visualization widget
- `CMakeLists.txt`: CMake build configuration
- `copy_dlls.bat`: Script to copy required runtime DLLs

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Qt Framework: https://www.qt.io/
- OpenCASCADE Technology: https://www.opencascade.com/

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request
