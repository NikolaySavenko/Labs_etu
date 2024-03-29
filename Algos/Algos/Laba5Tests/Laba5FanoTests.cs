using Laba5;
using Xunit;

namespace Laba5Tests;

public class Laba5FanoTests
{
    [Theory]
    [InlineData("it is test string", "0111110101110011111100101110110111010001110000000")]
    [InlineData("some another test", "01110110011101001001000110011100001110000001001111101011")]
    public void EncodeTest(string source, string encoded)
    {
        var encoder = new FanoEncoder(source);
        var actual = encoder.ToString();
        Assert.Equal(encoded, actual);
    }
    
    [Theory]
    [InlineData("it is test string")]
    [InlineData("some another test")]
    public void DecodeTest(string source)
    {
        var encoder = new FanoEncoder(source);
        var encoded = encoder.Encoded.ToArray();
        Assert.Equal(source, encoder.Decode(encoded));
    }

    [Theory]
    [InlineData("ytttttttttttttttttttttttttttttttt")]
    [InlineData("asdasdasdasdasdadsadasdasdasdasdasd")]
    [InlineData("testtestttestetesttetstestestestestest")]
    public void TestSize(string source)
    {
        var encoder = new FanoEncoder(source);
        var sourceSizeInBites = source.Length * 16;
        var encodedSize = encoder.Encoded.ToArray().Length;
        Assert.True(sourceSizeInBites > encodedSize);

    }
}