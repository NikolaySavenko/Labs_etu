namespace Laba2
{
    public static class Search
    {
        // Extension Method
        // For details read CLR via C# by Jeffrey Richter
        public static int BinarySearch<T>(this T[] array, T value) where T : IComparable<T>
        {
            int min = 0;
            int max = array.Length - 1;
            while (min <= max)
            {
                int mid = (min + max) / 2;
                if (value.CompareTo(array[mid]) == 0)
                {
                    return mid;
                }
                else if (value.CompareTo(array[mid]) < 0)
                {
                    max = mid - 1;
                }
                else
                {
                    min = mid + 1;
                }
            }
            return -1;
        }
    }
}