# 项目名称 
merkle_tree
# 项目简介
Merkle Tree 也被成为 Hash Tree，这种树其实就是用来存储 hash 值的一种树。Merkle树的叶子是数据块的hash值。非叶节点是其对应子节点串联字符串的hash。
![image](https://user-images.githubusercontent.com/104714591/181259074-58187af6-b3b8-4345-b6c9-811c539c61fd.png)
# 完成人
何静
# 项目流程
1、计算所有结点的值（应该填入的hash值）（采用sha256算法）
2、层序填入创建的二叉树中，要考虑到层中结点数为奇数还是偶数
#部分代码说明
关于meerkletree的创建，在cpp文件中有十分详细的注释；
以下介绍部分函数：
## void MerTree::create(MerNode* current, string str[],int count,int num_le_node[],int i)
根据层数判断该层的结点数为奇数还是偶数，填入该层结点的值
## void MerTree::LevelOrder(MerNode* hoot)
层序遍历输出结点存储的值
## int main()
main函数先计算好所有需要待填入的结点的hash值,依次存储在一个string类型的数组中，然后创建merkle树，把它们填进去。
#运行过程截图
存在问题，调用openssl中sha256库函数存在问题，尝试解决失败，具体问题如下：
![image](https://user-images.githubusercontent.com/104714591/180805176-07acaafd-bbe2-468e-adad-3ba955d33304.png)

#引用参考
[1]sha256的openssl库调用函数:https://codeleading.com/article/23094792584/
[2]https://blog.csdn.net/u010039377/article/details/79845483/?ops_request_misc=&request_id=&biz_id=102&utm_term=merkletree%E4%BB%A3%E7%A0%81c++&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-79845483.142^v33^pc_search_result_control_group,185^v2^control&spm=1018.2226.3001.4187
[3]https://blog.csdn.net/Ciellee/article/details/108006389?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165867686216782390533452%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165867686216782390533452&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-3-108006389-null-null.142^v33^pc_search_result_control_group,185^v2^control&utm_term=merkletree%E4%BB%A3%E7%A0%81c%2B%2B&spm=1018.2226.3001.4187
[4]https://blog.csdn.net/wo541075754/article/details/54632929
