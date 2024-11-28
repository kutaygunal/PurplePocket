# Qt OpenCASCADE 3D Viewer

A Qt-based 3D viewer application using OpenCASCADE 7.8 for geometric modeling and visualization.

## Features

- Interactive 3D viewer with OpenCASCADE integration
- Drag and drop functionality for creating 3D objects
- Smooth zoom controls with mouse wheel
- Component tree with draggable items
- Real-time 3D point conversion and object placement
- Modern CMake build system

## Recent Updates

- Fixed zoom functionality (both zoom in and out working)
- Improved cube creation with centered placement
- Reduced cube size to 10x10x10 units for better visibility
- Changed cube color to blue with gold material
- Removed automatic view fitting for better control
- Added PowerShell build script for easy compilation and running

## Requirements

- Qt 6.x
- OpenCASCADE 7.8
- Visual Studio 2022
- CMake 3.x

## Building

### Using PowerShell Script

1. Open PowerShell in the project directory
2. Run the build script:
   ```powershell
   .\run.ps1                                    # Debug build and run
   .\run.ps1 -Configuration Release             # Release build and run
   .\run.ps1 -BuildOnly                         # Only build Debug
   .\run.ps1 -Configuration Release -BuildOnly  # Only build Release
   ```

### Manual Build

1. Create build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Generate Visual Studio solution:
   ```bash
   cmake -G "Visual Studio 17 2022" -A x64 ..
   ```

3. Build the project:
   ```bash
   cmake --build . --config Debug
   # or
   cmake --build . --config Release
   ```

## Usage

1. Launch the application
2. Use the component tree on the left to select items
3. Drag items from the tree to the 3D view
4. Use mouse wheel to zoom in/out
5. Left mouse button to rotate view
6. Middle mouse button to pan

## Controls

- **Mouse Wheel**: Zoom in/out
- **Left Mouse Button**: Rotate view
- **Middle Mouse Button**: Pan view
- **Drag and Drop**: Create objects in 3D space
