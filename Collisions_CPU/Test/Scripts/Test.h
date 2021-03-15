#pragma once
#include "../../Intersector/Intersector3d.h"
#include "../../TreeAdapter/TreeAdapter.h"
#include "Utility.h"

// Calculated relatively from project root
static const std::string DATAPATH = "Test\\Datasets\\";
static const std::string RESPATH = "Test\\Results\\";


/*
	Load files from Datasets folder
	Write results to Results folder
*/
void intersect3d_test(const std::string& plane1, const std::string& plane2,
				const std::string& outfilename)
{
	const auto apts = read_csv<ntpoint3d>(DATAPATH + plane1);
	const auto bpts = read_csv<ntpoint3d>(DATAPATH + plane2);

	TreeAdapter a(apts);
	TreeAdapter b(bpts);

	Intersector3d inter(a, b);
	const auto colls = inter.intesect(0.0001);

	const auto mean = [](double a, double b) {
		return (b + a) / 2.0;
	};

	std::ofstream file(RESPATH + outfilename);
	file << "x,y,z\n";

	for (const auto col : colls)
	{
		const auto& cube = col.cube;
		const point3d p(
			mean(cube.x_down, cube.x_up),
			mean(cube.y_down, cube.y_up),
			mean(cube.z_down, cube.z_up));
		file << p << '\n';
	}
}

