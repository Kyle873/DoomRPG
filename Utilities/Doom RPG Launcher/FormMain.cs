using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

using Octokit;
using ICSharpCode.SharpZipLib;
using ICSharpCode.SharpZipLib.Zip;

namespace DoomRPG
{
    public partial class FormMain : Form
    {
        Version version = new Version(0, 9, 1);
        Config config = new Config();
        string currentBranch = string.Empty;
        List<PatchInfo> patches = new List<PatchInfo>();

        // Extensions of known mod filetypes
        string[] fileTypes =
        {
            "wad",                  // Original vanilla Doom archive type
            "zip", "pk3", "pk7",    // Archive File Types
            "deh", "bex"            // DeHackEd File Types
        };

        public FormMain()
        {
            InitializeComponent();

            // Title
            Text = "Doom RPG Launcher v" + version;

            // Load config
            config.Load();

            // Populate dynamic controls
            PopulateComboBoxes();

            // Patches
            PopulatePatches();

            // Mods
            PopulateMods();

            // Load Controls
            LoadControls();

            // Load Credits
            LoadCredits();
        }

        private void LoadCredits()
        {
            string creditsPath = textBoxDRPGPath.Text + "\\CREDITS.txt";

            if (File.Exists(creditsPath))
            {
                string credits = File.ReadAllText(creditsPath);

                richTextBoxCredits.Text = credits;
                richTextBoxCredits_TextChanged(null, null);
            }
        }

        private async Task PopulateComboBoxes()
        {
            // IWAD
            for (int i = 0; i < Enum.GetNames(typeof(IWAD)).Length; i++)
                comboBoxIWAD.Items.Add(Enum.GetName(typeof(IWAD), i));
            comboBoxIWAD.SelectedIndex = (int)config.iwad;

            // Difficulty
            for (int i = 0; i < Enum.GetNames(typeof(Difficulty)).Length; i++)
                comboBoxDifficulty.Items.Add(Enum.GetName(typeof(Difficulty), i));
            comboBoxDifficulty.SelectedIndex = (int)config.difficulty;

            // DRLA Class
            for (int i = 0; i < Enum.GetNames(typeof(DRLAClass)).Length; i++)
                comboBoxClass.Items.Add(Enum.GetName(typeof(DRLAClass), i));
            comboBoxClass.SelectedIndex = (int)config.rlClass;

            // Savegames
            if (config.portPath != string.Empty)
            {
                List<string> files = Directory.EnumerateFiles(Path.GetDirectoryName(config.portPath)).ToList<string>();

                foreach (string file in files)
                    if (file.EndsWith(".zds"))
                        comboBoxSaveGame.Items.Add(Path.GetFileName(file));
            }

            // Branches
            List<string> branches = await GetBranches();
            foreach (string branch in branches)
                comboBoxBranch.Items.Add(branch);
            comboBoxBranch.SelectedIndex = 0;
            comboBoxBranch.Enabled = true;
        }

        private void PopulatePatches()
        {
            patches.Clear();
            checkedListBoxPatches.Items.Clear();

            // Populate the patches list
            if (config.DRPGPath != string.Empty)
                if (Directory.Exists(config.DRPGPath))
                {
                    List<string> folders = Directory.EnumerateDirectories(config.DRPGPath).ToList<string>();

                    foreach (string folder in folders)
                    {
                        List<string> files = Directory.EnumerateFiles(folder).ToList<string>();
                        bool isValid = false;

                        foreach (string file in files)
                            if (file.Contains("DRPGINFO.txt"))
                            {
                                isValid = true;
                                break;
                            }

                        if (isValid)
                        {
                            PatchInfo info = PatchInfo.ReadPatch(folder + "\\DRPGINFO.txt");
                            patches.Add(info);
                        }
                        else
                            continue;
                    }
                }

            // Populate the Patches checklist box
            foreach (PatchInfo patch in patches)
            {
                checkedListBoxPatches.Items.Add(patch);
            }
        }

