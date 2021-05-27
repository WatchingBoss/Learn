using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.EntityFrameworkCore;

namespace Database
{
    public class BloggingContext : DbContext
    {
        public DbSet<Post> Posts { get; set; }
        public DbSet<Blog> Blogs { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder options)
        {
            string path = System.IO.Path.Combine(System.Environment.CurrentDirectory, "database.db");
            options.UseLazyLoadingProxies().UseSqlite($"Data Source={path}");

        }
    }
}
