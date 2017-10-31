package main

import "fmt"

const (
	_threshold = 16
)

// PartialSort test
func PartialSort(arr []int) {
	partialSort(arr, 0, len(arr)-1, len(arr)-1)
}

func partialSort(arr []int, first, mid, last int) {
	comp := func(a, b int) bool {
		return arr[a] > arr[b]
	}
	down := func(hole, bottom int) {
		for {
			j1 := 2*hole + 1
			if j1 >= bottom || j1 < 0 {
				break
			}
			j := j1
			if j2 := j1 + 1; j2 < bottom && !comp(j1, j2) {
				j = j2
			}
			if !comp(j, hole) {
				break
			}
			arr[hole], arr[j] = arr[j], arr[hole]
			hole = j
		}
	}
	makeHeap := func(f, l int) {
		bottom := l - f
		if 2 <= bottom {
			for hole := bottom / 2; 0 <= hole; hole-- {
				down(hole, bottom)
			}
		}
	}
	sortHeap := func(f, l int) {
		for i := l; i > 0; i-- {
			arr[f], arr[i] = arr[i], arr[f]
			down(f, i)
		}
	}
	makeHeap(first, mid)
	sortHeap(first, mid)
}

func _introSort(arr []int, first, last, depthLimit int) {
	_unguardedPartition := func (arr []int, first, last, pivot int) int {
		for true {
			for arr[first] < pivot {
				first++
			}
			last--
			for pivot < arr[last] {
				last--
			}
			if first >= last {
				return first
			}
			arr[first], arr[last] = arr[last], arr[first]
			first++
		}
		return -1
	}
	_median := func() int {
		mid := first + ((last - first) >> 1)
		var less int
		if arr[first] > arr[last] {
			less = arr[last]
		} else {
			less = arr[first]
		}
		if less > arr[mid] {
			return less
		}
		return arr[mid]
	}

	for (last - first) > _threshold {
		if depthLimit == 0 {
			partialSort(arr, first, last, last)
			return
		}
		depthLimit--
		cut := _unguardedPartition(arr, first, last, _median())
		_introSort(arr, cut, last, depthLimit)
		last = cut
	}
}

func _finalInsert(arr []int, first, last int) {
	_unguardedLinear := func(l, v int) {
		next := l
		next--
		for v < arr[next] {
			arr[l] = arr[next]
			l = next
			next--
		}
		arr[l] = v
	}
	_linearInsert := func(f, l int) {
		_copyBackward := func(_f, _l, _d int) {
			_d--
			_l--
			for _f <= _l {
				arr[_d] = arr[_l]
				_d--
				_l--
			}
		}
		v := arr[l]
		if v < arr[f] {
			_copyBackward(f, l, l+1)
			arr[f] = v
		} else {
			_unguardedLinear(l, v)
		}
	}

	_insertionSort := func(f, l int) {
		if f == l {
			return
		}
		for i := f + 1; i <= l; i++ {
			_linearInsert(f, i)
		}
	}

	_unguardedInsertion := func(f, l int) {
		for i := f; i <= l; i++ {
			_unguardedLinear(i, arr[i])
		}
	}
	if (last - first) > _threshold {
		_insertionSort(first, first+_threshold)
		_unguardedInsertion(first+_threshold, last)
	} else {
		_insertionSort(first, last)
	}
}

// IntroSort is a introspective sort
func IntroSort(arr []int) {
	_lg := func(_n int) int {
		_k := 0
		for ; _n != 0; _n >>= 1 {
			_k++
		}
		return _k - 1
	}
	first, last := 0, len(arr)-1
	if first <= last {
		_introSort(arr, first, last, _lg(last-first)*2)
		_finalInsert(arr, first, last)
	}
}

func main() {
	list := []int{1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15,1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15,1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 20, 6, 13, 14, 11, 17, 12, 16, 10, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 17, 12, 16, 10, 20, 6, 13, 14, 11, 17, 12, 16, 10, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 20, 6, 13, 14, 11, 17, 12, 16, 10, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15,1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15,1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 20, 6, 13, 14, 11, 17, 12, 16, 10, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 17, 12, 16, 10, 20, 6, 13, 14, 11, 17, 12, 16, 10, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 1, 5, 1, 5, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 3, 2, 4, 0, 9, 7, 8, 15, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10, 20, 6, 13, 14, 11, 17, 12, 16, 10, 18, 19, 20, 6, 13, 14, 11, 17, 12, 16, 10}
	fmt.Println("origin: ", list)
	IntroSort(list)
	fmt.Println("result: ", list)
}