using NUnit.Framework;
using System;
using System.ComponentModel.Design;
using System.Windows;
using Let_go;

namespace NUnitTest
{
    public class Tests
    {
        [SetUp]
        public void Setup( ) {
        }

        [Test] [STAThread]
        public void GetPowerTest1( ) {
            uint number = 3, power = 4,
                 expect = 1;

            for ( byte i = 0; i < power; ++i )
                expect *= number;

            Samples sample = new Samples();
            uint result = sample.GetPower( number, power );

            Assert.AreEqual( expect, result );
        }

        [Test]
        public void GetPowerTest2( ) {
            uint number = 2, power = 1;
            uint expect = 2;

            Samples sample = new Samples();
            uint result = sample.GetPower( number, power );

            Assert.AreEqual( expect, result );
        }

    }
}