// * https://www.codingninjas.com/codestudio/problems/max-xor-queries_1382020

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

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries)
{
    int n = arr.size();
    int q = queries.size();
    vector<int> result(q);
    Trie trie;

    // :- Insert the index so that we can maintain the order of queries in answer
    for (int i = 0; i < q; ++i)
        queries[i].push_back(i);

    // :- Sort the queries by the v[1] or ai.
    sort(queries.begin(), queries.end(), [](const vector<int> &v1, const vector<int> &v2)
         { return v1[1] < v2[1]; });

    // :- Sort the array to make our comparision easy because we want to store the values in trie that are only smaller & equal than ai
    sort(arr.begin(), arr.end());

    int indForAr = 0;
    for (int i = 0; i < q; ++i)
    {
        int ai = queries[i][1];
        int xi = queries[i][0];
        int indexForMaintainOrder = queries[i][2];

        while (indForAr < n && arr[indForAr] <= ai)
            trie.insert(arr[indForAr++]);

        if (indForAr == 0)
            result[indexForMaintainOrder] = -1;
        else
            result[indexForMaintainOrder] = trie.getMaxValueXOR(xi);
    }
    return result;
}
