#include <vector>

using namespace std;

struct sVertex
{
	float x, y, z;
};

struct sTexCoord
{
	float u, v;
};

struct sMaterial
{	
	char name[32];
	int illum;
	char map_Kd[32];
	float Ni;
	float Kd[3];
	float Ka[3];
	float Tf[3];
	unsigned int texture;

	sMaterial() {
		memset (this, 0, sizeof(sMaterial));
	}
};

struct sFace
{
	int n;

	int vi[5];	//vertices
	int ti[5];	//text coords
	int ni[5];	//normals
};

class CObjLoader
{
public:
	CObjLoader ();

	void loadMaterialsTexture ();
	bool Load (char *objfile, char *mtlfile = NULL);
	void Draw (float scale = 1.f);

private:
	vector<sVertex> vertexs;
	vector<sTexCoord> texcoords;
	vector<sVertex> normals;
	vector<sFace> faces;
	vector<sMaterial> materials;

	bool loadObjects (char *fileName);
	bool loadMaterials (char *fileName);

	int findMaterialIndex(char *name);
	bool loadTexture (char *fileName, unsigned int *texture);

private:	
	char directory[_MAX_DIR];
	bool load;
};