        private void PopulateMods()
        {
            checkedListBoxMods.Items.Clear();

            if (config.modsPath != string.Empty)
                if (Directory.Exists(config.modsPath))
                {
                    List<string> folders = Directory.EnumerateDirectories(config.modsPath).ToList<string>();
                    folders.Add(config.modsPath);

                    foreach (string folder in folders)
                    {
                        List<string> files = Directory.EnumerateFiles(folder).ToList<string>();

                        foreach (string file in files)
                            for (int i = 0; i < fileTypes.Length; i++)
                                if (file.ToLower().EndsWith("." + fileTypes[i]))
                                {
                                    string filePath = Path.GetFullPath(file);
                                    filePath = filePath.Substring(textBoxModsPath.Text.Length + 1);
                                    checkedListBoxMods.Items.Add(filePath);
                                }
                    }
                }
        }

        private bool CheckForErrors()
        {
            if (config.portPath == string.Empty)
            {
                Utils.ShowError("You must specify a source port path!");
                return false;
            }

            if (config.DRPGPath == string.Empty)
            {
                Utils.ShowError("You must specify Doom RPG's path!");
                return false;
            }

            if (Path.GetDirectoryName(config.portPath) == config.DRPGPath)
            {
                Utils.ShowError("The Port Path and Doom RPG path cannot be the same!");
                return false;
            }

            if (config.DRPGPath == Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location))
            {
                Utils.ShowError("You cannot keep the launcher within the Doom RPG folder! Please move it to a different location.");
                return false;
            }

            return true;
        }

        private bool CheckForMods()
        {
            if (textBoxDRPGPath.Text != string.Empty)
                if (Directory.Exists(textBoxDRPGPath.Text))
                {
                    List<string> files = Directory.EnumerateFiles(textBoxDRPGPath.Text).ToList<string>();

                    foreach (string file in files)
                        for (int i = 0; i < fileTypes.Length; i++)
                            if (file.ToLower().EndsWith(fileTypes[i]))
                                return true;
                }

            return false;
        }

        private void LoadControls()
        {
            textBoxPortPath.Text = config.portPath;
            textBoxDRPGPath.Text = config.DRPGPath;
            textBoxModsPath.Text = config.modsPath;
            numericUpDownMapNumber.Value = config.mapNumber;
            textBoxDemo.Text = config.demo;
            checkBoxEnableCheats.Checked = config.enableCheats;
            checkBoxLogging.Checked = config.enableLogging;
            for (int i = 0; i < patches.Count; i++)
                foreach (string patch in config.patches)
                    if (patches[i].Name.ToLower() == patch.ToLower())
                        checkedListBoxPatches.SetItemChecked(i, true);
            checkBoxMultiplayer.Checked = config.multiplayer;
            for (int i = 0; i < config.mods.Count; i++)
                if (checkedListBoxMods.FindStringExact(config.mods[i]) != -1)
                    checkedListBoxMods.SetItemChecked(checkedListBoxMods.FindStringExact(config.mods[i]), true);
            if (config.multiplayerMode == MultiplayerMode.Hosting)
                radioButtonHosting.Checked = true;
            if (config.multiplayerMode == MultiplayerMode.Joining)
                radioButtonJoining.Checked = true;
            if (config.serverType == ServerType.PeerToPeer)
                radioButtonPeerToPeer.Checked = true;
            if (config.serverType == ServerType.PacketServer)
                radioButtonPacketServer.Checked = true;
            numericUpDownPlayers.Value = config.players;
            textBoxHostname.Text = config.hostname;
            checkBoxExtraTics.Checked = config.extraTics;
            numericUpDownDuplex.Value = config.duplex;
            textBoxCustomCommands.Text = config.customCommands;
        }

