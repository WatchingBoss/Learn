using System;

namespace MyLib
{
    /// <summary>
    /// Geometric figure with 4 angles
    /// </summary>
    public class Figure
    {
        //
        // Variables
        //

        private UInt32 width, height;
        private UInt32 perimeter, square;

        //
        // Properties
        //

        public UInt32 Width
        {
            get => this.width;
            set => this.width = Width;
        }
        public UInt32 Height
        {
            get => this.height;
            set => this.height = Height;
        }
        public UInt32 Perimeter => this.perimeter;
        public UInt32 Square => this.square;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="width">Width of figure</param>
        /// <param name="height">Height of figure</param>
        public Figure(UInt32 width = 5, UInt32 height = 5)
        {
            this.width = width;
            this.height = height;

            this.CalcSquare();
            this.CalcPerimeter();
        }

        //
        // Instance functions
        //

        public void CalcPerimeter()
        {
            this.perimeter = CalcPerimeter(this.width, this.height);
        }
        public void CalcSquare()
        {
            this.square = CalcSquare(this.width, this.height);
        }

        //
        // Static functions
        //

        public static UInt32 CalcPerimeter(UInt32 width, UInt32 height)
            => (width + height) * 2;
        public static UInt32 CalcSquare(UInt32 width, UInt32 height) 
            => width * height;
    }
}
