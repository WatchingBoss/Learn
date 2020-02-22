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
using System.Reflection;

namespace LearnWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            ComboBoxColors.ItemsSource = new String[]{ "Aqua", "Pink", "Yellow", "Gray", "Cyan" };
        }

        private void MainGrid_MouseUp(object sender, MouseButtonEventArgs e)
        {
            MessageBox.Show("Clicked at: " + e.GetPosition(this).ToString());
        }

        private void MainGrid_MouseDown(object sender, MouseButtonEventArgs e)
        {
            MessageBox.Show("Clicked at: " + e.GetPosition(this).ToString());
        }

        private void RedButton_Click(object sender, RoutedEventArgs e)
        {
            TextBlock1.Foreground = Brushes.Red;
            TextBlock2.Text = "You clicked red button";
        }

        private void GreenButton_Click(object sender, RoutedEventArgs e)
        {
            TextBlock1.Foreground = Brushes.Green;
            TextBlock2.Text = "You clicked green button";
        }

        private void BlueButton_Click(object sender, RoutedEventArgs e)
        {
            TextBlock1.Foreground = Brushes.Blue;
            TextBlock2.Text = "You clicked blue button";
        }

        private void ComboBoxColors_SelectionChanged(object sender, RoutedEventArgs e)
        {
            String SelectedItem = ComboBoxColors.SelectedItem.ToString();
            Type t = typeof(Brushes);
            TextBlock1.Foreground = (Brush)t.GetProperty(SelectedItem).GetValue(null, null);
            TextBlock2.Text = ComboBoxColors.SelectedItem.ToString();
        }
    }

}
