using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace DoomRPG
{
    public class Config
    {
        private string path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\" + Assembly.GetEntryAssembly().GetName().Name + ".cfg";
        
        // Basic
        public string portPath = string.Empty;
        public string DRPGPath = string.Empty;
        public string modsPath = string.Empty;
        public Difficulty difficulty = Difficulty.Normal;
        public int mapNumber = 1;
        public bool[] patches = new bool[7];
        public List<string> mods = new List<string>();
        public string customCommands = string.Empty;

        // Multiplayer
        public bool multiplayer = false;
        public MultiplayerMode multiplayerMode = MultiplayerMode.Hosting;
        public ServerType serverType = ServerType.PeerToPeer;
        public int players = 2;
        public string hostname = string.Empty;
        public bool extraTics = false;
        public int duplex = 0;

        public void Save()
        {
            List<string> data = new List<string>();

            try
            {
                FieldInfo[] fields = this.GetType().GetFields();

                foreach (FieldInfo field in fields)
                {
                    // Array Types
                    if (field.GetValue(this).GetType() == typeof(bool[]))
                    {
                        bool[] bools = (bool[])field.GetValue(this);
                        string boolString = field.Name + "=";
                        for (int i = 0; i < bools.Length; i++)
                            boolString += bools[i] + ",";
                        data.Add(boolString.Substring(0, boolString.Length - 1));
                    }
                    // List types
                    else if (field.GetValue(this).GetType() == typeof(List<string>))
                    {
                        List<string> strings = (List<String>)field.GetValue(this);
                        string listString = field.Name + "=";
                        foreach (string s in strings)
                            listString += "{" + s + "};";
                        if (listString[listString.Length - 1] == ';')
                            listString = listString.Remove(listString.Length - 1);
                        data.Add(listString);
                    }
                    else // Basic Type
                        data.Add(field.Name + "=" + field.GetValue(this));
                }

                File.WriteAllLines(path, data);
            }
            catch (Exception e)
            {
                Utils.ShowError(e);
            }
        }

        public void Load()
        {
            try
            {
                if (File.Exists(path))
                {
                    FieldInfo[] fields = this.GetType().GetFields();
                    string[] lines = File.ReadAllLines(path);

                    foreach (string option in lines)
                    {
                        string[] s = option.Split('=');

                        if (s.Length != 2)
                            continue;

                        FieldInfo field = fields.FirstOrDefault(o => o.Name == s[0]);
                        
                        if (field != null)
                        {
                            // Basic Types
                            if (field.GetValue(this).GetType() == typeof(bool))
                                field.SetValue(this, bool.Parse(s[1]));
                            if (field.GetValue(this).GetType() == typeof(int))
                                field.SetValue(this, int.Parse(s[1]));
                            if (field.GetValue(this).GetType() == typeof(float))
                                field.SetValue(this, float.Parse(s[1]));
                            if (field.GetValue(this).GetType() == typeof(string))
                                field.SetValue(this, s[1]);

                            // Patches Array
                            if (field.Name == "patches")
                            {
                                bool[] bools = new bool[patches.Length];
                                for (int i = 0; i < patches.Length; i++)
                                    bools[i] = bool.Parse(s[1].Split(',')[i]);
                                field.SetValue(this, bools);
                            }

                            // String List
                            if (field.GetValue(this).GetType() == typeof(List<string>))
                            {
                                List<string> listStrings = new List<string>();
                                string[] entries = s[1].Split(';');
                                if (entries.Length > 0 && entries[0] != string.Empty)
                                    foreach (string entry in entries)
                                        listStrings.Add(entry.Trim(new char[] { '{', '}' }));
                                field.SetValue(this, listStrings);
                            }

                            // Enums
                            if (field.GetValue(this).GetType() == typeof(Difficulty))
                                for (int i = 0; i < Enum.GetNames(typeof(Difficulty)).Length; i++)
                                    if (Enum.GetNames(typeof(Difficulty))[i].Contains(s[1]))
                                        field.SetValue(this, Enum.ToObject(typeof(Difficulty), i));
                            if (field.GetValue(this).GetType() == typeof(MultiplayerMode))
                                for (int i = 0; i < Enum.GetNames(typeof(MultiplayerMode)).Length; i++)
                                    if (Enum.GetNames(typeof(MultiplayerMode))[i].Contains(s[1]))
                                        field.SetValue(this, Enum.ToObject(typeof(MultiplayerMode), i));
                            if (field.GetValue(this).GetType() == typeof(ServerType))
                                for (int i = 0; i < Enum.GetNames(typeof(ServerType)).Length; i++)
                                    if (Enum.GetNames(typeof(ServerType))[i].Contains(s[1]))
                                        field.SetValue(this, Enum.ToObject(typeof(ServerType), i));
                        }
                    }
                }
                else
                    Save();
            }
            catch (Exception e)
            {
                Utils.ShowError(e);
            }
        }
    }
}
