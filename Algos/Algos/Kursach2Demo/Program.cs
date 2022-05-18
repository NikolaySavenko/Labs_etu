// See https://aka.ms/new-console-template for more information

using Kursach2;

var edmonsKarp = new EdmonsKarp("./testData.csv");

Console.WriteLine("Cost from:");
var from = Console.ReadLine();

Console.WriteLine("Cost to:");
var to = Console.ReadLine();

var cost = edmonsKarp.CalculateMaxFlow(from, to);

Console.WriteLine($"Max Flow from {from} to {to} is {cost}");