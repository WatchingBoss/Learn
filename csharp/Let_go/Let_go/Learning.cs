using System;

namespace Let_go
{
    internal class Learning : ILearning {
        private DateTime _Time;

        public Learning() {
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

    internal interface ILearning
    {
        string CurrentDateTime {
            get;
        }

        long CurrentTicks {
            get;
        }
    }
}