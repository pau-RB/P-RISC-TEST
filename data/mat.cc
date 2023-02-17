#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

int main(int argc, char *argv[]) {

	std::string dir = (1 < argc) ? argv[1] : "data";
	int num_mat = (2 < argc) ? std::stoi(argv[2]) : 1;
	int siz_mat = (3 < argc) ? std::stoi(argv[3]) : 32;

	srand((unsigned) time(NULL));

	for (int i = 0; i < num_mat; ++i) {

		char path[15];
		snprintf (path, 15, "mat_%04d_%03d.h", siz_mat, i+1);

		std::ofstream mat_file;

		mat_file.open(dir+"/"+path);

		mat_file << "#define MSZ " << siz_mat << std::endl;

		mat_file << "int A[" << siz_mat << "][" << siz_mat << "] = {";
		for(int j = 0; j < siz_mat-1; ++j) {
			mat_file << "{";
			for (int k = 0; k < siz_mat-1; ++k)
				mat_file << rand() << ",";
			mat_file << rand() << "},\n";
		}
		mat_file << "{";
		for (int k = 0; k < siz_mat-1; ++k)
			mat_file << rand() << ",";
		mat_file << rand() << "}";
		mat_file << "};\n";

		mat_file << "int B[" << siz_mat << "][" << siz_mat << "] = {";
		for(int j = 0; j < siz_mat-1; ++j) {
			mat_file << "{";
			for (int k = 0; k < siz_mat-1; ++k)
				mat_file << rand() << ",";
			mat_file << rand() << "},\n";
		}
		mat_file << "{";
		for (int k = 0; k < siz_mat-1; ++k)
			mat_file << rand() << ",";
		mat_file << rand() << "}";
		mat_file << "};";

		mat_file.close();

	}
	
}