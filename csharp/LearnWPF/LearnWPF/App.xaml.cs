using System.Globalization;
using System.Threading;
using System.Windows;
using System.Windows.Threading;

namespace LearnWPF
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void MainApp(object sender, StartupEventArgs e)
        {
            Thread.CurrentThread.CurrentCulture = new CultureInfo("ru-Ru");

            //MainWindow win = new MainWindow();
            SecondWindow win = new SecondWindow();
            win.Show();
        }

        private void Application_DispatcherUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            MessageBox.Show("Unhandle exception occured: " + e.Exception.Message,
                "Global exception handling", MessageBoxButton.OK, MessageBoxImage.Warning);
            e.Handled = true;
        }
    }
}