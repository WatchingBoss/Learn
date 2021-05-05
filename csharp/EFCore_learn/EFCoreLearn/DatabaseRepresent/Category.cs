using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel.DataAnnotations.Schema;

namespace DatabaseRepresent
{
    public class Category
    {
        public int CategoryID { get; set; }
        public string CategoryName { get; set; }
        
        [Column(TypeName = "ntext")]
        public string Description { get; set; }

        public virtual ICollection<Product> Products { get; set; }

        public Category()
        {
            this.Products = new List<Product>();
        }

    }
}
