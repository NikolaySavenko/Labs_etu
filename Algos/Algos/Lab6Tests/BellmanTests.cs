using Lab6;
using Xunit;

namespace Lab6Tests;

public class BellmanTests
{
    [Theory]
    [InlineData("./testData.csv")]
    public void EncodeTest(string filePath)
    {
        var bellman = new BellmanFordOperator();
        var result = bellman.LoadFromFile(filePath);
        Assert.True(result);
    }

    [Theory]
    [InlineData(@"Санкт-Петербург;Москва;10;20
    Москва;Хабаровск;40;35
    Санкт-Петербург;Хабаровск;14;N/A
        Владивосток;Хабаровск;13;8
    Владивосток;Санкт-Петербург;N/A;20")]
    public void TestWithFile(string data)
    {
        File.WriteAllText("./TestData.csv", data);
        var bellman = new BellmanFordOperator("./TestData.csv");
        Assert.True(bellman.Links.Count > 0);
    }

    [Theory]
    [InlineData("Санкт-Петербург;Хабаровск;14;N/A", 1)]
    [InlineData("Москва;Хабаровск;40;35", 2)]
    public void NullParseTest(string data, int count)
    {
        var bellman = new BellmanFordOperator();
        bellman.ParseLinks(data);
        Assert.Equal(count, bellman.Links.Count);
    }
    
    [Theory]
    [InlineData(@"Санкт-Петербург;Москва;10;20
    Москва;Хабаровск;40;35
    Санкт-Петербург;Хабаровск;14;N/A
        Владивосток;Хабаровск;13;8
    Владивосток;Санкт-Петербург;N/A;20")]
    public void CostTest(string data)
    {
        File.WriteAllText("./TestData.csv", data);
        var bellman = new BellmanFordOperator("./TestData.csv");
        var cost = bellman.CalculateCost("Санкт-Петербург", "Москва");
        Assert.Equal(10, cost);
    } 
}