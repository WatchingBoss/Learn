using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace FirstLibrary
{
    public class APerson
    {
        public string Name;
        public DateTime DateOfBirth;
        public List<APerson> Children = new List<APerson>();

        public static APerson Procreate( APerson p1, APerson p2) {
            APerson baby = new APerson { Name = $"Baby of {p1.Name} and {p2.Name}"};

            p1.Children.Add(baby);
            p2.Children.Add(baby);

            return baby;
        }

        public static APerson operator *( APerson p1, APerson p2 ) => Procreate(p1, p2);

        public APerson ProcreateWith( APerson p) {
            return Procreate( this, p);
        }

        public string StringToWrite( ) {
            return String.Format( "{0} was born on a {1:dddd}", Name, DateOfBirth);
        }
    }
}
