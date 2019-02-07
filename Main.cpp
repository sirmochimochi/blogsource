/* 動画からフレームを取り出して処理を行い再び動画にするプログラムの例*/

#include "Image.h"
#include <opencv2/videoio.hpp> //OpenCVでビデオを読み書きするメソッドのヘッダ
#include <opencv2/highgui.hpp> //waitKey()やimshow()などの便利なGUI用メソッドのヘッダ
#include <iostream>

using namespace cv; //OpenCVの名前空間
using namespace std;

int main(int argc, const char* argv[])
{

	// 動画を読み込む
	VideoCapture cap("C:/hogehoge/erovideo.mp4");
	// オープンチェック
	if (!cap.isOpened()) return -1;


	// 入力動画のプロパティを取得
	double width, hight,fps;
	width = cap.get(CAP_PROP_FRAME_WIDTH);
	hight = cap.get(CAP_PROP_FRAME_HEIGHT);
	fps = cap.get(CAP_PROP_FPS);


	// 入力動画の再生開始時間を指定
	double start_min = 10; //分
	double start_sec = 34; //秒
	double start_ms = (start_min * 60 + start_sec) * 1000; 
	cap.set(CAP_PROP_POS_MSEC, start_ms); 


	// 出力する動画の入れ物を作る
	VideoWriter writer("C:/hogehoge/resultvideo.wmv", VideoWriter::fourcc('W', 'M', 'V', '1'), fps, Size(width, hight));
	// オープンチェック
	if (!writer.isOpened()) return -1; 


	Image image;
	Mat frame;
	int framecounter = 1; //現在のフレーム数
	for (;;)
	{
		// 1フレーム読み込む
		cap >> frame;

		if (!frame.empty()) {
			/******* ここに抽出したフレームの処理を記述 ******/

			//例えばガンマ補正したり？
			image.correctGamma(frame, 0.5);

			/*************************************************/

			//処理後のフレームをビデオファイルに出力
			writer << frame;

			//出力されたフレームを確認
			namedWindow("current frame", WINDOW_NORMAL); //↓のために必要
			resizeWindow("current frame", width / 4, hight / 4); //確認用のため小さく表示
			imshow("current frame", frame);
			printf("%d frame process complete...\n", framecounter++);
		}
		if (waitKey(30) >= 0) break; //30ミリ秒以内にキーが押されなければループ継続
	}

	return 0;
}