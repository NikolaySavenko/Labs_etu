// See https://aka.ms/new-console-template for more information

using Lab6;

var bellman = new BellmanFordOperator("./testData.csv");

Console.WriteLine("Cost from:");
var from = Console.ReadLine();

Console.WriteLine("Cost to:");
var to = Console.ReadLine();

var cost = bellman.CalculateCost(from, to);

Console.WriteLine($"Cost from {from} to {to} is {cost}");