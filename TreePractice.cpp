﻿// TreePractice.cpp: определяет точку входа для приложения.
//

#include "TreePractice.h"

using namespace std;

struct TreeNode
{
	int val;
	TreeNode* left, *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
public:

	vector<vector<int>> pathSum(TreeNode* root, int targetSum) // FindTargetSum
	{
		vector<vector<int>> answer;
		vector<int> path;
		FindSum(root, targetSum, path, answer);
		return answer;
	}
	
	bool hasPathSum(TreeNode* root, int targetSum) // Does Tree has pathsum?
	{
		if (!root) return false;
		if (!root->left && !root->right) return targetSum == root->val;

		bool answer = false;

		if (root->left) answer = hasPathSum(root->left, targetSum - root->val);
		if (root->right) answer = answer || hasPathSum(root->right, targetSum - root->val);

		return answer;
	}

	TreeNode* addOneRow(TreeNode* root, int val, int depth) // AddOneRow in a Tree
	{
		if (depth == 1)
		{
			TreeNode* newNode = new TreeNode(val);
			newNode->left = root;
			return newNode;
		}

		queue<TreeNode*> q;
		q.push(root);
		int count = 0;

		while (!q.empty())
		{
			int treeSize = q.size();

			count++;
			while(treeSize--)
			{
				TreeNode* curr = q.front();
				q.pop();

				if (count != depth - 1)
				{
					if (curr->left) q.push(curr->left);
					if (curr->right) q.push(curr->right);
				}
				else
				{
					TreeNode* newNode = new TreeNode(val);
					newNode->left = curr->left;
					curr->left = newNode;

					TreeNode* newNode2 = new TreeNode(val);
					newNode2->right = curr->right;
					curr->right = newNode2;
				}
			}
		}

		return root;
	}

	bool findTarget(TreeNode* root, int k) // two sum elements return target k
	{
		if (!root)
		{
			return false;
		}

		if (!root->left && !root->right)
		{
			int target = root->val;
			DelTree(root);
			return k == target;
		}

		bool answer = false;

		vector<int> rootValues = CollectTreeResult(root);

		sort(rootValues.begin(), rootValues.end());

		int low = 0;
		int high = rootValues.size() - 1;

		while (low < high)
		{
			// sum found
			if (rootValues[low] + rootValues[high] == k)
			{
				return true;
			}

			rootValues[low] + rootValues[high] < k ? low++ : high--;
		}

	}

	int countNodes(TreeNode* root) // CountAllNodes
	{
		if (!root)
		{
			return 0;
		}

		int count = 0;

		CountNodes(root, count);

		return count;

	}

	TreeNode* invertTree(TreeNode* root) // InvertBinaryTree
	{
		if (!root) return root;

		TreeNode* temp = root->left;
		root->left = root->right;
		root->right = temp;

		invertTree(root->left);
		invertTree(root->right);

		return root;
	}

	TreeNode* invertTreeIterative(TreeNode* root)
	{
		if (!root) return root;

		stack<TreeNode*> data;
		data.push(root);

		while (!data.empty())
		{
			TreeNode* node = data.top();
			data.pop();

			if (node)
			{
				data.push(node->left);
				data.push(node->right);

				TreeNode* temp = node->left;
				node->left = node->right;
				node->right = temp;
			}
		}

		return root;
	}

	int rangeSumBST(TreeNode* root, int low, int high) // sum of values of all nodes [low, high]
	{
		int resultSum = 0;
		IterateThrough(root, resultSum, low, high);

		return resultSum;
	}

	bool leafSimilar(TreeNode* root1, TreeNode* root2)
	{
		vector<int> leaves_1;
		vector<int> leaves_2;

		FindLeaves(root1, leaves_1);
		FindLeaves(root2, leaves_2);

		for (const auto& x : leaves_1)
		{
			cout << x << ' ';
		}

		cout << endl;

		for (const auto& x : leaves_2)
		{
			cout << x << ' ';
		}

		cout << endl;

		return equal(leaves_1.begin(), leaves_1.end(), leaves_2.begin(), leaves_2.end());
	}


private:

	void FindLeaves(TreeNode* root, vector<int>& leaves)
	{
		if (!root) return;

		if (!root->left && !root->right)
		{
			leaves.push_back(root->val);
		}

		if (root->left) FindLeaves(root->left, leaves);
		if (root->right) FindLeaves(root->right, leaves);
	}

	void IterateThrough(TreeNode* root, int& resultSum, int low, int high)
	{
		if (!root) return;

		if (root->val >= low && root->val <= high)
		{
			resultSum += root->val;
		}

		if(root->val > low)
		{
			if (root->left) IterateThrough(root->left, resultSum, low, high);
		}

		if (root->val < high)
		{
			if (root->right) IterateThrough(root->right, resultSum, low, high);
		}
	}

	void FindSum(TreeNode* root, int targetSum, vector<int>& path, vector<vector<int>>& answer) // FindTargetSum
	{
		if (!root) return;
		path.push_back(root->val);

		if (!root->left && !root->right && root->val == targetSum)
		{
			answer.push_back(path);
		}

		if (root->left) FindSum(root->left, targetSum - root->val, path, answer);
		if (root->right) FindSum(root->right, targetSum - root->val, path, answer);
		path.pop_back();
	}

	int FindDepth(TreeNode* root)
	{
		if (!root)
		{
			return 0;
		}

		int lDepth = FindDepth(root->left);
		int rDepth = FindDepth(root->right);

		return max(lDepth, rDepth) + 1;
	}

	void DelTree(const TreeNode* root)
	{
		if (root)
		{
			DelTree(root->left);
			DelTree(root->right);
			delete root;
		}
	}

	void CollectTree(TreeNode* root, vector<int>& store)
	{
		if (!root) return;
		store.push_back(root->val);

		if (root->left) CollectTree(root->left, store);
		if (root->right) CollectTree(root->right, store);
	}

	void CountNodes(TreeNode* root, int& count)
	{
		if (!root) return;
		++count;

		if (root->left) CountNodes(root->left, count);
		if (root->right) CountNodes(root->right, count);
	}

	vector<int> CollectTreeResult(TreeNode* root)
	{
		vector<int> result;
		CollectTree(root, result);

		return result;
	}

};


int main()
{
	TreeNode* root1 = new TreeNode(1);
	root1->left = new TreeNode(2);
	root1->right = new TreeNode(3);

	TreeNode* root2 = new TreeNode(1);
	root2->left = new TreeNode(3);
	root2->right = new TreeNode(2);

	Solution object;

	object.leafSimilar(root1, root2);

	return 0;
}
