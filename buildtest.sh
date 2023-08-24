sudo g++ -O2 -c test.cpp -o obj/test/test.o
sudo g++ -o bin/test.out obj/test/test.o -Lbin -lSCEngine -lGL
