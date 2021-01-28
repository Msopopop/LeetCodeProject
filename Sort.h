#pragma once
#include <random>
#include <iterator>
#include <algorithm>
class Sort
{
public:
	template<typename ForwardIt, typename Compare>
	static void SelectSort(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		using std::min_element;
		using std::iter_swap;
		if (e - b <= 1) return;
		for (auto tmp = b; tmp != e; ++tmp)
			iter_swap(tmp, min_element(tmp, e, std::forward<Compare>(compare)));
	}

	template<typename ForwardIt, typename Compare>
	static void InsertSort(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		/*
		for (auto i = b; i != e; ++i) {
			std::rotate(std::upper_bound(b, i, *i), i, next(i));
		}
		*/
		using std::min_element;
		using std::iter_swap;
		if (e - b <= 1) return;
		iter_swap(b, min_element(b, e, std::forward<Compare>(compare)));
		for (auto&& tmp = next(b); tmp != e; ++tmp)
			for (auto&& l = std::forward<ForwardIt>(tmp); ; --l) {
				if (!compare(*l, *prev(l))) break;
				else iter_swap(l, prev(l));
			}
	}

	template<typename ForwardIt, typename Compare>
	static void ShellSort(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		using std::min_element;
		using std::iter_swap;
		if (e - b <= 1) return;
		decltype(e - b) h = 1;
		while (h < (e - b) / 3) 
			h = 3 * h + 1;
		while (h >= 1) 
		{
			const auto hIter = next(b, h);
			for (auto tmp = hIter; tmp != e; ++tmp)
				for (auto l = tmp; l >= hIter ; l -= h) {
					if (!compare(*l, *prev(l, h))) break;
					else iter_swap(l, prev(l, h));
				}
			h /= 3;
		}
	}
	
	template<typename ForwardIt, typename Compare>
	static void MergeSort(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		if (e - b <= 1) return;
		const auto& mid = b + ((e - b) >> 1);
		MergeSort(b, mid, std::forward<Compare>(compare));
		MergeSort(mid, e, std::forward<Compare>(compare));
		innerMerge(b, mid, e, std::forward<Compare>(compare));
	}

	template<typename ForwardIt, typename Compare>
	static void HeapSort(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		if (e - b <= 1) return;
		auto N = e - b;
		for (auto mid = (N >> 1) - 1; mid >= 0; --mid) {
			heapSink(mid, b, N, compare);
		}
		while (N > 1) {
			iter_swap(b, b + N - 1);
			--N;
			heapSink(0, b, N, compare);
		}
	}

	template<typename ForwardIt, typename Compare>
	static void QuickSort(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(b, e, g);
		
		if (e - b <= 8) {
			InsertSort(b, e, std::forward<Compare>(compare));
			return;
		}
		auto mid = getPartition(b, e, compare);
		QuickSort(b, mid,std::forward<Compare>(compare));
		QuickSort(next(mid), e,std::forward<Compare>(compare));
	}
	
	template <class ForwardIt, typename Compare>
	static void Quick3Way(const ForwardIt& b, const ForwardIt& e, 
		Compare&& compare)
	{
		if (e - b <= 1) return;
		auto pivot = b + ((e - b) >> 1);
		using _Ty = typename ForwardIt::value_type;
		ForwardIt L = seek_partition(b, e,
			[&pivot, &compare](const _Ty& em) { return compare(em, *pivot); });
		ForwardIt R = seek_partition(L, e,
			[&pivot, &compare](const _Ty& em) { return !compare(*pivot, em); });
		Quick3Way(b, L, std::forward<Compare>(compare));
		Quick3Way(R, e, std::forward<Compare>(compare));
	}

	template <class ForwardIt, typename Compare>
	static typename ForwardIt::value_type 
		FindKthElement(const ForwardIt& b, const ForwardIt& e, 
			Compare&& compare, const size_t K)
	{
		if (e - b <= 1) return *b;
		auto N = e - b;
		for (auto mid = (N >> 1) - 1; mid >= 0; --mid) {
			heapSink(mid, b, N, compare);
		}
		auto k = K - 1;
		while (k --) {
			std::iter_swap(b, b + N - 1);
			--N;
			heapSink(0, b, N, compare);
		}
		return *b;
	}


