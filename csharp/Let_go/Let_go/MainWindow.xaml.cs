using System.Windows;
using System;
using System.Diagnostics;
using System.IO;
using Microsoft.Extensions.Configuration;
using System.Runtime.InteropServices.WindowsRuntime;

namespace Let_go
{
    public partial class MainWindow : Window
    {
        TraceSwitch ts;

        public MainWindow() {
            InitializeComponent();

            Trace.Listeners.Add( new TextWriterTraceListener(File.CreateText("log.txt")));
            Trace.AutoFlush = true;

            var builder = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true);
            IConfigurationRoot configuration = builder.Build();

            ts = new TraceSwitch(
                displayName: "mySwitch",
                description: "Switch via JSON file"
                );

            configuration.GetSection( "mySwitch" ).Bind( ts );

            PrintOutput();
        }

        private void PrintOutput() {
            Trace.WriteLineIf( ts.TraceInfo, "Trace: Call PrintOutput()");
            
        }

        /// <summary>
        /// Sample using Switch Expression
        /// </summary>
        private void usingSwitchExpression( ) {
            object[] values = new object[] { 3, 4.5, 11};
            string message = string.Empty;
            foreach(var value in values)
                message += value switch {
                int thisInt when thisInt > 10 => $"{thisInt} is int and greater then 10\n",
                int thisInt when thisInt <= 10 => $"{thisInt} is int and less or equal 10\n",
                Double thisDouble => $"{thisDouble} is double\n",
                _ => "This is default value\n"
            };

            tbTopLeft.Text = message;
        }
        
        private void usingPatternMatchingInSwitch( ) {
            byte integral_8_bits = Byte.MaxValue;
            short integral_16_bits = Int16.MaxValue;
            int integral_32_bits = Int32.MaxValue;
            long integral_64_bits = Int64.MaxValue;
            double float_64_bits = Double.MaxValue;
            decimal float_128_bits = Decimal.MaxValue;

            Object[] differentTypes = new Object[] {
                integral_8_bits, integral_16_bits,
                integral_32_bits, integral_64_bits,
                float_64_bits, float_128_bits
            };
            
            string toMessage = String.Empty;
            foreach ( var thisVar in differentTypes )
                switch ( thisVar ) {
                    case Byte thisByte:
                        toMessage += $"{thisByte} is a max value of byte\n";
                        break;
                    case Int16 thisShort:
                        toMessage += $"{thisShort} is a max value of short\n";
                        break;
                    case Int32 thisInt:
                        toMessage += $"{thisInt} is a max value of int\n";
                        break;
                    case Int64 thisLong:
                        toMessage += $"{thisLong} is a max value of long\n";
                        break;
                    case Double thisDouble:
                        toMessage += $"{thisDouble} is a max value of double\n";
                        break;
                    case Decimal thisDecimal:
                        toMessage += $"{thisDecimal} is a max value of decimal\n";
                        break;
                    default:
                        tbTopLeft.Text += "This is default";
                        break;
                }
            tbTopLeft.Text = toMessage;
        }

        private void DisplayTime() {
            // TODO Update using Disparcher
            TimeUsing TimeInst = new TimeUsing();
            TimeInst.RefreshTime();
            tbTopLeft.Text = $"Date:\n{TimeInst.CurrentDateTime}\n" +
                $"Ticks:\n{TimeInst.CurrentTicks}";
        }
    }
}