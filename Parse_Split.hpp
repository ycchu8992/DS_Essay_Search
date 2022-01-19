#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<utility>

using namespace std;

typedef pair<string, char> PAIR;

vector<string> word_parse(vector<string> tmp_string){
	vector<string> parse_string;
	for(auto& word : tmp_string){
		string new_str;
    	for(auto &ch : word){
			if(isalpha(ch))
				new_str.push_back(ch);
		}
		parse_string.emplace_back(new_str);
	}
	return parse_string;
}

vector<PAIR> search_parse(vector<string> tmp_string,bool& flag){
	vector<PAIR> parse_string;
	char signal = 'P';
	for(auto& word : tmp_string){
		string new_str;
		PAIR p;
		signal = 'P'; 
    	for(auto &ch : word){
			if(isalpha(ch))
				new_str.push_back(ch);
			else if(ch == '\"'){
				signal = 'E';
			}
			else if(ch == '*'){
				signal = 'S';
				flag = true;
			}
			else if(ch == '+'){
				new_str.push_back(ch);
				signal = 'X';
			}
			else if(ch == '/'){
				new_str.push_back(ch);
				signal = 'X';
			}
		}
		p = make_pair(new_str,signal);
		parse_string.emplace_back(p);
	}
	return parse_string;
}

vector<string> split(const string& str, const string& delim) {
	vector<string> res;
	if("" == str) return res;
	char * strs = new char[str.length() + 1] ;
	strcpy(strs, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char *p = strtok(strs, d);
	while(p) {
		string s = p;
		res.push_back(s);
		p = strtok(NULL, d);
	}
	return res;
}