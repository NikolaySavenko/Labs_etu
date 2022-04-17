namespace Lab6;

public class BellmanFordOperator
{
    public IList<Link> Links { get; init; }
    
    public BellmanFordOperator()
    {
        Links = new List<Link>();
    }
    
    public BellmanFordOperator(string filePath) : this()
    {
        LoadFromFile(filePath);
    }

    public void ParseLines(string[] lines)
    {
        foreach (var line in lines)
        {
            ParseLinks(line);
        }
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

    public void ParseLinks(string source)
    {
        var fields = source.Split(';');
        if (int.TryParse(fields[2], out var depCost))
        {
            AddLink(new Link(fields[0], fields[1], depCost));
        }
        if (int.TryParse(fields[3], out var destCost))
        {
            AddLink(new Link(fields[1], fields[0], destCost));
        }
    }

    public void AddLink(Link link)
    {
        Links.Add(link);
    }

    public int CalculateCost(string from, string to)
    {
        var vertices = GetVertices();
        var dist = vertices.ToDictionary(verticle => verticle, verticle => int.MaxValue);
        dist[from] = 0;

        for (var i = 0; i < vertices.Count - 1; i++)
        {
            foreach (var link in Links)
            {
                if (dist[link.from] != int.MaxValue && dist[link.to] > dist[link.from] + link.cost)
                {
                    dist[link.to] = dist[link.from] + link.cost;
                }
            }
        }

        return dist[to];
    }

    public List<string> GetVertices()
    {
        var verticles = new List<string>();
        
        foreach (var link in Links)
        {
            if (!verticles.Contains(link.from))
            {
                verticles.Add(link.from);
            }
            if (!verticles.Contains(link.to))
            {
                verticles.Add(link.to);
            }
        }

        return verticles;
    } 
}