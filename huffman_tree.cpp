#include "huffman_tree.h"

bool huffman_tree::isLeaf(Node* root) const {
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
	std::vector<Node*> myV;
	std::ifstream myFile(file_name);
	if (myFile.is_open()) {
		while (true) { 
			myFile.get(c);
			if (myFile.eof()) {
				break;
			}
			if (myMap.find(c) != myMap.end()) {
				myMap.at(c)++;
			}
			else {
				myMap.emplace(c, 1);
				Node* temp = new Node();
				temp->letter = c;
				myV.push_back(temp);
			}
		}
	}

	for (int i = 0; i < myV.size(); i++) {
		myV[i]->freq = myMap.at(myV[i]->letter);

	}
	root = makeHuffTree(myV);
	if (isLeaf(root)) {
		encodedMap.emplace(root->letter, "1");
		return;
	}
	else {
		HuffTreeCodes(root, "", encodedMap);
	}
}

huffman_tree::Node* huffman_tree::makeHuffTree(std::vector<Node*> & treeNodes)const {
	std::priority_queue<Node*, std::vector<Node*>, compareFreq> pq;
	for (int i = 0; i < treeNodes.size(); i++) {
		pq.push(treeNodes[i]);
	}
	Node* Tleft;
	Node* Tright;
	while (pq.size() != 0) {
		if (pq.size() > 1) {
			Tleft = pq.top();
			pq.pop();

			Tright = pq.top();
			pq.pop();

			Node* parentNode = new Node();
			parentNode->freq = Tleft->freq + Tright->freq;
			parentNode->left = Tleft;
			parentNode->right = Tright;
			pq.push(parentNode);
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

void huffman_tree::HuffTreeCodes(Node * head, std::string code, std::unordered_map<char, std::string > & table) const {
	std::string HTCodes = code;
	if (head == nullptr) {
		return;
	}
	if (isLeaf(head)) {
		table.emplace(head->letter, HTCodes);
	}
	if (head->left != nullptr) {
		HuffTreeCodes(head->left, HTCodes += '0', table);
		HTCodes.pop_back();
	}
	if (head->right != nullptr) {
		HuffTreeCodes(head->right, HTCodes += '1', table);
		HTCodes.pop_back();
	}
}

std::string huffman_tree::get_character_code(char character) const {
	if (encodedMap.find(character) != encodedMap.end()) {
		return encodedMap.at(character);
	}
	else {
		return "";
	}
}

std::string huffman_tree::encode(const std::string & file_name) const {
	if (isLeaf(root)) {
		return "1";
	}
	std::string translation;
	char c;
	std::ifstream file(file_name);

	if (file.is_open()) {
		while (true) {
			file.get(c);
			if (file.eof()) {
				break;
			}
			translation += get_character_code(c);
			if (translation == "") {
				return "";
			}
		}
	}
	else {
		return "";
	}
	return translation;
}


std::string huffman_tree::decode(const std::string & string_to_decode) const {
	std::string plainText;
	Node* temp = root;
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
				plainText += temp->letter;
				temp = root;
			}
			else {
				temp = temp->left;
				if (isLeaf(temp)) {
					plainText += temp->letter;
					temp = root;
				}
			}
		}
		else if (string_to_decode[i] == '1') {
			if (isLeaf(temp)) {
				plainText += temp->letter;
				temp = root;
			}
			else {
				temp = temp->right;
				if (isLeaf(temp)) {
					plainText += temp->letter;
					temp = root;
				}
			}
		}
		else {
			return "";
		}
		i++;
	}
	return plainText;
}