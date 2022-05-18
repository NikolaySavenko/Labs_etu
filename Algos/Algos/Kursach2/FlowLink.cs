namespace Kursach2;
//In this implementation, we do not need to save the initial bandwidth of the channels, for example. 1/3. Therefore links do not have this field
public record FlowLink(string from, string to, int cost);