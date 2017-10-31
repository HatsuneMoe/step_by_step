package main

import (
	"testing"
	"time"
	"sort"
	"math/rand"
)

func Test_Sort(t *testing.T) {
	rand.Seed(time.Now().Unix())
	arr := make([]int, 100000)
	arr2 := make([]int, 100000)
	SliceEqual:= func (a, b []int) {
		if len(a) != len(b) {
			t.Error("WA")
			return
		}
	
		if (a == nil) != (b == nil) {
			t.Error("WA")
			return 
		}
		for i, v := range a {
			if v != b[i] {
				t.Error("WA")
				return
			}
		}
		t.Log("AC!") 
	}


	for i := 0;i < 100000;i++ {
		arr[i] = rand.Intn(10000) - 5000
	}
	copy(arr2, arr)
	IntroSort(arr)
	sort.Ints(arr2)
    SliceEqual(arr, arr2)
}
