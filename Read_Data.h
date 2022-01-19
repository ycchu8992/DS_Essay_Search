#include<fstream>
#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<experimental/filesystem>
#include<list>
#include<utility>
#include"Parse_Split.h"
#include"Trie.h"

using namespace std;

namespace fs = experimental::filesystem;

typedef pair<bool, pair<TrieNode*,TrieNode*>> data_pair;

bool cmp (const string& str1, const string& str2)
{
  unsigned int i = 0;
  if(str1.length() !=  str2.length() ) return ( str1.length() < str2.length() );
  while ( ( i < str1.length() ) && ( i < str2.length()) )
  {
    if (tolower(str1[i])<tolower(str2[i])) return true;
    else if (tolower(str1[i])>tolower(str2[i])) return false;    
    ++i;
  }
}

void read_data(string data_dir, vector<data_pair>& trie_tree)
{

    list<string> path_container;
    
    for(auto& path : fs::directory_iterator(data_dir)) path_container.push_back(path.path().string());
    
    path_container.sort(cmp);

    string file, title_name, tmp;
	fstream fi;
	vector<string> tmp_string;

    for(auto& file_name: path_container)
    {

        fi.open(file_name, ios::in);

        getline(fi, title_name);

        tmp_string = split(title_name, " ");

        vector<string> title = word_parse(tmp_string);

        TrieNode* head_trie = createNode(title_name);

        TrieNode* head_suffix = createNode(title_name);

        for(auto &word : title){

            if(word == "") continue;

            create_Prefix_Tree(head_trie,word,0);

            create_Suffix_Tree(head_suffix,word,0);

        }

        while(getline(fi, tmp))
        {

            tmp_string = split(tmp, " ");

            vector<string> content = word_parse(tmp_string);

            for(auto &word : content){
                
                if(word == "") continue;

                create_Prefix_Tree(head_trie,word,0);

                create_Suffix_Tree(head_suffix,word,0);

            }

	    }

        data_pair p = make_pair(true,make_pair(head_trie,head_suffix));

        fi.close();

        trie_tree.push_back(p);

    }

}