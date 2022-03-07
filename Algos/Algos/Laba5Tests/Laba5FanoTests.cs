using Laba5;
using Xunit;

namespace Laba5Tests;

public class Laba5FanoTests
{
    [Theory]
    [InlineData("it is test string", "111 01 110 111 10 110 01 0011 10 01 110 10 01 0010 111 0001 0000")]
    public void EncodeTest(string source, string encoded)
    {
        var encoder = new FanoEncoder(source);
        Assert.Equal(encoded, encoder.ToString());
    }
}