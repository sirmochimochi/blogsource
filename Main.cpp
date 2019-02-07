/* ���悩��t���[�������o���ď������s���Ăѓ���ɂ���v���O�����̗�*/

#include "Image.h"
#include <opencv2/videoio.hpp> //OpenCV�Ńr�f�I��ǂݏ������郁�\�b�h�̃w�b�_
#include <opencv2/highgui.hpp> //waitKey()��imshow()�Ȃǂ֗̕���GUI�p���\�b�h�̃w�b�_
#include <iostream>

using namespace cv; //OpenCV�̖��O���
using namespace std;

int main(int argc, const char* argv[])
{

	// �����ǂݍ���
	VideoCapture cap("C:/hogehoge/erovideo.mp4");
	// �I�[�v���`�F�b�N
	if (!cap.isOpened()) return -1;


	// ���͓���̃v���p�e�B���擾
	double width, hight,fps;
	width = cap.get(CAP_PROP_FRAME_WIDTH);
	hight = cap.get(CAP_PROP_FRAME_HEIGHT);
	fps = cap.get(CAP_PROP_FPS);


	// ���͓���̍Đ��J�n���Ԃ��w��
	double start_min = 10; //��
	double start_sec = 34; //�b
	double start_ms = (start_min * 60 + start_sec) * 1000; 
	cap.set(CAP_PROP_POS_MSEC, start_ms); 


	// �o�͂��铮��̓��ꕨ�����
	VideoWriter writer("C:/hogehoge/resultvideo.wmv", VideoWriter::fourcc('W', 'M', 'V', '1'), fps, Size(width, hight));
	// �I�[�v���`�F�b�N
	if (!writer.isOpened()) return -1; 


	Image image;
	Mat frame;
	int framecounter = 1; //���݂̃t���[����
	for (;;)
	{
		// 1�t���[���ǂݍ���
		cap >> frame;

		if (!frame.empty()) {
			/******* �����ɒ��o�����t���[���̏������L�q ******/

			//�Ⴆ�΃K���}�␳������H
			image.correctGamma(frame, 0.5);

			/*************************************************/

			//������̃t���[�����r�f�I�t�@�C���ɏo��
			writer << frame;

			//�o�͂��ꂽ�t���[�����m�F
			namedWindow("current frame", WINDOW_NORMAL); //���̂��߂ɕK�v
			resizeWindow("current frame", width / 4, hight / 4); //�m�F�p�̂��ߏ������\��
			imshow("current frame", frame);
			printf("%d frame process complete...\n", framecounter++);
		}
		if (waitKey(30) >= 0) break; //30�~���b�ȓ��ɃL�[��������Ȃ���΃��[�v�p��
	}

	return 0;
}