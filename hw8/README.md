# CS 104 Student Repository

- **Name**: Audrey Brooke
- **USC ID**: 8899562687
- **Email**: abrooke@usc.edu

Report:

- Which sizes of input cases did you test your program on? This would apply both
 to the length m of the strings in the file, and the number n of strings/queries.

  For 62558 insertions, 98395 queries with stings of average length 9. The strings 
  were "dense" / similar (because they are the first 62558 entries of a dictionary, 
  many shared prefixes).
  total time for trie insertions: 0.037479 seconds (5.99108e-07 seconds per insertion)
  total time for trie queries: 0.015215 seconds (1.54632e-07 seconds per query)
  total time for bloom insertions: 0.069765 seconds (1.11521e-06 seconds per insertion)
  total time for bloom queries: 0.123192 seconds (1.25201e-06 seconds per query)
	88528 false positives (0.921591 false positive rate)
	Here, the inserts were far over the max size of the bloom filter so it is basically
	useless in terms of correctness. Otherwise, the queries took almost 10 times as long 
	for the bloom filter than the trie and the inserts took twice as long. This
	is partially because the strings are very similar so inserts to the trie are easy
	since only a few nodes on average are created each time. Also, the strings are 
	relatively short (only 9 chars long on average). So it is fast for the trie
	to insert and check for them because it only needs to move down ~9 nodes, while
	the bloom filter has about the same constant runtime no matter how long the
	inputs are.


  For 4 insertions, 4 queries and strings of average length 4.
  total time for trie insertions: 4e-06 seconds (1e-06 seconds per insertion)
  total time for trie queries: 4e-06 seconds (1e-06 seconds per query)
  total time for bloom insertions: 6e-06 seconds (1.5e-06 seconds per insertion)
  total time for bloom queries: 5e-06 seconds (1.25e-06 seconds per query)
	0 false positives (0 false positive rate)
	The Bloom Filter is initialized with size = 5 * number of inserts (rounded up 
	to nearest given prime). So it is likely that the number of false positives is
	low especially because 2 of these inputs were repeats so there were actually
	only 3 inserts. Repeats in insertion will likely cause the false positive rate to
	go down because the size is initialized greater than it would have been with the 
	same inputs but no repeats thus there is more "room" in the array and a lower
	likelihood that a query string will hash to 3 inputed values. Here the trie barely
	out performs the bloom filter for inserts and queries. With small strings it is
	really fast for the trie to insert and query since it moves down as many nodes
	as there are letters/symbols in the input.

  For 20 insertions, 20 queries and string of average length 56
  total time for trie insertions: 0.000127 seconds (6.35e-06 seconds per insertion)
  total time for trie queries: 1.1e-05 seconds (5.5e-07 seconds per query)
  total time for bloom insertions: 4.6e-05 seconds (2.3e-06 seconds per insertion)
  total time for bloom queries: 4.9e-05 seconds (2.45e-06 seconds per query)
  0 false positives (0 false positive rate)
	The 0 false positivies is likely do to the small number of queries compared to the
	array size. More queries makes a false positive more likely.
	The trie insertions took almost 3 times as long as the bloom filter for this input.
	This is because the input strings were longer than previous examples. The trie takes
	time equivalent to the length of the string to insert, so longer strings on average
	take more time, while the bloom filter is basically constant for inserts. Total
	time for trie queries was less than the bloom filter though. This is likely
	because while queries still run in O(string length), they are faster than inserts
	because no new nodes are created and the function returns once it can no longer find
	the next letter in the string, thus is often does not need to check even close to 
	the whole string length before returning. The bloom filter, on the other hand, is 
	not impacted by this because the hash functions are not related to how similar
	the inputs are to eachother. For every insert and query it must calculate all three
	hash functions. Also, the hash functions might take longer in this implementation
	because w must be redetermined for each hash, the values aren't saved and used again.

  For 2558 insertions, 158395 queries and strings with average length 9
  total time for trie insertions: 0.0133 seconds (5.19937e-06 seconds per insertion)
  total time for trie queries: 0.027749 seconds (1.75189e-07 seconds per query)
  total time for bloom insertions: 0.002325 seconds (9.08913e-07 seconds per insertion)
  total time for bloom queries: 0.190039 seconds (1.19978e-06 seconds per query)
  9089 false positives (0.0573819 false positive rate)
  	This false positive rate is higher than the previous because there were many more
  	queries than inserts. Thus, although the array might be sparse, there are many
  	combinations of hashes that are created for all these queries, so some of them
  	are going to match with inserted hashes. Otherwise, the results are similar to
  	the first example, because the query to insert ratio is not too critical to
  	the running time of insert and query for blooms or tries.



- How do you think the running time would compare if you were to implement your Set in 
  the following fashions?
	- Unsorted List
		This would be very fast to insert O(1) (either actual or amortized depending
		on the implementation) because the list is unordered the string
		would just be added to the end. This is probably faster than both the bloom
		filter and the trie because the work needed to add to a bloom filter, although
		basically constant is larger than adding to a list since there are a lot of
		calculations to determine the 3 hash values (especially this implementation
		which recalculated the w values each time.) It is also generally faster than a
		trie which takes O(input length) to insert since it is not dependent on the size
		of the input.
		But, the advantage of quick inserts is lost when it comes to query. An unordered
		list has runtime O(number of inserts) because at worst the query function would have 
		to check every index of the list to find an item at the end or determine the string
		was not in the list. This is much worse than tries and bloom filters because a trie
		only needs to to search the length of the string places (probably less than the
		number of inserts) and a bloom filter determines and checks the hashes in constant
		time (also proably faster to do a set number of operations than look through an entire
		list, unless that list is very small.)

	- Sorted list
		Inserting in a sorted list takes longer than an unsorted list but is faster to query.
		Inserting in a sorted list is generally faster than tries if the strings are relatively
		long and there are few entries (a very long string takes a while to insert). Tries are 
		faster if there are a relatively large number of inputs. Because, binary search (necesary 
		to find the placement of a new string in a sorted list) runs in O(log 
		(number of inserts)), thus is slower with more inserts and trie insert runs in 
		O(input length), thus is slower on longer inputs. Bloom filters run in constant time so
		it will be faster on a relatively large number of inputs.
		Querying a sorted list is faster than an unsorted because binary search takes O(log n)
		and a unsorted list taked O(n) to find an item.
		Inserting into a sorted list runs in O(log n) (binary search) and is dependent on how
		many pervious inserts there are. Inserting into a trie is based on the size of the input
		and a bloom filter is constant. So sorted lists are better for relatively small number of
		inputs, and tries are better for relatively shorter input size and bloom filters are better
		once when the time to calculate the hashes is shorter than O(log n), so when there are a
		relatively large number of inserts.
		Querying has the same results between the data structures because in all cases you need to
		locate the string (or where it should be if it had been added) to be able to insert or query.


	- Binary search tree, non-rotating variety
		A binary search tree, in the worst case is equivalent to creating a linked list.
		So the runtime for insert and query would be O(n). Thus, in the worst case it would
		only be better than a trie if there were less inserts than the length of the current
		insert and worse than a bloom filter if there were so few inserts that it took less
		time than the constant to determine and check all the hash values. In the average case,
		a binary search tree will have O(log n) hieght and thus O(log n) insert and query runtime.
		In this case the results are similar to a sorted lsit which also runs in O(log n) and is
		dependent on the number of inputs.

	- Binary search tree with AVL balancing
		An AVL tree runs in O(log n) so an AVL worst case would have the same results as an
		average case BST.