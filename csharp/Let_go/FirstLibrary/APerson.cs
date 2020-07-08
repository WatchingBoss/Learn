using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;

namespace FirstLibrary
{
    public class APerson: IComparable<APerson>
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
    }
}
