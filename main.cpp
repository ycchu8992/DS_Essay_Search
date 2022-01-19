#define FILE_EXTENSION ".txt"
#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<utility>
#include<experimental/filesystem>
#include"Read_Data.hpp"//The file "Parsee_Split.h" is already include in "Read_Data.h"

using namespace std;

typedef pair<string, char> PAIR;

typedef pair<bool, pair<TrieNode*,TrieNode*>> data_pair;

int main(int argc, char *argv[])
{
    string data_dir = argv[1] + string("/");
	string query = string(argv[2]);
	string output = string(argv[3]);

	string search_command;
	fstream qr;
	vector<string> command_string;
	
	vector<data_pair> trie_tree;

	vector<string> outputstring;

	read_data(data_dir, trie_tree);

	qr.open(query, ios::in);

	bool suffix_need_flag = false;

	while(getline(qr,search_command)){

		command_string = split(search_command," ");
		
		vector<PAIR> command = search_parse(command_string,suffix_need_flag);

		vector<data_pair>::iterator iter;

		int mode = 1;

		for(auto& cmd:command){
			if( ( cmd.second == 'E'|| cmd.second == 'P' ) && mode == 1 ){
				for(iter = trie_tree.begin(); iter != trie_tree.end();iter++){
					if( iter->first == false ) continue; 
					if(trie_search(iter->second.first,cmd.first,cmd.second) == false){
						iter->first = false;
					}
				}
			}else if( ( cmd.second == 'E'|| cmd.second == 'P' ) && mode == 2 ){
				for(iter = trie_tree.begin(); iter != trie_tree.end();iter++){
					if( iter->first == true ) continue;
					if(trie_search(iter->second.first,cmd.first,cmd.second) == true){
						iter->first = true;
					}
				}
				mode = 1;
			}else if( cmd.second == 'S' && mode == 1 ){
				for(iter = trie_tree.begin(); iter != trie_tree.end();iter++){
					if( iter->first == false ) continue; 
					if(trie_search(iter->second.second,cmd.first,cmd.second) == false){
						iter->first = false;
					}
				}
			}else if( cmd.second == 'S' && mode == 2 ){
				for(iter = trie_tree.begin(); iter != trie_tree.end();iter++){
					if( iter->first == true ) continue;
					if(trie_search(iter->second.second,cmd.first,cmd.second) == true){
						iter->first = true;
					}
				}
				mode = 1;
			}
			else if(cmd.second == 'X' && cmd.first == "+") continue;
			else if(cmd.second == 'X' && cmd.first == "/") mode = 2;
		}

		
		bool is_not_found = true;

		for(auto& ans:trie_tree){
			if( ans.first == true ){
				outputstring.push_back(ans.second.first->edge);
				is_not_found = false;
			}
			else{
				ans.first = true;
			}
		}

		if( is_not_found == true ){
			outputstring.push_back("Not Found!");
		}
		
		//outputstring.push_back("\n");

	}

	qr.close();

	fstream out_put;

	out_put.open(output, ios::out);

	for(auto& word:outputstring){
		out_put << word <<'\n';
	}

	out_put.close();
}