inicio:
	g++ -o exe ejemplo1.cpp
	./exe
	rm exe

tbb:
	g++ -o exe normaTbb.cpp -ltbb
	./exe
	rm exe