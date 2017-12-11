object = main.o huff_tree.o
compress: $(object)
	clang++ -o compress $(object)
main.o: main.h
huff_tree.o: main.h

.PHYON: run
run:
	./compress
.PHYON: clean
clean:
	-rm $(object)
