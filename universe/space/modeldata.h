#ifndef XHQM_SPACE_MODELDATA
#define XHQM_SPACE_MODELDATA
#include "system.h"
namespace xhqm
{
	namespace space
	{
		template<class datatype>
		class modeldata : public xhqm::space::system
		{
		public:
			bool needup = false;
			std::mutex mutex;

			datatype staticdata;
			datatype dynamicdata;
			datatype shaderdata;
			
			void init()
			{
				dynamicdata = staticdata;
				shaderdata = dynamicdata;
				needup = false;
			}
			void dele()
			{
				//staticdata.dele();
				//dynamicdata.dele();
				//shaderdata.dele();
			}
			void updata()
			{
				if (mutex.try_lock())
				{
					xhqm::natural copy = dynamicdata.size();
					if (needup && copy)
					{
						shaderdata = dynamicdata;
					}
					needup = false;
					mutex.unlock();
				}
			}
			~modeldata()
			{
				dele();
			}
			modeldata() {};
		};
	}
}
#endif // !UNIVERSE_SPACE_XMODEL
