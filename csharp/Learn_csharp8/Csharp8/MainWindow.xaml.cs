using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Text.Json;
using MyLib;

namespace Csharp8
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            dataDirectoryPath = Path.Combine(Directory.GetCurrentDirectory(), "data");
            PeopleListFilePathBinary = Path.Combine(dataDirectoryPath, "PeopleList.bin");
            PeopleListFilePathJSON = Path.Combine(dataDirectoryPath, "PeopleList.json");
            BankAppInit();


        }

        

        //
        // Person and BankAccount application

        List<Person> PeopleList;
        readonly string dataDirectoryPath;
        readonly string PeopleListFilePathBinary, PeopleListFilePathJSON;

        private void btBankAccountIncome_Click(object sender, RoutedEventArgs e)
        {
            Person p = (Person)cbPeopleList.SelectedItem;
            int number = Convert.ToInt32(tboxPersonBankAccountMoneyChange.Text);
            p.BankAcc.Income(number);

            tboxPersonBankAccountMoneyChange.Text = String.Empty;

            tbPersonBankAccountBalance.Text = Convert.ToString(p.BankAcc.CurrentBalance);
        }

        private void btBankAccountWithdraw_Click(object sender, RoutedEventArgs e)
        {
            Person p = (Person)cbPeopleList.SelectedItem;
            int number = Convert.ToInt32(tboxPersonBankAccountMoneyChange.Text);

            try
            {
                p.BankAcc.Withdraw(number);
            }
            catch(Exception ex)
            {
                MessageBox.Show($"Withdraw error: {ex.Message}");
            }

            tboxPersonBankAccountMoneyChange.Text = String.Empty;

            tbPersonBankAccountBalance.Text = Convert.ToString(p.BankAcc.CurrentBalance);
        }

        private void btAddNewPerson_Click(object sender, RoutedEventArgs e)
        {
            int year = default, month = default, day = default;
            string name = default;

            int minYear = DateTime.Today.Year - 120,
                maxYear = DateTime.Today.Year - 18;

            try
            {
                year = getNumberAndCheckValidation(tboxPersonNewBirthdayYear.Text, minYear, maxYear);
                month = getNumberAndCheckValidation(tboxPersonNewBirthdayMonth.Text, 1, 12);
                day = getNumberAndCheckValidation(tboxPersonNewBirthdayDay.Text, 1, 31);
                name = tboxPersonNewName.Text;

                PeopleList.Add(new Person(name, new DateTime(year, month, day)));
                PeopleList.Sort(delegate(Person p1, Person p2)
                {
                    if (p1.Name == null && p2.Name == null) return 0;
                    else if (p1.Name == null) return -1;
                    else if (p2.Name == null) return 1;
                    else return p1.Name.CompareTo(p2.Name);
                });
            }
            catch (ArgumentException ex)
            {
                MessageBox.Show($"Date error: {ex.Message}");
            }

            tboxPersonNewName.Text = String.Empty;
            tboxPersonNewBirthdayDay.Text = String.Empty;
            tboxPersonNewBirthdayMonth.Text = String.Empty;
            tboxPersonNewBirthdayYear.Text = String.Empty;

            cbPeopleList.ItemsSource = PeopleList;
            cbPeopleList.Items.Refresh();
            cbPeopleList.InvalidateArrange();
            cbPeopleList.UpdateLayout();
        }
        private void cbPeopleList_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Person p = (Person)cbPeopleList.SelectedItem;

            tbPersonName.Text = $"Name: {p.Name}";
            tbPersonAge.Text = $"Age: {p.Age}";
            tbPersonBirthday.Text = $"Birthday: {p.Birthday:d}";
            tbPersonBankAccountBalance.Text = Convert.ToString(p.BankAcc.CurrentBalance);
        }

        private int getNumberAndCheckValidation(string number, int min, int max)
        {
            if(int.TryParse(number, out int x))
            {
                if (x >= min & x <= max)
                    return x;
                else
                    throw new ArgumentException($"{x} not valid for range {min} - {max}");
            }
            else
            {
                throw new ArgumentException("No number in box");
            }
        }
        private void btSaveToFile_Click(object sender, RoutedEventArgs e)
        {
            string jsonString = JsonSerializer.Serialize<List<Person>>(PeopleList, new JsonSerializerOptions { WriteIndented = true });
            File.WriteAllText(PeopleListFilePathJSON, jsonString);

            using (Stream stream = File.Create(PeopleListFilePathBinary))
            {
                var binaryFormatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                binaryFormatter.Serialize(stream, PeopleList);
            }
        }
        private void BankAppInit()
        {
            if (!Directory.Exists(dataDirectoryPath))
            {
                Directory.CreateDirectory(dataDirectoryPath);
            }

            if (File.Exists(PeopleListFilePathBinary))
            {
                using (Stream stream = File.Open(PeopleListFilePathBinary, FileMode.Open))
                {
                    var binaryFormatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                    PeopleList = (List<Person>)binaryFormatter.Deserialize(stream);
                }
            }
            else
            {
                PeopleList = new List<Person>();
            }

            cbPeopleList.ItemsSource = PeopleList;
        }
        // End of Person and BankAccount application
        //

        /// <summary>
        /// Use simplifine of switch statement frome C# 8.0
        /// </summary>
        private void SimpleSwitchWithPatternMatching(double x)
        {
            TextBlock_1.Text = x switch
            { 
                double when x > 36.4 & x < 36.8 => "It's perfect temperature",
                double when x < 36 => "You have too low temperature",
                double when x > 37 => "You have too high temperature",
                _ => "Your temperature is fine"
            };
        }

        private void Button_1_Clik(object sender, RoutedEventArgs e)
        {
            if(UInt32.TryParse(Input_1.Text, out UInt32 x))
            {
                UInt32 factorial = GetFactorial(x);

                if (factorial == 0)
                    MessageBox.Show($"The factorial of {x} is greater then max value of uint32, {UInt32.MaxValue}");
                else
                    Output_1.Text = factorial.ToString();
            }
            else
            {
                MessageBox.Show("You should type number to the input box!");
            }
        }

        private UInt32 GetFactorial(UInt32 x)
        {
            if (x == 1) return 1;
            
            return GetFactorial(x-1)*x;
        }

        private void Input_1_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Input_1.Text = string.Empty;
        }

        private void InputTemp_PreviewKeyUp(object sender, KeyEventArgs e)
        {
            if (double.TryParse(InputTemp.Text, out double result))
            {
                SimpleSwitchWithPatternMatching(result);
            }
        }

        private void InputTemp_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            InputTemp.Text = string.Empty;
        }

    }
}
