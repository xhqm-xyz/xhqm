#pragma once
#ifndef XHQM_ALGOR_FORECAST
#define XHQM_ALGOR_FORECAST

#include "../../../../head.h"

namespace xhqm::forecast
{
	using timepot = xhqm::size;

	template<typename backpot, typename forepot>
	class model
	{
	protected:
		xhqm::size m_backsize = 0;	//历史数据量
		xhqm::size m_foresize = 0;	//预测数据量
		xhqm::size m_threshold = 0; //数据量阈值
		xhqm::size m_maxsize = 0;	//最大存放量 //0时不限制存放量
		std::vector<std::pair<timepot, backpot>> m_backqueue;//历史数据
		std::vector<std::pair<timepot, forepot>> m_forequeue;//预测数据
	public:
		constexpr xhqm::size backsize() const { return m_backsize; }
		constexpr void backsize(xhqm::size size) { m_backsize = size; }
		constexpr xhqm::size foresize() const { return m_foresize; }
		constexpr void foresize(xhqm::size size) { m_foresize = size; }
		constexpr xhqm::size threshold() const { return m_threshold; }
		constexpr void threshold(xhqm::size threshold) { m_threshold = threshold; }
		constexpr xhqm::size maxsize() const { return m_maxsize; }
		constexpr void maxsize(xhqm::size maxsize) { m_maxsize = maxsize; }

		constexpr const std::vector<std::pair<timepot, backpot>>& dataqueue() const { return m_backqueue; };
		constexpr const std::vector<std::pair<timepot, forepot>>& forequeue() const { return m_forequeue; };
	public:
		inline void clear()
		{
			m_backqueue.clear();
		}
		inline void push(const timepot& time, const backpot& data)
		{
			if (m_backqueue.size() >= m_maxsize && m_maxsize != 0)
				m_backqueue.erase(m_backqueue.begin());
			m_backqueue.emplace_back(time, data);
		}

		inline bool oversize() const //数据是否是充足的
		{
			return (m_backqueue.size() >= m_threshold && m_backqueue.size() >= m_backsize);
		}
		inline bool sequential() const //数据是否是时序的
		{
			for (xhqm::size pos = 1, size = m_backqueue.size(); pos < size; ++pos)
				if (m_backqueue[pos].first < m_backqueue[pos - 1].first) return false;
			return true;
		}
	public:
		virtual bool forecast() = 0;//开始预测
	};
}
#endif

