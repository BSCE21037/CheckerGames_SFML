all : compile link

test : clean compile linkTest
		main_test.exe

compile : 
	g++ -c *.cpp

linkRun : 
	g++ *.o -o main  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

linkTest : 
	g++ *.o -o main_test  -lsfml-graphics -lsfml-window -lsfml-system

clean : 
	del *.o

run : compile linkRun
		main.exe

