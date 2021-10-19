using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba1
{
    public class LinkedNode<T>
    {
        public T Value {  get; set; }
        public LinkedNode<T>? Next {  get; set; }
        public LinkedNode(T value)
        {
            Value = value;
            Next = null;
        }

        public override string ToString()
        {
            return Value.ToString();
        }
    }
}
