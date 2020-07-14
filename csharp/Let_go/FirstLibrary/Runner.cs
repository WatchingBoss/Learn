using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace FirstLibrary
{
    public class Runner : APerson
    {
        private double _speed, _distance, _time;

        public double Speed => _speed;
        public double Distance => _distance;
        public double Time => _time;

        /// <summary>
        /// Runner constructor
        /// </summary>
        /// <param name="name">Name</param>
        /// <param name="date">Date of birth</param>
        /// <param name="distance">Runned distance</param>
        /// <param name="time">Whole time of running</param>
        public Runner( string name, DateTime date, double distance, double time) {
            Name = name;
            DateOfBirth = date;
            _distance = distance;
            _time = time;

            _speed = time / distance;
        }

        public string ResultToString( ) {
            return $"Distance: {_distance} km\n" +
                $"Time: {_time} min\n" +
                $"Speed: {_speed} kpm\n";
        }
    }
}
