/// my
using FirstLibrary;

/// third part
using Microsoft.Extensions.Configuration;

/// core
using System;
using System.Diagnostics;
using System.IO;
using System.Windows;
using System.Net;
using System.Net.NetworkInformation;

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

        }
        private void tbutTopRight_Click( object sender, RoutedEventArgs e ) {
            workWithNetResources( );
        }
     

        private void workWithNetResources( ) {
            Trace.WriteLineIf(ts.TraceInfo, "Trace: Call workWithCommonDotNetTypes()");

            string inputURL = tboxTopLeft.Text, 
                outputServerInfo = "", outputServerPing = "";

            if ( string.IsNullOrWhiteSpace(inputURL) )
                inputURL = "https://google.com";

            Uri uri = default(Uri);

            try {
                uri = new Uri(inputURL);
            } catch ( Exception ex ) {
                MessageBox.Show($"{ex.GetType( ).ToString( )}: {ex.Message}");
                return;
            }

            outputServerInfo = 
                inputURL + '\n' + 
                uri.Scheme + '\n' + 
                uri.Port + '\n' + 
                uri.Host + '\n' + 
                uri.AbsolutePath + '\n' + 
                uri.Query + '\n';

            IPHostEntry entry = new IPHostEntry();
            try {
                entry = Dns.GetHostEntry(uri.Host);
            } catch(Exception ex) {
                MessageBox.Show($"{ex.GetType().ToString()}: {ex.Message}");
            }

            outputServerInfo += $"{entry.HostName} has following IP adresses: \n";
            foreach ( IPAddress address in entry.AddressList )
                outputServerInfo += $"{address} \n";

            try {
                Ping ping = new Ping();
                PingReply reply = ping.Send(uri.Host);
                outputServerPing = $"Status: {reply.Status}\n";

                if ( reply.Status == IPStatus.Success )
                    outputServerPing += $"Reply from {reply.Address} took {reply.RoundtripTime}ms\n";
            } catch (Exception ex) {
                outputServerPing = $"{ex.GetType().ToString()} says: {ex.Message}";
            }

            tbTopLeft.Text = outputServerInfo;
            tbTopRight.Text = outputServerPing;
        }

        /// <summary>
        /// Casting
        /// </summary>
        private void workWithCasting( ) {
            Trace.WriteLineIf(ts.TraceInfo, "Trace: Call workWithCasting()");

            Runner r1 = new Runner("John", new DateTime(1994, 4, 18), 15, 80);
            if ( r1 is APerson ) {
                APerson p1 = r1;
                tbTopLeft.Text += $"\n{p1.StringToWrite( )}\n";
            }

            APerson p2 = new APerson();
            p2.Name = "Kate";
            p2.DateOfBirth = new DateTime(1985, 11, 23);

            Runner r2 = p2 as Runner;

            if ( r2 != null )
                tbTopLeft.Text += $"\n{r2.Name} was born at {r2.DateOfBirth}\n";
            else
                tbTopLeft.Text += "p2 couldn't be cast to Runner type";
        }

        private void usingClassWithInheritance( ) {
            Trace.WriteLineIf(ts.TraceInfo, "Trace: Call usingClassWithInheritance()");

            Runner r1 = new Runner("John", new DateTime(1995, 3, 15), 10, 50);
            tbTopLeft.Text = r1.ResultToString( );
            tbTopRight.Text = r1.StringToWrite( );
        }

        /// <summary>
        /// Using strung Using Dispase() and "using" statement
        /// </summary>
        private void managingMemory( ) {
            Trace.WriteLineIf(ts.TraceInfo, "Trace: Call managingMemory()");

            MyVector v1 = new MyVector(2, -3);
            MyVector v2 = new MyVector(4, 7);
            MyVector v3 = v1 + v2;

            tbTopLeft.Text = $"{v1.ToString( )} + {v2.ToString( )} = {v3.ToString( )}";

            ManageMemory m1 = new ManageMemory();
            ManageMemory m2 = new ManageMemory();

            // Call Dispose to deallocate resourses
            m2.Dispose( );

            using ( ManageMemory m3 = new ManageMemory( ) ) {
                tbTopRight.Text = "m3 instance will be deallocated then";
            }
        }

        /// <summary>
        /// Generics sample
        /// </summary>
        private void workWithGenerics( ) {
            GenericSample<int> intSample = new GenericSample<int>();
            GenericSample<string> strSample = new GenericSample<string>();

            int oneInt = 55;
            string oneStr = "Hello";

            intSample.Data = 55;
            strSample.Data = "Potato";

            tbTopLeft.Text = $"{oneInt} and {intSample.Data} are {intSample.IsSameTo(oneInt)}\n";
            tbTopLeft.Text += $"{oneStr} and {strSample.Data} are {strSample.IsSameTo(oneStr)}\n";

            int first = 6;
            string second = "16";
            byte third = 32;
            short forth = 86;
            long fifth = 985;
            double sixth = 54.12;

            tbTopRight.Text =
                $"Square of {first,-8} is {SimpleMath.Square<int>(first):N0}\n" +
                $"Square of {second,-8} is {SimpleMath.Square<string>(second):N0}\n" +
                $"Square of {third,-8} is {SimpleMath.Square<byte>(third):N0}\n" +
                $"Square of {forth,-8} is {SimpleMath.Square<short>(forth):N0}\n" +
                $"Square of {fifth,-8} is {SimpleMath.Square<long>(fifth):N0}\n" +
                $"Square of {sixth,-8} is {SimpleMath.Square<double>(sixth):N2}\n";
        }

        /// <summary>
        /// Implementing interfaces in APerson class
        /// </summary>
        private void workWithInterfacesImplementation( ) {
            Trace.WriteLineIf(ts.TraceInfo, "Trace: Call workWithInterfacesImplementation");

            APerson[] people = {
                new APerson {Name = "Simon"},
                new APerson {Name = "Kate"},
                new APerson {Name = "Nora"},
                new APerson {Name = "Yalgur"},
                new APerson {Name = "Antonio"}
            };

            string concatNames( APerson[] people ) {
                string result = "";
                foreach ( APerson p in people )
                    result += $"{p.Name}\n";
                return result;
            };

            tbTopLeft.Text = "Before sort:\n" + concatNames(people);
            Array.Sort(people);
            tbTopRight.Text = "After sort:\n" + concatNames(people);
            Array.Sort(people, new APersonCompare( ));
            tbTopRight.Text += "\nAfter Length sort:\n" + concatNames(people);

            var dayly = people[1] as IDaylyLife;
            string daylyLifeLog = $"{dayly.WakeUp()}\n";
            daylyLifeLog += $"{dayly.Sleep( )}\n";

            tbTopLeft.Text += "\n" + daylyLifeLog;
        }

        /// <summary>
        /// Using class's statis methods, instance methods, delegates, operator overload
        /// </summary>
        private void workWithPersonClass( ) {
            int bornNumber = 0;
            string bornAlert = "";

            APerson.logProcreate += ( APerson p1, APerson p2 )
                => bornAlert += $"{DateTime.Now.TimeOfDay}\n";
            APerson.logProcreate += ( APerson p1, APerson p2 )
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