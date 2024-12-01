#include "queue.h"
#include <gtest.h>

TEST(queue, can_check_empty_queue)
{
	int repeat = 10;
	circularQueue<int> Q;

	for (int i = 0; i <repeat; i++) {
		Q.push(i);
	}
	for (int i = 0; i < repeat; i++) {
		Q.pop();
	}

	EXPECT_EQ(Q.isEmpty(),1); 
}
TEST(queue, can_push_one_elem)
{
	circularQueue<int> Q;

	Q.push(10);

	EXPECT_EQ(Q.isEmpty(),0);
}
TEST(queue, can_pop_one_elem)
{
	circularQueue<int> Q;

	Q.push(10);
	Q.pop();

	EXPECT_EQ(Q.isEmpty(), 1);
}
TEST(queue, can_push_some_elems)
{
	int repeat = 10;
	circularQueue<int> Q;

	for(int i=0; i<repeat; i++) Q.push(10);

	EXPECT_EQ(Q.getSize(), repeat);
}
TEST(queue, can_pop_some_elems)
{
	int size = 10, repeat = 3;
	circularQueue<int> Q;

	for (int i = 0; i < size; i++) Q.push(10);
	for (int i = 0; i < repeat; i++) Q.pop();

	EXPECT_EQ(Q.getSize(), size-repeat);
}
TEST(queue, can_push_and_pop_some_elems)
{
	int  repeat = 10;
	circularQueue<int> Q;

	for (int i = 0; i < repeat; i++) {
		Q.push(i);
		Q.pop();
	}

	EXPECT_EQ(Q.isEmpty(),1);
}
TEST(queue, can_not_pop_from_empty_queue)
{
	circularQueue<int> Q;

	ASSERT_ANY_THROW(Q.pop());
}
TEST(queue, can_get_top)
{
	int repeat = 10;
	circularQueue<int> Q;

	for (int i = 0; i < repeat; i++) {
		Q.push(i);
	}

	EXPECT_EQ(Q.getTop(), 0);
}
TEST(queue, can_not_get_top_from_empty_queue)
{
	circularQueue<int> Q;

	ASSERT_ANY_THROW(Q.getTop());
}
TEST(queue, testSomePushAndSomePop) {
	circularQueue<int> Q;

	for (int i = 0; i < 4; i++) {
		Q.push(i);
	}
	for (int i = 0; i < 3; i++) {
		Q.pop();
	}
	for (int i = 1; i <=8; i++) {
		Q.push(i);
	}
	EXPECT_EQ(Q.getTop(),3);
}