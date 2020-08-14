#ifndef __MODEL_H__
#define __MODEL_H__

#include <vector>
#include "geometry.h"

struct Vertex
{
	int v;
	int uv;
};

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<Vec3f> uvs_;
	std::vector<std::vector<Vertex> > faces_;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	Vec3f uv(int i);
	std::vector<Vertex> face(int idx);
};

#endif //__MODEL_H__
