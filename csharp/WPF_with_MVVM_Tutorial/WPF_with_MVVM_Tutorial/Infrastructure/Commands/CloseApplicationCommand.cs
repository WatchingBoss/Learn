using System.Windows;
using CV_WPF.Infrastructure.Commands.Base;

namespace CV_WPF.Infrastructure.Commands
{
    internal class CloseApplicationCommand : Command
    {
        public override bool CanExecute(object parameter) => true;

        public override void Execute(object parameter) => Application.Current.Shutdown();
    }
}
