#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<utility>
#include<experimental/filesystem>
#include"Read_Data.h"//The file "Parsee_Split.h" is already include in "Read_Data.h"

using namespace std;

typedef pair<string, char> PAIR;

int main(int argc, char *argv[])
{
    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);
 
	bool prefix_exist = false;
	bool suffix_exist = false;
	bool suffix_need_flag = false;

	string search_command;
	fstream qr;
	vector<string> command_string;
	
	vector<TrieNode*> trie;
	vector<TrieNode*> ans;
	vector<TrieNode*> temp;

	qr.open("query.txt", ios::in);

	while(getline(qr,search_command)){

		command_string = split(search_command," ");
		
		vector<PAIR> command = search_parse(command_string,suffix_need_flag);

		read_data(data_dir, trie);

		ans = trie;

		for(auto& cmd:command){
			if(cmd.second == 'E'){
				for(auto& tree:ans){
					if(exact_search(tree,cmd.first) == true){
						temp.push_back(tree);
					}
				}
				ans = temp;
				temp.clean();
			}
		}
		break;
	}

	qr.close();
}