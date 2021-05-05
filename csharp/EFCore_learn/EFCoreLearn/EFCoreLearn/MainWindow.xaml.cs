using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.EntityFrameworkCore;
using DatabaseRepresent;

namespace EFCoreLearn
{
    /// <summary>
    /// Northwind database window
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            tbMessage.Text = QueryingCategories();
        }

        private string QueryingCategories()
        {
            string message = "Categories and how many products they have: \n";

            using(var db = new Northwind())
            {
                IQueryable<Category> cats = db.Categories
                    .Include(c => c.Products);

                foreach(Category c in cats)
                {
                    message += $"{c.CategoryName} has {c.Products.Count} products\n";
                }
            }

            return message;
        }
    }
}
