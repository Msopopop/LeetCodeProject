#pragma once
class Sort
{
public:
	template<typename Iter, typename UnaryOp>
	static void SelectSort(const Iter& b, const Iter& e, UnaryOp&& unaryOp) {
		using std::min_element;
		using std::iter_swap;
		if (e - b <= 1) return;
		for (auto tmp = b; tmp != e; ++tmp)
			iter_swap(tmp, min_element(tmp, e, std::forward<UnaryOp>(unaryOp)));
	}

	template<typename Iter, typename UnaryOp>
	static void InsertSort(const Iter& b, const Iter& e, UnaryOp&& unaryOp) {
		using std::min_element;
		using std::iter_swap;
		if (e - b <= 1) return;
		iter_swap(b, min_element(b, e, std::forward<UnaryOp>(unaryOp)));
		for (auto&& tmp = next(b); tmp != e; ++tmp)
			for (auto&& l = std::forward<Iter>(tmp); ; --l) {
				if (!unaryOp(*l, *prev(l))) break;
				else iter_swap(l, prev(l));
			}
	}

	template<typename Iter, typename UnaryOp>
	static void ShellSort(const Iter& b, const Iter& e, UnaryOp&& unaryOp) {
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
	
	template<typename Iter, typename UnaryOp>
	static void MergeSort(const Iter& b, const Iter& e, UnaryOp&& unaryOp) {
		if (e - b <= 1) return;
		const auto& mid = b + ((e - b) >> 1);
		MergeSort(b, mid, std::forward<UnaryOp>(unaryOp));
		MergeSort(mid, e, std::forward<UnaryOp>(unaryOp));
		innerMerge(b, mid, e, std::forward<UnaryOp>(unaryOp));
	}

	template<typename Iter, typename UnaryOp>
	static void HeapSort(const Iter& b, const Iter& e, UnaryOp&& unaryOp) {
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

	template<typename Iter, typename UnaryOp>
	static void QuickSort(const Iter& b, const Iter& e, UnaryOp&& unaryOp) {
		if (e - b <= 4) {
			InsertSort(b, e, std::forward<UnaryOp>(unaryOp));
			return;
		}
		auto mid = getPartition(b, e, unaryOp);
		QuickSort(b, mid,std::forward<UnaryOp>(unaryOp));
		QuickSort(next(mid), e,std::forward<UnaryOp>(unaryOp));
	}
private:
	template<typename Iter, typename UnaryOp>
	static void innerMerge(const Iter& b, const Iter& mid, const Iter& e, 
		UnaryOp&& unaryOp) {
		using _Ty = typename Iter::value_type;
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

	template<typename Iter, typename UnaryOp>
	static void heapSink(typename Iter::difference_type offset,
		const Iter& b,
		const typename Iter::difference_type N,
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

	template<typename Iter, typename UnaryOp>
	static decltype(auto) getPartition(const Iter& b, const Iter& e, UnaryOp&& unaryOp) {
		Iter lo = b, hi = e;
		while (true) {
			while (unaryOp(*++lo, *b)) if (lo == prev(e)) break;
			while (unaryOp(*b, *--hi)) if (hi == b) break;
			if (lo >= hi) break;
			iter_swap(lo, hi);
		}
		iter_swap(b, hi);
		return hi;
	}
};
