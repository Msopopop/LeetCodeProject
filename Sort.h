#pragma once
class Sort
{
public:
	template<typename ForwardIt, typename UnaryOp>
	static void SelectSort(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
		using std::min_element;
		using std::iter_swap;
		if (e - b <= 1) return;
		for (auto tmp = b; tmp != e; ++tmp)
			iter_swap(tmp, min_element(tmp, e, std::forward<UnaryOp>(unaryOp)));
	}

	template<typename ForwardIt, typename UnaryOp>
	static void InsertSort(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
		using std::min_element;
		using std::iter_swap;
		if (e - b <= 1) return;
		iter_swap(b, min_element(b, e, std::forward<UnaryOp>(unaryOp)));
		for (auto&& tmp = next(b); tmp != e; ++tmp)
			for (auto&& l = std::forward<ForwardIt>(tmp); ; --l) {
				if (!unaryOp(*l, *prev(l))) break;
				else iter_swap(l, prev(l));
			}
	}

	template<typename ForwardIt, typename UnaryOp>
	static void ShellSort(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
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
					if (!unaryOp(*l, *prev(l, h))) break;
					else iter_swap(l, prev(l, h));
				}
			h /= 3;
		}
	}
	
	template<typename ForwardIt, typename UnaryOp>
	static void MergeSort(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
		if (e - b <= 1) return;
		const auto& mid = b + ((e - b) >> 1);
		MergeSort(b, mid, std::forward<UnaryOp>(unaryOp));
		MergeSort(mid, e, std::forward<UnaryOp>(unaryOp));
		innerMerge(b, mid, e, std::forward<UnaryOp>(unaryOp));
	}

	template<typename ForwardIt, typename UnaryOp>
	static void HeapSort(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
		if (e - b <= 1) return;
		auto N = e - b;
		for (auto mid = (N >> 1) - 1; mid >= 0; --mid) {
			heapSink(mid, b, N, unaryOp);
		}
		while (N > 1) {
			iter_swap(b, b + N - 1);
			--N;
			heapSink(0, b, N, unaryOp);
		}
	}

	template<typename ForwardIt, typename UnaryOp>
	static void QuickSort(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
		if (e - b <= 8) {
			InsertSort(b, e, std::forward<UnaryOp>(unaryOp));
			return;
		}
		auto mid = getPartition(b, e, unaryOp);
		QuickSort(b, mid,std::forward<UnaryOp>(unaryOp));
		QuickSort(next(mid), e,std::forward<UnaryOp>(unaryOp));
	}
	
	template <class ForwardIt, typename UnaryOp>
	static void Quick3Way(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp)
	{
		if (e - b <= 1) return;
		auto pivot = b + ((e - b) >> 1);
		using _Ty = typename ForwardIt::value_type;
		ForwardIt L = seek_partition(b, e,
			[&pivot, &unaryOp](const _Ty& em) { return unaryOp(em, *pivot); });
		ForwardIt R = seek_partition(L, e,
			[&pivot, &unaryOp](const _Ty& em) { return !unaryOp(*pivot, em); });
		Quick3Way(b, L, std::forward<UnaryOp>(unaryOp));
		Quick3Way(R, e, std::forward<UnaryOp>(unaryOp));
	}

	template <class ForwardIt, typename UnaryOp>
	static typename ForwardIt::value_type 
		FindKthElement(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp, const size_t K)
	{
		if (e - b <= 1) return *b;
		auto N = e - b;
		for (auto mid = (N >> 1) - 1; mid >= 0; --mid) {
			heapSink(mid, b, N, unaryOp);
		}
		auto k = K - 1;
		while (k --) {
			iter_swap(b, b + N - 1);
			--N;
			heapSink(0, b, N, unaryOp);
		}
		return *b;
	}


	template <class ForwardIt, typename UnaryOp>
	static void QuickSort_STL(ForwardIt b, ForwardIt e, UnaryOp&& unaryOp)
	{
		if (b - e <= 1) return;
		auto pivot = b + ((e - b) >> 1);
		ForwardIt middle1 = std::partition(b, e,
			[&pivot, &unaryOp](const auto& em) { return unaryOp(em, *pivot); });
		ForwardIt middle2 = std::partition(middle1, e,
			[&pivot, &unaryOp](const auto& em) { return !unaryOp(*pivot, em); });
		QuickSort_STL(b, middle1, unaryOp);
		QuickSort_STL(middle2, e, unaryOp);
	}

private:
	template<typename ForwardIt, typename UnaryOp>
	[[noreturn]]
	static void innerMerge(const ForwardIt& b, const ForwardIt& mid, const ForwardIt& e, 
		UnaryOp&& unaryOp) {
		using _Ty = typename ForwardIt::value_type;
		std::vector<_Ty> result;
		auto insertResult = std::back_inserter(result);
		auto l1 = b, l2 = mid, r1 = mid, r2 = e;
		while (l1 != r1) {
			if (l2 == r2) {
				std::move(l1, r1, insertResult);
				break;
			}
			if (unaryOp(*l1, *l2)) {
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

	template<typename ForwardIt, typename UnaryOp>
	[[noreturn]]
	static void heapSink(typename ForwardIt::difference_type offset,
		const ForwardIt& b,
		const typename ForwardIt::difference_type N,
		UnaryOp&& unaryOp) {
		while ((offset << 1) < N - 1) {
			auto sonOffset = (offset << 1) +1;
			if ((sonOffset < N - 1) &&
				unaryOp(*next(b, sonOffset),
					    *next(b, sonOffset + 1))) ++sonOffset;
			if (unaryOp(*next(b, sonOffset), *next(b, offset))) break;
			iter_swap(next(b, offset), next(b, sonOffset));
			offset = sonOffset;
		}
	}

	template<typename ForwardIt, typename UnaryOp>
#ifdef _HAS_NODISCARD
#if _HAS_NODISCARD == 1
	_NODISCARD
#endif
#endif
	static decltype(auto) getPartition(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
		ForwardIt lo = b, hi = e;
		while (true) {
			while (unaryOp(*++lo, *b)) if (lo == prev(e)) break;
			while (unaryOp(*b, *--hi)) if (hi == b) break;
			if (lo >= hi) break;
			iter_swap(lo, hi);
		}
		iter_swap(b, hi);
		return hi;
	}

	template<typename ForwardIt, typename UnaryOp>
#ifdef _HAS_NODISCARD
#if _HAS_NODISCARD == 1
	_NODISCARD
#endif
#endif
	static decltype(auto) seek_partition(const ForwardIt& b, const ForwardIt& e, UnaryOp&& unaryOp) {
		auto L = b;
		// L = std::find_if_not(b, e, p); R = next(L);
		for (; L != e; ++L) { // skip in-place elements at beginning
			if (!unaryOp(*L)) break;
		}
		for (auto R = L; R != e; ++R) {
			if (unaryOp(*R)) {
				iter_swap(L, R); // out of place, swap and loop
				++L;
			}
		}
		return L;
	}
};

