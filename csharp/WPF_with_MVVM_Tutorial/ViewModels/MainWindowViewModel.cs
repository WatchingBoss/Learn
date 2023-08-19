using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WPF_with_MVVM_Tutorial.ViewModels.Base;

namespace WPF_with_MVVM_Tutorial.ViewModels
{
    internal class MainWindowViewModel : ViewModel
    {
        #region Window Title
        private string _title = "Statistic Analyses CV";

        /// <summary>Window Title</summary>
        public string Title
        {
            get => _title;
            set => Set(ref _title, value);
        }
        #endregion
    }
}
