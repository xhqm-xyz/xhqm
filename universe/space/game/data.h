#ifndef XHQM_GAME_MODELDATA
#define XHQM_GAME_MODELDATA
#include "sys.h"
namespace xhqm
{
	namespace game
	{
		template<class pottype>
		struct box
		{
			xhqm::game::pot<pottype> minpoit;
			xhqm::game::pot<pottype> maxpoit;
		};

		template<class pottype, class coltype = xhqm::byte>
		struct rander {
			//存储顺序 点线面
			//存储大小 m_poitsize * 1 + m_linesize * 2 + m_facesize * 3
			xhqm::natural m_poitsize = 0;
			xhqm::natural m_linesize = 0;
			xhqm::natural m_facesize = 0;
			xhqm::game::box<pottype> m_box;
			xhqm::game::vertex<pottype>* m_vertexs = nullptr;
			xhqm::game::normal<pottype>* m_normals = nullptr;
			xhqm::game::colour<coltype>* m_colours = nullptr;
			inline xhqm::natural poitsize() { return m_poitsize; }
			inline xhqm::natural linesize() { return m_linesize; }
			inline xhqm::natural facesize() { return m_facesize; }
			inline xhqm::natural size() { return m_poitsize * 1 + m_linesize * 2 + m_facesize * 3; }

//            rander() {}
//            rander(const rander&rand)
//            {
//                m_poitsize = rand.m_poitsize;
//                m_linesize = rand.m_linesize;
//                m_facesize = rand.m_facesize;
//                m_vertexs = rand.m_vertexs;
//                m_normals = rand.m_normals;
//                m_colours = rand.m_colours;
//            }

			inline void upbox()
			{
				m_box = xhqm::game::box<pottype>();
				xhqm::natural ptsize = size();
				if (ptsize)
				{
					m_box.minpoit = m_vertexs[0];
					m_box.maxpoit = m_vertexs[0];
				}
				for (xhqm::natural i = 0; i < ptsize; ++i)
				{
					m_box.minpoit[0] = xmin(m_box.minpoit[0], m_vertexs[i][0]);
					m_box.minpoit[1] = xmin(m_box.minpoit[1], m_vertexs[i][1]);
					m_box.minpoit[2] = xmin(m_box.minpoit[2], m_vertexs[i][2]);
					m_box.maxpoit[0] = xmax(m_box.maxpoit[0], m_vertexs[i][0]);
					m_box.maxpoit[1] = xmax(m_box.maxpoit[1], m_vertexs[i][1]);
					m_box.maxpoit[2] = xmax(m_box.maxpoit[2], m_vertexs[i][2]);
				}
			}

