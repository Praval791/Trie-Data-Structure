// * https://www.codingninjas.com/codestudio/problems/count-distinct-substrings_985292?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos

struct Node
{
    Node *links[26];
    bool containKey(char ch)
    {
        return links[ch - 'a'] != NULL;
    }
    Node *getNext(char ch)
    {
        return links[ch - 'a'];
    }
    void put(char ch, Node *node)
    {
        links[ch - 'a'] = node;
    }
};

int countDistinctSubstrings(string &s)
{
    int countDS = 1; // 1 for empty string
    Node *root = new Node();
    for (int i = 0; i < s.length(); i++)
    {
        Node *node = root;
        for (int j = i; j < s.length(); j++)
        {
            if (!node->containKey(s[j]))
            {
                countDS++;
                node->put(s[j], new Node());
            }
            node = node->getNext(s[j]);
        }
    }
    return countDS;
}
