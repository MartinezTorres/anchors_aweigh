////////////////////////////////////////////////////////////////////////
// Build MSX1 palette
//
// Manuel Martinez (salutte@gmail.com)
//
// FLAGS: -std=gnu++14 -g `pkg-config opencv4 --cflags --libs` -Ofast -lpthread -fopenmp -lgomp -Wno-format-nonliteral

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <map>
#include <thread>
#include <chrono>
#include <functional>

typedef std::array<uint8_t, 8> Tile;


std::pair<cv::Mat1f,cv::Mat1f> dither(cv::Mat1f src, cv::Mat1f cumulativeError, cv::Mat1f mask = cv::Mat1f()) {

	cv::Mat1f dst = src.clone();
	
	src = src.clone();
	src += cumulativeError;
	
	cumulativeError *= 0.;
	dst *= 0.;
	
	if (mask.rows==0) mask = src + 1.0;
	for (int i=0; i<src.rows; i++) {
		for (int j=0; j<src.cols; j++) {	
			if (mask(i,j)<0.5) continue;
			dst(i,j) = src(i,j)>0.5;
			float err = src(i,j)-dst(i,j);

			if (                 j<src.cols-1) src(i  ,j+1) += err*7/32;
			if (i<src.rows-1 and j>0         ) src(i+1,j-1) += err*3/32;
			if (i<src.rows-1                 ) src(i+1,j  ) += err*5/32;
			if (i<src.rows-1 and j<src.cols-1) src(i+1,j+1) += err*1/32;
			cumulativeError(i,j) += err*9/32;
		}
	}
	
	return {dst, cumulativeError};
}

int main(int argc, char **argv) {
    
    cv::Mat1f imgOriginal = cv::Mat1f(cv::imread(argv[1], cv::IMREAD_GRAYSCALE))*(1/255.);
    cv::Mat3b maskOriginal = cv::imread(argv[2]);
    
    cv::Mat1f error = imgOriginal * 0.;
    cv::Mat1f mask = imgOriginal * 0.;
	for (int i=0; i<mask.rows; i++) {
		for (int j=0; j<mask.cols; j++) {
			mask(i,j) = not (maskOriginal(i,j)[0] < (maskOriginal(i,j)[2]-10));
		}
	}

	for (int i=0; i<imgOriginal.rows; i++) {
		for (int j=0; j<imgOriginal.cols; j++) {

			imgOriginal(i,j) = (imgOriginal(i,j)-0.1) * 1.9;
			if (imgOriginal(i,j)<0) imgOriginal(i,j)=0;

			if (imgOriginal(i,j)<0.04045) {
				imgOriginal(i,j) = imgOriginal(i,j)/12.92;
			} else {
				imgOriginal(i,j) = std::pow((imgOriginal(i,j)+0.055/1.055),2.4);
			}			

			if (imgOriginal(i,j)<0) imgOriginal(i,j)=0;
			if (imgOriginal(i,j)>1) imgOriginal(i,j)=1;
		}
	}

    
    std::vector<cv::Mat1f> images;
    for (int i=0; i<64; i++) {
		
		{
			std::pair<cv::Mat1f,cv::Mat1f> di = dither(imgOriginal, error,mask);
			error = di.second;
			images.push_back(di.first);
		}
		
		cv::rotate(imgOriginal, imgOriginal, cv::ROTATE_180);
		cv::rotate(mask, mask, cv::ROTATE_180);
		cv::rotate(error, error, cv::ROTATE_180);

		{
			std::pair<cv::Mat1f,cv::Mat1f> di = dither(imgOriginal, error,mask);
			error = di.second;
			cv::rotate(di.first, di.first, cv::ROTATE_180);
			images.push_back(di.first);
		}

		cv::rotate(imgOriginal, imgOriginal, cv::ROTATE_180);
		cv::rotate(mask, mask, cv::ROTATE_180);
		cv::rotate(error, error, cv::ROTATE_180);
	}
    
    if(0) while (true) {
		for (auto img : images) {
			cv::resize(img.clone(),img,cv::Size(),4,4,cv::INTER_NEAREST);
			cv::imshow("dithered", img);
			cv::waitKey(16);
		}
	}

	for (auto img : images) {
		
	}
    
    
    
/*    for (int w=0; w<3; w++) {

		std::map<Tile,int> MapA, MapB;
		cv::Mat3b img = imgOriginal.rowRange(w*64,(w+1)*64);
		for (int i=0; i<img.rows; i+=8) {
			for (int j=0; j<img.cols; j+=8) {
				Tile A, B;
				for (int ii=0; ii<8; ii+=2) {
					int ta0 = 0;
					int ta1 = 0;
					int tb0 = 0;
					int tb1 = 0;
					for (int jj=0; jj<8; jj++) {
						int c0 = img(i+ii+0,j+jj)[0];
						int c1 = img(i+ii+1,j+jj)[0];

						ta0 = (ta0<<1) + ((c0/64)>>1);
						ta1 = (ta1<<1) + ((c1/64)&1);
						tb0 = (tb0<<1) + ((c0/64)&1);
						tb1 = (tb1<<1) + ((c1/64)>>1);					
					}
					A[ii+0]=ta0;
					A[ii+1]=ta1;
					B[ii+0]=tb0;
					B[ii+1]=tb1;
				}
				MapA[A]++;
				MapB[B]++;			
			}
		}
		
		std::cout << "MapA: " << MapA.size() << std::endl;
		std::cout << "MapB: " << MapA.size() << std::endl;
	}*/
}
