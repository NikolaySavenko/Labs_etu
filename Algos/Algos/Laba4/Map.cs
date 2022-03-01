using Laba4.RedBlackTree;

namespace Laba4;

public class Map<TKey, TValue> where TValue : class where TKey : IComparable<TKey>, IComparable, IEquatable<TKey>
{
    private RedBlackTree<TKey, TValue> _tree { get; set; }

    // Works like get_keys
    // .NET Developers prefer explicit getters instead of old get methods
    public IEnumerable<TKey> Keys
    {
        get => _tree.Keys;
    }

    // Works like get_values
    // .NET Developers prefer explicit getters instead of old get methods
    public IEnumerable<TValue> Values
    {
        get => _tree.Values;
    }

    public Map()
    {
        _tree = new RedBlackTree<TKey, TValue>();
    }

    public void Insert(TKey key, TValue value)
    {
        _tree.Add(key, value);
    }

    public void Remove(TKey key)
    {
        _tree.TryRemove(key);
    }

    public TValue? Find(TKey key)
    {
        return _tree.Keys.Contains(key) ? _tree.GetData(key) : null;
    }

    public void Clear()
    {
        _tree.Clear();
    }

    // Works like "print()"
    // Please use ToString for map serialization and printing
    public override string ToString()
    {
        return _tree.ToString();
    }
}