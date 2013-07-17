using System;
using System.IO;

namespace DoomRPG
{
	static class Program
	{
		static int[] XPAmounts =
		{
			20, 	// Zombieman
			30,		// Shotgun Guy
			70,		// Chaingun Guy
			60,		// Imp
			150,	// Demon
			400,	// Cacodemon
			500,	// Hell Knight
			1000,	// Baron of Hell
			100,	// Lost Soul
			400,	// Pain Elemental
			300,	// Revenant
			600,	// Fatso
			500,	// Arachnotron
			700,	// Arch-Vile
			4000,	// Cyberdemon
			3000,	// Spider Mastermind
            100,    // Wolfenstein SS
 		};

        static string[] fileNames =
        {
            "zombiemen",
            "sergeants",
            "comando",
            "imps",
            "demons",
            "spectre",
            "knight",
            "baron",
            "lostsoul",
            "pain",
            "spiders",
            "cacodemo",
            "revenant",
            "mancubus",
            "archvile",
            "mastermind",
            "cyberdemon",
            "nazis",
        };

        static string[][] files =
        {
            File.ReadAllLines(fileNames[0] + ".dat"),
            File.ReadAllLines(fileNames[1] + ".dat"),
            File.ReadAllLines(fileNames[2] + ".dat"),
            File.ReadAllLines(fileNames[3] + ".dat"),
            File.ReadAllLines(fileNames[4] + ".dat"),
            File.ReadAllLines(fileNames[5] + ".dat"),
            File.ReadAllLines(fileNames[6] + ".dat"),
            File.ReadAllLines(fileNames[7] + ".dat"),
            File.ReadAllLines(fileNames[8] + ".dat"),
            File.ReadAllLines(fileNames[9] + ".dat"),
            File.ReadAllLines(fileNames[10] + ".dat"),
            File.ReadAllLines(fileNames[11] + ".dat"),
            File.ReadAllLines(fileNames[12] + ".dat"),
            File.ReadAllLines(fileNames[13] + ".dat"),
            File.ReadAllLines(fileNames[14] + ".dat"),
            File.ReadAllLines(fileNames[15] + ".dat"),
            File.ReadAllLines(fileNames[16] + ".dat"),
            File.ReadAllLines(fileNames[17] + ".dat"),
        };
        
        public static void Main(string[] Args)
		{
            Console.WriteLine("Optimizing...");

            try
            {
                for (int i = 0; i < XPAmounts.Length; i++)
                {
                    for (int j = 0; j < files[i].Length; j++)
                    {
                        if (files[i][j].Contains("DropItem"))
                            RemoveDrop(files[i], j);
                        if (files[i][j].Contains("Death:"))
                            AddXP(files[i], j, i);
                    }
                    File.WriteAllLines(fileNames[i], files[i]);
                }
            }
            catch (Exception e)
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.WriteLine(e.Message);
                Console.WriteLine(e.InnerException);
                Console.WriteLine(e.StackTrace);
                Console.WriteLine(e.Data);
            }

            Console.ReadLine();
		}

        static void RemoveDrop(string[] enemy, int index)
        {
            enemy[index] = "";
            Console.WriteLine(enemy[index]);
        }

        static void AddXP(string[] enemy, int index, int id)
        {
            string addXP = "TNT1 A 0 ACS_NamedExecuteAlways(\"AddXP\", 0, Random(" + XPAmounts[id] + ", " + XPAmounts[id] * 2 + "))";
            enemy[index] = enemy[index] + "\n\t\t" + addXP;
            Console.WriteLine(enemy[index]);
        }
	}
}