			inline void dele()
			{
				if (m_poitsize || m_linesize || m_facesize)
				{
					m_poitsize = 0;
					m_linesize = 0;
					m_facesize = 0;
					delete[] m_vertexs;
					delete[] m_normals;
					delete[] m_colours;
					m_vertexs = nullptr;
					m_normals = nullptr;
					m_colours = nullptr;
				}
			}
			inline void init(xhqm::natural poits, xhqm::natural lines, xhqm::natural faces)
			{
				dele();
				m_poitsize = poits;
				m_linesize = lines;
				m_facesize = faces;
				xhqm::natural creat = size();
				if (creat)
				{
					m_vertexs = new xhqm::game::vertex<pottype>[creat];
					m_normals = new xhqm::game::normal<pottype>[creat];
					m_colours = new xhqm::game::colour<coltype>[creat];
				}
			}
			inline rander& operator= (const rander& rand)
			{
				init(rand.m_poitsize, rand.m_linesize, rand.m_facesize);
				xhqm::natural copy = size();
				if (copy)
				{
                    std::memcpy((void*)m_vertexs, (void*)rand.m_vertexs, sizeof(xhqm::game::vertex<pottype>) * copy);
                    std::memcpy((void*)m_normals, (void*)rand.m_normals, sizeof(xhqm::game::normal<pottype>) * copy);
                    std::memcpy((void*)m_colours, (void*)rand.m_colours, sizeof(xhqm::game::colour<coltype>) * copy);
				}
				return (*this);
			}
			inline friend rander operator+ (const rander& rand1, const rander& rand2)
			{
				rander rand;
				rand.init(rand1.m_poitsize + rand2.m_poitsize, rand1.m_linesize + rand2.m_linesize, rand1.m_facesize + rand2.m_facesize);
				xhqm::game::vertex<pottype>* vertex1poitptr = rand.m_vertexs;
				xhqm::game::vertex<pottype>* vertex2poitptr = vertex1poitptr + rand1.m_poitsize * 1;
				xhqm::game::vertex<pottype>* vertex1lineptr = vertex2poitptr + rand2.m_poitsize * 1;
				xhqm::game::vertex<pottype>* vertex2lineptr = vertex1lineptr + rand1.m_linesize * 2;
				xhqm::game::vertex<pottype>* vertex1faceptr = vertex2lineptr + rand2.m_linesize * 2;
				xhqm::game::vertex<pottype>* vertex2faceptr = vertex1faceptr + rand1.m_facesize * 3;
				xhqm::game::normal<pottype>* normal1poitptr = rand.m_normals;
				xhqm::game::normal<pottype>* normal2poitptr = normal1poitptr + rand1.m_poitsize * 1;
				xhqm::game::normal<pottype>* normal1lineptr = normal2poitptr + rand2.m_poitsize * 1;
				xhqm::game::normal<pottype>* normal2lineptr = normal1lineptr + rand1.m_linesize * 2;
				xhqm::game::normal<pottype>* normal1faceptr = normal2lineptr + rand2.m_linesize * 2;
				xhqm::game::normal<pottype>* normal2faceptr = normal1faceptr + rand1.m_facesize * 3;
				xhqm::game::colour<coltype>* colour1poitptr = rand.m_colours;
				xhqm::game::colour<coltype>* colour2poitptr = colour1poitptr + rand1.m_poitsize * 1;
				xhqm::game::colour<coltype>* colour1lineptr = colour2poitptr + rand2.m_poitsize * 1;
				xhqm::game::colour<coltype>* colour2lineptr = colour1lineptr + rand1.m_linesize * 2;
				xhqm::game::colour<coltype>* colour1faceptr = colour2lineptr + rand2.m_linesize * 2;
				xhqm::game::colour<coltype>* colour2faceptr = colour1faceptr + rand1.m_facesize * 3;
				if (rand.size())
				{
					std::memcpy(vertex1poitptr, rand1.m_vertexs, sizeof(xhqm::game::vertex<pottype>) * rand1.m_poitsize * 1);
					std::memcpy(vertex2poitptr, rand2.m_vertexs, sizeof(xhqm::game::vertex<pottype>) * rand2.m_poitsize * 1);
					std::memcpy(vertex1lineptr, rand1.m_vertexs + rand1.m_poitsize * 1, sizeof(xhqm::game::vertex<pottype>) * rand1.m_linesize * 2);
					std::memcpy(vertex2lineptr, rand2.m_vertexs + rand2.m_poitsize * 1, sizeof(xhqm::game::vertex<pottype>) * rand2.m_linesize * 2);
					std::memcpy(vertex1faceptr, rand1.m_vertexs + rand1.m_poitsize * 1 + rand1.m_linesize * 2, sizeof(xhqm::game::vertex<pottype>) * rand1.m_facesize * 3);
					std::memcpy(vertex2faceptr, rand2.m_vertexs + rand2.m_poitsize * 1 + rand2.m_linesize * 2, sizeof(xhqm::game::vertex<pottype>) * rand2.m_facesize * 3);
					std::memcpy(normal1poitptr, rand1.m_normals, sizeof(xhqm::game::normal<pottype>) * rand1.m_poitsize * 1);
					std::memcpy(normal2poitptr, rand2.m_normals, sizeof(xhqm::game::normal<pottype>) * rand2.m_poitsize * 1);
					std::memcpy(normal1lineptr, rand1.m_normals + rand1.m_poitsize * 1, sizeof(xhqm::game::normal<pottype>) * rand1.m_linesize * 2);
					std::memcpy(normal2lineptr, rand2.m_normals + rand2.m_poitsize * 1, sizeof(xhqm::game::normal<pottype>) * rand2.m_linesize * 2);
					std::memcpy(normal1faceptr, rand1.m_normals + rand1.m_poitsize * 1 + rand1.m_linesize * 2, sizeof(xhqm::game::normal<pottype>) * rand1.m_facesize * 3);
					std::memcpy(normal2faceptr, rand2.m_normals + rand2.m_poitsize * 1 + rand2.m_linesize * 2, sizeof(xhqm::game::normal<pottype>) * rand2.m_facesize * 3);
					std::memcpy(colour1poitptr, rand1.m_colours, sizeof(xhqm::game::colour<coltype>) * rand1.m_poitsize * 1);
					std::memcpy(colour2poitptr, rand2.m_colours, sizeof(xhqm::game::colour<coltype>) * rand2.m_poitsize * 1);
					std::memcpy(colour1lineptr, rand1.m_colours + rand1.m_poitsize * 1, sizeof(xhqm::game::colour<coltype>) * rand1.m_linesize * 2);
					std::memcpy(colour2lineptr, rand2.m_colours + rand2.m_poitsize * 1, sizeof(xhqm::game::colour<coltype>) * rand2.m_linesize * 2);
					std::memcpy(colour1faceptr, rand1.m_colours + rand1.m_poitsize * 1 + rand1.m_linesize * 2, sizeof(xhqm::game::colour<coltype>) * rand1.m_facesize * 3);
					std::memcpy(colour2faceptr, rand2.m_colours + rand2.m_poitsize * 1 + rand2.m_linesize * 2, sizeof(xhqm::game::colour<coltype>) * rand2.m_facesize * 3);
				}
				return rand;
			}
		};

		template<class type>
		class data : public sys<type>
		{
		public:
			bool needup = false;
			std::mutex mutex;
			std::string shaderpath;
			std::string randshader;
			xhqm::game::rander<type> staticdata;
			xhqm::game::rander<type> dynamicdata;
			xhqm::game::rander<type> shaderdata;
			void init()
			{
				dynamicdata = staticdata;
				shaderdata = dynamicdata;
				needup = false;
			}
			void dele()
			{
				staticdata.dele();
				dynamicdata.dele();
				shaderdata.dele();
            }
			void updata() 
			{ 
				if (mutex.try_lock())
				{
                    xhqm::natural copy = dynamicdata.size();
					if (needup && copy)
					{
                        std::memcpy((void*)shaderdata.m_vertexs, (void*)dynamicdata.m_vertexs, sizeof(xhqm::game::vertex<type>) * copy);
                        std::memcpy((void*)shaderdata.m_normals, (void*)dynamicdata.m_normals, sizeof(xhqm::game::normal<type>) * copy);
                        std::memcpy((void*)shaderdata.m_colours, (void*)dynamicdata.m_colours, sizeof(xhqm::game::colour<xhqm::byte>) * copy);
					}
					needup = false;
					mutex.unlock();
				}
			}
			virtual ~data()
			{
				dele();
			}
		};
	}
}
#endif // !UNIVERSE_SPACE_XMODEL