        private void SaveControls()
        {
            config.portPath = textBoxPortPath.Text;
            config.DRPGPath = textBoxDRPGPath.Text;
            config.modsPath = textBoxModsPath.Text;
            config.iwad = (IWAD)comboBoxIWAD.SelectedIndex;
            config.difficulty = (Difficulty)comboBoxDifficulty.SelectedIndex;
            config.rlClass = (DRLAClass)comboBoxClass.SelectedIndex;
            config.mapNumber = (int)numericUpDownMapNumber.Value;
            config.demo = textBoxDemo.Text;
            config.enableCheats = checkBoxEnableCheats.Checked;
            config.enableLogging = checkBoxLogging.Checked;
            config.patches.Clear();
            for (int i = 0; i < patches.Count; i++)
                if (checkedListBoxPatches.GetItemChecked(i))
                    config.patches.Add(patches[i].Name);
            config.mods.Clear();
            for (int i = 0; i < checkedListBoxMods.Items.Count; i++)
                if (checkedListBoxMods.GetItemChecked(i))
                    config.mods.Add(checkedListBoxMods.Items[i].ToString());
            config.multiplayer = checkBoxMultiplayer.Checked;
            if (radioButtonHosting.Checked)
                config.multiplayerMode = MultiplayerMode.Hosting;
            if (radioButtonJoining.Checked)
                config.multiplayerMode = MultiplayerMode.Joining;
            if (radioButtonPeerToPeer.Checked)
                config.serverType = ServerType.PeerToPeer;
            if (radioButtonPacketServer.Checked)
                config.serverType = ServerType.PacketServer;
            config.players = (int)numericUpDownPlayers.Value;
            config.hostname = textBoxHostname.Text;
            config.extraTics = checkBoxExtraTics.Checked;
            config.duplex = (int)numericUpDownDuplex.Value;
            config.customCommands = textBoxCustomCommands.Text;
        }

        private async Task<string> GetMasterSHA()
        {
            GitHubClient client = new GitHubClient(new ProductHeaderValue("DoomRPG"));
            Branch master = await client.Repository.GetBranch("Kyle873", "DoomRPG", currentBranch);
            return master.Commit.Sha;
        }

        private async Task<List<String>> GetBranches()
        {
            GitHubClient client = new GitHubClient(new ProductHeaderValue("DoomRPG"));
            List<String> branchNames = new List<string>();
            IReadOnlyList<Branch> branches = await client.Repository.GetAllBranches("Kyle873", "DoomRPG");

            foreach (Branch branch in branches)
                branchNames.Add(branch.Name);

            return branchNames;
        }

        private async Task CheckForUpdates()
        {
            DialogResult result;

            // Save the config
            SaveControls();
            config.Save();

            // Wipe Warning
            if (!config.wipeWarning)
                result = MessageBox.Show("This process will wipe whatever is in your selected Doom RPG folder. Are you sure you want to continue?", "Warning", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);
            else
                result = DialogResult.Yes;

            // Extra check to see if your selected Doom RPG path already has stuff in it
            if (CheckForMods())
            {
                DialogResult createResult = MessageBox.Show("The Doom RPG folder contains other mod files. Would you like to create a subfolder for Doom RPG?", "Question", MessageBoxButtons.YesNo, MessageBoxIcon.Question);

                if (createResult == DialogResult.Yes)
                {
                    textBoxDRPGPath.Text += "\\DoomRPG";
                    config.DRPGPath += "\\DoomRPG";
                }
                else
                    return;
            }

            if (result == DialogResult.Yes)
            {
                config.wipeWarning = true;

                toolStripStatusLabel.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
                toolStripStatusLabel.Text = "Checking for updates...";
                toolStripProgressBar.Style = ProgressBarStyle.Marquee;

                try
                {
                    string masterSHA = await GetMasterSHA();
                    string SHAPath = config.DRPGPath + "\\SHA-1";

                    // Does the SHA-1 of the current version match the remote branch?
                    if (Directory.Exists(config.DRPGPath + "\\.git")) // Version is pulled from git, why bother updating with the launcher?
                    {
                        toolStripStatusLabel.Text = "This version of Doom RPG is managed by git";
                        toolStripProgressBar.Style = ProgressBarStyle.Continuous;
                        buttonCheckUpdates.Enabled = true;
                        buttonLaunch.Enabled = true;
                        return;
                    }
                    else if (!Directory.Exists(config.DRPGPath)) // Directory wasn't found
                    {
                        toolStripStatusLabel.ForeColor = Color.Red;
                        toolStripStatusLabel.Text = "Could not find Doom RPG directory, downloading latest version...";
                    }
                    else if (File.Exists(SHAPath))
                    {
                        string localSHA = File.ReadAllLines(SHAPath)[0];

                        // Not a match, need to grab the latest version
                        if (masterSHA != localSHA || !File.Exists(SHAPath))
                        {
                            toolStripStatusLabel.ForeColor = Color.Red;
                            toolStripStatusLabel.Text = "Out-of-date, downloading latest version...";
                        }
                        else // Up-to-date
                        {
                            toolStripStatusLabel.ForeColor = Color.Green;
                            toolStripStatusLabel.Text = "Already up-to-date!";
                            toolStripProgressBar.Style = ProgressBarStyle.Continuous;
                            buttonCheckUpdates.Enabled = true;
                            buttonLaunch.Enabled = true;
                            return;
                        }
                    }
                    else // Could not find SHA-1, download a new copy
                    {
                        toolStripStatusLabel.ForeColor = Color.Red;
                        toolStripStatusLabel.Text = "Could not find SHA-1, downloading latest version...";
                    }

                    // Delete the old folder
                    if (Directory.Exists(config.DRPGPath))
                        Directory.Delete(config.DRPGPath, true);

                    await Task.Delay(1000 * 3);
                    toolStripProgressBar.Style = ProgressBarStyle.Continuous;

                    DownloadDRPG();
                }
                catch (Exception e)
                {
                    Utils.ShowError(e);
                }
            }
            else
            {
                buttonCheckUpdates.Enabled = true;
                buttonLaunch.Enabled = true;
            }
        }

