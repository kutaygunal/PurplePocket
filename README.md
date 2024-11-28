# Qt Desktop Application

A modern desktop application built with Qt 6.8.0 and CMake.

## Prerequisites

- Qt 6.8.0 or later (MSVC 2022 64-bit version)
- CMake 3.16 or later
- Visual Studio 2022 with "Desktop development with C++" workload

## Project Structure

```
QtProject/
├── CMakeLists.txt        # CMake build configuration
├── main.cpp              # Application entry point
├── mainwindow.h          # Main window header
├── mainwindow.cpp        # Main window implementation
└── build/               # Build directory (generated)
```

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Configure the project with CMake:
```bash
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_PREFIX_PATH=C:\Qt\6.8.0\msvc2022_64 ..
```

3. Build the project:
```bash
cmake --build . --config Release
```

4. Deploy Qt dependencies (from the build/Release directory):
```bash
C:\Qt\6.8.0\msvc2022_64\bin\windeployqt.exe QtProject.exe
```

## Running the Application

After building, you can find the executable at:
```
build/Release/QtProject.exe
```

## Features

- Modern Qt 6 desktop application
- Clean and intuitive user interface
- Menu bar with File menu
- Toolbar with customizable actions
- Status bar for user feedback

## Development

To modify the application:
1. Edit `mainwindow.cpp` to change the UI and add features
2. Edit `mainwindow.h` to declare new functions and variables
3. Rebuild using the steps above

## License

This project is open source and available under the MIT License.
