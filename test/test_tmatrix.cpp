#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
 TDynamicMatrix<int> m(5);

 EXPECT_EQ(m, TDynamicMatrix<int>(m));
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  size_t size = 5;
  TDynamicMatrix<int> m1(size), m2(m1);

  EXPECT_NE(&m1[0], &m2[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	size_t size = 5;
	TDynamicMatrix<int> m(size);

	EXPECT_EQ(size, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);

	m[0][1] = 10;

	EXPECT_EQ(10, m[0][1]);
}
TEST(TDynamicMatrix, can_multiply_matrix_by_value)
{
	size_t size = 5;
	TDynamicMatrix<int> m(size);
	TDynamicMatrix<int> result(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m[i][j] = 2;
			result[i][j] = 6;
		}
	}

	m = m * 3;

	EXPECT_EQ(m,result);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);

	ASSERT_ANY_THROW(m.at(0,-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	size_t size = 5;
	TDynamicMatrix<int> m(size);

	ASSERT_ANY_THROW(m.at(0, size + 1));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	size_t size = 5;
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	size_t size = 5;
	TDynamicMatrix<int> m1(5), m2(5);
	m2[2][3] = 10;

	m1 = m2;

	EXPECT_EQ(m1[2][3], 10);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	size_t size1 = 5, size2 = 10;
	TDynamicMatrix<int> m1(5), m2(10);
	
	m1 = m2;

	EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	size_t size1 = 5, size2 = 10;
	TDynamicMatrix<int> m1(5), m2(10);

	m1 = m2;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	size_t size = 5;
	TDynamicMatrix<int> m1(size), m2(size);
	m1[0][3] = 3;
	m2[0][3] = 3;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	size_t size = 5;
	TDynamicMatrix<int> m(size);
	
	EXPECT_EQ(true, m==m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	size_t size1 = 5, size2 = 10;
	TDynamicMatrix<int> m1(5), m2(10);

	EXPECT_EQ(m1==m2,false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	size_t size = 5;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> result(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 2;
			result[i][j]=4;
		}
	}

	EXPECT_EQ(m1+m1,result);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	size_t size1= 5, size2=7;
	TDynamicMatrix<int> m1(size1), m2(size2);
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size1; j++) {
			m1[i][j] = 2;
		}
	}
	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size2; j++) {
			m2[i][j] = 4;
		}
	}

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	size_t size = 5;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> result(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 2;
			result[i][j] = 0;
		}
	}

	EXPECT_EQ(m1 - m1, result);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	size_t size1 = 5, size2 = 7;
	TDynamicMatrix<int> m1(size1), m2(size2);
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size1; j++) {
			m1[i][j] = 2;
		}
	}
	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size2; j++) {
			m2[i][j] = 4;
		}
	}

	ASSERT_ANY_THROW(m1 - m2);
}
TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	size_t size = 3;
	TDynamicMatrix<int> m1(size);
	TDynamicMatrix<int> m2(size), result(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			m1[i][j] = 2;
			m2[i][j] = 3;
			result[i][j] = 18;
		}
	}

	EXPECT_EQ(m1 * m2, result);
}
