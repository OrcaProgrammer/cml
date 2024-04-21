
#include <cml/vectors.h>
#include <cml/matrices.h>

#include <cmath>

int main() {

	cml::Vector<float, 3> translateDirection{ 2, 10, 2 };
	cml::Vector<float, 4> vector{ 1, 1, 1, 1 };

	cml::Matrix<float, 4, 4> matrix{ cml::create_translation_matrix(translateDirection) };

	std::cout << "Vector multiplied by matrix:\n" << matrix * vector << '\n';

	return 0;
}