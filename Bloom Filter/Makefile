all: webindex

webindex: webindex.cpp TrieSet.o BloomFilter.o
	g++ -g -Wall TrieSet.o BloomFilter.o webindex.cpp -o webindex

BloomFilter.o: BloomFilter.cpp BloomFilter.h
	g++ -g -Wall -c BloomFilter.cpp -o BloomFilter.o

TrieSet.o: TrieSet.cpp TrieSet.h
	g++ -g -Wall -c TrieSet.cpp -o TrieSet.o


clean:
	rm -f TrieSet.o
	rm -f webindex
	rm -f BloomFilter.o
