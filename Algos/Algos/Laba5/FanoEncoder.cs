using Laba5.Map;

namespace Laba5;

public class FanoEncoder
{
    public string Source { get; }
    public IDictionary<char, int> Dictionary { get; }

    public FanoEncoder(string source)
    {
        Source = source;
        Dictionary = new ArrayMap<char, int>();
    }
}