        private void DownloadDRPG()
        {
            Uri uri = new Uri("https://github.com/Kyle873/DoomRPG/archive/" + currentBranch + ".zip");
            string path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string zipName = "\\DoomRPG.zip";

            using (WebClient client = new WebClient())
            {
                client.DownloadFileAsync(uri, path + zipName);
                client.DownloadProgressChanged += client_DownloadProgressChanged;
                client.DownloadFileCompleted += client_DownloadFileCompleted;
            }
        }

        private void ExtractDRPG()
        {
            string path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string zipPath = path + "\\DoomRPG.zip";
            FastZip zip = new FastZip();

            try
            {
                toolStripStatusLabel.Text = "Extracting DoomRPG.zip...";
                toolStripProgressBar.Style = ProgressBarStyle.Marquee;
                Thread extractThread = new Thread(ExtractZip);
                extractThread.Start();
            }
            catch (Exception e)
            {
                Utils.ShowError(e);
            }
        }

        private async void ExtractZip()
        {
            string path = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            string zipPath = path + "\\DoomRPG.zip";
            FastZip zip = new FastZip();

            // Extract the zip
            zip.ExtractZip(zipPath, path, string.Empty);

            // Move the files to the root folder
            Directory.Move(path + "\\DoomRPG-" + currentBranch, config.DRPGPath);

            // Add the SHA-1 file
            File.WriteAllText(config.DRPGPath + "\\SHA-1", await GetMasterSHA());

            // Delete the zip
            File.Delete(zipPath);

            Invoke(new MethodInvoker(delegate
            {
                toolStripStatusLabel.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
                toolStripStatusLabel.Text = "Ready";
                toolStripProgressBar.Style = ProgressBarStyle.Continuous;
                buttonCheckUpdates.Enabled = true;
                buttonLaunch.Enabled = true;
            }));
        }

