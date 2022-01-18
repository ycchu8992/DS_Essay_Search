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

void addtotree(TrieNode* h, string word,int level)
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
    addtotree(h->child[idx], word, level + 1);
    return;
}