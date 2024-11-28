@echo off
set THIRD_PARTY_DIR=C:\Users\kutay\Downloads\3rdparty-vc14-64\3rdparty-vc14-64
set TARGET_DIR=C:\Users\kutay\Desktop\QtProject\build\Debug
set QT_DIR=C:\Qt\6.8.0\msvc2022_64\bin

rem Copy Qt DLLs
copy "%QT_DIR%\Qt6Cored.dll" "%TARGET_DIR%"
copy "%QT_DIR%\Qt6Guid.dll" "%TARGET_DIR%"
copy "%QT_DIR%\Qt6Widgetsd.dll" "%TARGET_DIR%"
copy "%QT_DIR%\Qt6OpenGLWidgetsd.dll" "%TARGET_DIR%"
copy "%QT_DIR%\Qt6OpenGLd.dll" "%TARGET_DIR%"

rem Copy Qt Platform DLLs
if not exist "%TARGET_DIR%\platforms" mkdir "%TARGET_DIR%\platforms"
copy "%QT_DIR%\..\plugins\platforms\qwindowsd.dll" "%TARGET_DIR%\platforms"

rem Copy OpenGL Platform DLLs
if not exist "%TARGET_DIR%\opengl32sw" mkdir "%TARGET_DIR%\opengl32sw"
copy "%QT_DIR%\..\plugins\opengl32sw\opengl32sw.dll" "%TARGET_DIR%\opengl32sw"

rem Copy FreeImage DLLs
copy "%THIRD_PARTY_DIR%\freeimage-3.17.0-vc14-64\bin\FreeImage.dll" "%TARGET_DIR%"
copy "%THIRD_PARTY_DIR%\freeimage-3.17.0-vc14-64\bin\FreeImagePlus.dll" "%TARGET_DIR%"

rem Copy FreeType DLLs
copy "%THIRD_PARTY_DIR%\freetype-2.5.5-vc14-64\bin\freetype.dll" "%TARGET_DIR%"

rem Copy TBB DLLs
copy "%THIRD_PARTY_DIR%\tbb2021.5-vc14-x64\bin\tbb.dll" "%TARGET_DIR%"
copy "%THIRD_PARTY_DIR%\tbb2021.5-vc14-x64\bin\tbb12.dll" "%TARGET_DIR%"
copy "%THIRD_PARTY_DIR%\tbb2021.5-vc14-x64\bin\tbbmalloc.dll" "%TARGET_DIR%"

rem Copy ZLIB DLLs
copy "%THIRD_PARTY_DIR%\zlib-1.2.8-vc14-64\bin\zlib.dll" "%TARGET_DIR%"

rem Copy OpenVR DLLs
copy "%THIRD_PARTY_DIR%\openvr-1.14.15-64\bin\win64\openvr_api.dll" "%TARGET_DIR%"

rem Copy FFmpeg DLLs
copy "%THIRD_PARTY_DIR%\ffmpeg-3.3.4-64\bin\avcodec-57.dll" "%TARGET_DIR%"
copy "%THIRD_PARTY_DIR%\ffmpeg-3.3.4-64\bin\avformat-57.dll" "%TARGET_DIR%"
copy "%THIRD_PARTY_DIR%\ffmpeg-3.3.4-64\bin\swscale-4.dll" "%TARGET_DIR%"
copy "%THIRD_PARTY_DIR%\ffmpeg-3.3.4-64\bin\avutil-55.dll" "%TARGET_DIR%"

rem Copy Jemalloc DLLs
copy "%THIRD_PARTY_DIR%\jemalloc-vc14-64\bin\jemalloc.dll" "%TARGET_DIR%"
