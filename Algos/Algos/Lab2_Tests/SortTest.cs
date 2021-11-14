using System;
using Xunit;
using Laba2;

namespace Lab2_Tests
{
    public class SortTests
    {
        private Random random = new Random();


        [Theory]
        [InlineData(2000, 1000)]
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
        [InlineData(2000, 1000)]
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
    }
}