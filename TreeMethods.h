#pragma once
#include <algorithm>
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
// TreeMethods
    struct TreeNode {
        int val;
        TreeNode* left, * right = nullptr;
        TreeNode(int x, TreeNode* leftN = nullptr, TreeNode* rightN = nullptr)
            :val(x), left(leftN), right(rightN) {
            ;
        }

    };
    class TreeMethods {     
    public:
        static void deleteTree(TreeNode* node)
        {
            if (!node) return;
            else {
                if (node->left) deleteTree(node->left);
                if (node->right) deleteTree(node->right);
                delete node;
                return;
            }
        }
        
        /**
           递归思想, 对以root为根的(子)树进行查找p和q, 如果root == null || p || q 直接返回root
           表示对于当前树的查找已经完毕, 否则对左右子树进行查找, 根据左右子树的返回值判断:
           1. 左右子树的返回值都不为null, 由于值唯一左右子树的返回值就是p和q, 此时root为LCA
           2. 如果左右子树返回值只有一个不为null, 说明只有p和q存在与左或右子树中, 最先找到的那个节点为LCA
           3. 左右子树返回值均为null, p和q均不在树中, 返回null
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

        // LeetCode 105
        static TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) 
        {
            return buildTreeUtils(std::cbegin(preorder), std::cend(preorder),
                std::begin(inorder), std::cend(inorder));
        }
        static TreeNode* buildTreeUtils(
            std::vector<int>::const_iterator&& L1, decltype(L1)&& R1, 
            decltype(R1)&& L2, decltype(L2)&& R2)
        {
            using std::find;
            using std::next;
            using std::distance;
            if (L2 == R2 || L1 == R1) return nullptr;
            TreeNode* node = new TreeNode(*L1);
            auto newL2 = find(L2, R2, *L1);
            auto newL1 = next(L1, distance(L2, newL2));
            if (newL1 == R1)
            {
                node->left = buildTreeUtils(next(L1), std::move(R1), std::move(L2), std::move(newL2));
                node->right = nullptr;
                return node;
            }
            if (newL2 == R2)
            {
                node->left = buildTreeUtils(next(L1), next(newL1),
                    std::next(L2), std::move(R2));
                node->right = nullptr;
                return node;
            }
            else
            {
                node->left = buildTreeUtils(next(L1), next(newL1),
                    std::move(L2), std::move(newL2));
                node->right = buildTreeUtils(next(newL1), std::move(R1),
                    std::next(newL2), std::move(R2));
                return node;
            }
        }
        
        //中序遍历
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
        // Search for MAX
        static bool isBSTSimple(TreeNode* const root)
        {
            return isBSTBase(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        }
        static bool isBSTBase(TreeNode* const root, int min, int max)
        {
            if (root == nullptr) return true;
            if (root->val <= min || root->val >= max) return false;
            return
                isBSTBase(root->left, min, root->val) &&
                isBSTBase(root->right, root->val, max);
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
        static size_t getKthLevelSize(TreeNode* const root, const size_t K)
        {
            if (root == nullptr || K == 0) return 0;
            if (K == 1) return 1;
            return getKthLevelSize(root->left, K - 1) + getKthLevelSize(root->right, K - 1);

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

        static TreeNode* treeToList(TreeNode* root) {
            if (!root) return nullptr;
            TreeNode* head = nullptr, * pre = nullptr;
            treeToDoublyListCore(root, head, pre);
            head->left = pre;
            pre->right = head;
            return head;
        }
        static void treeToDoublyListCore(TreeNode* root, TreeNode*& head, TreeNode*& pre) {
            if (!root)  return;
            treeToDoublyListCore(root->left, head, pre);
            if (!head) {
                head = root;   // 找到head
                pre = root;    // 对pre进行初始化
            }
            else {
                pre->right = root;
                root->left = pre;
                pre = root;
            }
            treeToDoublyListCore(root->right, head, pre);
        }
    };

    namespace Print {
        using std::stack;
        using std::queue;
        using std::cout;
        static void preOrder(TreeNode* const root)
        {
            
            if (root == nullptr) return;
            cout << root->val;
            preOrder(root->left);
            preOrder(root->right);
        }
        static void preOrderNonRecursive(TreeNode* const root)
        {
            if (root == nullptr) return;
            stack<TreeNode*> stackTree;
            stackTree.push(root);
            while (!stackTree.empty())
            {
                auto node = stackTree.top();
                cout << node->val;
                stackTree.pop();
                if (node->left) stackTree.push(node->left);
                if (node->right) stackTree.push(node->right);
            }
        }
        static void inOrder(TreeNode* const root)
        {
            if (root == nullptr) return;
            preOrder(root->left);
            cout << root->val;
            preOrder(root->right);
        }
        static void inOrderNonRecursive(TreeNode* const root)
        {
            if (root == nullptr) return;
            TreeNode* pRoot = root;
            stack<TreeNode*> stackTree;
            while (pRoot || !stackTree.empty())
            {
                if (pRoot) {
                    stackTree.push(pRoot);
                    pRoot = pRoot->left;
                }
                else
                {
                    pRoot = stackTree.top();
                    cout << pRoot->val;
                    stackTree.pop();
                    pRoot = pRoot->right;
                }
            }
        }
        static void postOrder(TreeNode* const root)
        {
            if (root == nullptr) return;
            preOrder(root->left);
            preOrder(root->right);
            cout << root->val;

        }
        /*注意到后序遍历可以看作是下面遍历的逆过程：
          即先遍历某个结点，然后遍历其右孩子，然后遍历其左孩子。这个过程逆过来就是后序遍历。*/

        //1.Push根结点到第一个栈s中。
        //2.从第一个栈s中Pop出一个结点，并将其Push到第二个栈output中。
        //3.然后Push结点的左孩子和右孩子到第一个栈s中。
        //4.重复过程2和3直到栈s为空。
        //5.完成后，所有结点已经Push到栈output中，且按照后序遍历的顺序存放，直接全部Pop出来即是二叉树后序遍历结果
        static void postOrderNonRecursive(TreeNode* const root)
        {
            if (root == nullptr) return;
            stack<TreeNode*> s, output;
            s.push(root);
            while (!s.empty()) {
                TreeNode* curr = s.top();
                output.push(curr);
                s.pop();
                if (curr->left)
                    s.push(curr->left);
                if (curr->right)
                    s.push(curr->right);
            }

            while (!output.empty()) {
                cout << output.top()->val;
                output.pop();
            }
        }
        static void levelOrder(TreeNode* const root)
        {
            if (root == nullptr) return;
            queue<TreeNode*> queueTree;
            queueTree.push(root);
            while (!queueTree.empty())
            {
                TreeNode* node = queueTree.front();
                queueTree.pop();
                cout << node->val;
                if (node->left) queueTree.push(node->left);
                if (node->right) queueTree.push(node->right);
                // Each Level In One Vector
                /*vector<int> tmp;
                auto len = queueTree.size();
                for (auto i = 0; i < len; i++)
                {
                    TreeNode* node = queueTree.front();
                    queueTree.pop();
                    tmp.push_back(node->val);
                    if xxxxx(left);
                    if xxxx(right);
                }
                ans.push_back(tmp);*/
            }

        }
        using std::vector;
        static void EachLevelOrderBase(TreeNode* const root, size_t depth, vector<vector<int>>& ans)
        {
            if (root == nullptr) return;
            if (depth >= ans.size()) ans.emplace_back(vector<int>{});
            ans[depth].push_back(root->val);
            EachLevelOrderBase(root->left, depth + 1, ans);
            EachLevelOrderBase(root->right, depth + 1, ans);
        }
        static vector<vector<int>> EachLevelOrder(TreeNode* const root)
        {
            vector<vector<int>> ans;
            EachLevelOrderBase(root, 0, ans);
            return ans;
        }
        
        static vector<vector<int>> ZhiOrder(TreeNode* root)
        {
            vector<vector<int>> ans;
            if (!root)
            {
                stack<TreeNode*> s1, s2;
                s1.push(root);
                while (!s1.empty() || !s2.empty())
                {
                    vector<int> ret1, ret2;
                    TreeNode* cur = nullptr;
                    while (!s1.empty())
                    {
                        //偶数行放栈2
                        cur = s1.top();
                        if (cur->left)
                            s2.push(cur->left);
                        if (cur->right)
                            s2.push(cur->right);
                        ret1.push_back(s1.top()->val);  //保存奇数行数据
                        s1.pop();
                    }
                    if (ret1.size()) ans.emplace_back(ret1);
                    while (!s2.empty())
                    {
                        //奇数行放栈1
                        cur = s2.top();
                        if (cur->right)
                            s1.push(cur->right);
                        if (cur->left)
                            s1.push(cur->left);
                        ret1.push_back(s2.top()->val);  //保存奇数行数据
                        s2.pop();
                    }
                    if (ret2.size()) ans.emplace_back(ret2);
                }
            }
            return ans;
        }
    }
