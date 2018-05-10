#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gl/gl.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include "ObjLoader.h"

CObjLoader::CObjLoader ()
{
	vertexs.reserve (1000);
	texcoords.reserve (1000);
	normals.reserve (1000);
	faces.reserve (1000);
	materials.reserve (1000);
	load = false;
}

bool CObjLoader::Load (char *objfile, char *mtlfile)
{
	_splitpath (objfile, NULL, directory, NULL, NULL);

	if (mtlfile && *mtlfile) {
		loadMaterials (mtlfile);
	}
	if (objfile && *objfile) {
		loadObjects (objfile);
	}
	return true;
}

bool CObjLoader::loadObjects (char *fileName)
{
	FILE *fp = fopen (fileName, "r");
	if (!fp) return false;

	char param[1024];

	while (fscanf (fp, "%s", param) != EOF) {
		if (!strncmp ("#", param, 1)) {
			fgets (param, 1024, fp);
		}
		else if (!strcmp ("mtllib", param)) {
			fscanf (fp, "%s", param);

			char path[MAX_PATH];
			_makepath (path, NULL, directory, param, NULL);

			loadMaterials (path);
		}
		else if (!strcmp ("v", param)) {
			sVertex v;
			fscanf (fp, "%f %f %f", &v.x, &v.y, &v.z);
			vertexs.push_back (v);
		}
		else if (!strcmp ("vt", param)) {
			sTexCoord t;
			fscanf (fp, "%f %f", &t.u, &t.v);
			texcoords.push_back (t);
		}
		else if (!strcmp ("vn", param)){
			sVertex v;
			fscanf (fp, "%f %f %f", &v.x, &v.y, &v.z);
			normals.push_back (v);
		}
		else if (!strcmp ("f", param)){
			sFace f;
			fgets (param, 1024, fp);

			char *p = param;
			for (int i=0; i<5; ++i) {
				while (*p==' ' || *p=='\t') p++;
				if (*p=='\0' || *p=='\r' || *p=='\n') break;

				f.vi[i] = strtoul (p, &p, 10);
				if (*p && *p=='/') p++;
				f.ti[i] = strtoul (p, &p, 10);
				if (*p && *p=='/') p++;
				f.ni[i] = strtoul (p, &p, 10);

				f.n = i + 1;
			}
			faces.push_back (f);
		}
		else if (!strcmp ("usemtl", param)) {
			fscanf (fp, "%s", param);
			int index = findMaterialIndex(param);

			sFace f;
			f.n = 1000 + index;
			faces.push_back (f);
		}
		else if (!strcmp ("s", param)) {
			fscanf (fp, "%s", param); 
		}
	}
	fclose (fp);
	return true;
}

bool CObjLoader::loadMaterials (char *fileName)
{
	FILE *fp = fopen (fileName, "r");
	if (!fp) return false;

	char param[1024];

	while (fscanf (fp, "%s", param) != EOF) {
		if (!strncmp ("#", param, 1)) {
			fgets (param, 1024, fp);
		}
		else if (!strcmp ("newmtl", param)){
			sMaterial m;
			fscanf (fp, "%s", m.name);

			materials.push_back (m);
		}
		else if (!strcmp ("illum", param)) {
			sMaterial &m = *materials.rbegin ();
			fscanf (fp, "%i", &m.illum);
		}
		else if (!strcmp ("map_Kd", param)) {
			sMaterial &m = *materials.rbegin ();
			fscanf (fp, "%s", m.map_Kd);
		}
		else if (!strcmp ("Ni", param)) {
			sMaterial &m = *materials.rbegin ();
			fscanf (fp, "%f", &m.Ni);
		}
		else if (!strcmp ("Kd", param)) {
			sMaterial &m = *materials.rbegin ();
			fscanf (fp, "%f %f %f", &m.Kd[0],&m.Kd[1],&m.Kd[2]);
		}
		else if (!strcmp ("Ka", param)) {
			sMaterial &m = *materials.rbegin ();
			fscanf (fp, "%f %f %f", &m.Ka[0],&m.Ka[1],&m.Ka[2]);
		}
		else if (!strcmp ("Tf", param)) {
			sMaterial &m = *materials.rbegin ();
			fscanf (fp, "%f %f %f", &m.Tf[0],&m.Tf[1],&m.Tf[2]);
		}
	}
	fclose (fp);
	return true;
}

int CObjLoader::findMaterialIndex(char *name)
{
	for (unsigned int i=0; i<materials.size (); ++i) {
		if (!strcmp (name, materials[i].name)) {
			return i;
		}
	}
	return -1;
}

bool CObjLoader::loadTexture (char *fileName, unsigned int *texture)
{
	IplImage *img = cvLoadImage (fileName);
	if (!img) return false;

	glGenTextures (1, texture);
	glBindTexture (GL_TEXTURE_2D, *texture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, 3, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);

	cvReleaseImage (&img);
	return true;
}

void CObjLoader::loadMaterialsTexture ()
{
	for (unsigned int i=0; i<materials.size (); ++i) {
		if (materials[i].map_Kd[0] && !materials[i].texture) {
			char path[MAX_PATH];
			_makepath (path, NULL, directory, materials[i].map_Kd, NULL);

			loadTexture (path, &materials[i].texture);
		}
	}
}

void CObjLoader::Draw (float scale)
{
	if (!load) {
		loadMaterialsTexture ();
		load = true;
	}

	for (unsigned int i=0; i<faces.size (); ++i) {
		if (1000 <= faces[i].n) {
			sMaterial &mat = materials[faces[i].n - 1000];

			glColor3f (mat.Kd[0], mat.Kd[1], mat.Kd[2]);
			if (mat.texture) {
				glEnable( GL_TEXTURE_2D );
				glBindTexture (GL_TEXTURE_2D, mat.texture);
			}
			else {
				glDisable ( GL_TEXTURE_2D );
			}
		}
		else {
			glBegin (GL_POLYGON);
			for (int j=0; j<faces[i].n; ++j) {
				int vi = faces[i].vi[j]-1;
				int ti = faces[i].ti[j]-1;
				int ni = faces[i].ni[j]-1;

				if (0 <= ti && ti < (int)texcoords.size ()) {
					glTexCoord2f (texcoords[ti].u, texcoords[ti].v);
				}
				if (0 <= ni && ni < (int)normals.size ()) {
					glNormal3f (normals[ni].x, normals[ni].y, normals[ni].z);
				}
				if (0 <= vi && vi < (int)vertexs.size ()) {
					glVertex3f (scale*vertexs[vi].x, scale*vertexs[vi].y, scale*vertexs[vi].z);
				}
			}
			glEnd ();
		}
	}
	glDisable ( GL_TEXTURE_2D );
}

