#include<string>
#include<cstring>
#include<vector>
#include<iostream>
#include<list>
#include<cctype>

using namespace std;

struct TrieNode
{
    string edge;
    TrieNode* child[26];
    bool word_end;//Once in the file, there is a word end exactly at here, it will be true.
};

TrieNode* createNode(string str){
    TrieNode* temp = new TrieNode;
    temp->edge = str;
    for(int i = 0; i<26; i++) temp->child[i] = NULL;
    temp->word_end = false;
    return temp;
}

void create_Prefix_Tree(TrieNode* h, string word,int level)
{
    int idx = toupper(word[level])- 'A';
    if( h->child[idx] == NULL )
    {
        h->child[idx] = createNode(word.substr(0,level));
    }

    if( level == word.length() - 1 ){
        h->child[idx]->word_end = true;
        return;
    }
    create_Prefix_Tree(h->child[idx], word, level + 1);
    return;
}

void create_Suffix_Tree(TrieNode* h, string word,int level)
{
    int idx = toupper(word[word.length() - level - 1])- 'A';
    if( h->child[idx] == NULL )
    {
        h->child[idx] = createNode(word.substr(0,level));
    }

    if( level == word.length() - 1 ){
        h->child[idx]->word_end = true;
        return;
    }
    create_Suffix_Tree(h->child[idx], word, level + 1);
    return;
}

bool trie_search(TrieNode* h, string target, char signal){
    TrieNode* node = h;
    int idx;
    for(int i = 0; i < target.length(); i++){
        if( signal == 'S' ) idx = toupper(target[target.length() - i - 1])- 'A';
        else idx = toupper(target[i])- 'A';
        
        if(node->child[idx] != NULL){
            node = node->child[idx];
            if( i == target.length() - 1 && signal == 'E' ) return node->word_end == true;
            else if( i == target.length() - 1 && signal != 'E' ) return true;  
        }else{
            break;
        }
    }
    return false;
}