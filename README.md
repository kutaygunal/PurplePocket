# PurplePocket - Qt OpenCASCADE 3D Visualization Application

A modern desktop application with 3D visualization capabilities using Qt and OpenCASCADE for engineering and simulation purposes.

## Features

### 3D Visualization
- Interactive OpenCASCADE view
- View cube for orientation control
- Dynamic camera manipulation
- View orientation buttons (Top, Bottom, Left, Right, Axonometric)
- Mouse controls for rotation, pan, and zoom

### User Interface
- Dark theme implementation
- Tree widget with categorized components
- Responsive toolbar
- Modular design

## Technical Stack
- Language: C++17
- Framework: Qt 6.8.0
- 3D Library: OpenCASCADE 7.7.0
- Compiler: MSVC 2022 (v143)
- Architecture: 64-bit

## UI Design
### Color Scheme
- Background: #1e1e1e (darkest)
- Secondary surfaces: #2b2b2b
- Hover/borders: #3f3f3f
- Text: #e0e0e0
- Selection: #2979ff (blue)

## Controls
- Left Mouse Button: Rotate view
- Middle Mouse Button: Pan view
- Mouse Wheel: Zoom in/out

## Development Environment
- Qt Creator recommended
- CMake build system
- Vcpkg for dependency management

## Getting Started
1. Install dependencies:
   - Qt 6.8.0
   - OpenCASCADE 7.7.0
   - CMake 3.24+
   - MSVC 2022

2. Clone the repository:
   ```bash
   git clone https://github.com/kutaygunal/PurplePocket.git
   ```

3. Build the project:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

## Current Implementation
- Basic 3D view with test sphere
- View control toolbar
- Tree widget with Flow and Thermal components
- Dark theme across application
- Interactive view manipulation

## Future Enhancements
- Advanced geometric modeling tools
- More interactive 3D view features
- Comprehensive error management
- Performance optimizations

## License
This project is licensed under the MIT License - see the LICENSE file for details.
