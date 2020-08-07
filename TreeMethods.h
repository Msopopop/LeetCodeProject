#pragma once
#include <algorithm>
#include <queue>
#include <stack>
// TreeMethods
class TreeMethods {
private:
    struct TreeNode {
        int val;
        TreeNode* left, * right = nullptr;
        TreeNode(int x, TreeNode* leftN = nullptr, TreeNode* rightN = nullptr)
            :val(x), left(leftN), right(rightN) {
            ;
        }
    };
public:
    /**
       �ݹ�˼��, ����rootΪ����(��)�����в���p��q, ���root == null || p || q ֱ�ӷ���root
       ��ʾ���ڵ�ǰ���Ĳ����Ѿ����, ����������������в���, �������������ķ���ֵ�ж�:
       1. ���������ķ���ֵ����Ϊnull, ����ֵΨһ���������ķ���ֵ����p��q, ��ʱrootΪLCA
       2. ���������������ֵֻ��һ����Ϊnull, ˵��ֻ��p��q�����������������, �����ҵ����Ǹ��ڵ�ΪLCA
       3. ������������ֵ��Ϊnull, p��q����������, ����null
       **/
    static TreeNode* lowestCommonAncestor(TreeNode* const root, TreeNode* const p, TreeNode* const q)
    {
        if (root == nullptr || root == q || root == p) return root;
        auto left = lowestCommonAncestor(root->left, p, q);
        auto right = lowestCommonAncestor(root->right, p, q);
        if (left == nullptr || right == nullptr) return nullptr;
        else if (left && right) return root;
        else return left == nullptr ? right : left;
    }
    //�������
    static bool isBSTree(TreeNode* const root)
    {
        TreeNode* pre = nullptr;
        if (root)
        {
            if (!isBSTree(root->left)) return false;
            if (pre && root->val <= pre->val) return false;
            pre = root;
            return isBSTree(root->right);
        }
    }
    static size_t getSize(TreeNode* const root)
    {
        if (root == nullptr) return 0;
        return getSize(root->left) + getSize(root->right) + 1;
    }

    static size_t getLeafSize(TreeNode* const root)
    {
        if (root == nullptr) return 0;
        if (!(root->left && root->right)) return 1;
        return getLeafSize(root->left) + getSize(root->right);
    }
    static size_t getHeight(TreeNode* const root)
    {
        if (root == nullptr) return 0;
        return std::max(getHeight(root->left), getHeight(root->right)) + 1;
    }
    static size_t getKthLevelLeafSize(TreeNode* const root, const size_t K)
    {
        if (root == nullptr || K == 0) return 0;
        if (K == 1) return 1;
        return getKthLevelLeafSize(root->left, K - 1) + getKthLevelLeafSize(root->right, K - 1);

        // non-recursive method
        /*
        auto pRoot = root;
        if (root == nullptr || K == 0) return 0;
        std::queue<TreeNode*> treeQueue;
        treeQueue.push(root);
        size_t curLevelNodeCount = 0, curLevel = 0;
        while (!treeQueue.empty())
        {
            ++curLevel;
            curLevelNodeCount = treeQueue.size();
            if (curLevel == K) break;
            size_t cntNode = 0;
            while (cntNode < curLevelNodeCount)
            {
                ++cntNode;
                pRoot = treeQueue.front();
                treeQueue.pop();
                if (pRoot->left) treeQueue.push(pRoot->left);
                if (pRoot->right) treeQueue.push(pRoot->right);
            }

        }
        while (!treeQueue.empty()) treeQueue.pop();
        if (curLevel == K) return curLevelNodeCount;
        return 0; // K > height(root)
        */
    }
    static size_t getKthLevelLeafSize(TreeNode* const root, const size_t K)
    {
        if (root == nullptr || K == 0) return 0;
        if (K == 1 && root->left == nullptr && root->right == nullptr) return 1;
        else return 0;
        return getKthLevelLeafSize(root->left, K - 1) + getKthLevelLeafSize(root->right, K - 1);

        // non-recursive method
        //auto pRoot = root;
        //if (root == nullptr || K == 0) return 0;
        //std::queue<TreeNode*> treeQueue;
        //treeQueue.push(root);
        //size_t curLevelNodeCount = 0, curLevel = 0;
        //while (!treeQueue.empty())
        //{
        //    ++curLevel;
        //    curLevelNodeCount = treeQueue.size();
        //    if (curLevel == K) break;
        //    size_t cntNode = 0;
        //    while (cntNode < curLevelNodeCount)
        //    {
        //        ++cntNode;
        //        pRoot = treeQueue.front();
        //        treeQueue.pop();
        //        if (pRoot->left) treeQueue.push(pRoot->left);
        //        if (pRoot->right) treeQueue.push(pRoot->right);
        //    }

        //}
        //while (!treeQueue.empty()) treeQueue.pop();
        //if (curLevel == K) {
        //    size_t cntNode = 0;
        //    size_t leafCount = 0;
        //    while (cntNode < curLevelNodeCount) {
        //        ++cntNode;
        //        pRoot = treeQueue.front();
        //        treeQueue.pop();

        //        if (pRoot->left == nullptr && pRoot->right == nullptr) leafCount++;
        //    }
        //    return leafCount;
        //}
        //return 0; // K > height(root)
    }
    static size_t getMaxDistance(TreeNode* const root)
    {
        size_t ans = 0;
        depth(root, ans);
        return ans;
    }
    static size_t depth(TreeNode* const root, size_t& maxD)
    {
        if (root == nullptr) return 0;
        size_t leftD = depth(root->left, maxD);
        size_t rightD = depth(root->right, maxD);
        maxD = std::max(maxD, leftD + rightD);
        return leftD + rightD;
    }
};
