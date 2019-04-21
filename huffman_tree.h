#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
#include <numeric>

using namespace std;

class huffman_tree {
public:
	//node
	struct node {
		char character;
		int freq;
		struct node* left;
		struct node* right;
	};

	struct compare {
		bool operator()(node* const temp1, node* const temp2) {
			return temp1->freq > temp2->freq;
		}
	};

	node* root;

	node* nodeNew(char newChar, int newFreq) {
		node* n = new node();
		n->character = newChar;
		n->freq = newFreq;
		return n;
	}
	node* parentNode(int sum, node* left, node* right) {
		node* n = new node();
		n->freq = sum;
		n->left = left;
		n->right = right;
		return n;
	}
	std::unordered_map<char,string> encodeMap;
	std::unordered_map<string,char> decodeMap;
	
	void recursive(node* newRoot, string s);

	huffman_tree(const std::string& file_name);
	~huffman_tree();
	std::string get_character_code(char character) const;
	std::string encode(const std::string& file_name) const;
	std::string decode(const std::string& string_to_decode) const;
};

#endif