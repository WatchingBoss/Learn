                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                using System;
using System.Collections.Generic;
using System.Text;

namespace MyLib
{
    [Serializable]
    public class BankAccount
    {
        static private uint _NumberOfIds = 0;

        private readonly uint id;
        private readonly string name;
        private readonly DateTime registrationDate;
        private TimeSpan timeUsing;
        private decimal currentBalance, balanceReturn;

        public DateTime RegistrationDate => this.registrationDate;
        public TimeSpan TimeUsing => UpdateTimeUsing();
        public decimal CurrentBalance => this.currentBalance;

        public decimal BalanceReturn
        {
            get => this.balanceReturn;
            set => this.balanceReturn = BalanceReturn;
        }
        public string Name => this.name;

        //
        // Public methods
        //
        public string DaysOfAccount() => UpdateTimeUsing().ToString();
        public void Income(decimal moneyValue) => this.currentBalance += moneyValue;
        public void Withdraw(decimal moneyValue)
        {
            decimal new_value = this.currentBalance - moneyValue;
            
            if(new_value >= 0)
            {
                this.currentBalance = new_value;
            }
            else
            {
                throw new InvalidOperationException($"Current balance couldn't be negative. You can spend less than {this.currentBalance}");
            }
        }
        public decimal MonthlyReturn() => this.currentBalance * this.balanceReturn / 12.0M;

        public BankAccount(string name)
        {
            BankAccount._NumberOfIds++;
            this.id = BankAccount._NumberOfIds;

            this.name = name;

            this.registrationDate = RandomDate();
            this.timeUsing = DateTime.Today.Subtract(this.registrationDate);

            this.balanceReturn = 0.03M;
        }

        private TimeSpan UpdateTimeUsing()
        {
            TimeSpan newTime = DateTime.Today.Subtract(this.registrationDate);
            this.timeUsing = newTime;
            return newTime;
        }

        private DateTime RandomDate()
        {
            Random gen = new Random();
            DateTime start = new DateTime(2005, 1, 1);
            int range = DateTime.Today.Subtract(start).Days;
            return start.AddDays(gen.Next(range));
        }
    }
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                