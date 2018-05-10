namespace PixelDemo
{
    partial class GUI
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.trans_btn = new System.Windows.Forms.Button();
            this.select_btn = new System.Windows.Forms.Button();
            this.resol_Size = new System.Windows.Forms.ComboBox();
            this.tile_Size = new System.Windows.Forms.ComboBox();
            this.tileInfoBox = new System.Windows.Forms.TextBox();
            this.resolInfoBox = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.originPic = new System.Windows.Forms.PictureBox();
            this.transPic = new System.Windows.Forms.PictureBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.statusBox = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.originPic)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.transPic)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 6;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel2.Controls.Add(this.trans_btn, 5, 0);
            this.tableLayoutPanel2.Controls.Add(this.select_btn, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.resol_Size, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.tile_Size, 4, 0);
            this.tableLayoutPanel2.Controls.Add(this.tileInfoBox, 3, 0);
            this.tableLayoutPanel2.Controls.Add(this.resolInfoBox, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(17, 19);
            this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(17, 19, 17, 0);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(1188, 56);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // trans_btn
            // 
            this.trans_btn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.trans_btn.Location = new System.Drawing.Point(964, 19);
            this.trans_btn.Margin = new System.Windows.Forms.Padding(17, 19, 17, 19);
            this.trans_btn.Name = "trans_btn";
            this.trans_btn.Size = new System.Drawing.Size(207, 18);
            this.trans_btn.TabIndex = 3;
            this.trans_btn.Text = "변환";
            this.trans_btn.UseVisualStyleBackColor = true;
            this.trans_btn.Click += new System.EventHandler(this.trans_btn_Click_1);
            // 
            // select_btn
            // 
            this.select_btn.AutoSize = true;
            this.select_btn.Dock = System.Windows.Forms.DockStyle.Fill;
            this.select_btn.Location = new System.Drawing.Point(17, 19);
            this.select_btn.Margin = new System.Windows.Forms.Padding(17, 19, 17, 19);
            this.select_btn.Name = "select_btn";
            this.select_btn.Size = new System.Drawing.Size(203, 18);
            this.select_btn.TabIndex = 4;
            this.select_btn.Text = "이미지 선택";
            this.select_btn.UseVisualStyleBackColor = true;
            this.select_btn.Click += new System.EventHandler(this.select_btn_Click_1);
            // 
            // resol_Size
            // 
            this.resol_Size.Dock = System.Windows.Forms.DockStyle.Fill;
            this.resol_Size.FormattingEnabled = true;
            this.resol_Size.Items.AddRange(new object[] {
            "20",
            "40",
            "80"});
            this.resol_Size.Location = new System.Drawing.Point(366, 19);
            this.resol_Size.Margin = new System.Windows.Forms.Padding(11, 19, 34, 19);
            this.resol_Size.Name = "resol_Size";
            this.resol_Size.Size = new System.Drawing.Size(192, 23);
            this.resol_Size.TabIndex = 5;
            this.resol_Size.Text = "20";
            this.resol_Size.SelectedIndexChanged += new System.EventHandler(this.resol_Size_SelectedIndexChanged);
            // 
            // tile_Size
            // 
            this.tile_Size.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tile_Size.FormattingEnabled = true;
            this.tile_Size.Items.AddRange(new object[] {
            "4",
            "8"});
            this.tile_Size.Location = new System.Drawing.Point(721, 19);
            this.tile_Size.Margin = new System.Windows.Forms.Padding(11, 19, 34, 19);
            this.tile_Size.Name = "tile_Size";
            this.tile_Size.Size = new System.Drawing.Size(192, 23);
            this.tile_Size.TabIndex = 6;
            this.tile_Size.Text = "4";
            this.tile_Size.SelectedIndexChanged += new System.EventHandler(this.tile_Size_SelectedIndexChanged);
            // 
            // tileInfoBox
            // 
            this.tileInfoBox.BackColor = System.Drawing.SystemColors.Control;
            this.tileInfoBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.tileInfoBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.tileInfoBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tileInfoBox.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.tileInfoBox.Location = new System.Drawing.Point(595, 25);
            this.tileInfoBox.Margin = new System.Windows.Forms.Padding(3, 25, 3, 19);
            this.tileInfoBox.Name = "tileInfoBox";
            this.tileInfoBox.ReadOnly = true;
            this.tileInfoBox.Size = new System.Drawing.Size(112, 18);
            this.tileInfoBox.TabIndex = 7;
            this.tileInfoBox.Text = "타일 크기";
            this.tileInfoBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // resolInfoBox
            // 
            this.resolInfoBox.BackColor = System.Drawing.SystemColors.Control;
            this.resolInfoBox.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.resolInfoBox.Cursor = System.Windows.Forms.Cursors.Default;
            this.resolInfoBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.resolInfoBox.Font = new System.Drawing.Font("굴림", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(129)));
            this.resolInfoBox.Location = new System.Drawing.Point(240, 25);
            this.resolInfoBox.Margin = new System.Windows.Forms.Padding(3, 25, 3, 19);
            this.resolInfoBox.Name = "resolInfoBox";
            this.resolInfoBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.resolInfoBox.Size = new System.Drawing.Size(112, 18);
            this.resolInfoBox.TabIndex = 8;
            this.resolInfoBox.Text = "해상도";
            this.resolInfoBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Controls.Add(this.originPic, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.transPic, 1, 0);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(3, 79);
            this.tableLayoutPanel3.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(1216, 517);
            this.tableLayoutPanel3.TabIndex = 3;
            // 
            // originPic
            // 
            this.originPic.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.originPic.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.originPic.Dock = System.Windows.Forms.DockStyle.Fill;
            this.originPic.Location = new System.Drawing.Point(34, 19);
            this.originPic.Margin = new System.Windows.Forms.Padding(34, 19, 34, 19);
            this.originPic.Name = "originPic";
            this.originPic.Padding = new System.Windows.Forms.Padding(114, 125, 114, 125);
            this.originPic.Size = new System.Drawing.Size(540, 479);
            this.originPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.originPic.TabIndex = 0;
            this.originPic.TabStop = false;
            // 
            // transPic
            // 
            this.transPic.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.transPic.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.transPic.Dock = System.Windows.Forms.DockStyle.Fill;
            this.transPic.Location = new System.Drawing.Point(642, 19);
            this.transPic.Margin = new System.Windows.Forms.Padding(34, 19, 34, 19);
            this.transPic.Name = "transPic";
            this.transPic.Size = new System.Drawing.Size(540, 479);
            this.transPic.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.transPic.TabIndex = 1;
            this.transPic.TabStop = false;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoScroll = true;
            this.tableLayoutPanel1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.statusBox, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 70F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1222, 750);
            this.tableLayoutPanel1.TabIndex = 4;
            // 
            // statusBox
            // 
            this.statusBox.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.statusBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.statusBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.statusBox.Location = new System.Drawing.Point(34, 604);
            this.statusBox.Margin = new System.Windows.Forms.Padding(34, 4, 34, 25);
            this.statusBox.Multiline = true;
            this.statusBox.Name = "statusBox";
            this.statusBox.ReadOnly = true;
            this.statusBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.statusBox.Size = new System.Drawing.Size(1154, 121);
            this.statusBox.TabIndex = 4;
            // 
            // GUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1222, 750);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "GUI";
            this.Text = "Tezzle";
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.originPic)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.transPic)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button trans_btn;
        private System.Windows.Forms.Button select_btn;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.PictureBox originPic;
        private System.Windows.Forms.PictureBox transPic;
        private System.Windows.Forms.TextBox statusBox;
        protected internal System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.ComboBox resol_Size;
        private System.Windows.Forms.ComboBox tile_Size;
        private System.Windows.Forms.TextBox tileInfoBox;
        private System.Windows.Forms.TextBox resolInfoBox;

    }
}

