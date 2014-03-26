using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace DoomRPG
{
    public partial class FormMain : Form
    {
        Config config = new Config();
        CommandLine cmdline = new CommandLine();

        public FormMain()
        {
            InitializeComponent();

            // Load config
            config.Load();
            textBoxPortPath.Text = config.portPath;
            textBoxDRPGPath.Text = config.DRPGPath;
            textBoxModsPath.Text = config.modsPath;
            numericUpDownMapNumber.Value = config.mapNumber;
            for (int i = 0; i < config.patches.Length; i++)
                checkedListBoxPatches.SetItemChecked(i, config.patches[i]);
            checkBoxMultiplayer.Checked = config.multiplayer;
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

            // Populate comboboxes
            for (int i = 0; i < Enum.GetNames(typeof(Difficulty)).Length; i++)
                comboBoxDifficulty.Items.Add(Enum.GetName(typeof(Difficulty), i));
            comboBoxDifficulty.SelectedIndex = (int)config.difficulty;

            // send initial events to specific controls to initialize enable states
            checkBoxMultiplayer_CheckedChanged(null, null);
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
        }
        
        private void buttonLaunch_Click(object sender, EventArgs e)
        {
            string cmdline;
            
            // Save config
            config.portPath = textBoxPortPath.Text;
            config.DRPGPath = textBoxDRPGPath.Text;
            config.modsPath = textBoxModsPath.Text;
            config.difficulty = (Difficulty)comboBoxDifficulty.SelectedIndex;
            config.mapNumber = (int)numericUpDownMapNumber.Value;
            for (int i = 0; i < config.patches.Length; i++)
                if (checkedListBoxPatches.GetItemChecked(i))
                    config.patches[i] = true;
                else
                    config.patches[i] = false;
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
            config.Save();
            
            // Build the command line
            cmdline = "\"" + config.portPath + "\"";
            
            // Skill
            cmdline += " -skill " + ((int)config.difficulty + 1);

            // Map Number
            cmdline += " -warp " + config.mapNumber;

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
            {
                cmdline += " \"" + config.modsPath + "\\brutalv19.pk3\"";
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-Brutal\"";
            }
            // DoomRL Arsenal
            if (checkedListBoxPatches.GetItemChecked(4))
            {
                cmdline += " \"" + config.modsPath + "\\DoomRL Arsenal Beta 6 HF13.wad\"";
                cmdline += " \"" + config.modsPath + "\\DoomRL HUD.wad\"";
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-RLArsenal\"";
            }
            // Brutal Doom
            if (checkedListBoxPatches.GetItemChecked(5))
            {
                cmdline += " \"" + config.modsPath + "\\DoomRL Monsters Beta 3.5.wad\"";
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-RLMonsters\"";
            }
            // TUTNT
            if (checkedListBoxPatches.GetItemChecked(6))
                cmdline += " \"" + config.DRPGPath + "\\DoomRPG-TUTNT\"";

#if DEBUG
            MessageBox.Show(cmdline);
#endif

            // Launch
            Process.Start(config.portPath, cmdline);
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
    }
}
