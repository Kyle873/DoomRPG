using System;
using System.IO;

namespace DoomRPG
{
	static class Program
	{
		public static void Main(string[] Args)
		{
            Console.ForegroundColor = ConsoleColor.Green;
            string filename = @"..\DoomRPG\Scripts\RPG.acs";
            string[] contents = File.ReadAllLines(filename);
            Console.WriteLine("Opening RPG.acs...");
            
            for (int i = 0; i < contents.Length; i++)
                if (contents[i].Contains("TimeStamp"))
                {
                    string date = DateTime.Now.ToLongDateString();
                    string time = DateTime.Now.ToLongTimeString();
                    string line = "str TimeStamp = \"" + date + " at " + time + "\";";
                    contents[i] = line;
                    File.WriteAllLines(filename, contents);
                    Console.WriteLine("Updated Timestamp!");
                    Console.ResetColor();
                    return;
                }
		}
	}
}
