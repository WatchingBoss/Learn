using System.Collections.Generic;

namespace FirstLibrary
{
    public class Person
    {
        private string _firstName, _lastName;
        private int _age;
        private List<Person> _children;

        public string FirstName => _firstName;
        public string LastName => _lastName;
        public int Age { get => _age; set => _age = Age; }
        public List<Person> Children => _children;

        /// <summary>
        /// Using Indexer
        /// </summary>
        /// <param name="index"> </param>
        /// <returns> </returns>
        public Person this[int index] {
            get => Children[index];
            set => Children[index] = value;
        }

        /// <summary>
        /// Constractor for Person class
        /// </summary>
        public Person( string fname, string lname, int age ) {
            _firstName = fname;
            _lastName = lname;
            _age = age;
            _children = new List<Person>( );
        }

        public (string fname, string lname, int age) GetInfo( ) {
            return (fname: _firstName, lname: _lastName, age: _age);
        }
    }
}