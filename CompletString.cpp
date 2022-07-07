// *Link https://www.codingninjas.com/codestudio/problems/complete-string_2687860?leftPanelTab=1

struct Node
{
    Node *links[26];
    bool flag = false;
    bool containKey(char ch)
    {
        return links[ch - 'a'] != NULL;
    }
    void put(char ch, Node *node)
    {
        links[ch - 'a'] = node;
    }
    Node *getNext(char ch)
    {
        return links[ch - 'a'];
    }
    void setEnd()
    {
        flag = true;
    }
    bool isEnd()
    {
        return flag;
    }
};

class Trie
{
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    void insert(string word)
    {
        Node *node = root;
        for (int i = 0; i < word.length(); i++)
        {
            if (!node->containKey(word[i]))
                node->put(word[i], new Node());
            node = node->getNext(word[i]);
        }
        node->setEnd();
    }
    bool startsWith(string prefix)
    {
        Node *node = root;
        for (int i = 0; i < prefix.length(); i++)
        {
            if (!node->containKey(prefix[i]))
                return false;
            node = node->getNext(prefix[i]);
        }
        return true && node->isEnd();
    }
};

string completeString(int n, vector<string> &a)
{
    // Write your code here.
    Trie trie;
    for (string word : a)
        trie.insert(word);

    string ans = "";
    for (string word : a)
    {
        bool completeString = true;
        for (int i = 0; i < word.size(); i++)
        {
            if (!trie.startsWith(word.substr(0, i + 1)))
            {
                completeString = false;
                break;
            }
        }
        if (completeString)
        {
            if ((ans.size() < word.length()) || (ans.size() == word.length() && ans > word))
                ans = word;
        }
    }
    if (ans == "")
        return "None";
    return ans;
}
