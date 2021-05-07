using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.Extensions.Logging;

namespace EFCore_SQLite_Console
{
    public class ConsoleLoggerProvider : ILoggerProvider
    {
        public ILogger CreateLogger(string categoryName)
        {
            return new ConsoleLogger();
        }

        public void Dispose() { }
    }

    public class ConsoleLogger : ILogger
    {
        public IDisposable BeginScope<TState> (TState state)
        {
            return null;
        }

        public bool IsEnabled(LogLevel logLevel)
        {
            switch(logLevel)
            {
                case LogLevel.Trace:
                case LogLevel.Information:
                case LogLevel.None:
                    return false;
                case LogLevel.Debug:
                case LogLevel.Warning:
                case LogLevel.Error:
                case LogLevel.Critical:
                default:
                    return true;
            }
        }

        public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception ex, Func<TState, Exception, string> formatter)
        {
            if (eventId.Id == 20100)
            {
                string message = $"Level: {logLevel}; EventID: {eventId}";

                if (state != null)
                {
                    message += $"; State: {state}";
                }
                if (ex != null)
                {
                    message += $"; Exception: {ex.Message}";
                }

                Console.WriteLine(message);
            }
        }
    }
}
