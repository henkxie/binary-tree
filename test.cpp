#define _CRT_SECURE_NO_WARNINGS 
#include"BinaryTree.h"
void Test()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	Binarytree <int>t1(a, 10);
	/*t1.Prevorder();
	t1.Inorder();
	t1.Postorder();*/
	//t1.Levelorder();
	/*cout << t1.Size() << endl;*/
	//cout << t1.Depth() << endl;
	//cout << t1.Find(3)->_data << endl;
	//cout<<t1.GetleafNum()<<endl;
	/*t1.Prevorder_nor();
	t1.Inorder_nor();
	t1.Postorder_nor();
	cout << t1.FindRecentCommonAncestor(3, 6)->_data << endl;*/

	//cout << t1.longestPath(0,0,0) << endl;
}
int main()
{
	Test();
	system("pause");
	return 0;
}