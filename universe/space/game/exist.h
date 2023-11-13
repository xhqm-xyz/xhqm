#ifndef XHQM_GAME_EXIST
#define XHQM_GAME_EXIST
#include "../head.h"
#include "../software/exist.h"
namespace xhqm
{
	namespace game
	{
		template<class type>
		class exist : public xhqm::software::exist, public type
		{
			typedef void(*active)(exist*);
			active m_doactive = nullptr;//首次执行一次
			active m_runactive = nullptr;//循环执行多次
			active m_undoactive = nullptr;//末尾只执行一次
		protected:
			virtual void doexcept() {
				if (m_doactive) //同一类个性
					m_doactive(this);
			};//首次执行一次
			virtual void runexcept() {
				if (m_runactive) //同一类个性
					m_runactive(this);
			};//循环执行多次
			virtual void undoexcept() {
				if (m_undoactive) //同一类个性
					m_undoactive(this);
			};//末尾只执行一次
		public:

			void updoactive(exist::active active)
			{
				std::lock_guard<std::mutex> lock(mutex());
				m_doactive = active;
			}
			void uprunactive(exist::active active)
			{
				std::lock_guard<std::mutex> lock(mutex());
				m_runactive = active;
			}
			void upundoactive(exist::active active)
			{
				std::lock_guard<std::mutex> lock(mutex());
				m_undoactive = active;
			}
		};

	}
}
#endif
