#ifndef __HASHSET_HPP__
#define __HASHSET_HPP__
#include <vector>
#include <iostream>
#include <cmath>
#include <numeric>
#include <random>

// Choose a prime number
#define HASHTABLE_SIZE 107 

template <class Key, class Value>
class NMHashNode {
public:
	Key  key;
	Value val;
	NMHashNode(Key key, Value val) : 
	key(key), val(val)
	{}
};

template <class Key>
class NMHashFunction {

	/*
	 * We'll use the C++ std hash function
	 * Using a class allows us to extend the functionality if 
	 * need be
	 */

	unsigned NMhash(const Key &key){
		std::hash<Key> h;
		return h(key) % HASHTABLE_SIZE;
	}
	
public:
	unsigned operator()(const Key &key){
		return this->NMhash(key);
	}
};

template <typename Key, typename Value, class Function = NMHashFunction<Key>>
class NMHashTable {
private:
	std::vector<std::vector<NMHashNode<Key, Value>> > table;
	std::vector<int> indices;
	Function hashIndex;

	// Proxy for overloading bracket operators
	template <typename K, typename V>
	class NMHashProxy {
		NMHashTable<K, V> &hash;
		K key;
	public:
		NMHashProxy(NMHashTable<K, V> &h, const K &key) : hash(h), key(key){}
		// Implement the get and set operators
		operator V() const {
			V v;
			bool res = this->hash.get(key, v);
			if(res) return v;
			else throw "Key: " + key + " Not Found";
		}
		NMHashProxy &operator=(const V &value){
			this->hash.insert(key, value);
			return *this;
		}
	};
	
	
public:
	NMHashTable(){
		
		table = std::vector<std::vector<NMHashNode<Key, Value>> >(HASHTABLE_SIZE);
	}
	~NMHashTable(){}

	bool get(const Key &key, Value &val){
		int hashTableIndex = hashIndex(key);
		std::vector<NMHashNode<Key, Value>> bucket = this->table[hashTableIndex];
		for(auto &entry : bucket){
			if(key == entry.key){
				val = entry.val;
				return true;
			}
		}	
		return false;
	}

	// O(1) Average, O(n) worst case depending on chaining
	bool insert(const Key key, const Value val){
		int hashTableIndex = hashIndex(key);
		std::vector<NMHashNode<Key, Value>> bucket = this->table[hashTableIndex];
		for(auto &entry : bucket){
			if(key == entry.key){
				return false;
			}
		}	
		this->table[hashTableIndex].push_back(NMHashNode<Key, Value>(key, val));
		return true;
	}

	NMHashProxy<Key, Value> operator[](const Key & key){
		return NMHashProxy<Key, Value>(*this, key);
	}

	bool remove(Key key){
		int hashTableIndex = hashIndex(key);
		std::vector<NMHashNode<Key, Value>> bucket = this->table[hashTableIndex];
		for(int i = 0; i < (int)bucket.size(); i++){
			auto entry = bucket[i];
			if(key == entry.key){
				this->table[hashTableIndex].erase(bucket.begin() + i);
				return true;
			}
		}
		return false;
	}

	unsigned size() const {
		unsigned sum = 0;
		for(auto bucket : this->table){
			unsigned sz = bucket.size();
			if(sz > 0){
				sum += sz;
			}
		}
		return sum;
	}

	bool empty(){
		for(auto &bucket : this->table){
			if(bucket.size() > 0){
				return false;
			}
		}
		return true;
	}

	std::vector<NMHashNode<Key, Value>> getBucket(int index) const{
		return this->table[index];
	}

	std::vector<Key> keys(){
		std::vector<Key> k;
		for(auto &bucket : this->table){
			for(auto &entry : bucket){
				k.push_back(entry.key);
			}
		}
		return k;
	}

	void print(){
		std::cout << "{ ";
		for(auto &bucket : this->table){
			for(auto &entry : bucket){
				std::cout << entry.key << " : " << entry.val << ", ";
			}
		}
		std::cout << "}" << std::endl;
	}
};

class NMHashSet {
	NMHashTable<int, bool> hash;
	std::random_device rd;
	std::mt19937 gen;//(rd());
public:
	NMHashSet(){
		gen = std::mt19937(rd());
	}

	unsigned size(){
		return this->hash.size();
	}

	bool insert(int val){
		return hash.insert(val, true);
	}

	bool remove(int val){
		return hash.remove(val);
	}

	int getRandomElement(){
		if(hash.empty()){
			return -1;
		}
		// Generate random hash index
		auto dis = std::uniform_int_distribution<>(0, HASHTABLE_SIZE - 1);
		int randHashIndex = dis(this->gen);
		auto bucket = hash.getBucket(randHashIndex);
		std::vector<int> tried(HASHTABLE_SIZE, 0);
		int randomValue = -1;
		int numVisitedBuckets = 0; 
		while(numVisitedBuckets < HASHTABLE_SIZE){
			if(bucket.size() == 0){
				if(!tried[randHashIndex]){
					tried[randHashIndex] = 1;
					numVisitedBuckets += 1;
				}
				randHashIndex = dis(this->gen);
				bucket = hash.getBucket(randHashIndex);
			}else{
				// Generate random index within bucket
				dis = std::uniform_int_distribution<>(0, bucket.size() - 1); 
				int randBucketIndex = dis(this->gen);
				randomValue = bucket[randBucketIndex].key;
				break;
			}
		}
		return randomValue;
	}

	void print(){
		std::cout << "{ ";
		for(auto &k : this->hash.keys()){
			std::cout << k << ", "; 
		}
		std::cout << "}" << std::endl;
	}
};

#endif // __HASHSET_HPP__
