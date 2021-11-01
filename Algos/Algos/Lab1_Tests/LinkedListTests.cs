using Xunit;
using Laba1;

namespace Lab1_Tests
{
    public class LinkedListTests
    {

        [Fact]
        public void push_backTest()
        {
            var list = new LinkedList<int>();
            Assert.Equal("", list.ToString());
            list.push_back(0);
            Assert.Equal("0", list.ToString());

            list.push_back(0);
            Assert.Equal("0 0", list.ToString());

            list.push_back(1);
            Assert.Equal("0 0 1", list.ToString());
        }

        [Fact]
        public void push_frontTest()
        {
            var list = new LinkedList<int>();
            Assert.Equal("", list.ToString());
            list.push_front(0);
            Assert.Equal("0", list.ToString());

            list.push_front(0);
            Assert.Equal("0 0", list.ToString());

            list.push_front(1);
            Assert.Equal("1 0 0", list.ToString());
        }

        [Fact]
        public void pop_backTest()
        {
            var list = new LinkedList<int>();
            Assert.Equal("", list.ToString());
            list.push_back(0);
            Assert.Equal("0", list.ToString());

            list.push_back(0);
            Assert.Equal("0 0", list.ToString());

            list.push_back(1);
            Assert.Equal("0 0 1", list.ToString());

            list.pop_back();
            Assert.Equal("0 0", list.ToString());

            list.pop_back();
            Assert.Equal("0", list.ToString());

            list.pop_back();
            Assert.Equal("", list.ToString());
        }

        [Fact]
        public void pop_frontTest()
        {
            var list = new LinkedList<int>();
            Assert.Equal("", list.ToString());
            list.push_front(0);
            Assert.Equal("0", list.ToString());

            list.push_front(0);
            Assert.Equal("0 0", list.ToString());

            list.push_front(1);
            Assert.Equal("1 0 0", list.ToString());

            list.pop_front();
            Assert.Equal("0 0", list.ToString());

            list.pop_front();
            Assert.Equal("0", list.ToString());

            list.pop_front();
            Assert.Equal("", list.ToString());
        }

        [Fact]
        public void insertTest()
        {
            var list = new LinkedList<int>();
            Assert.Equal("", list.ToString());
           
            list.insert(1, 0);
            Assert.Equal("1", list.ToString());

            list.insert(2, 0);
            Assert.Equal("2 1", list.ToString());

            list.insert(3, 2);
            Assert.Equal("2 1 3", list.ToString());
            
            list.insert(4, 2);
            Assert.Equal("2 1 4 3", list.ToString());
        }
        
        [Fact]
        public void atTest()
        {
            var list = new LinkedList<int>();
            list.insert(1, 0);
            list.insert(2, 0);
            list.insert(3, 2);
            list.insert(4, 2);

            Assert.Equal(2, list.at(0));
            Assert.Equal(1, list.at(1));
            Assert.Equal(4, list.at(2));
            Assert.Equal(3, list.at(3));
        }



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

        [Fact]
        public void clearTest()
        {
            var list = new LinkedList<int>();
            list.insert(1, 0);
            list.insert(2, 0);
            list.insert(3, 2);
            list.insert(4, 2);
            list.clear();
            
            Assert.Equal("", list.ToString());
            list.clear();
            Assert.Equal("", list.ToString());
        }
        
        [Fact]
        public void setTest()
        {
            var list = new LinkedList<int>();
            list.insert(1, 0);
            list.insert(2, 0);
            list.insert(3, 2);
            list.insert(4, 2);
           
            list.set(0, 11);
            Assert.Equal("11 1 4 3", list.ToString());

            list.set(1, 222);
            Assert.Equal("11 222 4 3", list.ToString());

            list.set(2, 33);
            Assert.Equal("11 222 33 3", list.ToString());
            
            list.set(3, 4123);
            Assert.Equal("11 222 33 4123", list.ToString());
        }
    }
}