#include<iostream>
#include<cmath>
#include<string>
#include"sha_256.h"
using namespace std;
//�жϲ���
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
//���򴴽�����merkle��
struct MerNode
{
	string hash;//��㴢���hashֵ
	struct MerNode* lchild, * rchild;
};
class MerTree
{
public:
	MerNode* root;//�����
	MerTree()//Ĭ�Ϲ��캯��
	{
		root = NULL;
	}
	MerNode* Root()//���ظ����
	{
		return root;
	}
	MerNode* Parent(MerNode* current);//���ص�ǰ���ĸ����
	MerNode* LChild(MerNode* current);//��ǰ��������
	MerNode* RChild(MerNode* current);//��ǰ�����Һ���
	void createMerTree(int n,int num_le_node[],string str[]);//��α�������
	void LevelOrder(MerNode* hoot);//��α�������merkle��
	void createNode(MerNode* current, string str[],int count,int num_le_node[],int i);
	int getheight;//���Ĳ���
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
MerNode* MerTree::LChild(MerNode* current)//��ǰ��������
{
	return current->lchild;
}
MerNode* MerTree::RChild(MerNode* current)//��ǰ�����Һ���
{
	return current->rchild;
}
//��α�������,n�ǽ������
void MerTree::createMerTree(int n,int num_le_node[],string str[])
{
	getheight = level_num(n);//���Ĳ���
	//��ø���㼰�����ĺ�����һ��
	createNode(root, str, n,num_le_node,0);
	//root->hash = str[count];
	//root->parent = NULL;
	/*if (num_le_node[getheight - 1] % 2 == 0)//��һ����2�����
	{
		int num_right = count - num_le_node[getheight - 1];//�Һ������
		root->rchild->hash = str[num_right];
		root->lchild->hash = str[num_right + 1];
		count -= 2;
	}
	else//��һ��ֻ��һ�����
	{
		int num_right = count - num_le_node[getheight - 1];//�Һ������
		root->rchild->hash = str[num_right];
		root->lchild = NULL;
		count -= 1;
	}*/
	//MerNode* temp = root;
	/*for (int i = 0; i < (getheight - 1); i++)//��ÿ���
	{
		for (int j = 0; j < num_le_node[getheight - i - 1]; j++)
		{
			//�����жϣ��жϸò�������orż��
			if (num_le_node[getheight - i - 2] % 2 == 0)//ż��,˵�����Һ��Ӷ���
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
	//�������д����hashֵ������һ��������
    const int n=5;//Ҷ�ӽڵ���Ŀ
	int num = n;//�ò�ڵ���Ŀ�����Ϊ��ײ�
	int num_level = level_num(n);
	int* num_le_node;//�洢ÿ��ڵ���Ŀ
	num_le_node = new int[num_level];
	num_le_node[0] = n;//��0�㣬��Ҷ�ӽڵ���Ŀ
	string r_leaf[n] = { "ABC12","CDA12","C35665","EVDF45","DS5846" };
	int num_final=num;//����ڵ����Ŀ,���Ϊ��ײ�Ҷ�ӽڵ���Ŀ
	string *hash_leaf;//��ײ�Ҷ�ӽڵ�洢��hashֵ
	hash_leaf = new string[num_final];
	for (int i = 0; i < n; i++)
	{
		hash_leaf[i] = result(r_leaf[i]);
	}
	int count = 0;//hashֵ�㵽�ĸ����ˣ��õ��ģ�
    //����ʣ���Ҷ�ӽڵ�����д���ڵ��hashֵ
	for (int i = 0; i < (num_level-1); i++)
	{
		//����ÿ��Ĵ���ڵ��hashֵ
		//�жϸò����һ��Ľڵ���Ŀ
		int num_r_node = (num + 1) / 2;//�ϲ�ڵ���Ŀ
		num_le_node[i + 1] = num_r_node;
		if (num % 2 != 0)//�жϸò����������ڵ����
		{
			for (int j = 0; j < num_r_node; j++)
			{
				num_final += 1;
				if (j == (num_r_node-1))//������ĩβ������
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
			num = num_r_node;//num����
		}
		else//ż���ڵ�
		{
			for (int j = 0; j < num_r_node; j++)
			{
				num_final += 1;
				hash_leaf[num_final - 1] = result(hash_leaf[count] + hash_leaf[count + 1]);
				count += 2;
			}
			num = num_r_node;//num����
		}
	}
	//
	//����õ�hashֵ����hash_leaf�ŵ�����
	MerTree tree;
	tree.createMerTree(count,num_le_node,hash_leaf);
	tree.LevelOrder(tree.root);
	return 0;
}