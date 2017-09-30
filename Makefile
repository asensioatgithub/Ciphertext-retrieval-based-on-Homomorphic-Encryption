main.o:main.cpp ./CreateIndex/GetKeyWords.h ./CreateIndex/Inverted_Index.h ./HE/instruct.h
	g++ -o main.o main.cpp -lntl -lgmp -lm
Index.o:./CreateIndex/Inverted_Index.cpp ./CreateIndex/Inverted_Index.h ./CreateIndex/Convert.h ./HE/instruct.h ./CreateIndex/NLPIR.h ./CreateIndex/iconv.h
	g++ -o Index ./CreateIndex/Inverted_Index.cpp ./lib/libiconv.so ./lib/libNLPIR.so -DOS_LINUX -m64
HE.o:./HE/*
	g++ -o HE ./HE/* -lntl -lgmp -lm
