using Xunit;
using Laba1;

namespace Lab1_Tests
{
    public class LinkedListTests
    {
        [Fact]
        public void SizeTest()
        {
            var list = new LinkedList<int>();
            Assert.Equal(0, list.get_size());
        }
    }
}