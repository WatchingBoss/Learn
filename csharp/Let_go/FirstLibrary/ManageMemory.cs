using System;

namespace FirstLibrary
{
    public class ManageMemory : IDisposable
    {
        private bool _disposed;

        public ManageMemory( ) {
            _disposed = false;
        }

        ~ManageMemory( ) {
            if ( _disposed ) return;
            Dispose(false);
        }

        public void Dispose( ) {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose( bool disposing ) {
            if ( _disposed ) return;
            // deallocate unmanaged resourses

            if ( disposing ) {
                // deallocate any other managed resourses
            }

            _disposed = true;
        }
    }

    public struct MyVector
    {
        public int X, Y;

        public (int, int) vec => (X, Y);

        public MyVector( int x, int y ) {
            X = x; Y = y;
        }

        public static MyVector operator +( MyVector v1, MyVector v2 ) =>
            new MyVector(v1.X + v2.X, v1.Y + v2.Y);

        public override string ToString( ) {
            return $"({X},{Y})";
        }
    }
}