﻿using System;
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

        // Destructor triggers when GC is making 'magic'
        // For details please read CLR via C# by Jeffrey Richter
        ~LinkedList()
        {
            while (_first != null)
            {
                // it removes roots to elements
                // thats gives CG opportunity to safely delete elements with no roots
                pop_front();
            }
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
                if (preLast.Next != null)
                {
                    while (preLast.Next.Next != null)
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

        public T? PopLastData()
        {
            var preLast = _first;
            // default bullshit
            T buf = _last.Value;
            if (preLast != null)
            {
                if (preLast.Next != null)
                {
                    while (preLast.Next.Next != null)
                    {
                        preLast = preLast.Next;
                    }
                    buf = preLast.Next.Value;
                    preLast.Next = null;
                    _last = preLast;
                }
                else
                {
                    _first = null;
                    _last = null;
                }

            }
            else throw new InvalidOperationException();
            return buf;
        }

        public void insert(T value, int position)
        {
            var newNode = new LinkedNode<T>(value);
            if (position == 0)
            {
                push_front(value);
            }
            else if (position == Count)
            {
                push_back(value);
            } else 
            {
                var current = _first;
                for (var i = 0; i < position - 1; i++)
                {
                    current = current.Next;
                }
                newNode.Next = current.Next;
                current.Next = newNode;
            }
        }

        public T at(int position)
        {
            var current = _first;
            for (var i = 0; i < position; i++)
            {
                current = current.Next;
            }
            return current.Value;
        }

        public LinkedNode<T> node_at(int position)
        {
            var current = _first;
            for (var i = 0; i < position; i++)
            {
                current = current.Next;
            }
            return current;
        }

        public void remove(int position)
        {
            if (position == Count - 1)
            {
                pop_back();
            }
            else if(position == 0)
            {
                pop_front();
            }
            else
            {
                var current = _first;

                for (var i = 0; i < position - 1; i++)
                {
                    current = current.Next;
                }
                current.Next = current.Next.Next;
            }
           
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
            var current = _first;
            for (var i = 0; i < position; i++)
            {
                current = current.Next;
            }

            current.Value = value;
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
                if (current != _first)
                {
                    sb.Append(" ");
                }
                sb.Append(current.ToString());
                current = current.Next;
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
