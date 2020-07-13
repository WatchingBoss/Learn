using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;

namespace FirstLibrary
{
    public class APerson: IComparable<APerson>, IDaylyLife
    {
        public delegate void logProcreateHandler( APerson p1, APerson p2);
        public static logProcreateHandler logProcreate;

        public string Name;
        public DateTime DateOfBirth;
        public List<APerson> Children = new List<APerson>();

        public static APerson Procreate( APerson p1, APerson p2) {
            APerson baby = new APerson { Name = $"Baby of {p1.Name} and {p2.Name}", 
                DateOfBirth = DateTime.Now};

            p1.Children.Add(baby);
            p2.Children.Add(baby);

            logProcreate?.Invoke( p1, p2);

            return baby;
        }

        public static APerson operator *( APerson p1, APerson p2 ) => Procreate(p1, p2);

        public APerson ProcreateWith( APerson p) {
            return Procreate( this, p);
        }

        public string StringToWrite( ) {
            return String.Format( "{0} was born on a {1:dddd}", Name, DateOfBirth);
        }

        public int CompareTo( [AllowNull] APerson other ) {
            return Name.CompareTo(other.Name);
        }

        public string WakeUp( ) => $"{Name} waked up";
        public string Sleep( ) => $"{Name} is sleeping";
    }

    public class APersonCompare: IComparer<APerson>
    {
        public int Compare( APerson x, APerson y ) {
            int result = x.Name.Length.CompareTo(y.Name.Length);

            if ( result == 0 )
                return x.Name.CompareTo(y.Name);

            return result;
        }
    }

    /// <summary>
    /// Defien interface with(out) default implementation of methods
    /// </summary>
    public interface IDaylyLife
    {
        // WakeUp has no default implementation
        string WakeUp( );
        // Sleep has default implementation
        string Sleep( ) => "Person has gotten sleep";
    }
}
