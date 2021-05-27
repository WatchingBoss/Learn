using System;
using System.Linq;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Storage;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Database;

namespace EFCore_getting_started_mdocs_console
{
    class Program
    {
        static void Main(string[] args)
        {
            ConsoleKey key = ConsoleKey.A;

            while(key != ConsoleKey.Escape || key != ConsoleKey.Q)
            {
                Console.WriteLine("Menu:\n" +
                    "1. List Blogs\n" +
                    "2. List Posts\n" +
                    "3. List all tables\n" +
                    "4. Add random blog\n" +
                    "5. Fill blog with posts\n");

                key = Console.ReadKey().Key;
                Console.WriteLine("\n");

                switch(key)
                {
                    case ConsoleKey.D1:
                        break;
                    case ConsoleKey.D2:
                        break;
                    case ConsoleKey.D3:
                        break;
                    case ConsoleKey.D4:
                        break;
                    default:
                        Console.WriteLine("Wrong input. Try again!");
                        break;
                }
            }
        }

        private static void ListBlogs()
        {
            using(var context = new BloggingContext())
            {
                Console.WriteLine($"{"Blog ID", -7} {"Title", -20} {"URL", -30}");
                foreach (Blog blog in context.Blogs)
                {
                    Console.WriteLine($"{blog.BlogID, -7} {blog.Title, -20} {blog.URL}, -30");
                }
            }
        }

        private static void ListPosts()
        {
            using (var context = new BloggingContext())
            {
                Console.WriteLine($"Choose Blog ID: from 0 to {context.Blogs.Count()}");
                int id = int.Parse(Console.ReadLine());

                Console.WriteLine($"{"Post ID",-7} {"Title",-20} {"Content"}");
                foreach (Post post in context.Posts.Where(p => p.BlogID == id))
                {
                    Console.WriteLine($"{post.PostID,-7} {post.Title,-20} {post.Content}");
                }
            }
        }

        private static void ListAllTables()
        {

        }
    }
}
