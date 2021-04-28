using System;
using System.Collections.Generic;
using System.Text;

namespace MyLib
{
    [Serializable]
    public class Person : IComparable<Person>
    {
        private int age;
        private readonly string name;
        private readonly DateTime birthday;
        private BankAccount ba;

        public string Name => this.name;
        public int Age => this.age;
        public DateTime Birthday => this.birthday;
        public BankAccount BankAcc => this.ba;

        public Person(string name, DateTime birthday)
        {
            this.name = name;
            this.birthday = birthday;
            age = DateTime.Today.Subtract(birthday).Days / 365;
            this.ba = new BankAccount(name);
        }

        public int CompareTo(Person other)
        {
            if (this.Name == null && other.Name == null) return 0;
            else if (this.Name == null) return -1;
            else if (other.Name == null) return 1;
            else return this.Name.CompareTo(other.Name);
        }
    }
}
