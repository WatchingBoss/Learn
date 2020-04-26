using System.Windows;
using System.Windows.Controls;

namespace LearnWPF
{
    /// <summary>
    /// Interaction logic for SecondWindow.xaml
    /// </summary>
    public partial class SecondWindow : Window
    {
        private bool FirstFocusTo_tbLabelKeyAccess = true;

        public SecondWindow()
        {
            InitializeComponent();

            PrintInTopMiddle();
        }

        private void PrintInTopMiddle()
        {
            object x = 50.5;

            textblock_TopMiddle.Text = $"This is x: {x}";
        }

        private void tbLabelKeyAccess_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            txtLabel.Text = tbLabelKeyAccess.Text;
        }

        private void tbLabelKeyAccess_GotFocus(object sender, RoutedEventArgs e)
        {
            if (!FirstFocusTo_tbLabelKeyAccess) return;

            tbLabelKeyAccess.Text = "";
            FirstFocusTo_tbLabelKeyAccess = false;
        }

        private void tbLabelKeyAccess_SelectionChanged(object sender, RoutedEventArgs e)
        {
            TextBox txtBox = sender as TextBox;
            GetSelectedText.Text = "Selected: \n" + txtBox.SelectedText;
        }

        private void FillTextBoxButton_Click(object sender, RoutedEventArgs e)
        {
            GetSelectedText.Text = tbLabelKeyAccess.Text;
        }
    }
}