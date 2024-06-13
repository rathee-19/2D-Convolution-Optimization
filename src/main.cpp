#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <fstream>
#include <memory>
#include <cstdint>
#include <filesystem>
#include <string>

namespace solution
{
	std::string compute(const std::string &m1_path, const std::string &m2_path, int n, int k, int m)
	{
		std::string sol_path = std::filesystem::temp_directory_path() / "student_sol.dat";
		std::ofstream sol_fs(sol_path, std::ios::binary);
		std::ifstream m1_fs(m1_path, std::ios::binary), m2_fs(m2_path, std::ios::binary);
		const auto m1 = std::make_unique<float[]>(n * k), m2 = std::make_unique<float[]>(k * m);
		m1_fs.read(reinterpret_cast<char *>(m1.get()), sizeof(float) * n * k);
		m2_fs.read(reinterpret_cast<char *>(m2.get()), sizeof(float) * k * m);
		m1_fs.close();
		m2_fs.close();
		auto result = std::make_unique<float[]>(n * m);
		// for (int i = 0; i < n; i++){
		//     for (int j = 0; j < m; j++) {
		//         result[i*m + j] = 0;
		//         for (int l = 0; l < k; ++l){
		//         	result[i*m + j] += m1[i*k + l] * m2[l*m + j];
		// 		}
		//     }
		// }
		int total_cols = n;
		int total_rows = m;
		for (int for_all_cols_of_mat_A; for_all_cols_of_mat_A < n; for_all_cols_of_mat_A++)
		{
			// Here Result Should be Zero and in Subsequent steps, it should be adding up
			for (int each_col_row_down_mat_A = 0; each_col_row_down_mat_A < m; each_col_row_down_mat_A++)
			{
				float multfactor = m1[each_col_row_down_mat_A * m + for_all_cols_of_mat_A];
				// Now we need to get rows and multiply the above variable to it
				for(int each_row_of_mat_B = 0; each_row_of_mat_B < m; each_row_of_mat_B++)
				{
					float prod = m2[for_all_cols_of_mat_A * m + each_row_of_mat_B];
					result[each_col_row_down_mat_A * m + each_row_of_mat_B] += multfactor * prod;
				}
			}
		}
		sol_fs.write(reinterpret_cast<const char *>(result.get()), sizeof(float) * n * m);
		sol_fs.close();
		return sol_path;
	}
}
__m256 r = _mm256_set1_ps(mat1[i * k + p]);
// Load 8 elements from mat2 into AVX register
                            __m256 a = _mm256_loadu_ps(&mat2[p * m + j]);
                            // Load 8 elements from result into AVX register
                            __m256 b = _mm256_loadu_ps(&result[i * m + j]);
                            // Multiply and accumulate
                            __m256 c = _mm256_fmadd_ps(r, a, b);
                            // Store result back to memory
                            _mm256_storeu_ps(&result[i * m + j], c);