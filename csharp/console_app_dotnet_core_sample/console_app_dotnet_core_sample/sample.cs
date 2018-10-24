using System;
using System.Linq;
using System.Reflection;

namespace console_app_dotnet_core_sample
{
    internal class Sample
    {
        public static void UserInput()
        {
            Console.Write( "Enter any two number: " );
            string [ ] numbers = Console.ReadLine( ).Split( );
            int [ ] int_numbers = new int [ 2 ];
            for ( short i = 0; i < 2; ++i )
                Int32.TryParse( numbers [ i ], out int_numbers [ i ] );
            int power = ( int )Math.Pow( ( double )int_numbers [ 0 ],
                ( double )int_numbers [ 1 ] );
            Console.WriteLine( $"{int_numbers [ 0 ]} power {int_numbers [ 1 ]} = {power}" );
        }

        public static void Numbers()
        {
            Console.WriteLine( $"bool: size = {sizeof( bool )}" );
            Console.WriteLine( $"char: size = {sizeof( char )}" );
            Console.WriteLine( $"short: size = {sizeof( short )}, max: {short.MaxValue:N0}" );
            Console.WriteLine( $"int: size = {sizeof( int )}, max: {int.MaxValue:N0}" );
            Console.WriteLine( $"long: size = {sizeof( long )}, max: {long.MaxValue:N0}" );
            Console.WriteLine( $"float: size = {sizeof( float )}, max: {float.MaxValue:N0}" );
            Console.WriteLine( $"double: size = {sizeof( double )}, max: {double.MaxValue:N0}" );
            Console.WriteLine( $"decimal: size = {sizeof( decimal )}, max: {decimal.MaxValue}" );
        }

        public static void MethodCount()
        {
            foreach ( var pack in Assembly.GetEntryAssembly( ).GetReferencedAssemblies( ) )
            {
                var a = Assembly.Load( new AssemblyName( pack.FullName ) );
                int methodCount = 0;

                foreach ( var type in a.DefinedTypes )
                    methodCount += type.GetMethods( ).Count( );

                Console.WriteLine( value: $"{a.DefinedTypes.Count( ):N0} types " +
                    $"with {methodCount:N0} methods in {pack.Name} assembly" );
            }
        }

        public static void Fibo( int max )
        {
            int a = 0, b = 1, c = 0;

            while ( b < max )
            {
                Console.WriteLine( $"{b}" );
                c = a;
                a = b;
                b += c;
            }
        }
    }
}