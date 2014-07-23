using System;
using System.Collections.Generic;
using System.IO;

namespace DoomRPG
{
    public class PatchInfo
    {
        string name;
        public string Name
        {
            get { return name; }
        }

        List<string> conflicts = new List<string>();
        public List<string> Conflicts
        {
            get { return conflicts; }
        }

        List<string> requires = new List<string>();
        public List<string> Requires
        {
            get { return requires; }
        }

        string path;
        public string Path
        {
            get { return path; }
        }

        bool enabled;
        public bool Enabled
        {
            get { return enabled; }
            set { enabled = value; }
        }

        public static PatchInfo ReadPatch(string path)
        {
            PatchInfo info = new PatchInfo();

            info.path = System.IO.Path.GetDirectoryName(path);

            if (File.Exists(path))
            {
                string[] lines = File.ReadAllLines(path);

                foreach (string line in lines)
                {
                    string[] s = line.Split('=');

                    if (s.Length != 2)
                        continue;

                    // Name
                    if (s[0].ToLower() == "name")
                        info.name = s[1];
                    
                    // Conflicts
                    if (s[0].ToLower() == "conflicts")
                        info.conflicts.Add(s[1]);

                    // Requires
                    if (s[0].ToLower() == "requires")
                        info.requires.Add(s[1]);
                }
            }
            else
            {
                Utils.ShowError("Invalid Patch path\n\n" + path);
                return null;
            }

            return info;
        }

        public static bool CheckForRequirements(List<PatchInfo> patches)
        {
            string error = string.Empty;
            bool hasError = false;

            for (int i = 0; i < patches.Count; i++)
            {
                if (!patches[i].Enabled) continue;

                for (int j = 0; j < patches.Count; j++)
                {
                    for (int k = 0; k < patches[i].Requires.Count; k++)
                        if (patches[i].Requires[k].ToLower() == patches[j].Name.ToLower() && !patches[j].Enabled)
                        {
                            error += "Patch " + patches[i].name + " requires the patch " + patches[j].name + "\n";
                            hasError = true;
                        }
                }
            }

            if (hasError)
            {
                Utils.ShowError(error.TrimEnd('\n'), "Patch Conflict");
                return false;
            }
            else
                return true;
        }

        public static bool CheckForConflicts(List<PatchInfo> patches)
        {
            string error = string.Empty;
            bool hasError = false;

            for (int i = 0; i < patches.Count; i++)
            {
                if (!patches[i].Enabled) continue;
                
                for (int j = 0; j < patches.Count; j++)
                {
                    if (!patches[j].Enabled) continue;

                    for (int k = 0; k < patches[j].Conflicts.Count; k++)
                        if (patches[j].Conflicts[k].ToLower() == patches[i].Name.ToLower())
                        {
                            error += "Patch " + patches[i].name + " conflicts with patch " + patches[j].name + "\n";
                            hasError = true;
                        }
                }
            }

            if (hasError)
            {
                Utils.ShowError(error.TrimEnd('\n'), "Patch Conflict");
                return false;
            }
            else
                return true;
        }

        public override string ToString()
        {
            return name;
        }
    }
}
