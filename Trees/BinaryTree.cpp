//Contains all the important questions for Binary Trees
#include <bits/stdc++.h>
using namespace std;

class TreeNode
{
public:
    int val = 0;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val)
    {
        this->val = val;
    }
};

//height of a BT in terms of edges
int height(TreeNode *root)
{
    return (root == NULL ? -1 : max(height(root->left), height(root->right)) + 1);
}

//Find a node in a BT

bool find(TreeNode *root, int data)
{

    if (root == NULL)
        return false;

    if (root->val == data)
        return true;

    bool res = find(root->left, data) || find(root->right, data);

    return res;
}

// Node to root path in a BT
bool nodeToRootPath_(TreeNode *root, int data, vector<TreeNode *> &ans)
{

    if (root == nullptr)
        return false;

    if (root->val == data)
    {
        ans.push_back(root);
        return true;
    }

    bool res = nodeToRootPath_(root->left, data, ans) || nodeToRootPath_(root->right, data, ans);

    if (res)
        ans.push_back(root);
    return res;
}

vector<TreeNode *> nodeToRootPath_(TreeNode *root, int data)
{
    if (root == nullptr)
    {
        return {};
    }

    if (root->val == data)
    {
        return {root};
    }

    vector<TreeNode *> left = nodeToRootPath_(root->left, data);
    if (left.size() != 0)
    {
        left.push_back(root);
        return left;
    }

    vector<TreeNode *> right = nodeToRootPath_(root->right, data);
    if (right.size() != 0)
    {
        right.push_back(root);
        return right;
    }

    return {};
}

vector<TreeNode *> nodeToRootPath(TreeNode *root, int data)
{
    return nodeToRootPath_(root, data);
}

// All Nodes at Distance K from a given Node using the block method
bool roottoNodePath(TreeNode *root, TreeNode *target, vector<TreeNode *> &temp)
{
    if (root == nullptr)
    {
        return false;
    }
    if (root == target)
    {
        temp.push_back(root);
        return true;
    }
    bool ans = roottoNodePath(root->left, target, temp) || roottoNodePath(root->right, target, temp);
    if (ans)
    {
        temp.push_back(root);
    }
    return ans;
}
void printKdown(TreeNode *target, int depth, TreeNode *block, vector<int> &ans)
{
    if (target == NULL || depth < 0 || target == block)
    {
        return;
    }
    if (depth == 0)
    {
        ans.push_back(target->val);
        return;
    }
    printKdown(target->left, depth - 1, block, ans);
    printKdown(target->right, depth - 1, block, ans);
}
vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
{
    vector<int> ans;
    vector<TreeNode *> temp;

    roottoNodePath(root, target, temp);
    for (auto it : temp)
    {
        cout << it->val << " ";
    }
    TreeNode *blockNode = NULL;
    for (int i = 0; i < temp.size(); i++)
    {
        printKdown(temp[i], k - i, blockNode, ans);
        blockNode = temp[i];
    }

    return ans;
}
//Reducing space in the above method
int distanceK(TreeNode *root, TreeNode *block, int target, int k, vector<int> &ans)
{
    if (root == NULL)
        return -1;

    if (root->val == target)
    {
        printKdown(root, k, NULL, ans);
        return 1;
    }

    int ld = distanceK(root->left, root, target, k, ans);
    if (ld != -1)
    {
        printKdown(root->left, k - ld, root, ans);
        return ld + 1;
    }

    int rd = distanceK(root->right, root, target, k, ans);
    if (rd != -1)
    {
        printKdown(root->right, k - rd, root, ans);
        return rd + 1;
    }

    return -1;
}
int main()
{
}
