using Laba3.Stack;
using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3.Enumerators
{
    public class DepthFirstTraverseEnumerator<T> : IEnumerator<BinaryNode<T>> where T : IComparable<T>
    {
        public BinarySearchTree<T> Tree { get; private set; }

        private BinaryNode<T> _current;

        private readonly CustomStack<T> _stack;
        public DepthFirstTraverseEnumerator(BinarySearchTree<T> tree)
        {
            Tree = tree ?? throw new ArgumentNullException(nameof(tree));
            _current = null;
            _stack = new CustomStack<T>();
        }

        object IEnumerator.Current => _current;

        BinaryNode<T> IEnumerator<BinaryNode<T>>.Current => _current;

        public bool MoveNext()
        {
            if (_current == null)
            {
                _current = Tree.Root;
                _stack.Push(_current);
                return true;
            }

            if (!HasNext())
            {
                return false;
            }

            if (_current.Right != null)
            {
                _stack.Push(_current.Right);
            }

            if (_current.Left != null)
                _current = _current.Left;
            else
            {
                _current = _stack.Top;
                _stack.Pop();
            }

            return true;
        }

        public void Reset()
        {
            _current = Tree.Root;
        }

        public bool HasNext()
        {
            if (_current == null)
            {
                return Tree.Root != null;
            }
            if (_current.Left != null || _current.Right != null)
            {
                return true;
            }
            return _stack.Count() > 1;
        }

        public void Dispose()
        {
            throw new NotImplementedException();
        }
    }
}