	template <class ForwardIt, typename Compare>
	static void QuickSort_STL(ForwardIt b, ForwardIt e, Compare&& compare)
	{
		if (b - e <= 1) return;
		auto pivot = b + ((e - b) >> 1);
		ForwardIt middle1 = std::partition(b, e,
			[&pivot, &compare](const auto& em) { return compare(em, *pivot); });
		ForwardIt middle2 = std::partition(middle1, e,
			[&pivot, &compare](const auto& em) { return !compare(*pivot, em); });
		QuickSort_STL(b, middle1, compare);
		QuickSort_STL(middle2, e, compare);
	}

private:
	template<typename ForwardIt, typename Compare>
	[[noreturn]]
	static void innerMerge(const ForwardIt& b, const ForwardIt& mid, const ForwardIt& e, 
		Compare&& compare) {
		using _Ty = typename ForwardIt::value_type;
		std::vector<_Ty> result;
		auto insertResult = std::back_inserter(result);
		auto l1 = b, l2 = mid, r1 = mid, r2 = e;
		while (l1 != r1) {
			if (l2 == r2) {
				std::move(l1, r1, insertResult);
				break;
			}
			if (compare(*l1, *l2)) {
				insertResult = std::move(*l1);
				++l1;
			}
			else {
				insertResult = std::move(*l2);
				++l2;
			}
		}
		if (l2 != r2) std::move(l2, r2, insertResult);
		auto tmp = b;
		std::move(begin(result), end(result), tmp);
	}

	template<typename ForwardIt, typename Compare>
	[[noreturn]]
	static void heapSink(typename ForwardIt::difference_type offset,
		const ForwardIt& b,
		const typename ForwardIt::difference_type N,
		Compare&& compare) {
		while ((offset << 1) < N - 1) {
			auto sonOffset = (offset << 1) +1;
			if ((sonOffset < N - 1) &&
				compare(*next(b, sonOffset),
					    *next(b, sonOffset + 1))) ++sonOffset;
			if (compare(*next(b, sonOffset), *next(b, offset))) break;
			iter_swap(next(b, offset), next(b, sonOffset));
			offset = sonOffset;
		}
	}

	template<typename ForwardIt, typename Compare>
#ifdef _HAS_NODISCARD
#if _HAS_NODISCARD == 1
	_NODISCARD
#endif
#endif
	static decltype(auto) getPartition(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		ForwardIt lo = b, hi = e;
		while (true) {
			while (compare(*++lo, *b)) if (lo == prev(e)) break;
			while (compare(*b, *--hi)) if (hi == b) break;
			if (lo >= hi) break;
			iter_swap(lo, hi);
		}
		iter_swap(b, hi);
		return hi;
	}

	template<typename ForwardIt, typename Compare>
#ifdef _HAS_NODISCARD
#if _HAS_NODISCARD == 1
	_NODISCARD
#endif
#endif
	static decltype(auto) seek_partition(const ForwardIt& b, const ForwardIt& e, Compare&& compare) {
		auto L = b;
		// L = std::find_if_not(b, e, p); R = next(L);
		for (; L != e; ++L) { // skip in-place elements at beginning
			if (!compare(*L)) break;
		}
		for (auto R = L; R != e; ++R) {
			if (compare(*R)) {
				iter_swap(L, R); // out of place, swap and loop
				++L;
			}
		}
		return L;
	}

	template<class RandomIt, class URBG>
	void shuffle(RandomIt first, RandomIt last, URBG&& g)
	{
		using diff_t = typename std::iterator_traits<RandomIt>::difference_type;
		using distr_t = typename std::uniform_int_distribution<diff_t>;
		using param_t = typename distr_t::param_type;

		distr_t D;
		diff_t n = last - first;
		for (diff_t i = n - 1; i > 0; --i) {
			std::swap(first[i], first[D(g, param_t(0, i))]);
		}
	}
};

