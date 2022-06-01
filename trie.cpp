#include <iostream>
#include "array_list.h"
#include <string>
using namespace std;
class Trie {
public:
	bool isLeaf;
	Trie* children[128];
	string value;
	Trie() {
		this->isLeaf = false;
		for (int i = 0; i < 128; i++) {
			this->children[i] = NULL;
		}
	}

	void insert(string key, string value);
	string search(string key);
	array_list<string> print_with_prefixes(string& prefix);
	void traverse(Trie* root, array_list<string>& res);
};

void Trie::insert(string key, string value) {
	Trie* curr = this;
	for (int i = 0; i < key.length(); ++i) {
		if (curr->children[key[i]] == nullptr) curr->children[key[i]] = new Trie();
		curr = curr->children[key[i]];
	}
	curr->value = value;
	curr->isLeaf = true;
}

string Trie::search(string key)
{
	Trie* curr = this;
	for (int i = 0; i < key.length(); ++i) {
		curr = curr->children[key[i]];
		if (curr == nullptr) return "-";
	}
	if (!isLeaf) return "-";
	return curr->value;
}

void Trie::traverse(Trie* root, array_list<string>& res) {
	if (root == nullptr)
		return;
	if (root->isLeaf) res.push_back(root->value);
	for (int i = 0; i < 128; ++i) {
		traverse(root->children[i], res);
	}
}

array_list<string> Trie::print_with_prefixes(string& prefix) {
	Trie* curr = this;
	for (int i = 0; i < prefix.length(); ++i) {
		curr = curr->children[prefix[i]];
		if (curr == nullptr) return array_list<string>();
	}
	array_list<string> res;
	traverse(curr, res);
	return res;
}

int main()
{
	Trie* root = new Trie();
	
    while (true) {
        char c;
        std::cin >> c;
        if (c == '+') {
			string key, val;
			cin >> key >> val;
			root->insert(key, val);
        }
		else if (c == '?') {
			string key;
			cin >> key;
			cout << root->search(key) << endl;
		}
		else if (c == '*') {
			string key;
			cin >> key;
			for (auto& e : root->print_with_prefixes(key))
				cout << e << endl;
		}
    }
}
