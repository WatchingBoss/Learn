using System.Windows;
using System.Windows.Input;
using CV_WPF.Infrastructure.Commands;
using CV_WPF.ViewModels.Base;

namespace CV_WPF.ViewModels
{
    internal class MainWindowViewModel : ViewModel
    {
        public MainWindowViewModel()
        {
            #region Commands

            CloseApplicationCommand = new LambdaCommand(OnCloseApplicationCommandExecute, CanCloseApplicationCommandExecute);

            #endregion
        }

        #region Window Title
        private string title = "Statistic Analyses CV";

        /// <summary>Window Title</summary>
        public string Title
        {
            get => title;
            set => Set(ref title, value);
        }
        #endregion

        #region Status : string - Status of program
        private string status = "Ready!";

        /// <summary>Status of program</summary>
        public string Status
        {
            get => status;
            set => Set(ref status, value);
        }
        #endregion

        #region Commands

        #region CloseApplicationCommand
        public ICommand CloseApplicationCommand { get; }
        public bool CanCloseApplicationCommandExecute(object p) => true;
        public void OnCloseApplicationCommandExecute(object p)
        {
            Application.Current.Shutdown();
        }
        #endregion
        
        #endregion
    }
}
