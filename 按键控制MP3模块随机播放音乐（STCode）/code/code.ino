#include <SoftwareSerial.h>  //添加软串口头文件
SoftwareSerial mySerial(4,5); // 音乐模块TX接4，音乐模块RX接5
unsigned char play_song1[8] = {0x7E,0xFF,0x06,0x08,0x00,0x00,0x01,0xEF};  //1
unsigned char play_song2[8] = {0x7E,0xFF,0x06,0x03,0x00,0x00,0x02,0xEF};  //2
unsigned char play_song3[8] = {0x7E,0xFF,0x06,0x08,0x00,0x00,0x03,0xEF};  //3
unsigned char play_song4[8] = {0x7E,0xFF,0x06,0x03,0x00,0x00,0x04,0xEF};  //4
unsigned char play_song5[8] = {0x7E,0xFF,0x06,0x08,0x00,0x00,0x05,0xEF};  //5
unsigned char play_song6[8] = {0x7E,0xFF,0x06,0x03,0x00,0x00,0x06,0xEF};  //6
unsigned char play_song7[8] = {0x7E,0xFF,0x06,0x08,0x00,0x00,0x07,0xEF};  //7
unsigned char play_song8[8] = {0x7E,0xFF,0x06,0x03,0x00,0x00,0x08,0xEF};  //8
unsigned char play_song9[8] = {0x7E,0xFF,0x06,0x08,0x00,0x00,0x09,0xEF};  //9
unsigned char play_song10[8] = {0x7E,0xFF,0x06,0x03,0x00,0x00,0x0A,0xEF};  //10
unsigned char pause[8]={0x7E,0xFF,0x06,0x0E,0x00,0x00,0x00,0xEF};         //暂停播放
unsigned char play[8]={0x7E,0xFF,0x06,0x0D,0x00,0x00,0x00,0xEF};          //恢复播放
unsigned char stop_play[8] = {0x7E,0xFF,0x06,0x16,0x00,0x00,0x00,0xEF};   //停止播放指令
unsigned char top_volume[8]={0x7E,0xFF,0x06,0x06,0x00,0x00,0x1E,0xEF};   //设置最大音量
int keypin=2;   //定义按键引脚2
int num=0;      //定义播放曲目
int start_flag=0; //定义播放标志位
void setup() 
{
  Serial.begin(9600);   //串口波特率设置
  mySerial.begin(9600);  //软串口波特率设置
  mySerial.write(top_volume, 8); //设置音量为最大
  mySerial.write(stop_play, 8);  //开机静音
  randomSeed(analogRead(A0));    //随机数种子A0
  pinMode(keypin,INPUT_PULLUP);
}

void loop()
{
  key_scan();
if(start_flag==1)   //播放标志位为1（按键有按下）
{
  switch (num)       //根据随机数随机播放曲目
  {
    case 1: mySerial.write(play_song1,8);
    break;
    case 2: mySerial.write(play_song2,8);
    break;
    case 3: mySerial.write(play_song3,8);
    break;
    case 4: mySerial.write(play_song4,8);
    break;
    case 5: mySerial.write(play_song5,8);
    break;
    case 6: mySerial.write(play_song6,8);
    break;
    case 7: mySerial.write(play_song7,8);
    break;
    case 8: mySerial.write(play_song8,8);
    break;
    case 9: mySerial.write(play_song9,8);
    break;
    case 10: mySerial.write(play_song10,8);
    break;
  default:
    break;
  }
  start_flag=0;    //播放标志为归0
}

}
void key_scan()    //按键扫描子函数
{
  if(digitalRead(keypin)==LOW)
  {
    delay(20);       //消抖
    if(digitalRead(keypin)==LOW)
    {
      num=random(1,11);  //随机数获取
      start_flag=1;      //播放标志位置1
    }
  }
}