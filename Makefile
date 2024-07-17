SegmentationFault:
ifeq ($(OS),Windows_NT)
	g++ -Wall -pipe -O0 *.cpp -g -o SegmentationFault.exe -I C:\SFML-2.6.1\include -L C:\SFML-2.6.1\lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
else
	g++ -Wall -pipe -O0 *.cpp -g -o SegmentationFault.out -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio
endif

run:
ifeq ($(OS),Windows_NT)
	.\SegmentationFault.exe
else
	./SegmentationFault.out
endif

rerun:
	make -B
	make run

debug:
ifeq ($(OS),Windows_NT)
	gdb .\SegmentationFault.exe
else
	gdb ./SegmentationFault.out
endif