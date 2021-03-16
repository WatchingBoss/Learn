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
