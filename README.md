# floatImage
An image maker inspired by floatbeat.

## How it works

Each image is 512 x 512 size.  And each pixel has x and y value relative to its position. left/top is -1, and right/down is 1.
3 random stack-based strings will be generated and used to make each of RGB channel.

## The String

Each string consist of lowercase alphabet and numbers. Each character repersents a number or an operator.

RPN notation is used.
- Unary operator is applied on top value of current stack.
- Binary operator pops 2 numbers, and apply the operator, and push result.
To prevent exceptions, when stack needs to pop but there's not enough values to pop, It returns last successfully popped value.
Dividing by 0 will always make result 0.

## How to use

Compile main.c and put /images directory and compiled program in same directory.  After running the program, you will get 1000 randomly generated images.
