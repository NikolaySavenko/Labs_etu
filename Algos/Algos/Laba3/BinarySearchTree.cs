using Laba3.Enumerators;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3
{
    public class BinarySearchTree<T> : IEnumerable<BinaryNode<T>> where T : IComparable<T>
    {
        public BinaryNode<T>? Root { get; private set; }

        public BinarySearchTree() {
            Root = null;
        }
        public BinarySearchTree(T root)
        {
            Root = new BinaryNode<T>(root);
        }

        //public BinaryNode<T> Add(T data, BinaryNode<T> parent) => Add(new BinaryNode<T>(data));

        public BinaryNode<T> Add(BinaryNode<T> node, BinaryNode<T> currentNode)
        {
            if (Root == null)
            {
                node.Parent = null;
                return Root = node;
            }

            currentNode = currentNode ?? Root;
            node.Parent = currentNode;

            int result;
            return (result = node.Value.CompareTo(currentNode.Value)) == 0
                ? currentNode
                : result < 0
                    ? currentNode.Left == null
                        ? (currentNode.Left = node)
                        : Add(node, currentNode.Left)
                    : currentNode.Right == null
                        ? (currentNode.Right = node)
                        : Add(node, currentNode.Right);
        }

        public void Remove(BinaryNode<T> node)
        {
            if (node == null)
            {
                return;
            }

            var currentNodeSide = node.Side;
            if (node.Left == null && node.Right == null)
            {

                if (currentNodeSide == -1)
                {
                    node.Parent.Left = null;
                }
                else if (currentNodeSide == 1)
                {
                    node.Parent.Right = null;
                } else
                {
                    // Reset
                    Root = null;
                }
            }
            else if (node.Left == null)
            {
                if (currentNodeSide == -1)
                {
                    node.Parent.Left = node.Right;
                }
                else
                {
                    node.Parent.Right = node.Right;
                }

                node.Right.Parent = node.Parent;
            }
            else if (node.Right == null)
            {
                if (currentNodeSide == -1)
                {
                    node.Parent.Left = node.Left;
                }
                else
                {
                    node.Parent.Right = node.Left;
                }

                node.Left.Parent = node.Parent;
            }
            else
            {
                switch (currentNodeSide)
                {
                    case -1:
                        node.Parent.Left = node.Right;
                        node.Right.Parent = node.Parent;
                        Add(node.Left, node.Right);
                        break;
                    case 1:
                        node.Parent.Right = node.Right;
                        node.Right.Parent = node.Parent;
                        Add(node.Left, node.Right);
                        break;
                    default:
                        var tmpLeft = node.Left;
                        var tmpRightLeft = node.Right.Left;
                        var tmpRightRight = node.Right.Right;
                        node.Value = node.Right.Value;
                        node.Right = tmpRightRight;
                        node.Left = tmpRightLeft;
                        Add(tmpLeft, node);
                        break;
                }
            }
        }

        public bool Contains(T value)
        {
            BinaryNode<T> current = Root;
            while (Root != null)
            {
                if (current.Value.CompareTo(value) == 0)
                {
                    return true;
                }
                else if ((value.CompareTo(current.Value) < 0))
                {
                    if (current.Left == null)
                    {
                        return false;
                    }
                    current = current.Left;
                }
                else
                {
                    if (current.Right == null)
                    {
                        return false;
                    }
                    current = current.Right;
                }
            }
            return false;
        }

        public void Insert(T value)
        {
            if (Root == null)
            {
                Root = new BinaryNode<T>(value);
                return;
            }
            BinaryNode<T> node = Root;
            while (true)
            {
                if (value.CompareTo(node.Value) <= 0)
                {
                    if (node.Left == null)
                    {
                        node.Left = new BinaryNode<T>(value);
                        return;
                    }
                    node = node.Left;
                }
                else
                {
                    if (node.Right == null)
                    {
                        node.Right = new BinaryNode<T>(value);
                        return;
                    }
                    node = node.Right;
                }
            }
        }

        public IEnumerator<BinaryNode<T>> GetEnumerator() => CreateBFTEnumerator();

        IEnumerator IEnumerable.GetEnumerator() => CreateBFTEnumerator();

        public IEnumerator<BinaryNode<T>> CreateDTFEnumerator()
        {
            return new DepthFirstTraverseEnumerator<T>(this);
        }

        public IEnumerator<BinaryNode<T>> CreateBFTEnumerator()
        {
            return new BreadthFirstTraverseEnumerator<T>(this);
        }
    }
}
