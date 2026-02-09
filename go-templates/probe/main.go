package main

import "fmt"

import "github.com/langhuihui/gomem"

func main() {
	fmt.Println("Hello, World!")
	a := 5
	b := 2
	c := 3
	fmt.Println(c)
	fmt.Println(c)
	x := multiplyAndAdd(a, b, c)
	fmt.Println(x)
	fmt.Println("KAFA")

	// Create a scalable memory allocator
	allocator := gomem.NewScalableMemoryAllocator(1024)

	// Allocate memory
	buf := allocator.Malloc(256)

	// Use the buffer...
	copy(buf, []byte("Hello, World!"))

	// Free the memory
	allocator.Free(buf)
}

func add(a int, b int) int {
	if a == 4 {
		return 5
	}
	return a + b
}

func multiplyAndAdd(a int, b int, c int) int {
	return a * add(b, c)
}
