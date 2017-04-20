# Set Implementation

## Overview

This repo was inspired by a google coaching call question. The question was as follows:

*Implement a set like data structure with efficient insert, remove and getRandomElement functions. The getRandomElement function should return items with equal probability.*

## Usage & Installation

### Run the example (main.cpp)
	git clone https://github.com/nmante/NMSet
	cd NMSet
	make
	./setDS

###Include in your own code

You can include either of the implementations [hashset/hashset.hpp](hashset/hashset.hpp) or [treeset/treeset.hpp](hashset/hashset.hpp) in your projects. They are template header only implementations. Compile with `-std=c++11` since this uses features from there. See the [Makefile](Makefile) as an example on how to use `c++11`.

## Implementation

There are several ways you can do this. The first thing to think of is what are the requirements for runtime complexity. 

- Should it be `O(n)`?
- Or maybe `O(log n)` or constant `O(1)`?
- Maybe some operations should be constant, and others logarithmic?

The point is, this is a purposely ambiguous question. Having said that, there were two main approaches that I thought of (there are more).

- Tree Based Implementation
	- We could use a self balancing tree as well to make sure operations remain logarithmic
- Hash Based Implementation

### Performance Tradeoffs

There are trade offs for each implementation. The tree based approach gives us `O(log n)` for all operations. So it's relatively fast. Additionally, items remain inherently sorted because insertion and removal depend key comparisons.

The hash based approach is fast (constant time `O(1)`) for all methods in the average case. However, in the worst case, we can see `O(n)` time complexity. That depends greatly on our hashtable size as well as the hash function we use. Additionally, for the `getRandomElement` it's possible that many elements may fall in the same bucket. Thus, we aren't guaranteed that the probability is equally distributed for finding items in the set. 

### Interview Tips

Of course, in the context of a 45 minute interview it would be difficult to implement a robust hashing function or self balancing tree... It's not realistic. But these are things that should be discussed while you're interviewing. The interviewer will likely let you assume that you could use an already implemented hash function, or just implement a simple binary search tree.

## Source Code

I've included a hash based implementation [hashset/hashset.hpp](hashset/hashset.hpp) and a tree based implementation in [treeset/treeset.hpp](treeset/treeset.hpp).  Usage of the two can be seen in [main.cpp](main.cpp).
