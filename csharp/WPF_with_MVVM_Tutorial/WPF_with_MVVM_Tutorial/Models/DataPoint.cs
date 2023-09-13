namespace CV_WPF.Models
{
    internal struct DataPoint
    {
        public DataPoint(double x, double y)
        {
            XValue = x;
            YValue = y;
        }

        public double XValue { get; set; }
        public double YValue { get; set; }
    }
}
