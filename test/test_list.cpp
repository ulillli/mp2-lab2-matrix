#include "tlist.h"

#include <gtest.h>

TEST(list, can_create_list_positive_len)
{
  ASSERT_NO_THROW(list<int> L(5));
}

TEST(list, can_not_create_list_negitive_len)
{
	ASSERT_ANY_THROW(list<int> L(-5));;
}
TEST(list, can_create_list_using_copy_construction)
{
	list<int> L1(4);

	list<int> L2(L1);

	EXPECT_NE(nullptr, L2.first);
}
TEST(list, can_get_size_of_list)
{
	size_t size = 10;
	list<int> L1(size);

	EXPECT_EQ(size, L1.size());
}
TEST(list, can_use_moving_constraction)
{
	list<int> L1(10);
	list<int> L2(std::move(L1));

	EXPECT_EQ(L1.first, nullptr);
}
TEST(list, can_set_elem)
{
	list<int> L1(10);
	
	L1[8].value = 100;

	EXPECT_EQ(L1[8].value, 100);
}
TEST(list, can_insert_front)
{
	list<int> L1(10);

	list<int>::Node* tmp = L1.insert_front(1000);

	EXPECT_EQ(tmp->value, 1000);
}
TEST(list, can_insert_after_elem)
{
	list<int> L1(10);

	L1.insert_after(1000, &L1[3]);

	EXPECT_EQ(L1[4].value, 1000);
}
TEST(list, can_erase_after_elem)
{
	list<int> L1(10);
	L1[6].value = 100;
	
	L1.erase_afer(&L1[4]);
	
	EXPECT_EQ(L1[5].value, 100);
}
TEST(list, can_erase_front_elem)
{
	list<int> L1(10);
	L1[1].value = 100;
	
	L1.erase_front();
	
	EXPECT_EQ(L1.first->value, 100);
}
TEST(list, can_erase_last_elem)
{
	list<int> L1(10);
	L1[9].value = 100;

	L1.erase_back();
	
	EXPECT_EQ(L1[8].next, nullptr);
}
TEST(list, can_insert_at_the_end_of_list)
{
	list<int> L1(10);
	
	L1.insert_back(100);
	
	EXPECT_EQ(L1[10].value, 100);
}
TEST(list, can_assign_other_list_equal_size)
{
	size_t size1 = 10, size2 = 10;
	list<int> L1(size1),L2(size2);
	L1[5].value = 10;
	
	L2 = L1;
	
	EXPECT_EQ(L2[5].value,10);
}
TEST(list, can_assign_other_list_not_equal_size)
{
	size_t size1 = 10, size2 = 12;
	list<int> L1(size1), L2(size2);
	L2[10].value = 10;

	L1 = L2;
	
	EXPECT_EQ(((L1.size()==size2)&&(L1[10].value==10)), 1);
}
TEST(list, can_use_moving_operator_assign)
{
	size_t size1 = 10, size2 = 12;
	list<int> L1(size1);

	ASSERT_NO_THROW(L1=list<int>(10));
}
TEST(list, iterator_can_do_post_INC)
{
	size_t size = 10;
	list<int> L1(size);
	L1[3].value = 10;
	list<int>::iterator it(&L1[2]);

	EXPECT_EQ((*it++).value, 0);
}
TEST(list, iterator_can_do_pref_INC)
{
	size_t size = 10;
	list<int> L1(size);
	L1[3].value = 10;
	list<int>::iterator it(&L1[2]);

	EXPECT_EQ((*++it).value, 10);
}
TEST(list, iterator_can_compare_similar_iterators)
{
	size_t size = 10;
	list<int> L1(size);
	L1[3].value = 10;
	list<int>::iterator it1(&L1[2]),it2(&L1[2]);

	EXPECT_EQ(it1==it2,1);
}
TEST(list, iterator_can_compare_not_similar_iterators)
{
	size_t size = 10;
	list<int> L1(size);
	L1[3].value = 10;
	list<int>::iterator it1(&L1[2]), it2(&L1[3]);

	EXPECT_EQ(it1 != it2, 1);
}
TEST(list, iterator_can_use_operator_arrow)
{
	size_t size = 10;
	list<int> L1(size);
	L1[3].value = 10;
	list<int>::iterator it(&L1[3]);
	
	//EXPECT_EQ(it->value, 10);
}

