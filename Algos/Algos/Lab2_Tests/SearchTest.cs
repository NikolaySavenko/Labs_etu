using Xunit;
using Laba2;
using System;

namespace Lab2_Tests
{
    public class SearchTest
    {
        [Theory]
        [InlineData(1000, 100, 100)]
        public void Binary(int count, int maxValue, int testCount)
        {
            var rnd = new Random();
            int[] array = new int[count];
            for (var i = 0; i < count; i++)
            {
                array[i] = rnd.Next(maxValue);
            }

            Array.Sort(array);

            while (testCount > 0)
            {
                var val = array[rnd.Next(count)];
                Assert.Equal(Array.BinarySearch(array, val), array.BinarySearch(val));
                testCount--;
            }
        }

        [Theory]
        [InlineData(7)]
        public void ManualBinaryTest(int index)
        {
            int[] array = new int[10] {0, 11, 22, 33, 44, 55, 66, 77, 88, 99};
            var val = array[index];
            var fIndex = array.BinarySearch(val);
            Assert.Equal(index, fIndex);
        }
    }
}