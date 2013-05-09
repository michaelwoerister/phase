:: cd to solution dir (which is the directory this batch file is located in)
cd %~dp0

xcopy Dependencies\Win32\SFML-2.0\bin\libsndfile-1.dll Build\Win32Debug /d
xcopy Dependencies\Win32\SFML-2.0\bin\openal32.dll Build\Win32Debug /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-audio-d-2.dll Build\Win32Debug /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-graphics-d-2.dll Build\Win32Debug /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-network-d-2.dll Build\Win32Debug /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-system-d-2.dll Build\Win32Debug /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-window-d-2.dll Build\Win32Debug /d

xcopy Dependencies\Win32\SFML-2.0\bin\libsndfile-1.dll Build\Win32Release /d
xcopy Dependencies\Win32\SFML-2.0\bin\openal32.dll Build\Win32Release /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-audio-2.dll Build\Win32Release /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-graphics-2.dll Build\Win32Release /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-network-2.dll Build\Win32Release /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-system-2.dll Build\Win32Release /d
xcopy Dependencies\Win32\SFML-2.0\bin\sfml-window-2.dll Build\Win32Release /d