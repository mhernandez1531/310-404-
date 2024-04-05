//
// Created by George Thiruvathukal on 2/17/24.
//

#include <gtest/gtest.h>

#include "int_stack.hh"

TEST(IntStackTests, Initialization)
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    ASSERT_EQ(int_stack_capacity(&stack1), 10);
}

TEST(IntStackTests, PushToCapacityAndOverflow)
{
    // create stack that can hold 10 items
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // ensure it's full
    ASSERT_EQ(int_stack_size(&stack1), capacity);

    // try to add one more
    int result = int_stack_push(&stack1, capacity+1);

    // and make sure it is an overflow (error)
    ASSERT_FALSE(result);
}


TEST(IntStackTests, PushToCapcacityPopUntilUnderflow
)
{
    // create stack that can hold 10 items [similar to previous test]
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // now drain it one item at a time, ensuring each item is the value expected
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }

    // try to remove from empty stack and ensure it fails
    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, Init) {
	int_stack_t stack;
	int_stack_init(&stack, 5); // initalize stack with capacity of 5
	ASSERT_EQ(stack.size, 0); //stack size shuld be 0
	ASSERT_EQ(stack.capacity, 5); // stack capacity should be 5
}

TEST(IntStackTests, Push) {
	int_stack_t stack;
	int_stack_init(&stack, 2); // initilize stack with capacity of 2 
	ASSERT_TRUE(int_stack_push(&stack, 10)); // pushing 1st element 
	ASSERT_TRUE(int_stack_push(&stack, 20)); // pushing the 2nd element
	ASSERT_FALSE(int_stack_push(&stack, 30)); // pushing the 3rd elemet. Shouldn't work because capacity is reached
	ASSERT_EQ(stack.size, 2); //stack size should be 2
}

TEST(IntStackTests, pop)  {
	int_stack_t stack;
	int_stack_init(&stack, 5); // initalize stack with capacity of 5
	int_stack_push(&stack, 10); //push 1st element
	int_stack_push(&stack, 20); //push 2nd element 

	int top_value; 
	ASSERT_TRUE(int_stack_pop(&stack, &top_value)); //pop top value 
	ASSERT_EQ(top_value, 20); //the value poped should be last pushed 20 
	ASSERT_TRUE(int_stack_pop(&stack, &top_value)); //pop next top vale 
	ASSERT_EQ(top_value, 10); //top value should now be 10
	ASSERT_FALSE(int_stack_pop(&stack, &top_value)); //should fail because the stack is empty
}

TEST(IntStacktests, Top) {
	int_stack_t stack;
	int_stack_init(&stack, 5);
	int_stack_push(&stack, 10);
	int_stack_push(&stack, 20);

	int top_value;
	ASSERT_TRUE(int_stack_top(&stack, &top_value)); //should get the top value
	ASSERT_EQ(top_value, 20); //the top value should be the last pushed 20

	int_stack_pop(&stack, &top_value); // pops the top value to get the nexxt top value
	ASSERT_TRUE(int_stack_top(&stack, &top_value));
	ASSERT_EQ(top_value, 10); // now top should be 10

	int_stack_pop(&stack, &top_value);
	// should fail because the stack is now empty
    ASSERT_FALSE(int_stack_top(&stack, &top_value)); 
}

TEST(IntStackTests, Dup) {
 	int_stack_t stack;
	int_stack_init(&stack, 10); // initialize stack with a capacity of 10
	int_stack_push(&stack, 5); //pusehes 5 onto the stack
	int_stack_dup(&stack); //operates duplicate

	int top_value;
	ASSERT_TRUE(int_stack_top(&stack, &top_value)); // checks if the duplication was sucessful
	ASSERT_EQ(top_value, 5);
	ASSERT_EQ(int_stack_size(&stack), 2); //confirms that the duplicated calue was added to the stack
}


TEST(IntStackTests, Swap) {
	int_stack_t stack; 
	int_stack_init(&stack, 3); //initalize stack capacity to 3
	int_stack_push(&stack, 10);
	int_stack_push(&stack, 20);
	ASSERT_EQ(int_stack_swap(&stack), 1); //should swap
	
	int top_value;
	int_stack_top(&stack, &top_value);
	ASSERT_EQ(top_value, 10); //after swap top value should be 10
}

//arithmetic

TEST(IntStackTests, Add) {
	int_stack_t stack;
	int_stack_init(&stack, 3); //initalizes the capacity to 3
	int_stack_push(&stack, 10);
	int_stack_push(&stack, 20);
	int_stack_add(&stack);
	
	int top_value;
	ASSERT_TRUE(int_stack_top(&stack, &top_value));
	ASSERT_EQ(top_value, 30); // checks if the result is cirect 
}

