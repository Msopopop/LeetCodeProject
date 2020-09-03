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
                head = root;   // �ҵ�head
                pre = root;    // ��pre���г�ʼ��
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
        /*ע�⵽����������Կ������������������̣�
          ���ȱ���ĳ����㣬Ȼ��������Һ��ӣ�Ȼ����������ӡ����������������Ǻ��������*/

        //1.Push����㵽��һ��ջs�С�
        //2.�ӵ�һ��ջs��Pop��һ����㣬������Push���ڶ���ջoutput�С�
        //3.Ȼ��Push�������Ӻ��Һ��ӵ���һ��ջs�С�
        //4.�ظ�����2��3ֱ��ջsΪ�ա�
        //5.��ɺ����н���Ѿ�Push��ջoutput�У��Ұ��պ��������˳���ţ�ֱ��ȫ��Pop�������Ƕ���������������
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
                        //ż���з�ջ2
                        cur = s1.top();
                        if (cur->left)
                            s2.push(cur->left);
                        if (cur->right)
                            s2.push(cur->right);
                        ret1.push_back(s1.top()->val);  //��������������
                        s1.pop();
                    }
                    if (ret1.size()) ans.emplace_back(ret1);
                    while (!s2.empty())
                    {
                        //�����з�ջ1
                        cur = s2.top();
                        if (cur->right)
                            s1.push(cur->right);
                        if (cur->left)
                            s1.push(cur->left);
                        ret1.push_back(s2.top()->val);  //��������������
                        s2.pop();
                    }
                    if (ret2.size()) ans.emplace_back(ret2);
                }
            }
            return ans;
        }
    }
