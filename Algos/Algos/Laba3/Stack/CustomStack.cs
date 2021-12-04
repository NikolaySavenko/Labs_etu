namespace Laba3.Stack
{
    class CustomStack<T> where T : IComparable<T>
    {
        readonly Laba1.LinkedList<BinaryNode<T>> list;

        public CustomStack()
        {
            list = new Laba1.LinkedList<BinaryNode<T>>();
        }
        public int Push(BinaryNode<T> element)
        {
            var len = list.Count;
            list.push_back(element);
            return len;
        }
        public BinaryNode<T>? Top => list.Count > 0 ? list.at(list.Count - 1) : null;
        public void Pop()
        {
            if (list.Count == 0)
            {
                throw new InvalidOperationException();
            }
            list.remove(list.Count - 1);
        }

        public int Count()
        {
            return list.Count;
        }
    }
}