        private string BuildCommandLine()
        {
            string cmdline;

            // Build the command line
            cmdline = "\"" + config.portPath + "\"";

            // IWAD
            if (config.iwad == IWAD.Doom1)
                cmdline += " -iwad Doom";
            else
                cmdline += " -iwad " + config.iwad.ToString();

            if (config.mapNumber > 0)
            {
                // Skill/Difficulty
                cmdline += " -skill " + ((int)config.difficulty + 1);

                // Map Number
                cmdline += " -warp " + config.mapNumber;

                // DRLA Class
                if (IsDRLAActive())
                    cmdline += " +playerclass " + config.rlClass.ToString();
            }

            // Multiplayer
            if (config.multiplayer)
            {
                // Hosting/Joining
                if (config.multiplayerMode == MultiplayerMode.Hosting)
                    cmdline += " -host " + config.players;
                if (config.multiplayerMode == MultiplayerMode.Joining)
                    cmdline += " -join " + config.hostname;

                // Server-side stuff
                if (config.multiplayerMode == MultiplayerMode.Hosting)
                {
                    // Server Type
                    if (config.serverType == ServerType.PeerToPeer)
                        cmdline += " -netmode 0";
                    if (config.serverType == ServerType.PacketServer)
                        cmdline += " -netmode 1";

                    // Server Options
                    if (config.extraTics)
                        cmdline += " -extratic";
                    if (config.duplex > 0)
                        cmdline += " -dup " + config.duplex;
                }
            }

            // Enable Cheats
            if (checkBoxEnableCheats.Checked)
                cmdline += " +sv_cheats 1";

            // Enable Logging to File
            if (checkBoxLogging.Checked)
                cmdline += " +logfile \"Doom RPG.log\"";

            // Load Savegame
            if (comboBoxSaveGame.Text != "None")
                cmdline += " -loadgame " + Path.GetDirectoryName(textBoxPortPath.Text) + "\\" + comboBoxSaveGame.Text;

            // Record Demo
            if (textBoxDemo.TextLength > 0)
                cmdline += " -record " + textBoxDemo.Text + ".lmp";

            // Mods & Patches
            cmdline += " -file";

            // Mods selected from the mods list
            for (int i = 0; i < checkedListBoxMods.Items.Count; i++)
                if (checkedListBoxMods.GetItemChecked(i))
                    cmdline += " \"" + config.modsPath + "\\" + checkedListBoxMods.Items[i].ToString() + "\"";

            // Doom RPG
            cmdline += " \"" + config.DRPGPath + "\\DoomRPG\"";

            // Doom RPG Patches
            for (int i = 0; i < patches.Count; i++)
                if (checkedListBoxPatches.GetItemChecked(i))
                    cmdline += " \"" + patches[i].Path + "\"";

            // Custom Commands
            if (config.customCommands != string.Empty)
                cmdline += " " + config.customCommands;

            return cmdline;
        }

        private bool IsDRLAActive()
        {
            for (int i = 0; i < patches.Count; i++)
                if (patches[i].Name.ToLower().Contains("doomrl"))
                    if (checkedListBoxPatches.GetItemChecked(i))
                        return true;

            return false;
        }

        private void buttonBrowsePortPath_Click(object sender, EventArgs e)
        {
            FileDialog dialog = new OpenFileDialog();
            dialog.Title = "Specify (G)ZDoom EXE...";
            dialog.ShowDialog();

            textBoxPortPath.Text = dialog.FileName;
        }

        private void buttonBrowseDRPGPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.ShowDialog();

            textBoxDRPGPath.Text = dialog.SelectedPath;

