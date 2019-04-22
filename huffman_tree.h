#pragma once
#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>
#include <math.h>

class huffman_tree {

public:
	struct node {
		int freq;
		char letter;
		node* left;
		node* right;

	};
	struct compare {
		bool operator()(node const* temp1, node const* temp2)const
		{
			return temp1->freq > temp2->freq;
		}
	};

	node* makeHuffTree(std::vector<node*>& treeNodes) const;
	void makeHuffCodes(node* root, std::string code, std::unordered_map<char, std::string >& table) const;
	bool isLeaf(node* root) const;
	node* root;
	std::unordered_map<char, std::string > huffCodes;

	huffman_tree(const std::string& file_name);

	~huffman_tree();

	std::string get_character_code(char character) const;
	std::string encode(const std::string& file_name) const;
	std::string decode(const std::string& string_to_decode) const;
};

#endif