sudo g++ -pthread -c Timer.cpp -o obj/Timer.o -fPIC
sudo g++ -c CloseEvent.cpp -o obj/CloseEvent.o -fPIC
sudo g++ -c Device.cpp -o obj/Device.o -fPIC
sudo g++ -c Driver.cpp -o obj/Driver.o -fPIC
sudo g++ -c Event.cpp -o obj/Event.o -fPIC
sudo g++ -c EventReceiver.cpp -o obj/EventReceiver.o -fPIC
sudo g++ -c KeyEvent.cpp -o obj/KeyEvent.o -fPIC
sudo g++ -c MouseEvent.cpp -o obj/MouseEvent.o -fPIC
sudo g++ -c PaintEvent.cpp -o obj/PaintEvent.o -fPIC
sudo g++ -c ResizeEvent.cpp -o obj/ResizeEvent.o -fPIC
sudo g++ -c TimerEvent.cpp -o obj/TimerEvent.o -fPIC
sudo g++ -shared obj/Timer.o obj/CloseEvent.o obj/Device.o obj/Event.o obj/Driver.o obj/EventReceiver.o obj/KeyEvent.o obj/MouseEvent.o  obj/PaintEvent.o obj/ResizeEvent.o  obj/TimerEvent.o  -o bin/libSCEngine.so -lGL -lX11
