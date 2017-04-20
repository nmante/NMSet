#include <iostream>
#include <vector>
#include <time.h>
#include "hashset/hashset.hpp"
#include "treeset/treeset.hpp"

/*
 * set-ds example
 *
 * Implement set like data structure
 *
 * Approach 1
 * 	- Back it by a tree
 * 	- O(log n) insert
 * 	- O(log n) remove
 * 	- O(log n) random
 * 	- Keep tree balanced, to make sure access is logarithmic 
 * 	- this keeps tree sorted inherently
 *
 * Approach 2
 * 	- Back it by a hash
 * 	- this wouldn't be sorted
 * 	- Remove/Insert O(1) (average), O(n) worst case
 * 	- Get random O(1)
 *
 */

namespace HashSetTest{
	void hashTableTest(){
		NMHashTable<std::string, int> stringIntHash;
		stringIntHash["hello"] = 1;
		std::cout << stringIntHash["hello"] << std::endl;
		stringIntHash.print();
	}

	void hashsetTest(){
		NMHashSet hs;
		hs.insert(0);hs.insert(20);
		hs.insert(20);hs.insert(20);
		hs.insert(50);hs.insert(51);
		hs.insert(4);hs.insert(3);
		hs.insert(3);hs.insert(51);
		hs.insert(1000000);
		hs.print();
		std::cout << "Random value: " << hs.getRandomElement() << std::endl;
	}
}

namespace TreeSetTest{
	void treesetTest(){
		NMTreeSet hs;
		hs.insert(0);hs.insert(20);
		hs.insert(20);hs.insert(20);
		hs.insert(50);hs.insert(51);
		hs.insert(4);hs.insert(3);
		hs.insert(3);hs.insert(51);
		hs.insert(1000000);
		hs.print();
		std::cout << "Random value: " << hs.getRandomElement() << std::endl;
	}
}

int main(){
	std::srand(std::time(NULL));
	HashSetTest::hashTableTest();
	HashSetTest::hashsetTest();
	TreeSetTest::treesetTest();
	return 0;
}
