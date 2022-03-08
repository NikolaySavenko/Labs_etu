// See https://aka.ms/new-console-template for more information

using Laba5;

var source = Console.ReadLine();
var encoder = new FanoEncoder(source);
Console.WriteLine($"Encoded: {encoder}");
Console.WriteLine($"Decoded: {encoder.Decode(encoder.Encoded.ToArray())}");
Console.WriteLine($"Source size: {source.Length*16}; Encoded size: {encoder.Encoded.ToArray().Length}");
Console.WriteLine($"Map: {String.Join(' ', encoder.EncodedMap.Select(pair => ($"{pair.Key}->{pair.Value}")))}");
Console.WriteLine($"FrequencyMap: {String.Join(' ', encoder.FrequencyDictionary.Select(pair => ($"{pair.Key}:{pair.Value}")))}");
Console.WriteLine($"Compress -> {encoder.Compress}");