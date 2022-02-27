namespace Laba4.RedBlackTree;

internal class RedBlackNode<TKey, TValue>
    where TValue : class
    where TKey : IComparable, IComparable<TKey>, IEquatable<TKey>
{
    public TValue Data { get; set; }

    public TKey Key { get; set; }

    internal NodeColor Color { get; set; }

    public RedBlackNode<TKey, TValue> Left { get; set; }

    public RedBlackNode<TKey, TValue> Right { get; set; }

    public RedBlackNode<TKey, TValue> Parent { get; set; }

    public RedBlackNode()
    {
        Color = NodeColor.Red;

        Right = RedBlackTree<TKey, TValue>.NullObjectNode;
        Left = RedBlackTree<TKey, TValue>.NullObjectNode;
    }

    public RedBlackNode(TKey key, TValue data)
        : this()
    {
        Key = key;
        Data = data;
    }
}