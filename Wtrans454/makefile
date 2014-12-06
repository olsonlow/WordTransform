Trans.out : morph.o Jhash.o JCSQue.o JBSTree.o
	g++ -o Trans.out morph.o Jhash.o JCSQue.o JBSTree.o

morph.o : morph.cpp Jhash.h JCSQue.h
	g++ -c morph.cpp

Jhash.o : Jhash.cpp Jhash.h
	g++ -c Jhash.cpp

JCSQue.o : JCSQue.cpp JCSQue.h
	g++ -c JCSQue.cpp

JBSTree.o : JBSTree.cpp JBSTree.h
	g++ -c JBSTree.cpp

clean :
	rm -f *.o *~ *.out *.*~