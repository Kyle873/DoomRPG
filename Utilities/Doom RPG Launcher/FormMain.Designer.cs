namespace DoomRPG
{
    partial class FormMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControlMain = new System.Windows.Forms.TabControl();
            this.tabPageBasic = new System.Windows.Forms.TabPage();
            this.buttonBrowseModsPath = new System.Windows.Forms.Button();
            this.textBoxModsPath = new System.Windows.Forms.TextBox();
            this.labelModsLocation = new System.Windows.Forms.Label();
            this.checkedListBoxPatches = new System.Windows.Forms.CheckedListBox();
            this.labelDoomRPGPatches = new System.Windows.Forms.Label();
            this.numericUpDownMapNumber = new System.Windows.Forms.NumericUpDown();
            this.labelMapNumber = new System.Windows.Forms.Label();
            this.comboBoxDifficulty = new System.Windows.Forms.ComboBox();
            this.labelDifficulty = new System.Windows.Forms.Label();
            this.buttonBrowseDRPGPath = new System.Windows.Forms.Button();
            this.textBoxDRPGPath = new System.Windows.Forms.TextBox();
            this.labelDoomRPGFolderLocation = new System.Windows.Forms.Label();
            this.buttonBrowsePortPath = new System.Windows.Forms.Button();
            this.textBoxPortPath = new System.Windows.Forms.TextBox();
            this.labelPortLocation = new System.Windows.Forms.Label();
            this.tabPageMultiplayer = new System.Windows.Forms.TabPage();
            this.groupBoxServerOptions = new System.Windows.Forms.GroupBox();
            this.labelDuplex = new System.Windows.Forms.Label();
            this.numericUpDownDuplex = new System.Windows.Forms.NumericUpDown();
            this.checkBoxExtraTics = new System.Windows.Forms.CheckBox();
            this.groupBoxServerMode = new System.Windows.Forms.GroupBox();
            this.radioButtonPacketServer = new System.Windows.Forms.RadioButton();
            this.radioButtonPeerToPeer = new System.Windows.Forms.RadioButton();
            this.groupBoxMode = new System.Windows.Forms.GroupBox();
            this.numericUpDownPlayers = new System.Windows.Forms.NumericUpDown();
            this.labelPlayers = new System.Windows.Forms.Label();
            this.textBoxHostname = new System.Windows.Forms.TextBox();
            this.radioButtonHosting = new System.Windows.Forms.RadioButton();
            this.radioButtonJoining = new System.Windows.Forms.RadioButton();
            this.checkBoxMultiplayer = new System.Windows.Forms.CheckBox();
            this.buttonLaunch = new System.Windows.Forms.Button();
            this.labelCustomCommands = new System.Windows.Forms.Label();
            this.textBoxCustomCommands = new System.Windows.Forms.TextBox();
            this.tabControlMain.SuspendLayout();
            this.tabPageBasic.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapNumber)).BeginInit();
            this.tabPageMultiplayer.SuspendLayout();
            this.groupBoxServerOptions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDuplex)).BeginInit();
            this.groupBoxServerMode.SuspendLayout();
            this.groupBoxMode.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPlayers)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControlMain
            // 
            this.tabControlMain.Controls.Add(this.tabPageBasic);
            this.tabControlMain.Controls.Add(this.tabPageMultiplayer);
            this.tabControlMain.Dock = System.Windows.Forms.DockStyle.Top;
            this.tabControlMain.Location = new System.Drawing.Point(0, 0);
            this.tabControlMain.Name = "tabControlMain";
            this.tabControlMain.SelectedIndex = 0;
            this.tabControlMain.Size = new System.Drawing.Size(428, 324);
            this.tabControlMain.TabIndex = 0;
            // 
            // tabPageBasic
            // 
            this.tabPageBasic.Controls.Add(this.buttonBrowseModsPath);
            this.tabPageBasic.Controls.Add(this.textBoxModsPath);
            this.tabPageBasic.Controls.Add(this.labelModsLocation);
            this.tabPageBasic.Controls.Add(this.checkedListBoxPatches);
            this.tabPageBasic.Controls.Add(this.labelDoomRPGPatches);
            this.tabPageBasic.Controls.Add(this.numericUpDownMapNumber);
            this.tabPageBasic.Controls.Add(this.labelMapNumber);
            this.tabPageBasic.Controls.Add(this.comboBoxDifficulty);
            this.tabPageBasic.Controls.Add(this.labelDifficulty);
            this.tabPageBasic.Controls.Add(this.buttonBrowseDRPGPath);
            this.tabPageBasic.Controls.Add(this.textBoxDRPGPath);
            this.tabPageBasic.Controls.Add(this.labelDoomRPGFolderLocation);
            this.tabPageBasic.Controls.Add(this.buttonBrowsePortPath);
            this.tabPageBasic.Controls.Add(this.textBoxPortPath);
            this.tabPageBasic.Controls.Add(this.labelPortLocation);
            this.tabPageBasic.Location = new System.Drawing.Point(4, 22);
            this.tabPageBasic.Name = "tabPageBasic";
            this.tabPageBasic.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageBasic.Size = new System.Drawing.Size(420, 298);
            this.tabPageBasic.TabIndex = 0;
            this.tabPageBasic.Text = "Basic";
            this.tabPageBasic.UseVisualStyleBackColor = true;
            // 
            // buttonBrowseModsPath
            // 
            this.buttonBrowseModsPath.Location = new System.Drawing.Point(347, 97);
            this.buttonBrowseModsPath.Name = "buttonBrowseModsPath";
            this.buttonBrowseModsPath.Size = new System.Drawing.Size(66, 20);
            this.buttonBrowseModsPath.TabIndex = 14;
            this.buttonBrowseModsPath.Text = "Browse...";
            this.buttonBrowseModsPath.UseVisualStyleBackColor = true;
            this.buttonBrowseModsPath.Click += new System.EventHandler(this.buttonBrowseModsPath_Click);
            // 
            // textBoxModsPath
            // 
            this.textBoxModsPath.Location = new System.Drawing.Point(12, 97);
            this.textBoxModsPath.Name = "textBoxModsPath";
            this.textBoxModsPath.ReadOnly = true;
            this.textBoxModsPath.Size = new System.Drawing.Size(329, 20);
            this.textBoxModsPath.TabIndex = 13;
            // 
            // labelModsLocation
            // 
            this.labelModsLocation.AutoSize = true;
            this.labelModsLocation.Location = new System.Drawing.Point(9, 81);
            this.labelModsLocation.Name = "labelModsLocation";
            this.labelModsLocation.Size = new System.Drawing.Size(139, 13);
            this.labelModsLocation.TabIndex = 12;
            this.labelModsLocation.Text = "WAD/PK3s Folder Location";
            this.labelModsLocation.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // checkedListBoxPatches
            // 
            this.checkedListBoxPatches.FormattingEnabled = true;
            this.checkedListBoxPatches.Items.AddRange(new object[] {
            "Doom 1",
            "Brightmaps",
            "Extras",
            "Brutal Doom",
            "DoomRL Arsenal",
            "DoomRL Monster Pack",
            "TUTNT"});
            this.checkedListBoxPatches.Location = new System.Drawing.Point(11, 176);
            this.checkedListBoxPatches.Name = "checkedListBoxPatches";
            this.checkedListBoxPatches.Size = new System.Drawing.Size(401, 109);
            this.checkedListBoxPatches.TabIndex = 11;
            // 
            // labelDoomRPGPatches
            // 
            this.labelDoomRPGPatches.AutoSize = true;
            this.labelDoomRPGPatches.Location = new System.Drawing.Point(9, 160);
            this.labelDoomRPGPatches.Name = "labelDoomRPGPatches";
            this.labelDoomRPGPatches.Size = new System.Drawing.Size(103, 13);
            this.labelDoomRPGPatches.TabIndex = 10;
            this.labelDoomRPGPatches.Text = "Doom RPG Patches";
            // 
            // numericUpDownMapNumber
            // 
            this.numericUpDownMapNumber.Location = new System.Drawing.Point(151, 136);
            this.numericUpDownMapNumber.Name = "numericUpDownMapNumber";
            this.numericUpDownMapNumber.Size = new System.Drawing.Size(74, 20);
            this.numericUpDownMapNumber.TabIndex = 9;
            // 
            // labelMapNumber
            // 
            this.labelMapNumber.AutoSize = true;
            this.labelMapNumber.Location = new System.Drawing.Point(148, 120);
            this.labelMapNumber.Name = "labelMapNumber";
            this.labelMapNumber.Size = new System.Drawing.Size(68, 13);
            this.labelMapNumber.TabIndex = 8;
            this.labelMapNumber.Text = "Map Number";
            // 
            // comboBoxDifficulty
            // 
            this.comboBoxDifficulty.FormattingEnabled = true;
            this.comboBoxDifficulty.Location = new System.Drawing.Point(11, 136);
            this.comboBoxDifficulty.Name = "comboBoxDifficulty";
            this.comboBoxDifficulty.Size = new System.Drawing.Size(121, 21);
            this.comboBoxDifficulty.TabIndex = 7;
            // 
            // labelDifficulty
            // 
            this.labelDifficulty.AutoSize = true;
            this.labelDifficulty.Location = new System.Drawing.Point(8, 120);
            this.labelDifficulty.Name = "labelDifficulty";
            this.labelDifficulty.Size = new System.Drawing.Size(47, 13);
            this.labelDifficulty.TabIndex = 6;
            this.labelDifficulty.Text = "Difficulty";
            // 
            // buttonBrowseDRPGPath
            // 
            this.buttonBrowseDRPGPath.Location = new System.Drawing.Point(346, 58);
            this.buttonBrowseDRPGPath.Name = "buttonBrowseDRPGPath";
            this.buttonBrowseDRPGPath.Size = new System.Drawing.Size(66, 20);
            this.buttonBrowseDRPGPath.TabIndex = 5;
            this.buttonBrowseDRPGPath.Text = "Browse...";
            this.buttonBrowseDRPGPath.UseVisualStyleBackColor = true;
            this.buttonBrowseDRPGPath.Click += new System.EventHandler(this.buttonBrowseDRPGPath_Click);
            // 
            // textBoxDRPGPath
            // 
            this.textBoxDRPGPath.Location = new System.Drawing.Point(11, 58);
            this.textBoxDRPGPath.Name = "textBoxDRPGPath";
            this.textBoxDRPGPath.ReadOnly = true;
            this.textBoxDRPGPath.Size = new System.Drawing.Size(329, 20);
            this.textBoxDRPGPath.TabIndex = 4;
            // 
            // labelDoomRPGFolderLocation
            // 
            this.labelDoomRPGFolderLocation.AutoSize = true;
            this.labelDoomRPGFolderLocation.Location = new System.Drawing.Point(8, 42);
            this.labelDoomRPGFolderLocation.Name = "labelDoomRPGFolderLocation";
            this.labelDoomRPGFolderLocation.Size = new System.Drawing.Size(137, 13);
            this.labelDoomRPGFolderLocation.TabIndex = 3;
            this.labelDoomRPGFolderLocation.Text = "Doom RPG Folder Location";
            this.labelDoomRPGFolderLocation.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // buttonBrowsePortPath
            // 
            this.buttonBrowsePortPath.Location = new System.Drawing.Point(346, 19);
            this.buttonBrowsePortPath.Name = "buttonBrowsePortPath";
            this.buttonBrowsePortPath.Size = new System.Drawing.Size(66, 20);
            this.buttonBrowsePortPath.TabIndex = 2;
            this.buttonBrowsePortPath.Text = "Browse...";
            this.buttonBrowsePortPath.UseVisualStyleBackColor = true;
            this.buttonBrowsePortPath.Click += new System.EventHandler(this.buttonBrowsePortPath_Click);
            // 
            // textBoxPortPath
            // 
            this.textBoxPortPath.Location = new System.Drawing.Point(11, 19);
            this.textBoxPortPath.Name = "textBoxPortPath";
            this.textBoxPortPath.ReadOnly = true;
            this.textBoxPortPath.Size = new System.Drawing.Size(329, 20);
            this.textBoxPortPath.TabIndex = 1;
            // 
            // labelPortLocation
            // 
            this.labelPortLocation.AutoSize = true;
            this.labelPortLocation.Location = new System.Drawing.Point(8, 3);
            this.labelPortLocation.Name = "labelPortLocation";
            this.labelPortLocation.Size = new System.Drawing.Size(134, 13);
            this.labelPortLocation.TabIndex = 0;
            this.labelPortLocation.Text = "ZDoom/GZDoom Location";
            this.labelPortLocation.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // tabPageMultiplayer
            // 
            this.tabPageMultiplayer.Controls.Add(this.groupBoxServerOptions);
            this.tabPageMultiplayer.Controls.Add(this.groupBoxServerMode);
            this.tabPageMultiplayer.Controls.Add(this.groupBoxMode);
            this.tabPageMultiplayer.Controls.Add(this.checkBoxMultiplayer);
            this.tabPageMultiplayer.Location = new System.Drawing.Point(4, 22);
            this.tabPageMultiplayer.Name = "tabPageMultiplayer";
            this.tabPageMultiplayer.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageMultiplayer.Size = new System.Drawing.Size(420, 298);
            this.tabPageMultiplayer.TabIndex = 1;
            this.tabPageMultiplayer.Text = "Multiplayer";
            this.tabPageMultiplayer.UseVisualStyleBackColor = true;
            // 
            // groupBoxServerOptions
            // 
            this.groupBoxServerOptions.Controls.Add(this.labelDuplex);
            this.groupBoxServerOptions.Controls.Add(this.numericUpDownDuplex);
            this.groupBoxServerOptions.Controls.Add(this.checkBoxExtraTics);
            this.groupBoxServerOptions.Location = new System.Drawing.Point(175, 29);
            this.groupBoxServerOptions.Name = "groupBoxServerOptions";
            this.groupBoxServerOptions.Size = new System.Drawing.Size(237, 263);
            this.groupBoxServerOptions.TabIndex = 5;
            this.groupBoxServerOptions.TabStop = false;
            this.groupBoxServerOptions.Text = "Server Options";
            // 
            // labelDuplex
            // 
            this.labelDuplex.Location = new System.Drawing.Point(6, 39);
            this.labelDuplex.Name = "labelDuplex";
            this.labelDuplex.Size = new System.Drawing.Size(70, 20);
            this.labelDuplex.TabIndex = 6;
            this.labelDuplex.Text = "Duplex";
            this.labelDuplex.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // numericUpDownDuplex
            // 
            this.numericUpDownDuplex.Location = new System.Drawing.Point(82, 39);
            this.numericUpDownDuplex.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDownDuplex.Name = "numericUpDownDuplex";
            this.numericUpDownDuplex.Size = new System.Drawing.Size(120, 20);
            this.numericUpDownDuplex.TabIndex = 6;
            // 
            // checkBoxExtraTics
            // 
            this.checkBoxExtraTics.AutoSize = true;
            this.checkBoxExtraTics.Location = new System.Drawing.Point(6, 20);
            this.checkBoxExtraTics.Name = "checkBoxExtraTics";
            this.checkBoxExtraTics.Size = new System.Drawing.Size(73, 17);
            this.checkBoxExtraTics.TabIndex = 0;
            this.checkBoxExtraTics.Text = "Extra Tics";
            this.checkBoxExtraTics.UseVisualStyleBackColor = true;
            // 
            // groupBoxServerMode
            // 
            this.groupBoxServerMode.Controls.Add(this.radioButtonPacketServer);
            this.groupBoxServerMode.Controls.Add(this.radioButtonPeerToPeer);
            this.groupBoxServerMode.Location = new System.Drawing.Point(8, 155);
            this.groupBoxServerMode.Name = "groupBoxServerMode";
            this.groupBoxServerMode.Size = new System.Drawing.Size(161, 68);
            this.groupBoxServerMode.TabIndex = 4;
            this.groupBoxServerMode.TabStop = false;
            this.groupBoxServerMode.Text = "Server Mode";
            // 
            // radioButtonPacketServer
            // 
            this.radioButtonPacketServer.AutoSize = true;
            this.radioButtonPacketServer.Location = new System.Drawing.Point(6, 42);
            this.radioButtonPacketServer.Name = "radioButtonPacketServer";
            this.radioButtonPacketServer.Size = new System.Drawing.Size(93, 17);
            this.radioButtonPacketServer.TabIndex = 1;
            this.radioButtonPacketServer.TabStop = true;
            this.radioButtonPacketServer.Text = "Packet Server";
            this.radioButtonPacketServer.UseVisualStyleBackColor = true;
            // 
            // radioButtonPeerToPeer
            // 
            this.radioButtonPeerToPeer.AutoSize = true;
            this.radioButtonPeerToPeer.Location = new System.Drawing.Point(6, 19);
            this.radioButtonPeerToPeer.Name = "radioButtonPeerToPeer";
            this.radioButtonPeerToPeer.Size = new System.Drawing.Size(84, 17);
            this.radioButtonPeerToPeer.TabIndex = 0;
            this.radioButtonPeerToPeer.TabStop = true;
            this.radioButtonPeerToPeer.Text = "Peer-to-Peer";
            this.radioButtonPeerToPeer.UseVisualStyleBackColor = true;
            // 
            // groupBoxMode
            // 
            this.groupBoxMode.Controls.Add(this.numericUpDownPlayers);
            this.groupBoxMode.Controls.Add(this.labelPlayers);
            this.groupBoxMode.Controls.Add(this.textBoxHostname);
            this.groupBoxMode.Controls.Add(this.radioButtonHosting);
            this.groupBoxMode.Controls.Add(this.radioButtonJoining);
            this.groupBoxMode.Location = new System.Drawing.Point(8, 29);
            this.groupBoxMode.Name = "groupBoxMode";
            this.groupBoxMode.Size = new System.Drawing.Size(161, 120);
            this.groupBoxMode.TabIndex = 3;
            this.groupBoxMode.TabStop = false;
            this.groupBoxMode.Text = "Mode";
            // 
            // numericUpDownPlayers
            // 
            this.numericUpDownPlayers.Location = new System.Drawing.Point(85, 41);
            this.numericUpDownPlayers.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.numericUpDownPlayers.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numericUpDownPlayers.Name = "numericUpDownPlayers";
            this.numericUpDownPlayers.Size = new System.Drawing.Size(70, 20);
            this.numericUpDownPlayers.TabIndex = 8;
            this.numericUpDownPlayers.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            // 
            // labelPlayers
            // 
            this.labelPlayers.Location = new System.Drawing.Point(6, 41);
            this.labelPlayers.Name = "labelPlayers";
            this.labelPlayers.Size = new System.Drawing.Size(73, 20);
            this.labelPlayers.TabIndex = 7;
            this.labelPlayers.Text = "Players";
            this.labelPlayers.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBoxHostname
            // 
            this.textBoxHostname.Location = new System.Drawing.Point(7, 94);
            this.textBoxHostname.Name = "textBoxHostname";
            this.textBoxHostname.Size = new System.Drawing.Size(148, 20);
            this.textBoxHostname.TabIndex = 6;
            // 
            // radioButtonHosting
            // 
            this.radioButtonHosting.AutoSize = true;
            this.radioButtonHosting.Location = new System.Drawing.Point(6, 19);
            this.radioButtonHosting.Name = "radioButtonHosting";
            this.radioButtonHosting.Size = new System.Drawing.Size(61, 17);
            this.radioButtonHosting.TabIndex = 1;
            this.radioButtonHosting.TabStop = true;
            this.radioButtonHosting.Text = "Hosting";
            this.radioButtonHosting.UseVisualStyleBackColor = true;
            // 
            // radioButtonJoining
            // 
            this.radioButtonJoining.AutoSize = true;
            this.radioButtonJoining.Location = new System.Drawing.Point(6, 71);
            this.radioButtonJoining.Name = "radioButtonJoining";
            this.radioButtonJoining.Size = new System.Drawing.Size(58, 17);
            this.radioButtonJoining.TabIndex = 2;
            this.radioButtonJoining.TabStop = true;
            this.radioButtonJoining.Text = "Joining";
            this.radioButtonJoining.UseVisualStyleBackColor = true;
            // 
            // checkBoxMultiplayer
            // 
            this.checkBoxMultiplayer.AutoSize = true;
            this.checkBoxMultiplayer.Location = new System.Drawing.Point(8, 6);
            this.checkBoxMultiplayer.Name = "checkBoxMultiplayer";
            this.checkBoxMultiplayer.Size = new System.Drawing.Size(107, 17);
            this.checkBoxMultiplayer.TabIndex = 0;
            this.checkBoxMultiplayer.Text = "Multiplayer Game";
            this.checkBoxMultiplayer.UseVisualStyleBackColor = true;
            this.checkBoxMultiplayer.CheckedChanged += new System.EventHandler(this.checkBoxMultiplayer_CheckedChanged);
            // 
            // buttonLaunch
            // 
            this.buttonLaunch.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.buttonLaunch.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonLaunch.Location = new System.Drawing.Point(0, 370);
            this.buttonLaunch.Name = "buttonLaunch";
            this.buttonLaunch.Size = new System.Drawing.Size(428, 35);
            this.buttonLaunch.TabIndex = 6;
            this.buttonLaunch.Text = "Launch Doom RPG";
            this.buttonLaunch.UseVisualStyleBackColor = true;
            this.buttonLaunch.Click += new System.EventHandler(this.buttonLaunch_Click);
            // 
            // labelCustomCommands
            // 
            this.labelCustomCommands.Location = new System.Drawing.Point(5, 327);
            this.labelCustomCommands.Name = "labelCustomCommands";
            this.labelCustomCommands.Size = new System.Drawing.Size(419, 14);
            this.labelCustomCommands.TabIndex = 7;
            this.labelCustomCommands.Text = "Custom Commands";
            this.labelCustomCommands.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // textBoxCustomCommands
            // 
            this.textBoxCustomCommands.Location = new System.Drawing.Point(4, 344);
            this.textBoxCustomCommands.Name = "textBoxCustomCommands";
            this.textBoxCustomCommands.Size = new System.Drawing.Size(420, 20);
            this.textBoxCustomCommands.TabIndex = 8;
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(428, 405);
            this.Controls.Add(this.textBoxCustomCommands);
            this.Controls.Add(this.labelCustomCommands);
            this.Controls.Add(this.buttonLaunch);
            this.Controls.Add(this.tabControlMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "FormMain";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Doom RPG Launcher";
            this.tabControlMain.ResumeLayout(false);
            this.tabPageBasic.ResumeLayout(false);
            this.tabPageBasic.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapNumber)).EndInit();
            this.tabPageMultiplayer.ResumeLayout(false);
            this.tabPageMultiplayer.PerformLayout();
            this.groupBoxServerOptions.ResumeLayout(false);
            this.groupBoxServerOptions.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDuplex)).EndInit();
            this.groupBoxServerMode.ResumeLayout(false);
            this.groupBoxServerMode.PerformLayout();
            this.groupBoxMode.ResumeLayout(false);
            this.groupBoxMode.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPlayers)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl tabControlMain;
        private System.Windows.Forms.TabPage tabPageBasic;
        private System.Windows.Forms.TabPage tabPageMultiplayer;
        private System.Windows.Forms.Label labelPortLocation;
        private System.Windows.Forms.Button buttonBrowsePortPath;
        private System.Windows.Forms.TextBox textBoxPortPath;
        private System.Windows.Forms.Button buttonBrowseDRPGPath;
        private System.Windows.Forms.TextBox textBoxDRPGPath;
        private System.Windows.Forms.Label labelDoomRPGFolderLocation;
        private System.Windows.Forms.Button buttonLaunch;
        private System.Windows.Forms.ComboBox comboBoxDifficulty;
        private System.Windows.Forms.Label labelDifficulty;
        private System.Windows.Forms.NumericUpDown numericUpDownMapNumber;
        private System.Windows.Forms.Label labelMapNumber;
        private System.Windows.Forms.CheckedListBox checkedListBoxPatches;
        private System.Windows.Forms.Label labelDoomRPGPatches;
        private System.Windows.Forms.CheckBox checkBoxMultiplayer;
        private System.Windows.Forms.RadioButton radioButtonJoining;
        private System.Windows.Forms.RadioButton radioButtonHosting;
        private System.Windows.Forms.GroupBox groupBoxServerMode;
        private System.Windows.Forms.RadioButton radioButtonPacketServer;
        private System.Windows.Forms.RadioButton radioButtonPeerToPeer;
        private System.Windows.Forms.GroupBox groupBoxMode;
        private System.Windows.Forms.GroupBox groupBoxServerOptions;
        private System.Windows.Forms.Label labelDuplex;
        private System.Windows.Forms.NumericUpDown numericUpDownDuplex;
        private System.Windows.Forms.CheckBox checkBoxExtraTics;
        private System.Windows.Forms.TextBox textBoxHostname;
        private System.Windows.Forms.NumericUpDown numericUpDownPlayers;
        private System.Windows.Forms.Label labelPlayers;
        private System.Windows.Forms.Button buttonBrowseModsPath;
        private System.Windows.Forms.TextBox textBoxModsPath;
        private System.Windows.Forms.Label labelModsLocation;
        private System.Windows.Forms.Label labelCustomCommands;
        private System.Windows.Forms.TextBox textBoxCustomCommands;
    }
}

