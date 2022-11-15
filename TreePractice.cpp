// TreePractice.cpp: определяет точку входа для приложения.
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


private:

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
	TreeNode* val = new TreeNode (1);
	Solution object;

	cout << object.findTarget(val, 1) << endl;
	return 0;
}
