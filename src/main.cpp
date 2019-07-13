#include <string>
#include <chrono>

#include "FluidSolver3d.h"
#include "FluidRenderer3d.h"
#include "SimUtil.h"

const float GRID_CELL_WIDTH = 0.005f;
const float TIME_STEP = 0.01f;

const std::string geometry_in = "res/geo_small.txt";

int main(int argc, char** argv) {
  int w, h, d, b;

  FluidSolver3D solver(geometry_in, GRID_CELL_WIDTH, TIME_STEP);
  solver.init(geometry_in);

  solver.getDim(w, h, d, b);

  FluidRenderer3D render(solver.getGeometry(), w, h, d, b );

  solver.step();

  SimUtil::Mesh3D data = solver.meshData();
  auto start = std::chrono::system_clock::now();
  bool newFrame = true;
  while (!render.isClosed()) {
	auto particles = solver.particleData();
	render.draw(particles, data.vertices, data.normals, data.indices);
	if (!render.isPaused() && newFrame) {
	  start = std::chrono::system_clock::now();
	  if (render.gManipulationActive()) {
		solver.updateOrientation(render.currentOrientation());
	  }
	  solver.step();
	  data = solver.meshData();
	  newFrame = false;
	}
	if (render.isPaused() && render.forwardPressed()) {
	  if (render.gManipulationActive()) {
		solver.updateOrientation(render.currentOrientation());
	  }
	  solver.step();
	  data = solver.meshData();
	}
	if (!render.isPaused() && !newFrame) {
	  auto now = std::chrono::system_clock::now();
	  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
	  if (elapsed.count() > 1000 * TIME_STEP) {
		newFrame = true;
	  }
	}
  }

  return 0;
}
