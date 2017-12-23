create: create.cpp check.cpp
	clang++ -o create create.cpp
	clang++ -o check check.cpp

.PHYON: clean
clean:
	-rm *.o

.PHYON: rm
rm:
	-rm main.txt.compress main.txt.unzip

.PHYON: open
open:
	vim main.txt
