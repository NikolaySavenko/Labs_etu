// See https://aka.ms/new-console-template for more information
using Laba3;

var tree = new BinarySearchTree<int>();
tree.Insert(8);
tree.Insert(3);
tree.Insert(10);
tree.Insert(1);
tree.Insert(6);
tree.Insert(4);
tree.Insert(7);
tree.Insert(14);
tree.Insert(13);
var iterator = tree.CreateBFTEnumerator();
while (iterator.MoveNext())
{
    Console.WriteLine(iterator.Current.Value);
}