            LoadCredits();
        }

        private void buttonBrowseModsPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.ShowDialog();

            textBoxModsPath.Text = dialog.SelectedPath;

            // Re-populate the mods list
            PopulateMods();
        }

        private void textBoxModsPath_TextChanged(object sender, EventArgs e)
        {
            // Re-populate the mods list
            PopulateMods();
        }

        private async void buttonCheckUpdates_Click(object sender, EventArgs e)
        {
            // Check the current branch
            if (currentBranch == string.Empty)
            {
                Utils.ShowError("No branch has been selected");
                return;
            }
            
            // Save config
            SaveControls();
            config.Save();

            // Error Handling
            if (!CheckForErrors())
                return;

            buttonCheckUpdates.Enabled = false;
            buttonLaunch.Enabled = false;
            await CheckForUpdates();
        }

        private void buttonLaunch_Click(object sender, EventArgs e)
        {
            try
            {
                // Check for patch requirements
                if (!PatchInfo.CheckForRequirements(patches))
                    return;

                // Check for patch conflicts
                if (!PatchInfo.CheckForConflicts(patches))
                    return;

                // Save config
                SaveControls();
                config.Save();

                // Error Handling
                if (!CheckForErrors())
                    return;

                // Launch
                Process.Start(config.portPath, BuildCommandLine());
            }
            catch (Exception ex)
            {
                Utils.ShowError(ex);
            }
        }

        private void richTextBoxCredits_TextChanged(object sender, EventArgs e)
        {
            richTextBoxCredits.Find("Testers");
            richTextBoxCredits.SelectionFont = new Font(FontFamily.GenericSansSerif, 12, FontStyle.Bold);
            richTextBoxCredits.SelectionColor = Color.Green;
            richTextBoxCredits.Find("Contributors");
            richTextBoxCredits.SelectionFont = new Font(FontFamily.GenericSansSerif, 12, FontStyle.Bold);
            richTextBoxCredits.SelectionColor = Color.Red;
            richTextBoxCredits.Find("Resources");
            richTextBoxCredits.SelectionFont = new Font(FontFamily.GenericSansSerif, 12, FontStyle.Bold);
            richTextBoxCredits.SelectionColor = Color.Blue;
            richTextBoxCredits.Find("Libraries");
            richTextBoxCredits.SelectionFont = new Font(FontFamily.GenericSansSerif, 12, FontStyle.Bold);
            richTextBoxCredits.SelectionColor = Color.Blue;
        }

        private void client_DownloadProgressChanged(object sender, DownloadProgressChangedEventArgs e)
        {
            toolStripStatusLabel.ForeColor = Color.FromKnownColor(KnownColor.ControlText);
            toolStripStatusLabel.Text = "Downloading... " + (e.BytesReceived / 1024) + "KB / " + (e.TotalBytesToReceive / 1024) + "KB (" + e.ProgressPercentage + "%)";
            toolStripProgressBar.Value = e.ProgressPercentage;
        }

        private void client_DownloadFileCompleted(object sender, System.ComponentModel.AsyncCompletedEventArgs e)
        {
            try
            {
                ExtractDRPG();
            }
            catch (Exception ex)
            {
                Utils.ShowError(ex);
            }
        }

        private void timer_Tick(object sender, EventArgs e)
        {
            // Check loaded patches
            for (int i = 0; i < patches.Count; i++)
                patches[i].Enabled = checkedListBoxPatches.GetItemChecked(i);

            // If Map Number is 0, skill is irrelevent
            if (numericUpDownMapNumber.Value == 0)
                comboBoxDifficulty.Enabled = false;
            else
                comboBoxDifficulty.Enabled = true;

            // Player Class
            if (numericUpDownMapNumber.Value > 0 && IsDRLAActive())
                comboBoxClass.Enabled = true;
            else
                comboBoxClass.Enabled = false;

            // Multiplayer Checkbox
            if (checkBoxMultiplayer.Checked)
            {
                groupBoxMode.Enabled = true;
                groupBoxServerMode.Enabled = true;
                if (radioButtonHosting.Checked)
                {
                    numericUpDownPlayers.Enabled = true;
                    radioButtonPeerToPeer.Enabled = true;
                    radioButtonPacketServer.Enabled = true;
                    groupBoxServerOptions.Enabled = true;
                }
                else
                {
                    numericUpDownPlayers.Enabled = false;
                    radioButtonPeerToPeer.Enabled = false;
                    radioButtonPacketServer.Enabled = false;
                    groupBoxServerOptions.Enabled = false;
                }
                if (radioButtonJoining.Checked)
                    textBoxHostname.Enabled = true;
                else
                    textBoxHostname.Enabled = false;
            }
            else
            {
                groupBoxMode.Enabled = false;
                groupBoxServerMode.Enabled = false;
                groupBoxServerOptions.Enabled = false;
            }
        }

        private void timerPulse_Tick(object sender, EventArgs e)
        {
            // Launch button pulse
            int red = 160 + (int)(Math.Sin((double)DateTime.Now.Millisecond / 256) * 64);
            buttonLaunch.ForeColor = Color.FromArgb(255, red, 0, 0);
        }
        
        private void buttonCopyCommandClipboard_Click(object sender, EventArgs e)
        {
            PatchInfo.CheckForRequirements(patches);
            PatchInfo.CheckForConflicts(patches);
            SaveControls();
            config.Save();
            Clipboard.SetText(BuildCommandLine());
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            PopulatePatches();
            PopulateMods();
            LoadControls();
        }

        private void textBoxDRPGPath_TextChanged(object sender, EventArgs e)
        {
            LoadCredits();
        }
        
        private void comboBoxBranch_SelectedIndexChanged(object sender, EventArgs e)
        {
            currentBranch = comboBoxBranch.Text;
        }
    }
}
