using System;
using System.Linq;
using System.Collections.Generic;

namespace quickstart
{
  class Program
  {
	  static void Main(string[] args)
	  {
		  /* max_values(); */
		  /* using_var(); */
		  /* invent(); */
		  /* lists(); */
		  /* fibo(); */
	  }

	  public static void fibo()
	  {
		  List<int> fibo_seq = new List<int> {1, 1};

		  for(int i = 0; i < 20; ++i)
		  {
			  int pr_1 = fibo_seq[fibo_seq.Count - 1];
			  int pr_2 = fibo_seq[fibo_seq.Count - 2];
			  int new_num = pr_1 + pr_2;
			  fibo_seq.Add(new_num);
		  }
		  foreach(int i in fibo_seq)
			  Console.WriteLine(i);
	  }

	  public static void lists()
	  {
		  List<string> words = new List<string> {"first", "second", "third"};
		  words.Add("fours");
		  words.Remove("second");
		  int i = 1;
		  foreach(var w in words)
			  Console.WriteLine($"{i++}: {w}");
		  foreach(var w in words)
			  Console.WriteLine($"Index of {w} is {words.IndexOf(w)}");
		  words.Sort();
		  for(int j = 0; j < words.Count; ++j)
			  Console.WriteLine($"{j + 1}: {words[j]}");
		  foreach(var w in words)
			  Console.WriteLine($"Index of {w} is {words.IndexOf(w)}");
	  }

	  public static void invent()
	  {
		  var inventory = new Dictionary<string, int>()
			  {
				  ["First string"] = 15,
				  ["Second string"] = 20,
				  ["Third string"] = 45,
			  };

		  Console.WriteLine($"Inventory on {DateTime.Now:d}");
		  Console.WriteLine($"|{"Item", -20}|{"Quantity", 4}");
		  foreach(var item in inventory)
			  Console.WriteLine($"|{item.Key, -25}|{item.Value, 10}");
	  }

	  public static void using_var()
	  {
		  string[] words = {"first", "second", "thirs"};
		  var word = from i in words where i[0] == 's' select i;
		  foreach(string s in word)
			  Console.WriteLine(s);
	  }

	  public static void max_values()
	  {
		  byte max_byte = byte.MaxValue;
		  uint max_uint = uint.MaxValue;
		  ulong max_ulong = ulong.MaxValue;
		  decimal max_decimal = decimal.MaxValue;
		  float max_float = float.MaxValue;
		  double max_double = double.MaxValue;

		  string output =
			  "max_byte    : " + max_byte        + "\n" +
			  "max_short   : " + ushort.MaxValue + "\n" + 
			  "max_uint    : " + max_uint        + "\n" + 
			  "max_ulong   : " + max_ulong       + "\n" + 
			  "max_decimal : " + max_decimal     + "\n" + 
			  "max_float   : " + max_float       + "\n" +
			  "max_double  : " + max_double;
		  Console.WriteLine(output);
	  }
  }
}
