#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <SDL2/SDL.h>

#include "RenderUtil.h"
#include "SimUtil.h"

class FluidRenderer3D {
public:
	FluidRenderer3D(SimUtil::Mat3Di *labels, int gridWidth, int gridHeight, int gridDepth, int borderCount);
	~FluidRenderer3D();
	void draw(std::vector<glm::vec3> &particles, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<int> &indicies);
	
	bool isClosed() { return m_display->isClosed(); };
	bool isPaused() { return m_isPaused; };
	bool gManipulationActive() { return m_gManipulation; };
	bool forwardPressed() { if (m_forwardPressed) { m_forwardPressed = false; return true; } return false; };
	glm::vec3 currentOrientation() { return m_orientation; };

	static void capturePicture(std::string name);

private:
	Display *m_display;
	Camera *m_camera;
	Transform *m_transform;
	Shader *m_colorShader;
	Shader *m_normalShader;
	Mesh *m_meshSolid;
	Line *m_borderSolid;
	Light m_gLight;
	bool m_isPaused;
	bool m_forwardPressed;
	bool m_gManipulation;
	/* 
	 * 1 - Draw Fluid as Particles
	 * 2 - Draw Fluid as Triangle Mesh
	 */
	int m_visualMode;
	glm::vec3 m_orientation;

	void initGeom(SimUtil::Mat3Di *label, int x, int y, int z, int borderCount);
	void initBorderLines(int x, int y, int z, int borderCount, int maxGridSize);
	

	void bottomLineAt(std::vector<glm::vec3> &lines, int yLoc, int crop, int x, int y, int z, int maxGridSize);
	void sideLineAt(std::vector<glm::vec3> &lines, int xLoc, int crop, int bottomCrop, int topCrop, int x, int y, int z, int maxGridSize);
	void frontLineAt(std::vector<glm::vec3> &lines, int zLoc, int crop, int bottomCrop, int topCrop, int x, int y, int z, int maxGridSize);
};

