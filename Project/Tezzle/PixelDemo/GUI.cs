using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace PixelDemo
{
    public partial class GUI : Form
    {
        Image originImg;
        Image transImg;
        string originImgPath;
        string tempImgPath;
        string transImgPath;
        string[] pathList;
        int resol;
        int tile;
        Thread worker;

        public GUI()
        {
            InitializeComponent();
            resol = 0;
            tile = 4;
            setStatusBox("프로그램 시작!");
            this.WindowState = FormWindowState.Maximized;
            this.Location = new Point(0, 0);
            this.Size = Screen.PrimaryScreen.WorkingArea.Size;
        }

        public string ShowFileOpenDialog()
        {
            //파일오픈창 생성 및 설정
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "탐색기";
            ofd.FileName = "";
            ofd.Filter = "그림 파일 (*.jpg, *.gif, *.bmp) | *.jpg; *.gif; *.bmp; | 모든 파일 (*.*) | *.*";

            //파일 오픈창 로드
            DialogResult dr = ofd.ShowDialog();

            //OK버튼 클릭시
            if (dr == DialogResult.OK)
            {
                //File명과 확장자를 가지고 온다.
                string fileName = ofd.SafeFileName;
                //File경로와 File명을 모두 가지고 온다.
                string fileFullName = ofd.FileName;
                //File경로만 가지고 온다.
                string filePath = fileFullName.Replace(fileName, "");

                //출력 예제용 로직
                //label1.Text = "File Name  : " + fileName;
                //label2.Text = "Full Name  : " + fileFullName;
                //label3.Text = "File Path  : " + filePath;
                //File경로 + 파일명 리턴
                return fileFullName;
            }
            //취소버튼 클릭시 또는 ESC키로 파일창을 종료 했을경우
            else if (dr == DialogResult.Cancel)
            {
                return "";
            }

            return "";
        }

     
        
        private void select_btn_Click_1(object sender, EventArgs e)               //이미지 선택 버튼
        {
            try {                                 //모든 예외를 처리하기 위해 try catch 사용
                originImgPath = ShowFileOpenDialog();
                pathList = originImgPath.Split('\\');
                tempImgPath = transImgPath = pathList[0];

                originImg = Image.FromFile(originImgPath);
                transImg = (Image)originImg.Clone();

                originPic.Image = originImg;
                transPic.Image = null;                      //또 다른 이미지를 변환하고 싶을때는 transPic의 값을 null로 바꿔준다.
                setStatusBox(pathList[pathList.Length - 1] + " 파일 열었습니다!");
            }
            catch(Exception){
                return;
            }
        }

        private void trans_btn_Click_1(object sender, EventArgs e)         //변환 버튼
        {

            //입력된 경로를 가지고 툴을 이용하여 tran_Img에 출력
            //  ManagedPixelation.MainWrap mainWrap = new ManagedPixelation.MainWrap();
            tempImgPath = pathList[0];
            transImgPath = pathList[0];
            for (int i = 1; i < pathList.Length; i++)
            {
                
                if(i<pathList.Length-2)
                {
                    tempImgPath += ("\\" + pathList[i]);
                    transImgPath += ("\\" + pathList[i]);
                }
                else if (i == pathList.Length - 2)
                {
                    tempImgPath += "\\tempImage";
                    transImgPath += "\\transImage";
                }
                else
                {
                    tempImgPath += ("\\" + pathList[i]);
                    transImgPath += ("\\trans_" + pathList[i]);
                }
            }
         

            unsafe
            {
                setStatusBox("변환 시작...");
                /////////////////////////////////// 스레드 작업 넣기


                worker = new Thread(new ThreadStart(Run));         //작업 스레드 할당.
                
               
                worker.Start();
                worker.Join();
                ///////////////////////////////////
                
                try 
                {
                    //lock(this){
                    // Monitor.Wait(this);                  //스레드 wait()
                    //}
                   
                    transImg = Image.FromFile(transImgPath);// + test("mario01.bmp", resol, tile));
                    transPic.Image = transImg;

                    setStatusBox("변환 성공!");
                
                        
                }
                catch (Exception) 
                { 
                    setStatusBox("변환 실패!");
                }
            }
            
        }


        private void Run()                     //스레드 run 되는 함수 정의.
        {
            ManagedPixelation.MainWrap mainWrap = new ManagedPixelation.MainWrap();

            byte[] originbytes = Encoding.ASCII.GetBytes(tempImgPath);             
            byte[] transbytes = Encoding.ASCII.GetBytes(transImgPath);
            unsafe {
                sbyte* originPathchar;
                sbyte* transPathchar;
                fixed (byte* p = originbytes)
                {
                    originPathchar = (sbyte*)p;
                }
                fixed (byte* p = transbytes)
                {
                    transPathchar = (sbyte*)p;
                }

                mainWrap.start(resol, tile, originPathchar, transPathchar);

                //lock(this){
                //    Monitor.Pulse(this);                 //스레드 notify()
                //}
                
            }
            
        }
    

        private void tile_Size_SelectedIndexChanged(object sender, EventArgs e)
        {
            tile = int.Parse(((ComboBox)sender).Text);
        }

        private void resol_Size_SelectedIndexChanged(object sender, EventArgs e)
        {
            resol = int.Parse(((ComboBox)sender).Text);
        }

        private void setStatusBox(string status) {
            statusBox.Text += status+"\n\r\n\r";
        }
    }
}
