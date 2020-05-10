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
            
        }

        private void DisplayTime() {
            // TODO Update using Disparcher
            TimeUsing TimeInst = new TimeUsing();
            TimeInst.RefreshTime();
            tbTopLeft.Text = $"Date:\n{TimeInst.CurrentDateTime}\n" +
                $"Ticks:\n{TimeInst.CurrentTicks}";
        }
    }
}