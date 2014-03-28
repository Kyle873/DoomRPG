using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
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
        Version version = new Version(0, 7, 0, 2);
        Config config = new Config();

        public FormMain()
        {
            InitializeComponent();

            // Title
            Text = "Doom RPG Launcher v" + version;

            // Load config
            config.Load();

            // Populate dynamic controls
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

            // Load Controls
            LoadControls();

            // Mods
            PopulateMods();
            
            // send initial events to specific controls to refresh their states
            checkBoxMultiplayer_CheckedChanged(null, null);
            richTextBoxCredits_TextChanged(null, null);
        }

        private void PopulateMods()
        {
            checkedListBoxMods.Items.Clear();

            if (textBoxModsPath.Text != string.Empty)
                if (Directory.Exists(textBoxModsPath.Text))
                {
                    IEnumerable<string> mods = Directory.EnumerateFiles(textBoxModsPath.Text);
                    foreach (string mod in mods)
                        if (mod.Contains(".wad") || mod.Contains("pk3") || mod.Contains("pk7"))
                            checkedListBoxMods.Items.Add(Path.GetFileName(mod));
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
            if (config.modsPath == string.Empty && (config.patches[3] == true || config.patches[4] == true || config.patches[5] == true))
            {
                Utils.ShowError("You must specify a WAD/PK3 path for the selected patches!");
                return false;
            }
            if (Path.GetDirectoryName(config.portPath) == config.DRPGPath)
            {
                Utils.ShowError("The Port Path and Doom RPG path cannot be the same!");
                return false;
            }

            return true;
        }

        private void LoadControls()
        {
            textBoxPortPath.Text = config.portPath;
            textBoxDRPGPath.Text = config.DRPGPath;
            textBoxModsPath.Text = config.modsPath;
            numericUpDownMapNumber.Value = config.mapNumber;
            for (int i = 0; i < config.patches.Length; i++)
                checkedListBoxPatches.SetItemChecked(i, config.patches[i]);
            checkBoxMultiplayer.Checked = config.multiplayer;
            for (int i = 0; i < config.mods.Count; i++)
                if (checkedListBoxMods.FindString(config.mods[i]) >= 0)
                    checkedListBoxMods.SetItemChecked(checkedListBoxMods.FindString(config.mods[i]), true);
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
            for (int i = 0; i < config.patches.Length; i++)
                if (checkedListBoxPatches.GetItemChecked(i))
                    config.patches[i] = true;
                else
                    config.patches[i] = false;
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
            Branch master = await client.Repository.GetBranch("Kyle873", "DoomRPG", "master");
            return master.Commit.Sha;
        }

        private async Task CheckForUpdates()
        {
            // Save the config
            SaveControls();
            config.Save();

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

        private void DownloadDRPG()
        {
            Uri uri = new Uri("https://github.com/Kyle873/DoomRPG/archive/master.zip");
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
            Directory.Move(path + "\\DoomRPG-master", config.DRPGPath);

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
            cmdline += " -iwad " + config.iwad.ToString();

            if (config.mapNumber > 0)
            {
                // Skill/Difficulty
                cmdline += " -skill " + ((int)config.difficulty + 1);

                // Map Number
                cmdline += " -warp " + config.mapNumber;

                // DRLA Class
                if (checkedListBoxPatches.GetItemChecked(4))
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

            // Mods & Patches
            cmdline += " -file";

            // Mods selected from the mods list
            for (int i = 0; i < checkedListBoxMods.Items.Count; i++)
                if (checkedListBoxMods.GetItemChecked(i))
                    cmdline += " \"" + config.modsPath + "\\" + checkedListBoxMods.Items[i].ToString() + "\"";

            // Doom RPG
            cmdline += " \"" + config.DRPGPath + "\\DoomRPG\"";
            // Doom 1
            if (checkedListBoxPatches.GetItemChecked(0))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-Doom1\"";
            // Brightmaps
            if (checkedListBoxPatches.GetItemChecked(1))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-Brightmaps\"";
            // Extras
            if (checkedListBoxPatches.GetItemChecked(2))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-Extras\"";
            // Brutal Doom
            if (checkedListBoxPatches.GetItemChecked(3))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-Brutal\"";
            // DoomRL Arsenal
            if (checkedListBoxPatches.GetItemChecked(4))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-RLArsenal\"";
            // Brutal Doom
            if (checkedListBoxPatches.GetItemChecked(5))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-RLMonsters\"";
            // TUTNT
            if (checkedListBoxPatches.GetItemChecked(6))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-TUTNT\"";

            // Custom Commands
            if (config.customCommands != string.Empty)
                cmdline += " " + config.customCommands;

            return cmdline;
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

        private void buttonLaunch_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                SaveControls();
                config.Save();
                MessageBox.Show(BuildCommandLine(), "Command Line", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        private void checkBoxMultiplayer_CheckedChanged(object sender, EventArgs e)
        {
            // Multiplayer Checkbox
            if (checkBoxMultiplayer.Checked)
            {
                groupBoxMode.Enabled = true;
                groupBoxServerMode.Enabled = true;
                groupBoxServerOptions.Enabled = true;
            }
            else
            {
                groupBoxMode.Enabled = false;
                groupBoxServerMode.Enabled = false;
                groupBoxServerOptions.Enabled = false;
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
            try
            {
                // Brutal Doom
                if (checkedListBoxPatches.GetItemChecked(3))
                    checkedListBoxMods.SetItemChecked(checkedListBoxMods.FindString("brutalv19"), true);
                // DoomRL Arsenal
                if (checkedListBoxPatches.GetItemChecked(4))
                {
                    checkedListBoxMods.SetItemChecked(checkedListBoxMods.FindString("DoomRL Arsenal Beta 6"), true);
                    checkedListBoxMods.SetItemChecked(checkedListBoxMods.FindString("DoomRL HUD"), true);
                }
                // DoomRL monster Pack
                if (checkedListBoxPatches.GetItemChecked(5))
                    checkedListBoxMods.SetItemChecked(checkedListBoxMods.FindString("DoomRL Monsters"), true);
            }
            catch
            {
            }

            // If Map Number is 0, skill is irrelevent
            if (numericUpDownMapNumber.Value == 0)
                comboBoxDifficulty.Enabled = false;
            else
                comboBoxDifficulty.Enabled = true;

            // Player Class
            if (numericUpDownMapNumber.Value > 0 && checkedListBoxPatches.GetItemChecked(4))
                comboBoxClass.Enabled = true;
            else
                comboBoxClass.Enabled = false;
        }
    }
}
