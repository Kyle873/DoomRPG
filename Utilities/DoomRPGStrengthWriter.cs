using System;
using System.IO;

namespace DoomRPG
{
	static class Program
	{
		public static void Main(string[] Args)
		{
			float strength = 1.01f;
            TextWriter output = File.CreateText("Strength.txt");
			
            for (int i = 1; i <= 32000; i++)
			{
                string item = "actor Strength" + i + " : Strength { DamageFactor \"Normal\", " + string.Format("{0:0.00}", strength) + " }";
                Console.WriteLine(item);
                output.WriteLine(item);
				strength += 0.01f;
			}
            
            Console.ReadLine();
		}
	}
}
