#ifndef __SOCKDATA_H__
#define __SOCKDATA_H__


#define MSG_CTRL    16			//ctrl键
#define MSG_SHIFT    17			//shift键
#define MSG_LBUTTONDBLCLK 1		//左键双击
#define MSG_LBUTTONDOWN 2		//左键单击
#define MSG_RBUTTONDOWN 3		//右键单击

struct BMP_SEND_LEN
{
	unsigned long oldlen;	//最初未压缩前的长度
	unsigned long newlen;	//压缩后长度
};

struct msg_data
{
	CPoint point;	//鼠标的坐标
	int mouse;		//鼠标的3个状态
	int flag;		//是否是组合键
	int ch;			//key
	msg_data():point(0,0),mouse(-1),flag(-1),ch(-1){}
};

#endif