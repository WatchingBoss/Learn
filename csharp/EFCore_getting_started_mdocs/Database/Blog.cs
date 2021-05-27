using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace Database
{
    public class Blog
    {
        public int BlogID { get; set; }
        public string URL { get; set; }
        public  string Title { get; set; }

        public virtual ICollection<Post> Posts { get; }

        public Blog()
        {
            Posts = new ObservableCollection<Post>();
        }
    }
}
