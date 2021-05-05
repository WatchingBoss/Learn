using System;
using System.Linq;
using Microsoft.EntityFrameworkCore;

namespace EFCore_SQLite_Console
{
    class Program
    {
        static void Main(string[] args)
        {
         //   QueryingCategories();
            QueryingProducts();
        }

        private static void QueryingCategories()
        {
            using(var db = new Northwind())
            {
                IQueryable<Category> cats = db.Categories
                    .Include(c => c.Products);

                foreach(Category c in cats)
                {
                    Console.WriteLine($"{c.CategoryName} has {c.Products.Count} products\n");
                }
            }
        }

        private static void QueryingProducts()
        {
            using(var db = new Northwind())
            {
                Console.WriteLine("Products that costs more than a price, highest at top");

                string input = string.Empty;
                decimal price = 60;

                //while(!decimal.TryParse(input, out price))
                //{
                //    Console.WriteLine("Enter the product price: ");
                //    input = Console.ReadLine();
                //}

                IQueryable<Product> prods = db.Products
                    .Where(p => p.Cost > price)
                    .OrderByDescending(p => p.Cost);

                foreach(Product p in prods)
                {
                    Console.WriteLine($"{p.ProductID, -4}: {p.ProductName, -30} costs {p.Cost, -7:$#,##0.00} and has {p.Stock, -3} in stock");
                }
            }
        }
    }
}
