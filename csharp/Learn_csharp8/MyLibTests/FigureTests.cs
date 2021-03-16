using System;
using NUnit.Framework;
using MyLib;

namespace MyLibTests
{
    public class FigureTests
    {
        private Figure _figure_1;
        private UInt32 width = 7, height = 4;

        [SetUp]
        public void Setup()
        {
            _figure_1 = new Figure(this.width, this.height);
        }

        [Test]
        public void TestPerimeter()
        {
            UInt32 test = _figure_1.Perimeter;
            UInt32 right = (this.width + this.height) * 2;

            Assert.AreEqual(test, right);
        }

        [Test]
        public void TestSquare()
        {
            UInt32 test = _figure_1.Square;
            UInt32 right = this.width * this.height;

            Assert.AreEqual(test, right);
        }
    }
}