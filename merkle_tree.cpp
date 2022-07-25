#include<iostream>
#include<cmath>
#include<string>
#include"sha_256.h"
using namespace std;
//判断层数
int level_num(int n)
{
	int llnum = 0;
	while (n > 1)
	{
		n = (n + 1) / 2;
		llnum += 1;
	}
	return (llnum + 1);
}
//层序创建遍历merkle树
struct MerNode
{
	string hash;//结点储存的hash值
	struct MerNode* lchild, * rchild;
};
class MerTree
{
public:
	MerNode* root;//根结点
	MerTree()//默认构造函数
	{
		root = NULL;
	}
	MerNode* Root()//返回根结点
	{
		return root;
	}
	MerNode* Parent(MerNode* current);//返回当前结点的父结点
	MerNode* LChild(MerNode* current);//当前结点的左孩子
	MerNode* RChild(MerNode* current);//当前结点的右孩子
	void createMerTree(int n,int num_le_node[],string str[]);//层次遍历创建
	void LevelOrder(MerNode* hoot);//层次遍历给定merkle树
	void createNode(MerNode* current, string str[],int count,int num_le_node[],int i);
	int getheight;//树的层数
};
void MerTree::createNode(MerNode* current, string str[],int count,int num_le_node[],int i)
{
	int nn = count;
	current->hash = str[count-1];
	int ii = i + 1;
	while (count != 0)
	{
		if (num_le_node[ii] % 2 == 0)
		{
			createNode(current->rchild, str, nn - num_le_node[getheight - i - 2], num_le_node, ii);
			createNode(current->lchild, str, nn - num_le_node[getheight - i - 2] + 1, num_le_node, ii);
			count -= 2;
		}
		else
		{
			createNode(current->rchild, str, nn - num_le_node[getheight - i - 2], num_le_node, ii);
			count -= 1;
		}
	}
}
MerNode* MerTree::LChild(MerNode* current)//当前结点的左孩子
{
	return current->lchild;
}
MerNode* MerTree::RChild(MerNode* current)//当前结点的右孩子
{
	return current->rchild;
}
//层次遍历创建,n是结点总数
void MerTree::createMerTree(int n,int num_le_node[],string str[])
{
	getheight = level_num(n);//树的层数
	//填好根结点及根结点的孩子那一层
	createNode(root, str, n,num_le_node,0);
	//root->hash = str[count];
	//root->parent = NULL;
	/*if (num_le_node[getheight - 1] % 2 == 0)//下一层有2个结点
	{
		int num_right = count - num_le_node[getheight - 1];//右孩子序号
		root->rchild->hash = str[num_right];
		root->lchild->hash = str[num_right + 1];
		count -= 2;
	}
	else//下一层只有一个结点
	{
		int num_right = count - num_le_node[getheight - 1];//右孩子序号
		root->rchild->hash = str[num_right];
		root->lchild = NULL;
		count -= 1;
	}*/
	//MerNode* temp = root;
	/*for (int i = 0; i < (getheight - 1); i++)//填每层的
	{
		for (int j = 0; j < num_le_node[getheight - i - 1]; j++)
		{
			//层数判断，判断该层是奇数or偶数
			if (num_le_node[getheight - i - 2] % 2 == 0)//偶数,说明左右孩子都有
			{
				int num_right = count - num_le_node[getheight - i - 2];
				createNode(RChild(temp), str[num_right]);
				createNode(LChild(temp), str[num_right + 1]);
				count -= 2;
				temp = temp->rchild;
			}
			else
			{
				int num_right = count - num_le_node[getheight - i - 1];
				createNode(RChild(temp), str[num_right]);
				count -= 1;
				temp = temp->rchild;
			}
		}
	}
	int i = 0;
		i += 1;
		int l_n = num_le_node[getheight-i-1];
		if (l_n % 2 == 0)
		{
			int num_right = count - num_le_node[getheight - i -1];
			createNode(root->rchild, str[num_right],&count);
			createNode(root->lchild, str[num_right + 1],&count);
			count -= 2;
		}
		else
		{
			int num_right = count - num_le_node[getheight - i - 1];
			createNode(root->rchild, str[num_right],&count);
			count -= 1;
		}*/
}
void MerTree::LevelOrder(MerNode* hoot)
{
	while (hoot->hash != "")
	{
		cout << hoot->hash.substr(0, 3) << endl;
	}
	while (hoot->lchild != NULL)
	{
		LevelOrder(hoot->lchild);
	}
	while (hoot->rchild != NULL)
	{
		LevelOrder(hoot->rchild);
	}
}
int main()
{
	//计算所有待存的hash值，放在一个数组里
    const int n=5;//叶子节点数目
	int num = n;//该层节点数目，最初为最底层
	int num_level = level_num(n);
	int* num_le_node;//存储每层节点数目
	num_le_node = new int[num_level];
	num_le_node[0] = n;//第0层，即叶子节点数目
	string r_leaf[n] = { "ABC12","CDA12","C35665","EVDF45","DS5846" };
	int num_final=num;//待存节点的数目,最初为最底层叶子节点数目
	string *hash_leaf;//最底层叶子节点存储的hash值
	hash_leaf = new string[num_final];
	for (int i = 0; i < n; i++)
	{
		hash_leaf[i] = result(r_leaf[i]);
	}
	int count = 0;//hash值算到哪个点了（用到的）
    //计算剩余除叶子节点的所有待存节点的hash值
	for (int i = 0; i < (num_level-1); i++)
	{
		//计算每层的待存节点的hash值
		//判断该层的上一层的节点数目
		int num_r_node = (num + 1) / 2;//上层节点数目
		num_le_node[i + 1] = num_r_node;
		if (num % 2 != 0)//判断该层是奇数个节点与否
		{
			for (int j = 0; j < num_r_node; j++)
			{
				num_final += 1;
				if (j == (num_r_node-1))//计算最末尾单个的
				{
					hash_leaf[num_final - 1] = result(hash_leaf[count]+hash_leaf[count]);
					count += 1;
				}
				else
				{
					hash_leaf[num_final - 1] = result(hash_leaf[count] + hash_leaf[count + 1]);
					count += 2;
				}
			}
			num = num_r_node;//num更新
		}
		else//偶数节点
		{
			for (int j = 0; j < num_r_node; j++)
			{
				num_final += 1;
				hash_leaf[num_final - 1] = result(hash_leaf[count] + hash_leaf[count + 1]);
				count += 2;
			}
			num = num_r_node;//num更新
		}
	}
	//
	//把算好的hash值数组hash_leaf放到树里
	MerTree tree;
	tree.createMerTree(count,num_le_node,hash_leaf);
	tree.LevelOrder(tree.root);
	return 0;
}