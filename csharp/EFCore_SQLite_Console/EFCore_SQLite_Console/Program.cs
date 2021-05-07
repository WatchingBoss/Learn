using System;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace EFCore_SQLite_Console
{
    class Program
    {
        static void Main(string[] args)
        {
            QueryingCategories();
            QueryingProducts();
            QueryingWithLike();
        }

        private static void QueryingCategories()
        {
            using(var db = new Northwind())
            {
                var loggerFactory = db.GetService<ILoggerFactory>();
                loggerFactory.AddProvider(new ConsoleLoggerProvider());

                IQueryable<Category> cats = db.Categories
                    .TagWith("Categories query")
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
                var loggerFactory = db.GetService<ILoggerFactory>();
                loggerFactory.AddProvider(new ConsoleLoggerProvider());

                Console.WriteLine("Products that costs more than a price, highest at top");

                //string input = string.Empty;
                decimal price = 60;

                //while (!decimal.TryParse(input, out price))
                //{
                //    Console.WriteLine("Enter the product price: ");
                //    input = Console.ReadLine();
                //}
                
                IQueryable<Product> prods = db.Products
                    .TagWith("Products filtered by price and sorted")
                    .Where(p => p.Cost > price)
                    .OrderByDescending(p => p.Cost);

                foreach(Product p in prods)
                {
                    Console.WriteLine($"{p.ProductID, -4}: {p.ProductName, -30} costs {p.Cost, -7:$#,##0.00} and has {p.Stock, -3} in stock");
                }
            }
        }

        private static void QueryingWithLike()
        {
            using(var db = new Northwind())
            {
                var loggerFactory = db.GetService<ILoggerFactory>();
                loggerFactory.AddProvider(new ConsoleLoggerProvider());

                string input = "er";

                IQueryable<Product> prods = db.Products
                    .TagWith("Products query with Like")
                    .Where(p => EF.Functions.Like(p.ProductName, $"%{input}%"));

                foreach(Product p in prods)
                {
                    Console.WriteLine($"{p.ProductName, -40} has {p.Stock, -4} units in stock. Discounted? {p.Discontinued, 5}");
                }
            }
        }
    }
}
