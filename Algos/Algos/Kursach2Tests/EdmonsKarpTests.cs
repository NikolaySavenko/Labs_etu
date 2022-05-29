using Kursach2;
using System.IO;
using Xunit;

namespace Kursach2Tests
{
	public class EdmonsKarpTests
	{
		[Theory]
		[InlineData("./testData.csv")]
		public void EncodeTest(string filePath)
		{
			var edmonsKarp = new EdmonsKarp();
			var result = edmonsKarp.LoadFromFile(filePath);
			Assert.True(result);
		}

		[Theory]
		[InlineData(@"S O 3
				S P 3
				O Q 3
				O P 2
				P R 2
				Q R 4
				Q T 2
				R T 3")]
		public void TestWithFile(string data)
		{
			File.WriteAllText("./TestData.csv", data);
			var edmonsKarp = new EdmonsKarp("./TestData.csv");
			Assert.True(edmonsKarp.Links.Count > 0);
		}

		[Theory]
		[InlineData("Санкт-Петербург Хабаровск 14", 1)]
		[InlineData("Москва Хабаровск 40", 1)]
		public void NullParseTest(string data, int count)
		{
			var edmonsKarp = new EdmonsKarp();
			edmonsKarp.ParseLinks(data);
			Assert.Equal(count, edmonsKarp.Links.Count);
		}
		
		[Theory]
		[InlineData(@"S O 3
				O T 3")]
		public void SingleFlowTest(string data)
		{
			File.WriteAllText("./TestData.csv", data);
			var edmonsKarp = new EdmonsKarp("./TestData.csv");
			var cost = edmonsKarp.CalculateMaxFlow("S", "T");
			Assert.Equal(3, cost);
		}
		
		[Theory]
		[InlineData(@"S A 3
					S B 3
					B T 3
				A T 3")]
		public void DoubleFlowTest(string data)
		{
			File.WriteAllText("./TestData.csv", data);
			var edmonsKarp = new EdmonsKarp("./TestData.csv");
			var cost = edmonsKarp.CalculateMaxFlow("S", "T");
			Assert.Equal(6, cost);
		}
		
		[Theory]
		[InlineData(@"S A 3
					S B 3
					B C 3
					A C 3
					C D 3
					D E 3
					E T 3")]
		public void LongFlowTest(string data)
		{
			File.WriteAllText("./TestData.csv", data);
			var edmonsKarp = new EdmonsKarp("./TestData.csv");
			var cost = edmonsKarp.CalculateMaxFlow("S", "T");
			Assert.Equal(3, cost);
		}
		
		[Theory]
		[InlineData(@"S B 3
					B C 3
					C D 3
					D E 3
					D F 3
					E T 3
					F T 3")]
		public void ReverceLongFlowTest(string data)
		{
			File.WriteAllText("./TestData.csv", data);
			var edmonsKarp = new EdmonsKarp("./TestData.csv");
			var cost = edmonsKarp.CalculateMaxFlow("S", "T");
			Assert.Equal(6, cost);
		}

		[Theory]
		[InlineData(@"S O 3
				S P 3
				O Q 3
				O P 2
				P R 2
				Q R 4
				Q T 2
				R T 3")]
		public void WikiFlowTest(string data)
		{
			File.WriteAllText("./TestData.csv", data);
			var edmonsKarp = new EdmonsKarp("./TestData.csv");
			var cost = edmonsKarp.CalculateMaxFlow("S", "T");
			Assert.Equal(5, cost);
		}
	}
}