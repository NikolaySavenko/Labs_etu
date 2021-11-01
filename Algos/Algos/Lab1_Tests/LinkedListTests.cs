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

            list.push_front(1);
            Assert.Equal(1, list.get_size());

            list.pop_front();
            Assert.Equal(0, list.get_size());

            list.push_back(1);
            Assert.Equal(1, list.get_size());

            list.pop_back();
            Assert.Equal(0, list.get_size());
        }
    }
}