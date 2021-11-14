using System;
using Xunit;
using Laba2;

namespace Lab2_Tests
{
    public class SortTests
    {
        private Random random = new Random();


        [Theory]
        [InlineData(10, 1000)]
        [InlineData(100, 1000)]
        [InlineData(1_000, 1000)]
        [InlineData(10_000, 1000)]
        [InlineData(100_000, 1000)]
        public void QuickSortTest(int count, int maxValue)
        {
            int[] array = new int[count];

            for (var i = 0; i < count; i++)
            {
                array[i] = random.Next(maxValue);
            }

            var nativeSortedArray = (int[]) array.Clone();
            Array.Sort(nativeSortedArray);
            array.QuickSort(0, array.Length - 1);

            Assert.Equal(nativeSortedArray, array);
        }

        [Theory]
        [InlineData(10, 1000)]
        [InlineData(100, 1000)]
        [InlineData(1_000, 1000)]
        [InlineData(10_000, 1000)]
        [InlineData(100_000, 1000)]
        public void InsertionSortTest(int count, int maxValue)
        {
            int[] array = new int[count];

            for (var i = 0; i < count; i++)
            {
                array[i] = random.Next(maxValue);
            }

            var nativeSortedArray = (int[])array.Clone();
            Array.Sort(nativeSortedArray);
            array.InsertionSort();

            Assert.Equal(nativeSortedArray, array);
        }

        [Fact]
        public void IsSortedTest()
        {
            int[] array = new int[] {0, 1, 2, 3};

            Assert.True(array.IsSorted());

            array = new int[] { 0, 1, 2, 1 };

            Assert.False(array.IsSorted());

            array = new int[] { 2, 1, 2, 1 };

            Assert.False(array.IsSorted());

            array = new int[] { 2, 2, 2, 2 };

            Assert.True(array.IsSorted());

            array = new int[] { 0, 1, 7, 6, 7 };

            Assert.False(array.IsSorted());
        }

        [Theory]
        [InlineData(10, 1000)]
        public void BogoSortTest(int count, int maxValue)
        {
            int[] array = new int[count];

            for (var i = 0; i < count; i++)
            {
                array[i] = random.Next(maxValue);
            }

            var nativeSortedArray = (int[])array.Clone();
            Array.Sort(nativeSortedArray);
            array.BogoSort();

            Assert.Equal(nativeSortedArray, array);
        }

        [Theory]
        [InlineData(1000, "abcdefghijklmnopqrstuvwxyz")]
        public void ConuntingSortTest(int count, string source)
        {
            char[] alphabet = source.ToCharArray();
            char[] array = new char[count];

            for (var i = 0; i < count; i++)
            {
                array[i] = alphabet[random.Next(alphabet.Length - 1)];
            }

            array.CountingSort();

            Assert.True(array.IsSorted());
        }
    }
}