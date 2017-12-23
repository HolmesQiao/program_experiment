object = main.o huff_tree.o file_operation.o Huffman_char.o
compress: $(object)
	clang++ -o compress $(object)
main.o: main.h
huff_tree.o: main.h
file_operation.o: main.h
Huffman_char.o: main.h

.PHYON: run
run:
	./compress file/main.txt compress
	./compress file/main.txt unzip 
#	cat file/main.txt
.PHYON: clean
clean:
	-rm $(object)
