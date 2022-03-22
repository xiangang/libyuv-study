#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "3rd/libyuv/include/libyuv.h"

void clip(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height, int cropX, int cropY, int cropWidth, int cropHeight) {
    ConvertToI420(
            srcYuvData,
            width*height*3/2,
            dstYuvData,
            cropWidth,
            dstYuvData+cropWidth*cropHeight,
            (cropWidth+1)/2,
            dstYuvData+cropWidth*cropHeight+((cropWidth+1)/2)*((cropHeight+1)/2),
            (cropWidth+1)/2,
            cropX,
            cropY,
            width,
            height,
            cropWidth,
            cropHeight,
            kRotate0,
            FOURCC_YU12);
}
//yuv剪裁demo
void clip_test(){
    uint32_t width = 700, height = 700;
    uint32_t clipWidth = 200, clipHeight = 200;
    uint8_t YUV[width*height*3/2];
    uint8_t YUV_CLIP[clipWidth*clipHeight*3/2];

    FILE *yuv420pFile = fopen("./resources/rainbow-yuv420p.yuv", "rb");
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    clip(YUV, YUV_CLIP, width, height, 0, 0, clipWidth, clipHeight);

    FILE *yuvClipFile = fopen("./resources/rainbow-yuv420p-clip-0-0.yuv", "wb");
    fwrite(YUV_CLIP, sizeof(YUV_CLIP), 1, yuvClipFile);

    fclose(yuvClipFile);
    fclose(yuv420pFile);
}

void scale(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height, int dstWidth, int dstHeight) {
    I420Scale(
            srcYuvData,
            width,
            srcYuvData+width*height,
            (width+1)/2,
            srcYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            width,
            height,
            dstYuvData,
            dstWidth,
            dstYuvData+dstWidth*dstWidth,
            (dstWidth+1)/2,
            dstYuvData+dstWidth*dstHeight+((dstWidth+1)/2)*((dstHeight+1)/2),
            (dstWidth+1)/2,
            dstWidth,
            dstHeight,
            kFilterNone
            );
}

//yuv缩放demo
void fun_scale_test(){
    uint32_t width = 700, height = 700;
    uint32_t dstWidth = 100, dstHeight = 100;
    uint8_t YUV[width*height*3/2];
    uint8_t YUV_SCALE[dstWidth*dstHeight*3/2];

    FILE *yuv420pFile = fopen("./resources/rainbow-yuv420p.yuv", "rb");
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    scale(YUV, YUV_SCALE, width, height, dstWidth, dstHeight);

    FILE *yuvScaleFile = fopen("./resources/rainbow-yuv420p-scale-6.yuv", "wb");
    fwrite(YUV_SCALE, sizeof(YUV_SCALE), 1, yuvScaleFile);

    fclose(yuvScaleFile);
    fclose(yuv420pFile);
}

void rotation(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height) {
    I420Rotate(
            srcYuvData,
            width,
            srcYuvData+width*height,
            (width+1)/2,
            srcYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            dstYuvData,
            width,
            dstYuvData+width*height,
            (width+1)/2,
            dstYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            width,
            height,
            kRotate90
            );
}

//yuv旋转demo
void rotation_test(){
    uint32_t width = 700, height = 700;
    uint8_t YUV[width*height*3/2];
    uint8_t YUV_ROTATION[width*height*3/2];

    FILE *yuv420pFile = fopen("./resources/rainbow-yuv420p.yuv", "rb");
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    rotation(YUV, YUV_ROTATION, width, height);

    FILE *yuvRotationFile = fopen("./resources/rainbow-yuv420p-rotation-90.yuv", "wb");
    fwrite(YUV_ROTATION, sizeof(YUV_ROTATION), 1, yuvRotationFile);

    fclose(yuvRotationFile);
    fclose(yuv420pFile);
}


void mirror(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height) {
    I420Mirror(
            srcYuvData,
            width,
            srcYuvData+width*height,
            (width+1)/2,
            srcYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            dstYuvData,
            width,
            dstYuvData+width*height,
            (width+1)/2,
            dstYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            width,
            height
            );
}
//yuv镜像demo
void mirror_test(){
    uint32_t width = 700, height = 700;
    uint8_t YUV[width*height*3/2];
    uint8_t YUV_MIRROR[width*height*3/2];

    FILE *yuv420pFile = fopen("./resources/rainbow-yuv420p-rotation-90.yuv", "rb");
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    mirror(YUV, YUV_MIRROR, width, height);

    FILE *yuvMirrorFile = fopen("./resources/rainbow-yuv420p-rotation-90-mirror.yuv", "wb");
    fwrite(YUV_MIRROR, sizeof(YUV_MIRROR), 1, yuvMirrorFile);

    fclose(yuvMirrorFile);
    fclose(yuv420pFile);
}


void blend(uint8_t *srcYuvData, uint8_t *dstYuvData, int width, int height) {
    uint8_t YUV_ROTATION[width*height*3/2];
    I420Rotate(
            srcYuvData,
            width,
            srcYuvData+width*height,
            (width+1)/2,
            srcYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            YUV_ROTATION,
            width,
            YUV_ROTATION+width*height,
            (width+1)/2,
            YUV_ROTATION+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            width,
            height,
            kRotate90
    );

    // 透明度
    uint8_t alpha[width*height];
    memset(alpha, 0X88, width*height);

    I420Blend(
            srcYuvData,
            width,
            srcYuvData+width*height,
            (width+1)/2,
            srcYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            YUV_ROTATION,
            width,
            YUV_ROTATION+width*height,
            (width+1)/2,
            YUV_ROTATION+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            alpha,
            width,
            dstYuvData,
            width,
            dstYuvData+width*height,
            (width+1)/2,
            dstYuvData+width*height+((width+1)/2)*((height+1)/2),
            (width+1)/2,
            width,
            height
            );
}

//yuv混合测试
void blend_test(){
    uint32_t width = 700, height = 700;
    uint8_t YUV[width*height*3/2];
    uint8_t YUV_BLEND[width*height*3/2];

    FILE *yuv420pFile = fopen("./resources/rainbow-yuv420p.yuv", "rb");
    fread(YUV, sizeof(YUV), 1, yuv420pFile);

    blend(YUV, YUV_BLEND, width, height);

    FILE *yuvBlendFile = fopen("./resources/rainbow-yuv420p-blend.yuv", "wb");
    fwrite(YUV_BLEND, sizeof(YUV_BLEND), 1, yuvBlendFile);

    fclose(yuvBlendFile);

}
/**
 * @brief 《音视频学习基础系列》使用c语言集成第三方库libyuv对yuv数据进行剪裁，缩放，旋转，镜像，混合等操作，
 * 基于CMake工具进行编译构建，支持Linux平台下使用VisualStudio Code进行开发。
 * 
 * @return int 
 */
int main() {
    //由于以下测试方法读取了同一个文件，所以建议不要同时调用
    //clip_test();
    //fun_scale_test();
    //rotation_test();
    //mirror_test();
    blend_test();
    return 0;
}
