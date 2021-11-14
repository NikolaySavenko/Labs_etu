using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba2
{
    public static class Sort
    {
        static void Swap<T>(ref T x, ref T y)
        {
            T t = x;
            x = y;
            y = t;
        }

        static int Partition<T>(T[] array, int minIndex, int maxIndex) where T : IComparable<T>
        {
            var pivot = minIndex - 1;
            for (var i = minIndex; i < maxIndex; i++)
            {
                if (array[i].CompareTo(array[maxIndex]) < 0)
                {
                    pivot++;
                    Swap(ref array[pivot], ref array[i]);
                }
            }

            pivot++;
            Swap(ref array[pivot], ref array[maxIndex]);
            return pivot;
        }

        public static T[] QuickSort<T>(this T[] array, int minIndex, int maxIndex) where T : IComparable<T>
        {
            if (minIndex >= maxIndex)
            {
                return array;
            }

            var pivot = Partition(array, minIndex, maxIndex);
            array.QuickSort(minIndex, pivot - 1);
            array.QuickSort(pivot + 1, maxIndex);

            return array;
        }

        public static T[] InsertionSort<T>(this T[] array) where T : IComparable<T>
        {
            for (int i = 0; i < array.Length - 1; i++)
            {
                for (int j = i + 1; j > 0; j--)
                {
                    if (array[j - 1].CompareTo(array[j]) > 0)
                    {
                        T temp = array[j - 1];
                        array[j - 1] = array[j];
                        array[j] = temp;
                    }
                }
            }
            return array;
        }

        public static bool IsSorted<T>(this T[] array) where T : IComparable<T>
        {
            if (array.Length < 2) 
                return true;

            for (int i = 1; i < array.Length; i++)
            {
                if (array[i].CompareTo(array[i - 1]) < 0)
                {
                    return false;
                }
            }
            return true;
        }

        private static void Shuffle<T>(this T[] array)
        {
            Random rand = new Random();
            for (int i = 0; i < array.Length; i++)
            {
                int swapIndex = rand.Next(array.Length);
                Swap(ref array[swapIndex], ref array[i]);
            }
        }

        public static T[] BogoSort<T>(this T[] array) where T : IComparable<T>
        {
            while (!array.IsSorted())
            {
                array.Shuffle();
            }
            return array;
        }

        public static void CountingSort(char[] array)
        {

        }
    }
}
