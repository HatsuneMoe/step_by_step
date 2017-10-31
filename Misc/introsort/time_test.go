package main

import (
	"sort"
	"math/rand"
	"testing"
)

func Benchmark_TimeConsumingFunction(b *testing.B) {
    b.StopTimer() 
	rand.Seed(1)
	arr := make([]int, 5000000)
	for i := 0;i < 5000000;i++ {
		arr[i] = rand.Intn(10000) - 5000
	}

    b.StartTimer() 
    for i := 0; i < b.N; i++ {
        IntroSort(arr)
    }
}

func Benchmark_TimeConsumingFunction2(b *testing.B) {
    b.StopTimer()
	rand.Seed(1)
	arr := make([]int, 5000000)
	for i := 0;i < 5000000;i++ {
		arr[i] = rand.Intn(10000) - 5000
	}

    b.StartTimer()
    for i := 0; i < b.N; i++ {
        sort.Ints(arr)
    }
}