using WPF_with_MVVM_Tutorial.ViewModels.Base;

namespace WPF_with_MVVM_Tutorial.ViewModels
{
    internal class MainWindowViewModel : ViewModel
    {
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
    }
}
