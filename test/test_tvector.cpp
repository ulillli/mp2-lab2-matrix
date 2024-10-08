#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_using_temproray_object)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(std::move(TDynamicVector<int>(5))));
}
TEST(TDynamicVector, can_create_vector_using_temproray_object_and_temproray_object_will_not_exist_after_it)
{
	TDynamicVector<int> tmp(5);

	TDynamicVector<int> v(std::move(tmp));

	EXPECT_EQ(0,tmp.size());
}
TEST(TDynamicVector, can_assing_vector_using_temproray_object_and_temproray_object_will_not_exist_after_it)
{
	TDynamicVector<int> tmp(5), v;

	v = std::move(tmp);

	EXPECT_EQ(0, tmp.size());
}
TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	EXPECT_EQ(v, TDynamicVector<int>(v));
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(v1);
	
	EXPECT_NE(&v1,&v2);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(10);

	ASSERT_ANY_THROW(v.at(-3)=2);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(10);

  ASSERT_ANY_THROW(v.at(15)=2);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{

	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(v=v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	size_t size = 10;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	for (int i = 0; i < size; i++) {
		v2[i] = 2;
	}

	v1 = v2;
	
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	size_t size1 = 10, size2=5;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);

	v1 = v2;

	EXPECT_EQ(size2, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	size_t size1 = 10, size2 = 5;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);
	for (int i = 0; i < size2; i++) {
		v2[i] = 2;
	}

	v1 = v2;

	EXPECT_EQ(v1,v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	size_t size = 10;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	for (int i = 0; i < size; i++) {
		v1[i] = 2;
		v2[i] = 2;
	}

	bool flag = (v1 == v2);

	EXPECT_EQ(true, flag);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  size_t size = 10;
  TDynamicVector<int> v1(size);
  for (int i = 0; i < size; i++) {
	  v1[i] = 2;
  }

  bool flag = (v1 == v1);

  EXPECT_EQ(true, flag);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	size_t size1 = 10, size2 = 5;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);

	bool flag = (v1 == v2);

	EXPECT_EQ(false, flag);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	size_t size1 = 10;
	TDynamicVector<int> v(size1), result(size1);
	for (int i = 0; i < size1; i++) {
		v[i] = 2;
	}

	for (int i = 0; i < size1; i++) result[i] = 10;

	EXPECT_EQ(v+8,result);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	size_t size1 = 10;
	TDynamicVector<int> v(size1), result(size1);
	for (int i = 0; i < size1; i++) {
		v[i] = 10;
	}

	for (int i = 0; i < size1; i++) result[i] = 2;

	EXPECT_EQ(v - 8, result);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	size_t size1 = 10;
	TDynamicVector<int> v(size1), result(size1);
	for (int i = 0; i < size1; i++) {
		v[i] = 1;
	}

	for (int i = 0; i < size1; i++) result[i] = 3;

	EXPECT_EQ(v*3, result);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	size_t size = 10;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	for (int i = 0; i < size; i++) {
		v1[i] = 2;
		v2[i] = 2;
	}

	TDynamicVector<int> v(std::move(v1+v2));

	EXPECT_EQ(v1*2, v);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	size_t size1 = 10, size2 = 5;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	size_t size = 10;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	for (int i = 0; i < size; i++) {
		v1[i] = 10;
		v2[i] = 2;
	}
	TDynamicVector<int> result(size);
	for (int i = 0; i < size; i++) {
		result[i] = v1[i] - v2[i];
	}

	TDynamicVector<int> v(std::move(v1-v2));

	EXPECT_EQ(v, result);

}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	size_t size1 = 10, size2 = 5;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	size_t size = 10;
	TDynamicVector<int> v1(size);
	TDynamicVector<int> v2(size);
	for (int i = 0; i < size; i++) {
		v1[i] = 1;
		v2[i] = 2;
	}
	
	EXPECT_EQ(v1*v2, 20);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	size_t size1 = 10, size2 = 5;
	TDynamicVector<int> v1(size1);
	TDynamicVector<int> v2(size2);

	ASSERT_ANY_THROW(v1*v2);

}

