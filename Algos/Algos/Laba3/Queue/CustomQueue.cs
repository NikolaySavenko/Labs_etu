using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3.Queue
{
    class CustomQueue<T> where T : IComparable<T>
    {
        public T? Head { get; private set; }
        readonly Laba1.LinkedList<T> list;

        public CustomQueue()
        {
            list = new Laba1.LinkedList<T>();
        }

        public void Enqueue(T element)
        {
            list.push_front(element);
        }

        public T Dequeue()
        {
            return list.PopLastData();
        }

        public T Peek() => list.at(list.Count - 1);

        public int Count => list.Count;
    }
}
