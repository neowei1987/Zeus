#ifndef __UTIL_SLIDING_WINDOW_H__
#define __UTIL_SLIDING_WINDOW_H__

#include <vector>
#include "time_util.h"
#include "sstream"

//基于时间向前滑动的窗口

template <typename T>
class SlidingWindow
{
public:
	//滑动窗口对应的时间（单位ms）， 每一个bucket对应的时间粒度(单位ms)
	SlidingWindow(int window_ts, int bucket_ts) {
		_bucket_ts = bucket_ts;
		_window_size = window_ts / bucket_ts;
		_bucket_cnt = _window_size * 10;
		_buckets = new T[_bucket_cnt];
		reset();
	}

	virtual ~SlidingWindow() {
		delete []_buckets;
	}

	std::string str() {
		std::stringstream ss;
		char time_buf[64];
		uint64_t ts = (_window_start_ts / 1000);
		ss 	<< "窗口开始时间：" << ctime_r((const time_t*)&ts, time_buf) << "ms\n"
			<< "窗口开始序号：" << _window_start_idx << "\n"
			<< "聚合信息：" << _aggregation.str() << "\n";
        for (int i = 0; i < _window_size; ++i) {
            ss << "小窗口[" << i << "]:" << _buckets[(i + _window_start_idx) % _bucket_cnt].str() << "\n";
        }

		return ss.str();
	}
	
	void reset()
	{
		_window_start_ts = get_milli_second();
		_window_start_idx = 0;
		for (size_t i = 0;i < _bucket_cnt; ++i) {
			_buckets[i].clear();
		}
		_aggregation.clear();
	}

	//获取聚集的数据(过去一段时间统计的统计信息)
	const T& getAggregation() {
		return _aggregation;
	}

	//新的数据
	void feedNewItem(uint64_t now, const T& item) {
		int interval = (now - _window_start_ts) / _bucket_ts; 
		if (interval < _window_size) { //数据没有满
			_buckets[ (_window_start_idx + interval) % _bucket_cnt] += item;
			_aggregation += item;
		}	
		else if (interval > (2 * _window_size  -1)) {
			reset();
			_aggregation += item;
			_buckets[0] += item;
            fprintf(stderr, "long time no access, reset. %d\n", interval);
		}
		else {
			int advance = interval - _window_size + 1;
			int idx = 0;
			for(int i = 0; i < advance; ++i) {
				idx = (_window_start_idx+i)%_bucket_cnt;
				_aggregation -= _buckets[idx];
				_buckets[idx].clear();
			}
			_buckets[ (_window_start_idx + interval) % _bucket_cnt] += item;
			_window_start_idx = (_window_start_idx + advance) % _bucket_cnt; 
			_window_start_ts += advance * _bucket_ts;	
            _aggregation += item;
		}
	}

private:
	int _bucket_ts;		//每一个分桶对应的时间粒度（单位ms)
	int _window_size; 	//滑动窗口大小
	int _bucket_cnt; 		//分桶数
	T* _buckets;				//分桶数据

	uint64_t _window_start_ts; 	//窗口开始的时间
	size_t _window_start_idx; 	//windows开始的offset

	T _aggregation; 			//滑动窗口下的聚合数据
};


#endif//__UTIL_SLIDING_WINDOW_H__

