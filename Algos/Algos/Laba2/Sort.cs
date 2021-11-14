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

        


        public static void BogoSort<T>(T[] array)
        {

        }

        public static void CountingSort(char[] array)
        {

        }
    }
}
