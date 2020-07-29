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

int main(int argc, char **argv) {
    
    cv::Mat3b img = cv::imread(argv[1]);
    
    std::vector<int> startPositions;
    std::vector<std::pair<int,int>> pts;
    std::vector<int> len;
    
    for (int i=0; i<img.rows-16; i+=17) {
        for (int j=0; j<img.cols-16; j+=17) {

            startPositions.push_back(pts.size());
            int leftmost = -1;
            for (int jj=0; jj<16; jj++) {
                for (int ii=0; ii<16; ii++) {
                    if (img(i+ii+1,j+jj+1)[1]<127) {
                        leftmost = std::max(leftmost,jj);
                        pts.emplace_back(jj,ii);
                    }
                }
            }
            std::random_shuffle(pts.begin()+startPositions.back(), pts.end());
            len.push_back(leftmost+1);
        }
    }

    std::cout << "static const uint16_t font_pts[] = {" << std::endl;
    for (uint i=0; i<pts.size(); i++) {
        printf("0x%04X, ",pts[i].first*256+pts[i].second);
        if (i%16 == 15) printf("\n");
    }    
    printf("};\n");

    std::cout << "static const uint16_t font_pos[] = {" << std::endl;
    for (uint i=0; i<startPositions.size(); i++) {
        printf("0x%04X, ", startPositions[i]);
        if (i%16 == 15) printf("\n");
    }    
    printf("};\n");

    std::cout << "static const uint8_t font_len[] = {" << std::endl;
    for (uint i=0; i<len.size(); i++) {
        printf("0x%02X, ", (len[i]<1?2:len[i]+1));
        if (i%16 == 15) printf("\n");
    }    
    printf("};\n");

}
