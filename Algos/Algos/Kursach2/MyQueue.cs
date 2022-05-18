namespace Kursach2
{
	internal class MyQueue<T>
	{
		public T? Head { get; private set; }
		readonly Laba1.LinkedList<T> list;
		
		public MyQueue(T[] items) : this()
		{
			foreach(var item in items)
			{
				Enqueue(item);
			}
		}

		public MyQueue()
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

		internal bool TryDequeue(out T point)
		{
			point = default;
			if (list.Count == 0) return false;

			point = Dequeue();
			return true;
		}
	}
}