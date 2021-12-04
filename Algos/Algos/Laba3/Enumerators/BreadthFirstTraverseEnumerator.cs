using Laba3.Queue;
using Laba3.Stack;
using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3.Enumerators
{
    class BreadthFirstTraverseEnumerator<T> : IEnumerator<BinaryNode<T>> where T : IComparable<T>
    {
        public BinarySearchTree<T> Tree { get; private set; }

        private CustomQueue<BinaryNode<T>> _queue;

        private BinaryNode<T> _current;

        public BreadthFirstTraverseEnumerator(BinarySearchTree<T> tree)
        {
            Tree = tree ?? throw new ArgumentNullException(nameof(tree));
            _current = null;
            _queue = new CustomQueue<BinaryNode<T>>();
        }

        object IEnumerator.Current => _queue.Peek();

        BinaryNode<T> IEnumerator<BinaryNode<T>>.Current => _queue.Peek();

        public bool MoveNext()
        {
            if (_current == null)
            {
                _current = Tree.Root;
                _queue.Enqueue(_current);
                return true;
            }

            if (!HasNext())
            {
                return false;
            }

            _current = _queue.Dequeue();

            if (_current.Left != null)
            {
                _queue.Enqueue(_current.Left);
            }
            if (_current.Right != null)
            {
                _queue.Enqueue(_current.Right);
            }
                
            return true;
        }

        public void Reset()
        {
            _current = Tree.Root;
        }

        public bool HasNext()
        {
            if(_current == null)
            {
                return Tree.Root != null;
            }
            if (_current.Left != null || _current.Right != null)
            {
                return true; 
            }
            return _queue.Count > 1;
        }

        public void Dispose()
        {
            //throw new NotImplementedException();
        }
    }
}