TEST(IntStackTests, Subtraction){
	int_stack_t stack; 
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 5);
	int_stack_push(&stack, 3);
	int_stack_subtraction(&stack);

	int top_value;
	ASSERT_TRUE(int_stack_top(&stack, &top_value));
	ASSERT_EQ(top_value, 2);
}

TEST(IntStackTests, Multiply) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 2);
	int_stack_push(&stack, 3);
	int_stack_multiply(&stack);

	int top_value;
	ASSERT_TRUE(int_stack_top(&stack, &top_value));
	ASSERT_EQ(top_value, 6);
}


TEST(IntStackTests, Divide) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 6);
	int_stack_push(&stack, 3);
	int_stack_divide(&stack);
	
	int top_value;
	ASSERT_TRUE(int_stack_top(&stack, &top_value));
	ASSERT_EQ(top_value, 2); // Verify 6 / 3 = 2
}

TEST(IntStackTests, DivMod) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 10);
	int_stack_push(&stack, 3);
	int_stack_divmod(&stack);
	
	int remainder, quotient;
   	ASSERT_TRUE(int_stack_pop(&stack, &quotient)); // Pop quotient first due to stack order
	ASSERT_TRUE(int_stack_top(&stack, &remainder)); // Then check the remainder on top
	ASSERT_EQ(quotient, 3); // Verify quotient of 10 / 3 = 3
	ASSERT_EQ(remainder, 1); // Verify remainder of 10 % 3 = 1
}

TEST(IntStackTests, Mod) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 10);
	int_stack_push(&stack, 3);
	ASSERT_TRUE(int_stack_mod(&stack));

	int result; 
	ASSERT_TRUE(int_stack_top(&stack, &result));
	ASSERT_EQ(result, 1);
}

//stack manipulation 
TEST(intStackTests, Over) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	int_stack_push(&stack, 2);
	ASSERT_TRUE(int_stack_over(&stack));
	
	int top_value;
	ASSERT_TRUE(int_stack_top(&stack, &top_value)); 
	ASSERT_EQ(top_value, 1); // verify the second to top value 1 is now top
}

TEST(IntStackTests, Rot) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	int_stack_push(&stack, 2);
	int_stack_push(&stack, 3);
	ASSERT_TRUE(int_stack_rot(&stack));

	int third_value;
	int_stack_pop(&stack, &third_value); // Remove what is now the top value to get to the rotated one
	ASSERT_EQ(third_value, 1); // Verify the original bottom value (1) is now on top
}

TEST(IntStackTests, Drop) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	ASSERT_TRUE(int_stack_drop(&stack)); // Perform drop operation
	ASSERT_EQ(int_stack_size(&stack), 0); // Confirm the stack is empty after dropping the element
}

//double element operations 

TEST(IntStackTests, 2Swap) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	int_stack_push(&stack, 2);
	int_stack_push(&stack, 3);
	int_stack_push(&stack, 4);
	ASSERT_TRUE(int_stack_2swap(&stack));
	
	int top_value, next_value;
	int_stack_pop(&stack, &top_value); // Should now be 2, previously the second pair's top
	int_stack_pop(&stack, &next_value); // Should now be 1, previously the second pair's bottom
	ASSERT_EQ(top_value, 2);
	ASSERT_EQ(next_value, 1); // Confirm the top two pairs have been swapped
}

TEST(IntStackTests, 2Dup) {
	int_stack_t stack; 
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	int_stack_push(&stack, 2);
	ASSERT_TRUE(int_stack_2dup(&stack));
	ASSERT_EQ(int_stack_size(&stack), 4); //stack size should now be 4 after duplication

	int top_value;
	int_stack_pop(&stack, &top_value);
	ASSERT_EQ(top_value, 2); // the last duplicated value should be 2
}

TEST(IntStackTests, 2Over) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	int_stack_push(&stack, 2);
	int_stack_push(&stack, 3);
	int_stack_push(&stack, 4);
	ASSERT_TRUE(int_stack_2over(&stack));
	
	int top_value, next_value;
	int_stack_pop(&stack, &top_value); // Should be 2, the over value of the second pair
	int_stack_pop(&stack, &next_value); // Should be 1, the over value of the second
}
TEST(IntStackTests, 2Drop) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	int_stack_push(&stack, 2);
	ASSERT_TRUE(int_stack_2drop(&stack) == 0);//sucess on dropping 2 elements 
	ASSERT_EQ(int_stack_size(&stack), 0);
}



TEST(IntStackTests, Print) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
}

TEST(IntStackTests, Size) {
	int_stack_t stack;
	int_stack_init(&stack, 10);
	int_stack_push(&stack, 1);
	int_stack_push(&stack, 2);
	ASSERT_EQ(int_stack_size(&stack), 2); // verify the size is 2 after 2 pushes 
}

TEST(IntStackTests, Capacity) {
	int_stack_t stack; 
	int_stack_init(&stack, 10);
	ASSERT_EQ(int_stack_capacity(&stack), 10);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
