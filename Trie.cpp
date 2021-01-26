#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

struct Node
{
    char ch;
    bool isWordEnd;
    vector<Node> children;
    Node(char c, bool end) : ch(c), isWordEnd(end)
    {
        this->children = {};
    }
};

class Trie
{
private:
    Node *root;

    vector<string> *getChildWords(Node *cur_node, string cur_word, vector<string> *res)
    {
        for (int i = 0; i < cur_node->children.size(); i++)
        {
            if (cur_node->children[i].isWordEnd)
                res->push_back(cur_word + cur_node->children[i].ch);
            res = this->getChildWords(&cur_node->children[i], cur_word + cur_node->children[i].ch, res);
        }
        return res;
    }

public:
    Trie(vector<string> words)
    {
        this->root = new Node('/', false);
        for (int i = 0; i < words.size(); i++)
        {
            cout << "Adding word " << words[i] << endl;
            this->addWord(words[i]);
        }
    }

    void addWord(string w)
    {
        Node *cur = this->root;
        bool cont_flag = false;
        boost::algorithm::to_lower(w);
        for (int i = 0; i < w.length(); i++)
        {
            for (int j = 0; j < cur->children.size(); j++)
            {
                if (w[i] == cur->children[j].ch) // if char in node on layer
                {
                    cur = &cur->children[j]; // switch to that node
                    cont_flag = true;
                    break; // and break to next character
                }
                else if (j > 0 && cur->children[j - 1].ch < w[i] && w[i] < cur->children[j].ch)
                { // Place in a sorted order of the children layer
                    cur->children.insert(cur->children.begin() + j, Node(w[i], false));
                    cur = &cur->children[j];
                    cont_flag = true;
                    break;
                }
            }
            if (cont_flag)
            {
                cont_flag = false;
                continue;
            }
            Node *new_node = new Node(w[i], false);
            cur->children.push_back(*new_node);
            cur = &cur->children[cur->children.size() - 1];
            cout << "Str index: " << i << " Value: " << cur->ch << endl;
        }
        cur->isWordEnd = true;
    }

    vector<string> *matchPartial(string w)
    {
        Node *cur = this->root;
        boost::algorithm::to_lower(w);
        for (int i = 0; i < w.length(); i++)
            for (int j = 0; j < cur->children.size(); j++)
                if (cur->children[j].ch == w[i])
                    cur = &cur->children[j];

        cout << "Getting all words matching with " << w << endl;
        return this->getChildWords(cur, w, new vector<string>());
    }

    bool wordExists(string w)
    {
        cout << "Searching for: " << w << endl;
        Node *cur = this->root;
        bool cont_flag = false;
        boost::algorithm::to_lower(w);
        for (int i = 0; i < w.length(); i++)
        {
            for (int j = 0; j < cur->children.size(); j++)
            {
                if (cur->children[j].ch == w[i])
                {
                    cur = &cur->children[j];
                    cont_flag = true;
                    break;
                }
            }
            if (cont_flag)
            {
                cont_flag = false;
                continue;
            }
            return false;
        }
        if (cur->isWordEnd)
            return true;
        else
            return false;
    }
};

int main(int argc, char const *argv[])
{
    vector<string> word_list = {"bottle", "cattle", "battle", "braptis"};
    Trie trie = Trie(word_list);

    cout << (trie.wordExists("bottle") ? "bottle found" : "bottle NOT found") << endl;
    cout << "printing matches: " << endl;
    vector<string> *matches = trie.matchPartial("b");
    for (int i = 0; i < matches->size(); i++)
        cout << matches->at(i) << endl;

    /* code */
    return 0;
}
