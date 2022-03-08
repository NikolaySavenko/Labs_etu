using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Laba5;

public class FanoEncoder
{
    private IDictionary<char, int>? _frequencyMap;
    private IDictionary<char, string>? _encodedMap;
    private string Source { get; }

    public IDictionary<char, string> EncodedMap
    {
        get
        {
            if (_encodedMap != null)
            {
                return _encodedMap;
            }

            var dict = new Dictionary<char, string>();
            foreach (var key in FrequencyDictionary.Keys)
            {
                dict.Add(key, "");
            }
            _encodedMap = MakeCodeMap(dict, KeysSortedByDesc);
            return _encodedMap;
        }
    }

    public MemoryStream Encoded
    {
        get
        {
            var stream = new MemoryStream();
            using var writer = new BinaryWriter(stream);
            foreach (var pseudoBit in Source.Select(key => EncodedMap[key]).SelectMany(code => code))
            {
                writer.Write(pseudoBit == '1');
            }

            return stream;
        }
    }

    public IDictionary<char, int> FrequencyDictionary
    {
        get
        {
            if (_frequencyMap != null)
            {
                return _frequencyMap;
            }

            _frequencyMap = new Dictionary<char, int>();
            foreach (var symbol in Source)
            {
                if (_frequencyMap.Keys.Contains(symbol))
                {
                    _frequencyMap[symbol]++;
                }
                else
                {
                    _frequencyMap.Add(symbol, 1);
                }
            }

            return _frequencyMap;
        }
    }

    private IEnumerable<char> KeysSortedByDesc => FrequencyDictionary.Keys.OrderByDescending(key => FrequencyDictionary[key]);
    public double Compress => Encoded.ToArray().Length / (double)(Source.Length * 16);
    public FanoEncoder(string source)
    {
        Source = source;
        _frequencyMap = null;
        _encodedMap = null;
    }
    
    private IDictionary<char, string> MakeCodeMap(IDictionary<char, string> codeMap, IEnumerable<char> keys)
    {
        (IEnumerable<char> leftGroup, IEnumerable<char> rightGroup) = SplitByFrequency(keys);
        var leftPart = leftGroup as char[] ?? leftGroup.ToArray();
        var rightPart = rightGroup as char[] ?? rightGroup.ToArray();

        foreach (var c in leftPart)
        {
            codeMap[c] = $"1{codeMap[c]}";
        }

        if (leftPart.Count() > 1)
        {
            MakeCodeMap(codeMap, leftPart);
        }

        foreach (var c in rightPart)
        {
            codeMap[c] = $"0{codeMap[c]}";
        }
        
        if (rightPart.Count() > 1)
        {
            MakeCodeMap(codeMap, rightPart);
        }

        return codeMap;
    }

    private (IEnumerable<char>, IEnumerable<char>) SplitByFrequency(IEnumerable<char> keys)
    {
        var keysArray = keys as char[] ?? keys.ToArray();
        var keysList = keysArray.ToList();
        var groups = (Left: new List<char>(), Right: new List<char>());
        var sumFrequency = keysArray.Sum(key => FrequencyDictionary[key]);
        var tmpSum = 0;
        
        foreach (char key in keysList)
        {
            if (tmpSum < sumFrequency / 2)
            {
                groups.Left.Add(key);
                tmpSum += FrequencyDictionary[key];
            }
            else
            {
                groups.Right.Add(key);
            }
        }

        return groups;
    }

    public string Decode(byte[] bites)
    {
        string tempKey = String.Empty;
        string result = String.Empty;
        var reverted = bites.Reverse();
        foreach (var bite in reverted)
        {
            if (EncodedMap.Values.Contains(tempKey))
            {
                result += EncodedMap.Keys.First(key => EncodedMap[key] == tempKey);
                tempKey = $"{bite}";
            }
            else
            {
                tempKey = $"{bite}{tempKey}";
            }
        }
        if (EncodedMap.Values.Contains(tempKey))
        {
            result += EncodedMap.Keys.First(key => EncodedMap[key] == tempKey);
        }

        return String.Concat(result.Reverse());
    }

    public override string ToString()
    {
        return String.Concat(Encoded.ToArray());
    }
}
    