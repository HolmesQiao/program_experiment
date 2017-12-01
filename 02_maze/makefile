object = main.o set.o create_map.o gl.o find_road.o file_operation.o
maze: $(object)
	clang++ -o maze $(object) -framework OpenGL -framework GLUT -framework Foundation -l sfml-audio
main.o:  data.h
set.o: data.h
create_map.o: data.h
gl.o: data.h
find_road.o: data.h
file_operation.o: data.h
.PHONY: clean
clean:
	-rm $(object)
