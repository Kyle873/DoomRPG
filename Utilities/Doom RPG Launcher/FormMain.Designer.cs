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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.tabControlMain = new System.Windows.Forms.TabControl();
            this.tabPageBasic = new System.Windows.Forms.TabPage();
            this.comboBoxClass = new System.Windows.Forms.ComboBox();
            this.labelPlayerClass = new System.Windows.Forms.Label();
            this.comboBoxIWAD = new System.Windows.Forms.ComboBox();
            this.labelIWAD = new System.Windows.Forms.Label();
            this.buttonBrowseModsPath = new System.Windows.Forms.Button();
            this.textBoxModsPath = new System.Windows.Forms.TextBox();
            this.labelModsLocation = new System.Windows.Forms.Label();
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
            this.tabPageModsPatches = new System.Windows.Forms.TabPage();
            this.checkedListBoxMods = new System.Windows.Forms.CheckedListBox();
            this.labelMods = new System.Windows.Forms.Label();
            this.checkedListBoxPatches = new System.Windows.Forms.CheckedListBox();
            this.labelPatches = new System.Windows.Forms.Label();
            this.tabPageCredits = new System.Windows.Forms.TabPage();
            this.richTextBoxCredits = new System.Windows.Forms.RichTextBox();
            this.buttonLaunch = new System.Windows.Forms.Button();
            this.labelCustomCommands = new System.Windows.Forms.Label();
            this.textBoxCustomCommands = new System.Windows.Forms.TextBox();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripProgressBar = new System.Windows.Forms.ToolStripProgressBar();
            this.buttonCheckUpdates = new System.Windows.Forms.Button();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.tabControlMain.SuspendLayout();
            this.tabPageBasic.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownMapNumber)).BeginInit();
            this.tabPageMultiplayer.SuspendLayout();
            this.groupBoxServerOptions.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownDuplex)).BeginInit();
            this.groupBoxServerMode.SuspendLayout();
            this.groupBoxMode.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDownPlayers)).BeginInit();
            this.tabPageModsPatches.SuspendLayout();
            this.tabPageCredits.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControlMain
            // 
            this.tabControlMain.Controls.Add(this.tabPageBasic);
            this.tabControlMain.Controls.Add(this.tabPageMultiplayer);
            this.tabControlMain.Controls.Add(this.tabPageModsPatches);
            this.tabControlMain.Controls.Add(this.tabPageCredits);
            this.tabControlMain.Dock = System.Windows.Forms.DockStyle.Top;
            this.tabControlMain.Location = new System.Drawing.Point(0, 0);
            this.tabControlMain.Name = "tabControlMain";
            this.tabControlMain.SelectedIndex = 0;
            this.tabControlMain.Size = new System.Drawing.Size(428, 324);
            this.tabControlMain.TabIndex = 0;
            // 
            // tabPageBasic
            // 
            this.tabPageBasic.Controls.Add(this.comboBoxClass);
            this.tabPageBasic.Controls.Add(this.labelPlayerClass);
            this.tabPageBasic.Controls.Add(this.comboBoxIWAD);
            this.tabPageBasic.Controls.Add(this.labelIWAD);
            this.tabPageBasic.Controls.Add(this.buttonBrowseModsPath);
            this.tabPageBasic.Controls.Add(this.textBoxModsPath);
            this.tabPageBasic.Controls.Add(this.labelModsLocation);
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
            // comboBoxClass
            // 
            this.comboBoxClass.Enabled = false;
            this.comboBoxClass.FormattingEnabled = true;
            this.comboBoxClass.Location = new System.Drawing.Point(11, 177);
            this.comboBoxClass.Name = "comboBoxClass";
            this.comboBoxClass.Size = new System.Drawing.Size(121, 21);
            this.comboBoxClass.TabIndex = 18;
            // 
            // labelPlayerClass
            // 
            this.labelPlayerClass.AutoSize = true;
            this.labelPlayerClass.Location = new System.Drawing.Point(8, 161);
            this.labelPlayerClass.Name = "labelPlayerClass";
            this.labelPlayerClass.Size = new System.Drawing.Size(64, 13);
            this.labelPlayerClass.TabIndex = 17;
            this.labelPlayerClass.Text = "Player Class";
            // 
            // comboBoxIWAD
            // 
            this.comboBoxIWAD.FormattingEnabled = true;
            this.comboBoxIWAD.Location = new System.Drawing.Point(12, 136);
            this.comboBoxIWAD.Name = "comboBoxIWAD";
            this.comboBoxIWAD.Size = new System.Drawing.Size(121, 21);
            this.comboBoxIWAD.TabIndex = 16;
            // 
            // labelIWAD
            // 
            this.labelIWAD.AutoSize = true;
            this.labelIWAD.Location = new System.Drawing.Point(9, 120);
            this.labelIWAD.Name = "labelIWAD";
            this.labelIWAD.Size = new System.Drawing.Size(67, 13);
            this.labelIWAD.TabIndex = 15;
            this.labelIWAD.Text = "Doom IWAD";
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
            this.textBoxModsPath.Size = new System.Drawing.Size(329, 20);
            this.textBoxModsPath.TabIndex = 13;
            this.textBoxModsPath.TextChanged += new System.EventHandler(this.textBoxModsPath_TextChanged);
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
            // numericUpDownMapNumber
            // 
            this.numericUpDownMapNumber.Location = new System.Drawing.Point(294, 136);
            this.numericUpDownMapNumber.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDownMapNumber.Name = "numericUpDownMapNumber";
            this.numericUpDownMapNumber.Size = new System.Drawing.Size(74, 20);
            this.numericUpDownMapNumber.TabIndex = 9;
            // 
            // labelMapNumber
            // 
            this.labelMapNumber.AutoSize = true;
            this.labelMapNumber.Location = new System.Drawing.Point(291, 120);
            this.labelMapNumber.Name = "labelMapNumber";
            this.labelMapNumber.Size = new System.Drawing.Size(68, 13);
            this.labelMapNumber.TabIndex = 8;
            this.labelMapNumber.Text = "Map Number";
            // 
            // comboBoxDifficulty
            // 
            this.comboBoxDifficulty.FormattingEnabled = true;
            this.comboBoxDifficulty.Location = new System.Drawing.Point(152, 136);
            this.comboBoxDifficulty.Name = "comboBoxDifficulty";
            this.comboBoxDifficulty.Size = new System.Drawing.Size(121, 21);
            this.comboBoxDifficulty.TabIndex = 7;
            // 
            // labelDifficulty
            // 
            this.labelDifficulty.AutoSize = true;
            this.labelDifficulty.Location = new System.Drawing.Point(149, 120);
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
            // tabPageModsPatches
            // 
            this.tabPageModsPatches.Controls.Add(this.checkedListBoxMods);
            this.tabPageModsPatches.Controls.Add(this.labelMods);
            this.tabPageModsPatches.Controls.Add(this.checkedListBoxPatches);
            this.tabPageModsPatches.Controls.Add(this.labelPatches);
            this.tabPageModsPatches.Location = new System.Drawing.Point(4, 22);
            this.tabPageModsPatches.Name = "tabPageModsPatches";
            this.tabPageModsPatches.Size = new System.Drawing.Size(420, 298);
            this.tabPageModsPatches.TabIndex = 3;
            this.tabPageModsPatches.Text = "Mods/Patches";
            this.tabPageModsPatches.UseVisualStyleBackColor = true;
            // 
            // checkedListBoxMods
            // 
            this.checkedListBoxMods.FormattingEnabled = true;
            this.checkedListBoxMods.Location = new System.Drawing.Point(201, 16);
            this.checkedListBoxMods.Name = "checkedListBoxMods";
            this.checkedListBoxMods.Size = new System.Drawing.Size(210, 274);
            this.checkedListBoxMods.TabIndex = 20;
            // 
            // labelMods
            // 
            this.labelMods.AutoSize = true;
            this.labelMods.Location = new System.Drawing.Point(198, 0);
            this.labelMods.Name = "labelMods";
            this.labelMods.Size = new System.Drawing.Size(82, 13);
            this.labelMods.TabIndex = 19;
            this.labelMods.Text = "WAD/PK3 Files";
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
            this.checkedListBoxPatches.Location = new System.Drawing.Point(10, 16);
            this.checkedListBoxPatches.Name = "checkedListBoxPatches";
            this.checkedListBoxPatches.Size = new System.Drawing.Size(185, 274);
            this.checkedListBoxPatches.TabIndex = 18;
            // 
            // labelPatches
            // 
            this.labelPatches.AutoSize = true;
            this.labelPatches.Location = new System.Drawing.Point(8, 0);
            this.labelPatches.Name = "labelPatches";
            this.labelPatches.Size = new System.Drawing.Size(103, 13);
            this.labelPatches.TabIndex = 17;
            this.labelPatches.Text = "Doom RPG Patches";
            // 
            // tabPageCredits
            // 
            this.tabPageCredits.Controls.Add(this.richTextBoxCredits);
            this.tabPageCredits.Location = new System.Drawing.Point(4, 22);
            this.tabPageCredits.Name = "tabPageCredits";
            this.tabPageCredits.Size = new System.Drawing.Size(420, 298);
            this.tabPageCredits.TabIndex = 2;
            this.tabPageCredits.Text = "Credits";
            this.tabPageCredits.UseVisualStyleBackColor = true;
            // 
            // richTextBoxCredits
            // 
            this.richTextBoxCredits.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.richTextBoxCredits.Dock = System.Windows.Forms.DockStyle.Fill;
            this.richTextBoxCredits.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.richTextBoxCredits.Location = new System.Drawing.Point(0, 0);
            this.richTextBoxCredits.Name = "richTextBoxCredits";
            this.richTextBoxCredits.ReadOnly = true;
            this.richTextBoxCredits.Size = new System.Drawing.Size(420, 298);
            this.richTextBoxCredits.TabIndex = 0;
            this.richTextBoxCredits.Text = resources.GetString("richTextBoxCredits.Text");
            this.richTextBoxCredits.TextChanged += new System.EventHandler(this.richTextBoxCredits_TextChanged);
            // 
            // buttonLaunch
            // 
            this.buttonLaunch.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonLaunch.Location = new System.Drawing.Point(206, 370);
            this.buttonLaunch.Name = "buttonLaunch";
            this.buttonLaunch.Size = new System.Drawing.Size(222, 35);
            this.buttonLaunch.TabIndex = 6;
            this.buttonLaunch.Text = "Launch Doom RPG";
            this.buttonLaunch.UseVisualStyleBackColor = true;
            this.buttonLaunch.Click += new System.EventHandler(this.buttonLaunch_Click);
            this.buttonLaunch.MouseDown += new System.Windows.Forms.MouseEventHandler(this.buttonLaunch_MouseDown);
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
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel,
            this.toolStripProgressBar});
            this.statusStrip.Location = new System.Drawing.Point(0, 411);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(428, 22);
            this.statusStrip.TabIndex = 9;
            // 
            // toolStripStatusLabel
            // 
            this.toolStripStatusLabel.AutoSize = false;
            this.toolStripStatusLabel.Name = "toolStripStatusLabel";
            this.toolStripStatusLabel.Size = new System.Drawing.Size(311, 17);
            this.toolStripStatusLabel.Spring = true;
            this.toolStripStatusLabel.Text = "Ready";
            this.toolStripStatusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // toolStripProgressBar
            // 
            this.toolStripProgressBar.Name = "toolStripProgressBar";
            this.toolStripProgressBar.Size = new System.Drawing.Size(100, 16);
            this.toolStripProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Continuous;
            // 
            // buttonCheckUpdates
            // 
            this.buttonCheckUpdates.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buttonCheckUpdates.Location = new System.Drawing.Point(4, 370);
            this.buttonCheckUpdates.Name = "buttonCheckUpdates";
            this.buttonCheckUpdates.Size = new System.Drawing.Size(196, 35);
            this.buttonCheckUpdates.TabIndex = 10;
            this.buttonCheckUpdates.Text = "Check for Updates";
            this.buttonCheckUpdates.UseVisualStyleBackColor = true;
            this.buttonCheckUpdates.Click += new System.EventHandler(this.buttonCheckUpdates_Click);
            // 
            // timer
            // 
            this.timer.Enabled = true;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(428, 433);
            this.Controls.Add(this.buttonCheckUpdates);
            this.Controls.Add(this.statusStrip);
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
            this.tabPageModsPatches.ResumeLayout(false);
            this.tabPageModsPatches.PerformLayout();
            this.tabPageCredits.ResumeLayout(false);
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
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
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.TabPage tabPageCredits;
        private System.Windows.Forms.RichTextBox richTextBoxCredits;
        private System.Windows.Forms.Button buttonCheckUpdates;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar;
        private System.Windows.Forms.TabPage tabPageModsPatches;
        private System.Windows.Forms.CheckedListBox checkedListBoxMods;
        private System.Windows.Forms.Label labelMods;
        private System.Windows.Forms.CheckedListBox checkedListBoxPatches;
        private System.Windows.Forms.Label labelPatches;
        private System.Windows.Forms.ComboBox comboBoxIWAD;
        private System.Windows.Forms.Label labelIWAD;
        private System.Windows.Forms.ComboBox comboBoxClass;
        private System.Windows.Forms.Label labelPlayerClass;
        private System.Windows.Forms.Timer timer;
    }
}

