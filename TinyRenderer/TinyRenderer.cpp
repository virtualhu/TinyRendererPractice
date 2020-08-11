// TinyRenderer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);

int main()
{
    std::cout << "Hello World!\n";
    const float width = 400;
    const float height = 400;
    TGAImage image(width, height, TGAImage::RGB);
    /*image.set(52, 41, red);
    Model model("res/african_head.obj");
    for (int idx = 0; idx < model.nfaces(); ++idx)
    {
        std::vector<int> verts = model.face(idx);
        for (int vidx = 0; vidx < 3; ++vidx)
        {
            Vec3f v0 = model.vert(verts[vidx]);
            Vec3f v1 = model.vert(verts[(vidx + 1) % 3]);

            int x0 = (v0.x + 1.) * width / 2.;
            int y0 = (v0.y + 1.) * height / 2.;
            int x1 = (v1.x + 1.) * width / 2.;
            int y1 = (v1.y + 1.) * height / 2.;
            line(x0, y0, x1, y1, image, white);

        }
    }*/
    line(0, 0, 200, 0, image, white);
    line(0, 0, 200, 20, image, white);
    line(0, 0, 200, 200, image, white);
    line(0, 0, 20, 200, image, white);
    line(0, 0, 0, 200, image, white);

    line(399, 399, 200, 399, image, red);
    line(399, 399, 200, 380, image, red);
    line(399, 399, 200, 200, image, red);
    line(399, 399, 380, 200, image, red);
    line(399, 399, 399, 200, image, red);

    line(0, 399, 200, 399, image, green);
    line(0, 399, 200, 380, image, green);
    line(0, 399, 200, 200, image, green);
    line(0, 399, 0, 200, image, green);
    line(0, 399, 20, 200, image, green);

    line(399, 0, 200, 0, image, blue);
    line(399, 0, 399, 200, image, blue);
    line(399, 0, 200, 200, image, blue);
    line(399, 0, 380, 200, image, blue);
    line(399, 0, 200, 20, image, blue);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}

void setImage(int x, int y, TGAImage& image, TGAColor color)
{
    image.set(x, y, color);
}

void setImageFlipXY(int x, int y, TGAImage& image, TGAColor color)
{
    image.set(y, x, color);
}

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
    void (*setFunc)(int, int, TGAImage&, TGAColor) = setImage;
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {//象限转换，以保证x+1递增
        std::swap(x0, y0);
        std::swap(x1, y1);
        setFunc = setImageFlipXY;
    }
    if (x0 > x1) {//方向转换
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int inc = y1 > y0 ? 1 : -1;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        setFunc(x, y, image, color);
        error2 += derror2;
        if (error2 > dx) {
            y += inc;
            error2 -= dx * 2;
        }
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
