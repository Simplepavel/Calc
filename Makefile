libs = -L C:\msys64\ucrt64\lib -l Qt6Widgets -l Qt6Core -l Qt6Gui
includes = 	-I C:\msys64\ucrt64\include\qt6 -I C:\msys64\ucrt64\include\qt6\QtWidgets \
			-I C:\msys64\ucrt64\include\qt6\QtCore -I C:\msys64\ucrt64\include\qt6\QtGui 

files = main.cpp Calc.cpp


all:
	g++ $(files) $(includes) $(libs) -o main

compile: files = main.cpp Calc.cpp moc_calc.cpp

compile: moc
	g++ $(files) $(includes) $(libs) -o main


moc:
	rm -f moc_*.cpp
	C:\msys64\ucrt64\share\qt6\bin\moc.exe Calc.h -o moc_calc.cpp