using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Channels;
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

        #region Status : string - Status of program
        private string _status = "Ready!";

        /// <summary>Status of program</summary>
        public string Status
        {
            get => _status;
            set => Set(ref _status, value);
        }
        #endregion
    }
}
