using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba1
{
    public class LinkedList<T>
    {
        private LinkedNode<T>? _first;
        private LinkedNode<T>? _last;
        public int Count { get
            {
                int count = 0;
                var current = _first;
                while (current != null)
                {
                    current = current.Next;
                    count++;
                }
                return count;
            }
        }

        public LinkedList() {
            _first = null;
            _last = _first;
        }

        public void push_back(T value)
        {
            var newNode = new LinkedNode<T>(value);
            if (_last != null)
            {
                _last.Next = newNode;
                _last = newNode;
            } else 
            {
                _first = newNode;
                _last = newNode;
            }
            
        }

        public void push_front(T value)
        {
            var newNode = new LinkedNode<T>(value);
            newNode.Next = _first;
            _first = newNode;
            if (_last == null)
            {
                _last = newNode;
            }
        }

        public void pop_back()
        {
            var preLast = _first;
            if (preLast != null)
            {
                LinkedNode<T>? next = preLast.Next;
                if (next != null)
                {
                    while (next.Next != null)
                    {
                        preLast = preLast.Next;
                    }
                    preLast.Next = null;
                    _last = preLast;
                } else
                {
                    _first = null;
                    _last = null;
                }
                
            }
            else throw new InvalidOperationException();
        }

        public void pop_front()
        {
            _first = _first.Next;
            if (_first == null)
            {
                _last = null;
            }
        }

        public void insert(T value, int position)
        {
            var newNode = new LinkedNode<T>(value);
            var current = _first;
            for (var i = 0; i < position; i++)
            {
                current = current.Next;
            }
            newNode.Next = current.Next;
            current.Next = newNode;
        }

        public T at(int position)
        {
            var current = _first;
            for (var i = 0; i <= position; i++)
            {
                current = current.Next;
            }
            return current.Value;
        }

        public LinkedNode<T> node_at(int position)
        {
            var current = _first;
            for (var i = 0; i <= position; i++)
            {
                current = current.Next;
            }
            return current;
        }

        public void remove(int position)
        {
            var current = _first;
            for (var i = 0; i < position; i++)
            {
                current = current.Next;
            }
            current.Next = current.Next.Next;
        }

        public int get_size()
        {
            return Count;
        }

        public void clear()
        {
            _first = null;
            _last = null;
        }

        public void set(int position, T value)
        {
            var newNode = new LinkedNode<T>(value);
            var nodeOnPrePosition = _first;
            for (var i = 0; i < position; i++)
            {
                nodeOnPrePosition = nodeOnPrePosition.Next;
            }
            newNode.Next = nodeOnPrePosition.Next.Next;
            nodeOnPrePosition.Next = newNode;
        }

        public bool isEmpty()
        {
            return _first == null;
        }

        public override string ToString()
        {
            var sb = new StringBuilder();
            var current = _first;
            while (current != null)
            {
                sb.AppendLine(current.ToString());
            }
            return sb.ToString();
        }

        public void swap(int pos0, int pos1)
        {
            var buffer = node_at(pos0).Value;
            node_at(pos0).Value = node_at(pos1).Value;
            node_at(pos1).Value = buffer;
        }
    }
}
