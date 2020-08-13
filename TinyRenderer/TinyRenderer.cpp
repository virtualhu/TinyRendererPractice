// TinyRenderer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "tgaimage.h"
#include "model.h"
#include <algorithm>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor green = TGAColor(0, 255, 0, 255);
const TGAColor blue = TGAColor(0, 0, 255, 255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color);
void triangle(Vec2i* pt3, TGAImage& image, TGAColor color);

int main()
{
    std::cout << "Hello World!\n";
    const float width = 400;
    const float height = 400;
    TGAImage image(width, height, TGAImage::RGB);

    Vec3f light_dir(0, 0, -1);

    Model model("res/african_head.obj");
    for (int idx = 0; idx < model.nfaces(); ++idx)
    {
        std::vector<int> face = model.face(idx);

        Vec3f world_coords[3];
        Vec2i screen_coords[3];
        for (int j = 0; j < 3; j++) {
            Vec3f v = model.vert(face[j]);
            screen_coords[j] = Vec2i((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
            world_coords[j] = v;
        }
        Vec3f u = world_coords[2] - world_coords[0];
        Vec3f v = world_coords[1] - world_coords[0];
        Vec3f n = u ^ v;
        n.normalize();
        float intensity = n * light_dir;
        if (intensity > 0)
        {
            triangle(screen_coords, image, TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
        }
        //for (int vidx = 0; vidx < 3; ++vidx)
        //{
        //    Vec3f v0 = model.vert(verts[vidx]);
        //    Vec3f v1 = model.vert(verts[(vidx + 1) % 3]);

        //    //to screen cor
        //    int x0 = (v0.x + 1.) * width / 2.;
        //    int y0 = (v0.y + 1.) * height / 2.;
        //    int x1 = (v1.x + 1.) * width / 2.;
        //    int y1 = (v1.y + 1.) * height / 2.;
        //    //draw
        //    line(x0, y0, x1, y1, image, white);

        //}
    }
   /* Vec2i pts[3] =
    {
        Vec2i(0, 10),
        Vec2i(200, 10),
        Vec2i(0, 200)
    };
    triangle(pts, image, white);*/
    /*line(0, 0, 200, 0, image, white);
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
    line(399, 0, 200, 20, image, blue);*/
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

bool inTriangle(Vec2i* threePoint, Vec2i p)
{
    Vec2f v2 = Vec2f(p.x - threePoint[0].x, p.y - threePoint[0].y);
    Vec2f v0 = Vec2f(threePoint[1].x - threePoint[0].x, threePoint[1].y - threePoint[0].y);
    Vec2f v1 = Vec2f(threePoint[2].x - threePoint[0].x, threePoint[2].y - threePoint[0].y);

    float d00 = v0 * v0;
    float d01 = v0 * v1;
    float d02 = v0 * v2;
    float d11 = v1 * v1;
    float d12 = v1 * v2;

    float t = (d00 * d11 - d01 * d01);
    float m = (d02 * d11 - d12 * d01) / t;
    float n = (d12 * d00 - d01 * d02) / t;
    return m >= 0 && n >= 0 && m + n <= 1;
}

void triangle(Vec2i* pt3, TGAImage& image, TGAColor color)
{
    Vec2i min(image.get_width() - 1, image.get_height() - 1);
    Vec2i max(0, 0);
    for (int pi = 0; pi < 3; ++pi)
    {
        for (int ci = 0; ci < 2; ++ci)
        {
            min[ci] = std::min(pt3[pi][ci], min[ci]);
            max[ci] = std::max(pt3[pi][ci], max[ci]);
        }
    }

    Vec2i p;
    for (p.x = min.x; p.x <= max.x; ++p.x)
    {
        for (p.y = min.y; p.y <= max.y; ++p.y)
        {
            if (!inTriangle(pt3, p))
            {
                continue;
            }
            image.set(p.x, p.y, color);
        }
    }
}

//void triangle(Vec2i* pt3, TGAImage& image, TGAColor color) {
//    Vec2i t0 = pt3[0];
//    Vec2i t1 = pt3[1];
//    Vec2i t2 = pt3[2];
//    if (t0.y == t1.y && t0.y == t2.y) return; // i dont care about degenerate triangles
//    if (t0.y > t1.y) std::swap(t0, t1);
//    if (t0.y > t2.y) std::swap(t0, t2);
//    if (t1.y > t2.y) std::swap(t1, t2);
//    int total_height = t2.y - t0.y;
//    for (int i = 0; i < total_height; i++) {
//        bool second_half = i > t1.y - t0.y || t1.y == t0.y;
//        int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
//        float alpha = (float)i / total_height;
//        float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height; // be careful: with above conditions no division by zero here
//        Vec2i A = t0 + (t2 - t0) * alpha;
//        Vec2i B = second_half ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
//        if (A.x > B.x) std::swap(A, B);
//        for (int j = A.x; j <= B.x; j++) {
//            image.set(j, t0.y + i, color); // attention, due to int casts t0.y+i != A.y
//        }
//    }
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
