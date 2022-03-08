using System.Collections;

namespace Laba5.Map;

public class ListMap<TKey, TValue> : IDictionary<TKey, TValue>
{
    public ListMap()
    {
        Keys = new List<TKey>();
        Values = new List<TValue>();
    }

    public int Count { get; }
    public bool IsReadOnly { get; }
    public ICollection<TKey> Keys { get; }
    public ICollection<TValue> Values { get; private set; }
    public IEnumerator<KeyValuePair<TKey, TValue>> GetEnumerator()
    {
        throw new NotImplementedException();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return GetEnumerator();
    }

    public void Add(KeyValuePair<TKey, TValue> item)
    {
        throw new NotImplementedException();
    }

    public void Clear()
    {
        throw new NotImplementedException();
    }

    public bool Contains(KeyValuePair<TKey, TValue> item)
    {
        throw new NotImplementedException();
    }

    public void CopyTo(KeyValuePair<TKey, TValue>[] array, int arrayIndex)
    {
        throw new NotImplementedException();
    }

    public bool Remove(KeyValuePair<TKey, TValue> item)
    {
        throw new NotImplementedException();
    }


    public void Add(TKey key, TValue value)
    {
        Keys.Add(key);
        Values.Add(value);
    }

    public bool ContainsKey(TKey key)
    {
        throw new NotImplementedException();
    }

    public bool Remove(TKey key)
    {
        throw new NotImplementedException();
    }

    public bool TryGetValue(TKey key, out TValue value)
    {
        throw new NotImplementedException();
    }

    public TValue this[TKey key]
    {
        get
        {
            var index = Keys.Select( (item, index) => new {Item = item, Index = index}).First(i => i.Item.Equals(key)).Index;
            return Values.ToList()[index];
        }
        set
        {
            var tmpKeys = Keys.ToList();
            var tmpValues = Values.ToList();
            var index = tmpKeys.IndexOf(key);
            tmpValues[index] = value;
            Values = tmpValues;
        }
    }
}