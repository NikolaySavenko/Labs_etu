namespace Kursach2;

public class EdmonsKarp
{
    public IList<FlowLink> Links { get; init; }
    
    public EdmonsKarp()
    {
        Links = new List<FlowLink>();
    }
    
    public EdmonsKarp(string filePath) : this()
    {
        LoadFromFile(filePath);
    }
    
    public bool LoadFromFile(string filePath)
    {
        try
        {
            string[] lines = File.ReadAllLines(filePath);
            ParseLines(lines);
            return true;
        }
        catch (Exception e)
        {
            return false;
        }
    }

	// In this implementation, we do not need to save the initial bandwidth of the channels
	public long CalculateMaxFlow(string from, string to)
    {
	    long maxFlow = 0;

	    while (TryFindLowerCost(from, to, out var flow))
	    {
		    var minFlow = flow.Min(link => link.cost);

		    foreach (var flowLink in flow)
		    {
			    var linkWithUpdatedCost = flowLink with {cost = flowLink.cost - minFlow};
			    Links.Remove(flowLink);
                Links.Add(linkWithUpdatedCost);
                if (Links.FirstOrDefault(link => link.from == flowLink.to && link.to == flowLink.from) != null)
                {
	                var opposite = Links.First(link => link.from == flowLink.to && link.from == flowLink.to);
	                var newOpposite = opposite with {cost = opposite.cost + minFlow};
	                Links.Remove(opposite);
	                Links.Add(newOpposite);
                }
		    }

		    maxFlow += minFlow;

	    }

	    return maxFlow;
    }

    private bool TryFindLowerCost(string from, string to, out List<FlowLink>? flow)
    {
	    flow = new List<FlowLink>();
	    var linkQueue = new MyQueue<MeetablePoint>(new [] { new MeetablePoint(from, null) });
	    var metPoints = new List<string>(new [] { from });
	    var findedFlag = false;

	    while (linkQueue.TryDequeue(out var point) && findedFlag)
	    {
		    var relativeLinks = Links.Where(link => link.from == point.name && !metPoints.Contains(link.to));
		    foreach (var relativeLink in relativeLinks)
		    {
			    metPoints.Add(relativeLink.to);
                linkQueue.Enqueue(new MeetablePoint(relativeLink.to, relativeLink.from));
                if (relativeLink.from == to)
                {
	                findedFlag = true;
                    break;
                }
		    }
	    }

	    if (linkQueue.Count == 0)
	    {
		    return false;
	    }

	    var lastPoint = metPoints.First(point => point == to);
	    while (lastPoint != from)
	    {
		    var link = Links.First(link => link.to == lastPoint);
		    flow.Add(link);
		    lastPoint = link.from;
	    }

	    return true;
    }

    public void ParseLinks(string source)
    {
        var fields = source.Split();
        if (int.TryParse(fields[2], out var depCost))
        {
            AddLink(new FlowLink(fields[0], fields[1], depCost));
        }
    }
    
    public void ParseLines(string[] lines)
    {
        foreach (var line in lines)
        {
            ParseLinks(line);
        }
    }

    public void AddLink(FlowLink link)
    {
        Links.Add(link);
    }
}