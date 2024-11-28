# PurplePocket - Qt OpenCASCADE 3D Viewer

A modern desktop application for 3D visualization using Qt 6.8.0 and OpenCASCADE 7.7.0.

## Features

### 3D Visualization
- Interactive 3D viewer powered by OpenCASCADE
- Mouse-based navigation (rotate, pan, zoom)
- Coordinate system display (trihedron)
- High-performance rendering using OpenGL

### Modern User Interface
- Dark mode theme support
- Resizable split layout
- Hierarchical tree-based component organization
- Modern styling with hover effects and visual feedback

### Component Categories
#### Flow Components
- **Chambers**
  - Momentum
  - Plenum
- **Elements**
  - Tube
  - Orifice

#### Thermal Components
- **Thermal Nodes**
  - Boundary Thermal Node
  - Internal Thermal Node
- **Resistors**
  - Conductor
  - Convector
  - Heat Transfer

## Prerequisites

- Windows 10/11
- Visual Studio 2022
- CMake 3.20 or higher
- Qt 6.8.0
- OpenCASCADE 7.7.0

## Development Environment Setup

1. Install Visual Studio 2022 with C++ development tools
2. Install Qt 6.8.0 for MSVC 2022 64-bit
3. Install OpenCASCADE 7.7.0
4. Set up environment variables:
   - Qt: `C:/Qt/6.8.0/msvc2022_64`
   - OpenCASCADE: `C:/Users/kutay/Downloads/occt-vc143-64/occt-vc143-64`

## Building the Project

1. Clone the repository:
```bash
git clone https://github.com/kutaygunal/PurplePocket.git
cd PurplePocket
```

2. Create build directory:
```bash
mkdir build
cd build
```

3. Configure with CMake:
```bash
cmake ..
```

4. Build the project:
```bash
cmake --build .
```

## Running the Application

1. Ensure all required DLLs are in place by running:
```bash
copy_dlls.bat
```

2. Launch the application from the build directory:
```bash
.\Debug\QtProject.exe
```

## User Interface

### Dark Mode Theme
The application features a modern dark mode theme with:
- Dark backgrounds (#1e1e1e, #2b2b2b)
- Light text (#e0e0e0)
- Blue selection highlights (#2979ff)
- Consistent styling across all components
- Smooth hover effects and transitions

### Layout
- Left Panel: Component tree with expandable categories
- Right Panel: 3D visualization area
- Resizable split view
- Menu bar with File and View options
- Status bar for application messages

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Qt Framework
- OpenCASCADE Technology
- Visual Studio
- CMake
