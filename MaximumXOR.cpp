// * https://www.codingninjas.com/codestudio/problems/maximum-xor_973113?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos
/*
? Parent Problem :- Given a array of numbers & find the maximum value of (array[i] ^ X) ['^' = BITWISE XOR]
:- 1. Insert all the numbers into the trie.
:- 2. Take X and find the maximum value from the trie (trie contains all the numbers in binary format) where (number ^ X) is maximum
*/

struct Node
{
    Node *links[2];
    bool containKey(int bit)
    {
        return (links[bit] != NULL);
    }
    void put(int bit, Node *node)
    {
        links[bit] = node;
    }
    Node *getNext(int bit)
    {
        return links[bit];
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
    void insert(int num)
    {
        Node *node = root;
        for (int i = 31; i >= 0; --i)
        {
            // :- To get the ith position bit of a number
            int bit = (num >> i) & 1;
            if (!node->containKey(bit))
                node->put(bit, new Node());
            node = node->getNext(bit);
        }
    }
    int getMaxValueXOR(int num)
    {
        Node *node = root;
        int maxValue = 0;
        for (int i = 31; i >= 0; --i)
        {
            int bit = (num >> i) & 1;
            // :- If trie stores opposite of bit of ith position then we will set the ith bit on
            if (node->containKey(1 - bit))
            {
                maxValue = maxValue | (1 << i);
                node = node->getNext(1 - bit);
            }
            else
                node = node->getNext(bit);
        }
        return maxValue;
    }
};

int maxXOR(int n, int m, vector<int> &arr1, vector<int> &arr2)
{
    // Write your code here.
    int ans = 0;
    Trie trie;
    for (int num : arr1)
        trie.insert(num);

    for (int X : arr2)
        ans = max(ans, trie.getMaxValueXOR(X));
    return ans;
}
