# merkle_tree
存在问题，调用openssl中sha256库函数存在问题，尝试解决失败，具体问题如下：

![image](https://user-images.githubusercontent.com/104714591/180805176-07acaafd-bbe2-468e-adad-3ba955d33304.png)

关于meerkletree的创建，在cpp文件中有十分详细的注释；
sha256的openssl库调用函数不是自己写的。
