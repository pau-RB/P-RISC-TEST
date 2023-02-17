#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

int main(int argc, char *argv[]) {

	int num_vec = (1 < argc) ? std::stoi(argv[1]) : 1;
	int len_vec = (2 < argc) ? std::stoi(argv[2]) : 10;

	srand((unsigned) time(NULL));

	for (int i = 0; i < num_vec; ++i) {

		char path[15];
		snprintf (path, 15, "vec_%04d_%03d.h", len_vec/1000, i+1);

		std::ofstream vec_file;

		vec_file.open (path);
		vec_file << "#define VSZ " << len_vec << std::endl;
		vec_file << "int VEC[" << len_vec << "] = {";

		for(int j = 0; j < len_vec-1; ++j)
			vec_file << rand() << ",";
		vec_file << rand();

		vec_file << "};";
		vec_file.close();

	}
	
}