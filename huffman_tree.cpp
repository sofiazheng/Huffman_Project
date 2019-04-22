#include "huffman_tree.h"

bool huffman_tree::isLeaf(node* root) const {
	if (root->right == nullptr && root->left == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

huffman_tree::huffman_tree(const std::string& file_name) {
	char c;
	std::unordered_map<char, int> myMap;
	std::vector<node*> myV;
	std::ifstream file(file_name);
	if (file.is_open()) {
		while (true) {
			file.get(c);
			if (file.eof()) {
				break;
			}
			if (myMap.find(c) != myMap.end()) {
				myMap.at(c)++;
			}
			else {
				myMap.emplace(c, 1);
				node* temp = new node();
				temp->letter = c;
				myV.push_back(temp);
			}
		}
	}

	root = makeHuffTree(myV);
	if (isLeaf(root)) {
		huffCodes.emplace(root->letter, "1");
		return;
	}
	else {
		makeHuffCodes(root, "", huffCodes);
	}
}

huffman_tree::node* huffman_tree::makeHuffTree(std::vector<node*> & treeNodes)const {
	std::priority_queue<node*, std::vector<node*>, compare> pq;
	for (int i = 0; i < treeNodes.size(); i++) {
		pq.push(treeNodes[i]);
	}
	node* left;
	node* right;
	while (pq.size() != 0) {
		if (pq.size() > 1) {
			left = pq.top();
			pq.pop();

			right = pq.top();
			pq.pop();

			node* parent = new node();
			parent->freq = left->freq + right->freq;
			parent->left = left;
			parent->right = right;
			pq.push(parent);
		}
		else {
			return pq.top();
		}
	}
	return pq.top();
}

huffman_tree::~huffman_tree() {
	delete root;
	root = nullptr;
}

void huffman_tree::makeHuffCodes(node * head, std::string code, std::unordered_map<char, std::string > & table) const {
	std::string huffCodes = code;
	if (head == nullptr) {
		return;
	}
	if (isLeaf(head)) {
		table.emplace(head->letter, huffCodes);
	}
	if (head->left != nullptr) {
		makeHuffCodes(head->left, huffCodes += '0', table);
		huffCodes.pop_back();
	}
	if (head->right != nullptr) {
		makeHuffCodes(head->right, huffCodes += '1', table);
		huffCodes.pop_back();
	}
}


std::string huffman_tree::get_character_code(char character) const {
	if (huffCodes.find(character) != huffCodes.end()) {
		return huffCodes.at(character);
	}
	else {
		return "";
	}
}


std::string huffman_tree::encode(const std::string & file_name) const {
	if (isLeaf(root)) {
		return "1";
	}
	std::string encodedString;
	char c;
	std::ifstream fileToEncode(file_name);

	if (fileToEncode.is_open()) {
		while (true) {
			fileToEncode.get(c);
			if (fileToEncode.eof()) {
				break;
			}
			encodedString += get_character_code(c);
			if (encodedString == "") {
				return "";
			}
		}
	}
	else {
		return "";
	}
	return encodedString;
}

std::string huffman_tree::decode(const std::string & string_to_decode) const {
	std::string decodedString;
	node* temp = root;
	int i = 0;
	if (string_to_decode.size() == 0) {
		return "";
	}
	if (root == nullptr) {
		return "";
	}
	if (isLeaf(root) && (string_to_decode.size() > 1 || string_to_decode != "1")) {
		return "";
	}

	while (i < string_to_decode.size()) {
		if (string_to_decode[i] == '0') {
			if (isLeaf(temp)) {
				decodedString += temp->letter;
				temp = root;
			}
			else {
				temp = temp->left;
				if (isLeaf(temp)) {
					decodedString += temp->letter;
					temp = root;
				}
			}
		}
		else if (string_to_decode[i] == '1') {
			if (isLeaf(temp)) {
				decodedString += temp->letter;
				temp = root;
			}
			else {
				temp = temp->right;
				if (isLeaf(temp)) {
					decodedString += temp->letter;
					temp = root;
				}
			}
		}
		else {
			return "";
		}
		i++;
	}
	return decodedString;
}