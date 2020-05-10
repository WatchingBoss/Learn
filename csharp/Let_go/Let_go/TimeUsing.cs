using System;
using System.Windows.Controls;

namespace Let_go
{
    internal class TimeUsing : ITimeUsing
    {
        private DateTime _Time;

        public TimeUsing() {
            _Time = DateTime.Now;
        }

        public void RefreshTime() => _Time = DateTime.Now;

        private string _currentDateTime;
        public string CurrentDateTime {
            get => _currentDateTime = _Time.ToString();
        }
        private long _currentTicks;
        public long CurrentTicks {
            get => _currentTicks = _Time.Ticks;
        }
    } 

    internal interface ITimeUsing
    {
        string CurrentDateTime {
            get;
        }

        long CurrentTicks {
            get;
        }
    }
}