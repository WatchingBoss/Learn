using System.Windows;
using WPF_with_MVVM_Tutorial.Infrastructure.Commands.Base;

namespace WPF_with_MVVM_Tutorial.Infrastructure.Commands
{
    internal class CloseApplicationCommand : Command
    {
        public override bool CanExecute(object parameter) => true;

        public override void Execute(object parameter) => Application.Current.Shutdown();
    }
}
