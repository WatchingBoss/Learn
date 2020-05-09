using System.Windows;
using System.Threading;
using System.Windows.Media;

namespace Let_go
{
    public partial class MainWindow : Window
    {
        public MainWindow() {
            InitializeComponent();

            PrintOutput();
        }

        private void PrintOutput() {
            Learning FirstInstance = new Learning();
            FirstInstance.RefreshTime();
            tbTopLeft.Text = $"Date and time:\n{FirstInstance.CurrentDateTime}\n" +
                $"All ticks:\n{FirstInstance.CurrentTicks}";
        }
    }
}