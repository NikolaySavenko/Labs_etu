﻿// See https://aka.ms/new-console-template for more information
using System.Diagnostics;
using Laba2;

Console.WriteLine("Hello, Motherfucker!");

var random = new Random();
const int maxValue = 1000;
var stopWatch = new Stopwatch();


for (var arraySize = 10; arraySize < 1_000_000; arraySize *= 10)
{
    for (var i = 0; i < 10; i++)
    {
        var array = new int[arraySize];
        for (var j = 0; j < arraySize; j++)
        {
            array[j] = random.Next(maxValue);
        }

        Console.WriteLine($"[QuickSort{i}] Array size {arraySize}. Starting....");
        stopWatch.Start();
        array.QuickSort(0, array.Length - 1);
        stopWatch.Stop();
        Console.WriteLine($"[QuickSort{i}] Sorted! Ellapsed {stopWatch.Elapsed}");
        stopWatch.Reset();
        Console.WriteLine();
    } 
}
Console.WriteLine();

for (var arraySize = 10; arraySize < 1_000_000; arraySize *= 10)
{
    for (var i = 0; i < 10; i++)
    {
        var array = new int[arraySize];
        for (var j = 0; j < arraySize; j++)
        {
            array[j] = random.Next(maxValue);
        }

        Console.WriteLine($"[InsertionSort#{i}] Array size {arraySize}. Starting....");
        stopWatch.Start();
        array.InsertionSort();
        stopWatch.Stop();
        Console.WriteLine($"[InsertionSort#{i}] Sorted! Ellapsed {stopWatch.Elapsed}");
        stopWatch.Reset();
        Console.WriteLine();
    }
}
Console.WriteLine("Finished!");
Console.ReadKey();