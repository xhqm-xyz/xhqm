#include "stlfile.h"

namespace xhqm
{
	namespace info
	{
		bool stlfile::writestl_bin(const std::string& path, const std::vector<Triangle>& triangles)
		{
			FILE* fid = fopen(path.c_str(), "w");
			fprintf(fid, "solid WRAP\n");
			for (xhqm::size i = 0, size = triangles.size(); i != size; ++i) {
				fprintf(fid, "facet normal\t");
				fprintf(fid, "%8.12f\t", triangles[i].normal[0]);
				fprintf(fid, "%8.12f\t", triangles[i].normal[1]);
				fprintf(fid, "%8.12f\n", triangles[i].normal[2]);
				fprintf(fid, "outer loop\n");
				fprintf(fid, "vertex\t");
				fprintf(fid, "%8.12f\t", triangles[i].vertex1[0]);
				fprintf(fid, "%8.12f\t", triangles[i].vertex1[1]);
				fprintf(fid, "%8.12f\n", triangles[i].vertex1[2]);
				fprintf(fid, "vertex\t");
				fprintf(fid, "%8.12f\t", triangles[i].vertex2[0]);
				fprintf(fid, "%8.12f\t", triangles[i].vertex2[1]);
				fprintf(fid, "%8.12f\n", triangles[i].vertex2[2]);
				fprintf(fid, "vertex\t");
				fprintf(fid, "%8.12f\t", triangles[i].vertex3[0]);
				fprintf(fid, "%8.12f\t", triangles[i].vertex3[1]);
				fprintf(fid, "%8.12f\n", triangles[i].vertex3[2]);
				fprintf(fid, "endloop\n");
				fprintf(fid, "endfacet\n");
			}
			fprintf(fid, "endsolid\n");
			fclose(fid);
			return true;
		}
		bool stlfile::writestl_txt(const std::string& path, const std::vector<Triangle>& triangles)
		{
			FILE* fid = fopen(path.c_str(), "w");
			fprintf(fid, "solid WRAP\n");
			for (xhqm::size i = 0, size = triangles.size(); i != size; ++i) {
				fprintf(fid, "facet normal\t");
				fprintf(fid, "%8.12f\t", triangles[i].normal[0]);
				fprintf(fid, "%8.12f\t", triangles[i].normal[1]);
				fprintf(fid, "%8.12f\n", triangles[i].normal[2]);
				fprintf(fid, "outer loop\n");
				fprintf(fid, "vertex\t");
				fprintf(fid, "%8.12f\t", triangles[i].vertex1[0]);
				fprintf(fid, "%8.12f\t", triangles[i].vertex1[1]);
				fprintf(fid, "%8.12f\n", triangles[i].vertex1[2]);
				fprintf(fid, "vertex\t");
				fprintf(fid, "%8.12f\t", triangles[i].vertex2[0]);
				fprintf(fid, "%8.12f\t", triangles[i].vertex2[1]);
				fprintf(fid, "%8.12f\n", triangles[i].vertex2[2]);
				fprintf(fid, "vertex\t");
				fprintf(fid, "%8.12f\t", triangles[i].vertex3[0]);
				fprintf(fid, "%8.12f\t", triangles[i].vertex3[1]);
				fprintf(fid, "%8.12f\n", triangles[i].vertex3[2]);
				fprintf(fid, "endloop\n");
				fprintf(fid, "endfacet\n");
			}
			fprintf(fid, "endsolid\n");
			fclose(fid);
			return true;
		}
		bool stlfile::readstl_bin(const std::string& path, std::vector<Triangle>& triangles)
		{
			std::size_t size = filesize(path);
			std::ifstream file(path, std::ios::binary);

			// 检查文件是否成功打开
			if (!file.is_open()) {
				std::cout << "无法打开文件" << std::endl;
				return false;
			}

			// 读取STL文件头部信息（80字节）
			char header[80];
			file.read(header, 80);

			// 读取三角形面片数量（4字节）
			int numTriangles;
			file.read(reinterpret_cast<char*>(&numTriangles), sizeof(int));

			std::cout << "STL文件头部信息：" << header << std::endl;
			std::cout << "三角形面片数量：" << numTriangles << std::endl;

                if (size != static_cast<xhqm::size>(84 + numTriangles * 50))
			{
				std::cout << "无效的STL文件" << std::endl;
				return false;
			}

			triangles = std::vector<Triangle>(numTriangles);
			// 逐个读取三角形面片数据
			for (int i = 0; i < numTriangles; i++) {
				// 读取法线向量（12字节）
				file.read(reinterpret_cast<char*>(&triangles[i].normal), sizeof(float) * 3);
				// 读取三个顶点坐标（36字节）
				file.read(reinterpret_cast<char*>(&triangles[i].vertex1), sizeof(float) * 9);
				// 忽略属性字节（2字节）
				char attributes[2];
				file.read(attributes, 2);
			}

			// 关闭文件
			file.close();

			return true;
		}
		bool stlfile::readstl_txt(const std::string& path, std::vector<Triangle>& triangles)
		{
			FILE* file;
			char line[256];
			int numTriangles = 0;

			// 打开STL文件
			file = fopen(path.c_str(), "r");
			if (file == NULL) {
				std::cout << "无法打开文件" << std::endl;
				return false;
			}

			// 解析STL文件头部
			fgets(line, sizeof(line), file);
			if (strncmp(line, "solid", 5) != 0) {
				std::cout << "无效的STL文件" << std::endl;
				fclose(file);
				return false;
			}

			// 解析三角形数量
			while (fgets(line, sizeof(line), file) != NULL) {
				if (strncmp(line, "endsolid", 8) == 0)
					break;
				if (std::string str = line; str.find("outer loop") != std::string::npos)
					numTriangles++;
			}

			std::cout << "三角形面片数量：" << numTriangles << std::endl;
			triangles = std::vector<Triangle>(numTriangles);

			// 重置文件指针到起始位置
			fseek(file, 0, SEEK_SET);
			// 跳过STL文件头部
			fgets(line, sizeof(line), file);

			// 解析每个三角形
			for (int i = 0; i < numTriangles; i++) {
				fgets(line, sizeof(line), file); // normal
                sscanf(line, " facet normal %f %f %f", &triangles[i].normal[0], &triangles[i].normal[1], &triangles[i].normal[2]);
				fgets(line, sizeof(line), file); // outer loop

				fgets(line, sizeof(line), file); // vertex 1
                sscanf(line, " vertex %f %f %f", &triangles[i].vertex1[0], &triangles[i].vertex1[1], &triangles[i].vertex1[2]);

				fgets(line, sizeof(line), file); // vertex 2
                sscanf(line, " vertex %f %f %f", &triangles[i].vertex2[0], &triangles[i].vertex2[1], &triangles[i].vertex2[2]);

				fgets(line, sizeof(line), file); // vertex 3
                sscanf(line, " vertex %f %f %f", &triangles[i].vertex3[0], &triangles[i].vertex3[1], &triangles[i].vertex3[2]);

				fgets(line, sizeof(line), file); // endloop
				fgets(line, sizeof(line), file); // endfacet
			}

			// 关闭文件
			fclose(file);
			return true;
		}
		bool stlfile::readstl(const std::string& path, std::vector<Triangle>& triangles)
		{
			if (readstl_bin(path, triangles)) return true;
			if (readstl_txt(path, triangles)) return true;
			return false;
		}

		stlfile::stlfile(std::string igespath)
			: xhqm::info::fileinfo(igespath)
		{
		}
		xhqm::sign stlfile::read()
		{
			close();
			return readstl(filepath(), m_data);
		}
		xhqm::sign stlfile::save()
		{
			close();
			return writestl_txt(filepath(), m_data);
		}
	}
}
