package main

import (
	"fmt"
	"math"
	l "utility/testpackage"
) 
	
type shape interface{
	area() float64
	peri() float64
}
type circle struct{
	radius float64
}
func (c circle)area()float64{
	return math.Pi*c.radius*c.radius;
}
func (c circle)peri()float64{
	return math.Pi*c.radius*2;
}
func (c circle)dia()float64{
	return 2*c.radius;
}

func main() {
	//fmt.Println("hi")
	//l.Greeting()
//	fmt.Println(l.Greet())
	var s shape
	s=circle{5}
	fmt.Println(s.area())
	fmt.Println(s.peri())
	fmt.Println("hi")
	l.Greeting()
	fmt.Println(l.Greet())
	
}