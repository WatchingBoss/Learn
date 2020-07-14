using System;
using System.Threading;

namespace FirstLibrary
{
    public class GenericSample<T> where T : IComparable
    {
        private T _data;

        public T Data { get => _data; set => _data = value; }

        public GenericSample( ) => _data = default(T);

        public string IsSameTo( T x ) {
            if ( _data.CompareTo(x) == 0 )
                return "Same";
            return "Different";
        }
    }

    static public class SimpleMath
    {
        static public double Square<T>(T x ) 
            where T : IConvertible {
            double number = x.ToDouble(Thread.CurrentThread.CurrentCulture);
            return number * number;
        }
    }
}
