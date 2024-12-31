g++ -c ./src/svgtran.cpp ./src/svglib.cpp ./src/main.cpp ./src/view.cpp 
g++ ./svgtran.o ./svglib.o ./main.o ./view.o -o svgviewer -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml2
rm ./svgtran.o ./svglib.o ./main.o ./view.o
./svgviewer  ./svgs/flower.svg
