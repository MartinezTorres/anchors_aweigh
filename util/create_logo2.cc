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

int main(int argc, char **argv) {
    
    cv::Mat1b img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    cv::Mat3b img2(img.rows, img.cols,cv::Vec3b(255,255,255));

	for (int i=0; i<img.rows; i++) {
		for (int j=0; j<img.cols; j++) {
            if (img(i,j)<64) {
                img(i,j)=0;
            } else if (img(i,j)<192) {
                img(i,j)=1;
            } else {
                img(i,j)=2;
            }
        }
    }

    

    std::vector<int> palettes;
	for (int i=0; i<img.rows; i++) {
		for (int j=0; j<img.cols; j+=8) {
            
            int bestPalette = 0;
            int err, bestErr = 1000;
            
            err = 0;
            for (int k=0; k<8; k++)
                if (img(i,j+k)==2) err+=3;
            bestErr = err;

            err = 0;
            for (int k=0; k<8; k++)
                if (img(i,j+k)==1) err+=1;
            if (err<bestErr) {
                bestErr = err;
                bestPalette  = 1;
            }

            err = 0;
            for (int k=0; k<8; k++)
                if (img(i,j+k)==0) err+=4;
            if (err<bestErr) {
                bestPalette = 2;
            }
            
            if (bestPalette==0) {
                for (int k=0; k<8; k++) {
                    if (img(i,j+k)==0)
                        img2(i,j+k)=cv::Vec3b(0,0,0);
                    if (img(i,j+k)==1)
                        img2(i,j+k)=cv::Vec3b(224,89,85);
                    if (img(i,j+k)==2)
                        img2(i,j+k)=cv::Vec3b(224,89,85);
                }
            }

            if (bestPalette==1) {
                for (int k=0; k<8; k++) {
                    if (img(i,j+k)==0)
                        img2(i,j+k)=cv::Vec3b(0,0,0);
                    if (img(i,j+k)==1)
                        img2(i,j+k)=cv::Vec3b(208,208,208);
                    if (img(i,j+k)==2)
                        img2(i,j+k)=cv::Vec3b(208,208,208);
                }
            }

            if (bestPalette==2) {
                for (int k=0; k<8; k++) {
                    if (img(i,j+k)==0)
                        img2(i,j+k)=cv::Vec3b(224,89,85);
                    if (img(i,j+k)==1)
                        img2(i,j+k)=cv::Vec3b(224,89,85);
                    if (img(i,j+k)==2)
                        img2(i,j+k)=cv::Vec3b(208,208,208);
                }
            }
		}
	}
    cv::imwrite("img.png", img2);
    cv::resize(img2, img2, cv::Size(), 4, 4, cv::INTER_NEAREST);
    cv::imshow("img2", img2);
    cv::waitKey(0);

}
