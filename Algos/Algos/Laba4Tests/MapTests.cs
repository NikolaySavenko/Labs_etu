using System.Collections.Generic;
using Laba4;
using Laba4.RedBlackTree;
using Xunit;

namespace Laba4Tests;

public class UnitTest1
{
	[Fact]
	public void NullMapCheck()
	{
		var tree = new RedBlackTree<string, string>();
		Assert.NotNull(tree);
	}

	[Fact]
	public void TestMapInsert()
	{
		var map = new Map<string, string>();
		map.Insert("a", "a");
		map.Insert("b", "b");
		map.Insert("c", "c");
		map.Insert("d", "d");
		
		Assert.Equal("d", map.Find("d"));
	}

	[Fact]
	public void TestMapRemove()
	{
		var map = new Map<string, string>();
		map.Insert("a", "a");
		map.Insert("b", "b");
		map.Insert("c", "c");
		map.Insert("d", "d");
		map.Remove("d");
		
		Assert.Null(map.Find("d"));
		
		var map2 = new Map<int, string>();
		for (int i = 0; i < 5; i++)
			map2.Insert(i, (i - 1).ToString());
		
		map2.Remove(4);
		Assert.Null(map2.Find(4));
	}

	[Fact]
	public void TestMapFind()
	{
		var map = new Map<int, string>();
		for (int i = 0; i < 5; i++)
			map.Insert(i, i.ToString());
		
		Assert.Equal("0", map.Find(0));
		Assert.Equal("4", map.Find(4));
	}

	[Fact]
	public void TestMapClear()
	{
		var map = new Map<int, string>();
		for (int i = 0; i < 5; i++)
			map.Insert(i, i.ToString());
		
		Assert.Equal("0", map.Find(0));
		Assert.Equal("4", map.Find(4));
		
		map.Clear();
		Assert.Null(map.Find(4));
	}
	
	[Fact]
	public void TestMapKeys()
	{
		var map = new Map<int, string>();
		var elements = new List<int>();
		
		for (int i = 0; i < 5; i++)
		{
			map.Insert(i, i.ToString());
			elements.Add(i);
		}

		Assert.Equal(elements, map.Keys);
	}
	
	[Fact]
	public void TestMapValues()
	{
		var map = new Map<int, string>();
		var values = new List<string>();
		
		for (int i = 0; i < 5; i++)
		{
			map.Insert(i, i.ToString());
			values.Add(i.ToString());
		}

		Assert.Equal(values, map.Values);
	}
	
	[Fact]
	public void TestMapPrint()
	{
		var map = new Map<int, dynamic>();

		map.Insert(55, 65);
		map.Insert(60, 57);
		map.Insert(33, 13);
		map.Insert(3, 2);
		Assert.Equal("3->2 33->13 55->65 60->57 ", map.ToString());
	}
}