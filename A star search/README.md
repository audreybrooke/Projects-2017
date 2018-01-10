Completes A* search on over 1,000,000 strings to find a "path" from one word to another.
A path is a series of words (from the input list) that are one letter different.
The program is case-insentive.

Using a heuristic (how many letters off the word being searched is from target)
and a priority queue the program accurately determines the shortest path between
the two given words using only words in the input file.

The program takes the input file name and 2 words as command line arguements.
First it translates the file into an adjancecny list.
Then, A* search is run with the first word as begining location and second word
as target. The path determined between the words is outputed and the number of
expansions is displayed.

example.txt is a small example of an input file that works with head and tail as the 
target and starting words.
