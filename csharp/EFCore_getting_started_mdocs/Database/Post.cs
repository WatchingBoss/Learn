using System;
using System.Collections.Generic;
using System.Text;

namespace Database
{
    public class Post
    {
        public int PostID { get; set; }
        public string Title { get; set; }
        public string Content { get; set; }

        public int BlogID { get; set; }
        public virtual Blog Blog { get; set; }
    }
}
