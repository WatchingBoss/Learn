using System;
using System.Collections.Generic;
using System.Text;

namespace Let_go
{
    public class Samples
    {
        public Samples( ) {

        }

        /// <summary>
        /// Function for test sample
        /// </summary>
        /// <param name="number">Number to exponent</param>
        /// <param name="power">Exponent value</param>
        /// <returns>The exponent of number</returns>
        public uint GetPower( uint number, uint power ) {
            uint result = 1;
            for ( byte i = 0; i < power; ++i )
                result *= number;
            return result;
        }
    }
}
