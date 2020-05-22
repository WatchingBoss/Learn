/// my
using FirstLibrary;

/// third part
using Microsoft.Extensions.Configuration;
using System;
using System.Diagnostics;
using System.IO;

/// core
using System.Windows;

namespace Let_go
{
    public partial class MainWindow : Window
    {
        private TraceSwitch ts;

        public MainWindow( ) {
            InitializeComponent( );

            // Configure Trace.Listener and TraceSwitch

            Trace.Listeners.Add(new TextWriterTraceListener(File.CreateText("log.txt")));
            Trace.AutoFlush = true;

            var builder = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true);
            IConfigurationRoot configuration = builder.Build();

            ts = new TraceSwitch(
                displayName: "mySwitch",
                description: "Switch via JSON file"
                );

            configuration.GetSection("mySwitch").Bind(ts);

            // Done Trace configuration

            PrintOutput( );
        }

        private void PrintOutput( ) {
            Trace.WriteLineIf(ts.TraceInfo, "Trace: Call PrintOutput()");

            workWithPersonClass( );
        }

        /// <summary>
        /// Using class's statis methods, instance methods, delegates, operator overload
        /// </summary>
        private void workWithPersonClass( ) {
            int bornNumber = 0;
            string bornAlert = "";

            APerson.logProcreate += ( APerson p1, APerson p2 )
                => bornAlert += $"{DateTime.Now.TimeOfDay}\n";
            APerson.logProcreate += ( APerson p1, APerson p2) 
                => bornAlert += $"{++bornNumber}) {p1.Name} and {p2.Name} made a baby\n";

            APerson david = new APerson {Name = "David", DateOfBirth = new DateTime(1995, 3, 6)};
            APerson kate  = new APerson {Name = "Kate",  DateOfBirth = new DateTime(1996, 4, 15)};
            APerson molly = new APerson {Name = "Molly", DateOfBirth = new DateTime(1994, 2, 28)};

            APerson baby1 = APerson.Procreate( david, kate);
            APerson baby2 = david.ProcreateWith(molly);
            APerson baby3 = david * molly;
            APerson baby4 = kate * david;

            string getPersonInfo( APerson p ) =>
                $"{p.Name} has {p.Children.Count} {(p.Children.Count == 1 ? "child" : "children")}\n";

            string output = getPersonInfo(david) + getPersonInfo(kate) + getPersonInfo(molly);
            foreach ( var child in david.Children )
                output += $"\n{david.Children.IndexOf(child) + 1}) {child.Name}";

            tbTopLeft.Text = output;
            tbTopRight.Text = bornAlert;
        }

        /// <summary>
        /// Using indexer
        /// </summary>
        private void usingIndexer( ) {
            Trace.WriteLineIf(ts.TraceInfo, "Calling List members through indexer");

            Person person = new Person("David", "Mitchel", 23);
            person.Children.Add(new Person("Sam", "Mitchel", 5));
            person.Children.Add(new Person("Mark", "Mitchel", 4));

            string info = $"{person[0].FirstName} :\t{person[0].Age}\n";
            info += $"{person[1].FirstName} : \t{person[1].Age}\n";

            tbTopLeft.Text = info;
        }

        /// <summary>
        /// Sample of using tuple
        /// </summary>
        private void usingTuple( ) {
            Person person = new Person("Jon", "Romeras", 32);

            Trace.WriteLineIf(ts.TraceInfo, "Calling tuple sample");
            // Explicite type definition
            ///(string fname, string lname, int age) personInfo = person.GetInfo();
            var personInfo = person.GetInfo();

            tbTopLeft.Text = $"First name: {personInfo.fname}\n" +
                $"Last name: {personInfo.lname}\n" +
                $"Age: {personInfo.age}";

            Trace.WriteLineIf(ts.TraceInfo, "Deconstructing tuple");
            // Tuple deconstructing
            (string firstName, string lastName, int age) = personInfo;
            tbTopLeft.Text += $"\n\nSame after deconstructing tuple\n\n" +
                $"{firstName}\n" +
                $"{lastName}\n" +
                $"{age}";
        }

        /// <summary>
        /// Sample using Switch Expression
        /// </summary>
        private void usingSwitchExpression( ) {
            object[] values = new object[] { 3, 4.5, 11};
            string message = string.Empty;
            foreach ( var value in values )
                message += value switch
                {
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

        private void DisplayTime( ) {
            // TODO Update using Disparcher
            TimeUsing TimeInst = new TimeUsing();
            TimeInst.RefreshTime( );
            tbTopLeft.Text = $"Date:\n{TimeInst.CurrentDateTime}\n" +
                $"Ticks:\n{TimeInst.CurrentTicks}";
        }
    }
}