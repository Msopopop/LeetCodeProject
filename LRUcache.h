#pragma once

#include <unordered_map>
#include <list>
#include <iterator>
#include <stdexcept>

	template<typename _Kty, // key type
		typename _Ty> // mapped type
class LRUcache {
	public:
		using key_value_pair_t = typename std::pair<_Kty, _Ty>;
		using list_iterator_t = typename std::list<key_value_pair_t>::iterator;
		LRUcache() :_size(16uLL) { ; }

		LRUcache(const size_t& max_size) :
			_size(max_size) {
		}

		LRUcache(const LRUcache&) = delete;

		LRUcache(LRUcache&& rhs)
		{
			if (&rhs != this)
			{
				_size = std::move(rhs._size);
				cacheList = std::move(rhs.cacheList);
				hash = std::move(rhs.hash);
				rhs._size = 0;
			}
			
		}
		
		[[noreturn]]
		void insert(const _Kty& key, _Ty&& value) noexcept {
			auto it = hash.find(key);
			cacheList.emplace_front(key, std::forward<_Ty>(value));
			if (it != end(hash)) {
				cacheList.erase(it->second);
				hash.erase(it);
			}
			hash[key] = begin(cacheList);

			if (size(hash) > _size) {
				auto last = end(cacheList);
				last--;
				hash.erase(last->first);
				cacheList.pop_back();
			}
		}
#ifdef _HAS_NODISCARD
		_NODISCARD
#endif 
		_Ty& at(const _Kty& key) noexcept(false) {
			auto it = hash.find(key);
			if (it == end(hash)) {
				throw std::range_error("There is no such key in cache");
			}
			else {
				cacheList.splice(cacheList.begin(), cacheList, it->second);
				return it->second->second;
			}
		}
#ifdef _HAS_NODISCARD
		_NODISCARD
#endif 
		const _Ty& at(const _Kty& key) const noexcept(false) {
			auto it = hash.find(key);
			if (it == hash.end()) {
				throw std::range_error("There is no such key in cache");
			}
			else {
				cacheList.splice(cacheList.begin(), cacheList, it->second);
				return it->second->second;
			}
		}
#ifdef _HAS_NODISCARD
		_NODISCARD
#endif 
		bool exists(_Kty&& key) const noexcept{
			return hash.find(key) != hash.end();
		}

#ifdef _HAS_NODISCARD
		_NODISCARD
#endif 
		size_t size() const noexcept {
			return hash.size();
		}

	private:
		std::list<key_value_pair_t> cacheList;
		std::unordered_map<_Kty, list_iterator_t> hash;
		size_t _size;
	};

