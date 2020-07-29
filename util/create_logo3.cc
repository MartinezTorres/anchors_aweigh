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

std::map<std::string, std::vector<cv::Vec3b>> allColors = { // Note, those are RGB
    { "HW-MSX", {//https://paulwratt.github.io/programmers-palettes/HW-MSX/HW-MSX-palettes.html
        {   0,   0,   0}, // transparent
        {   1,   1,   1}, // black
        {  62, 184,  73}, // medium green
        { 116, 208, 125}, // light green
        {  89,  85, 224}, // dark blue
        { 128, 118, 241}, // light blue
        { 185,  94,  81}, // dark red
        { 101, 219, 239}, // cyan
        { 219, 101,  89}, // medium red
        { 255, 137, 125}, // light red
        { 204, 195,  94}, // dark yellow
        { 222, 208, 135}, // light yellow
        {  58, 162,  65}, // dark green
        { 183, 102, 181}, // magenta
        { 204, 204, 204}, // gray
        { 255, 255, 255}  // white
    } }, 
        
    { "Toshiba Palette", {
        {   0,   0,   0 }, // transparent,
        {   0,   0,   0 }, // black,
        { 102, 204, 102 }, // medium green,
        { 136, 238, 136 }, // light green,
        {  68,  68, 221 }, // dark blue,
        { 119, 119, 255 }, // light blue,
        { 187,  85,  85 }, // dark red,
        { 119, 221, 221 }, // cyan,
        { 221, 102, 102 }, // medium red,
        { 255, 119, 119 }, // light red,
        { 204, 204,  85 }, // dark yellow,
        { 238, 238, 136 }, // light yellow,
        {  85, 170,  85 }, // dark green,
        { 187,  85, 187 }, // magenta,
        { 204, 204, 204 }, // gray,
        { 238, 238, 238 }  // white,
    } },
    
    { "TMS9918A (NTSC)", {
        {   0,   0,   0 }, // transparent,
        {   0,   0,   0 }, // black,
        {  71, 183,  62 }, // medium green,
        { 124, 208, 108 }, // light green,
        {  99, 91,  169 }, // dark blue,
        { 127, 113, 255 }, // light blue,
        { 183, 98,   73 }, // dark red,
        {  92, 199, 239 }, // cyan,
        { 217, 107,  72 }, // medium red,
        { 253, 142, 108 }, // light red,
        { 195, 206,  66 }, // dark yellow,
        { 211, 219, 117 }, // light yellow,
        {  61, 160,  47 }, // dark green,
        { 183,  99, 199 }, // magenta,
        { 205, 205, 205 }, // gray,
        { 255, 255, 255 }  // white,
    } },
    
    { "TMS9929A (PAL)", {
        {   0,   0,   0 }, // transparent,
        {   0,   0,   0 }, // black,
        {  81, 202,  92 }, // medium green,
        { 133, 223, 141 }, // light green,
        { 108, 103, 240 }, // dark blue,
        { 146, 137, 255 }, // light blue,
        { 213, 100, 113 }, // dark red,
        { 102, 219, 239 }, // cyan,
        { 231, 118, 131 }, // medium red,
        { 255, 152, 164 }, // light red,
        { 215, 207,  97 }, // dark yellow,
        { 230, 222, 112 }, // light yellow,
        {  74, 177,  81 }, // dark green,
        { 200, 121, 200 }, // magenta,
        { 205, 205, 205 }, // gray,
        { 255, 255, 255 }  // white,
    } },
    
    { "TMS9929A (PAL, alternate GAMMA)", {
        {   0,   0,   0 }, // transparent,
        {   0,   0,   0 }, // black,
        {  72, 178,  81 }, // medium green,
        { 117, 196, 125 }, // light green,
        {  95,  91, 212 }, // dark blue,
        { 129, 121, 224 }, // light blue,
        { 187,  89,  99 }, // dark red,
        {  90, 193, 210 }, // cyan,
        { 203, 104, 115 }, // medium red,
        { 224, 134, 145 }, // light red,
        { 189, 182,  86 }, // dark yellow,
        { 203, 196,  99 }, // light yellow,
        {  66, 156,  72 }, // dark green,
        { 176, 108, 175 }, // magenta,
        { 180, 180, 180 }, // gray,
        { 255, 255, 255 }  // white,
    } }
};

auto colors = allColors["TMS9929A (PAL)"];

double colorDistance(cv::Vec3b c, int p) {
 
    return std::pow(double(c[0])-colors[p][2],2.) + 
           std::pow(double(c[1])-colors[p][1],2.) + 
           std::pow(double(c[2])-colors[p][0],2.);
}


int main(int argc, char **argv) {
        
    cv::Mat3b img = cv::imread(argv[1]);

    std::vector<uint8_t> patterns;
    std::vector<uint8_t> palettes;

    for (int s=0; s<3; s++) {
        for (int j=0; j<img.cols; j+=8) {
            for (int i=s*(img.rows/3); i<(s+1)*(img.rows/3); i++) {
                double bestError = 1e+10;
                int bestPalette = 0;
                int bestPattern = 0;
                for (int p0 = 1; p0<15; p0++) {
                    for (int p1 = p0+1; p1<16; p1++) {
                        double err = 0;
                        int pattern = 0;
                        for (int k=0; k<8; k++) {
                            double d0 = colorDistance(img(i,j+k),p0);
                            double d1 = colorDistance(img(i,j+k),p1);
                            if (d0<d1) {
                                err += d0;
                                pattern = 2*pattern+0;
                            } else {
                                err += d1;
                                pattern = 2*pattern+1;
                            }
                        }
                        if (err<bestError) {
                            bestError = err;
                            bestPattern = pattern;
                            bestPalette = p1*16+p0;
                        }
                    }
                }
                patterns.push_back(bestPattern);
                palettes.push_back(bestPalette);
            }
        }
    }

    std::cout << "static const uint8_t pattern[] = {" << std::endl;
    for (uint i=0; i<patterns.size(); i++) {
        printf("0x%02X, ",patterns[i]);
        if (i%32 == 31) printf("\n");
    }    
    printf("};\n");

    std::cout << "static const uint8_t color[] = {" << std::endl;
    for (uint i=0; i<palettes.size(); i++) {
        printf("0x%02X, ",palettes[i]);
        if (i%32 == 31) printf("\n");
    }    
    printf("};\n");

}
