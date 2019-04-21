#include "huffman_tree.h"



/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Reads the contents of file_name and constructs a
				huffman tree based on the character frequencies of the file contents
*/
huffman_tree::huffman_tree(const std::string& file_name) {

	fstream myFile(file_name);
	char c = NULL;
	//char letter;
	int counter = 0;
	vector<char> myVector;
	unordered_map <char, int> myMap;
	priority_queue<node*, vector<node*>, compare> pq;
	int yes = 0;

	//int n = myFile.tellg();

	if (myFile.is_open()) {
		while (true) {
			myFile.get(c);
			if (myFile.eof()) {
				break;
			}
			if (myMap.count(c) > 0) {
				myMap[c]++;
			}
			if (myFile.eof()) {
				break;
			}
			else {
				std::pair<char, int> tempPair(c, 1);
				myMap.insert(tempPair);
			}
		}
	}
	myFile.close();

	auto it = myMap.begin();

	for (it; it != myMap.end(); it++) {
		pq.push(nodeNew(it->first, it->second));
	}

	node* temp1 = new node();
	node* temp2 = new node();

	while (true) {

		temp1 = pq.top();
		//cout << temp1->character << endl;
		//cout << temp1->freq << endl;
		pq.pop();
		temp2 = pq.top();
		pq.pop();
		//cout << temp2->character << endl;
		//cout << temp2->freq << endl;
		int sum = temp1->freq + temp2->freq;
		//cout << sum << endl;
		//cout << "____________________________" << endl;
		pq.push(parentNode(sum, temp1, temp2));

		if (pq.size() == 1) {
			break;
		}
	}
	root = pq.top();

	//recursive function to make maps
	recursive(root, "");
}


huffman_tree::~huffman_tree() {

}

/*
Preconditions: Character is a character with an ASCII value
				between 0 and 127 (inclusive).
Postconditions: Returns the Huffman code for character if character is in the tree
				and an empty string otherwise.
*/

void huffman_tree::recursive(node* rroot, string s) {
	if (!rroot) {
		return;
	}
	if (root->right == nullptr && root->left == nullptr) {
		std::pair<char, string> epair(root->character, "0");
		std::pair<string, char> dpair("0", root->character);
		encodeMap.insert(epair);
		decodeMap.insert(dpair);
		return;
	}
	if (rroot->right == nullptr && rroot->left == nullptr) {
		std::pair<char, string> epair(rroot->character, s);
		std::pair<string, char> dpair(s, rroot->character);
		encodeMap.insert(epair);
		decodeMap.insert(dpair);
	}
	recursive(rroot->left, s += '0');
	recursive(rroot->right, s += '1');
}


std::string huffman_tree::get_character_code(char character) const {
	
	if (encodeMap.find(character) == encodeMap.end()) {
		return "";
	}
	else {
		cout << encodeMap.find(character)->second<<endl;
		return encodeMap.find(character)->second;
	}

	//return "";
}



/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Returns the Huffman encoding for the contents of file_name
				if file name exists and an empty string otherwise.
				If the file contains letters not present in the huffman_tree,
				return an empty string
*/
std::string huffman_tree::encode(const std::string& file_name) const {
	string coded;
	char c;
	fstream file_to_decode(file_name);

	while (file_to_decode.get(c)) {
		
		if (encodeMap.find(c) == encodeMap.end()) {
			return "";
		}

		else {
			coded += encodeMap.find(c)->second;
		}
	}
	//cout << coded<<endl;
	return coded;
}

/*
Preconditions: string_to_decode is a string containing Huffman-encoded text
Postconditions: Returns the plaintext represented by the string if the string
				is a valid Huffman encoding and an empty string otherwise
*/
std::string huffman_tree::decode(const std::string& string_to_decode) const {
	vector<string> dv;
	node* iter = root; //helpppp
	char c;
	string decoded;

	int i = 0;
	int n = string_to_decode.size();
	while(true) {
		if (iter->right == nullptr && iter->left == nullptr) {
			c = iter->character;
			string s(1, c);
			dv.insert(dv.end(), s);
			iter = root;
			if (n == 0) {
				break;
			}
		}
		if (string_to_decode[i] == '0') {			
			iter = iter->left;
		}
		if (string_to_decode[i] == '1') {
			iter = iter->right;
		}
		i++;
		n--;
	}
	//string vector to string
	for (auto const& s : dv) {
		decoded += s;
	}
	//cout << decoded<<endl;
	return decoded;
	//return "";
}
