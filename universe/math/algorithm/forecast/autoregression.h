#pragma once
#ifndef XHQM_FORECAST_AR
#define XHQM_FORECAST_AR

#include "forecast.h"
#include "../analysis.h"

namespace xhqm::forecast
{
	template<typename datapot>
	class _ar_model : public xhqm::forecast::model<datapot, datapot>
	{
	protected:
		using forecastModel = xhqm::forecast::model<datapot, datapot>;
	public:
		inline bool predictable() const// «∑Òø…‘§≤‚
		{
			return (forecastModel::oversize() && forecastModel::sequential() && !noises());
		}

	public:
		virtual bool noises() const = 0;//∞◊‘Î“Ù
		virtual bool strong() const = 0;//«ø∆ΩŒ»
		virtual bool scanty() const = 0;//»ı∆ΩŒ»
		virtual bool smoothing() = 0;//∆ΩŒ»ªØ
		//virtual bool forecast() override;//‘§≤‚
	};

	template<typename datapot>
	class autoregression : public xhqm::forecast::_ar_model<datapot>
	{

	};

	template<>
	class autoregression<xhqm::measure>
		: public xhqm::forecast::_ar_model<xhqm::measure>
	{
	public:

		static std::vector<xhqm::measure> autocorrelation_function(const std::vector<xhqm::measure>& values, const xhqm::size& subk, bool adjusted)
		{
			std::vector<xhqm::measure> autocorrelation;

			xhqm::analysis::infomation<xhqm::measure> variance = xhqm::analysis::variance_values<xhqm::measure, std::vector>(values);
			if (adjusted)
			{
				for (xhqm::size k = 1, size = values.size(); k <= subk && k <= size; ++k)
				{
					xhqm::analysis::infomation<xhqm::measure> covariance = xhqm::analysis::self_covariance_adjusted<xhqm::measure>(values, k);
					autocorrelation.push_back(covariance.value / variance.value);
				}
			}
			else
			{
				for (xhqm::size k = 1, size = values.size(); k <= subk && k <= size; ++k)
				{
					xhqm::analysis::infomation<xhqm::measure> covariance = xhqm::analysis::self_covariance<xhqm::measure>(values, k);
					autocorrelation.push_back(covariance.value / variance.value);
				}
			}

			return autocorrelation;
		}
		template<class type>
		static xhqm::analysis::infomation<type> partial_autocorrelation_function(const std::vector<type>& values, const xhqm::size& subk)
		{
			xhqm::analysis::infomation<type> autocorrelation{ type(), subk, values.size() };
			if (autocorrelation.count > autocorrelation.index)
			{
				xhqm::analysis::infomation<type> covariance = xhqm::analysis::self_covariance<type>(values, subk);
				xhqm::analysis::infomation<type> variance = xhqm::analysis::variance_values<type, std::vector>(values);
				autocorrelation.value = covariance.value / variance.value;
			}
			return autocorrelation;
		}
		
	public:
		virtual bool noises() const override
		{
			return false;
		}
		virtual bool strong() const override
		{
			return true;
		}
		virtual bool scanty() const override
		{
			return true;
		}
		virtual bool smoothing() override
		{
			return true;
		}
		virtual bool forecast() override
		{
			std::cout << "forecast" << std::endl;




			return true;
		}
	};
}
#endif

