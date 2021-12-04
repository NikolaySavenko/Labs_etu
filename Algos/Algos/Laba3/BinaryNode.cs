using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3
{
    public class BinaryNode<T> : IComparable<BinaryNode<T>> where T : IComparable<T>
    {
        public T Value { get; set; }

        public BinaryNode<T> Parent { get; set; }
        public BinaryNode<T> Left { get; set; }
        public BinaryNode<T> Right { get; set; }

        // Left: -1
        // Right: 1
        public int Side
        {
            get
            {
                return Parent != null ? (Parent.Left == this ? -1 : 1) : 0;
            }
        }
        // TODO Add parent
        public BinaryNode(T value)
        {
            Value = value;
        }

        public int CompareTo(BinaryNode<T>? other)
        {
            return Value.CompareTo(other.Value);
        }
    }
}
