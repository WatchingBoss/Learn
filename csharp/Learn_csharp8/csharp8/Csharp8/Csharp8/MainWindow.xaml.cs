using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

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
        }

        private void Button_1_Clik(object sender, RoutedEventArgs e)
        {
            if(Input_1.Text.Equals("Type int"))
            {
                MessageBox.Show("You should type number to the input box!");
            }
            else
            {
                UInt32 number = Convert.ToUInt32(Input_1.Text);
                UInt32 factorial = GetFactorial(number);

                if (factorial == 0)
                    MessageBox.Show($"The factorial of {number} is greater then max value of uint32, {UInt32.MaxValue}");
                else
                    Output_1.Text = factorial.ToString();
            }
        }

        private UInt32 GetFactorial(uint x)
        {
            if (x == 1) return 1;
            
            return GetFactorial(x-1)*x;
        }

        private void Input_1_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Input_1.Text = string.Empty;
        }
    }
}
