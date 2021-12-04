using Laba3;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xunit;

namespace Laba3Tests
{
    public class Tests
    {
        [Fact]
        public void ContainsTest()
        {
            var tree = new BinarySearchTree<int>();
            tree.Insert(4);
            tree.Insert(7);
            tree.Insert(9);
            tree.Insert(1);
            tree.Insert(2);
            tree.Insert(40);
            Assert.True(tree.Contains(2));
            Assert.True(tree.Contains(9));
            Assert.True(tree.Contains(1));
            Assert.True(tree.Contains(40));
        }

        [Fact]
        public void InsertTest()
        {
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
            Assert.True(iterator.MoveNext());
            Assert.Equal(8, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(3, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(10, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(1, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(6, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(14, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(4, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(7, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(13, iterator.Current.Value);
            Assert.False(iterator.MoveNext());
        }

        [Theory]
        [InlineData(4)]
        [InlineData(6)]
        [InlineData(3)]
        public void RemoveTest(int element)
        {
            var tree = new BinarySearchTree<int>();
            tree.Insert(8);
            tree.Insert(3);
            tree.Insert(10);
            tree.Insert(1);
            tree.Insert(6);
            tree.Insert(4);
            tree.Insert(7);
            tree.Insert(14);
            Assert.True(tree.Contains(element));
            tree.Remove(tree.First(node => node.Value == element));
            Assert.False(tree.Contains(element));
        }

        [Fact]
        public void BFTTest()
        {
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
            Assert.True(iterator.MoveNext());
            Assert.Equal(8, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(3, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(10, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(1, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(6, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(14, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(4, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(7, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(13, iterator.Current.Value);
            Assert.False(iterator.MoveNext());
        }

        [Fact]
        public void DFTTest()
        {
            var tree = new BinarySearchTree<int>();
            tree.Insert(8);
            tree.Insert(3);
            tree.Insert(10);
            tree.Insert(1);
            tree.Insert(6);
            tree.Insert(4);
            tree.Insert(7);
            tree.Insert(14);
            var iterator = tree.CreateDTFEnumerator();
            Assert.True(iterator.MoveNext());
            Assert.Equal(8, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(3, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(1, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(6, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(4, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(7, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(10, iterator.Current.Value);
            Assert.True(iterator.MoveNext());
            Assert.Equal(14, iterator.Current.Value);
            Assert.False(iterator.MoveNext());
        }
    }
}
