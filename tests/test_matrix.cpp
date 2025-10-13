#include <gtest/gtest.h>
#include "../lib_matrix/matrix.h"

#include <gtest/gtest.h>
#include "matrix.h"

class MatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        mathVector<int> row1{ 1, 2, 3 };
        mathVector<int> row2{ 4, 5, 6 };
        mathVector<int> row3{ 7, 8, 9 };
        mathVector<mathVector<int>> vec_mat{ row1, row2, row3 };
        mat_from_vec = matrix<int>(vec_mat);
    }

    matrix<int> mat_from_vec;
};

TEST_F(MatrixTest, DefaultConstructor) {
    matrix<int> mat;
    EXPECT_EQ(mat.rows(), 0);
    EXPECT_EQ(mat.cols(), 0);
    EXPECT_TRUE(mat.is_empty());
}

TEST_F(MatrixTest, SizeConstructor) {
    matrix<int> mat(3, 4);
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 4);
    EXPECT_FALSE(mat.is_empty());

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_EQ(mat[i][j], 0);
        }
    }
}

TEST_F(MatrixTest, SizeConstructorThrowsOnNegative) {
    EXPECT_THROW(matrix<int>(-1, 3), std::invalid_argument);
    EXPECT_THROW(matrix<int>(3, -1), std::invalid_argument);
}

TEST_F(MatrixTest, MathVectorConstructor) {
    EXPECT_EQ(mat_from_vec.rows(), 3);
    EXPECT_EQ(mat_from_vec.cols(), 3);
    EXPECT_EQ(mat_from_vec[0][0], 1);
    EXPECT_EQ(mat_from_vec[1][1], 5);
    EXPECT_EQ(mat_from_vec[2][2], 9);
}

TEST_F(MatrixTest, InitializerListConstructor) {
    matrix<int> mat{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[1][1], 5);
    EXPECT_EQ(mat[2][2], 9);
}

TEST_F(MatrixTest, InitializerListConstructorThrowsOnInvalid) {
    EXPECT_THROW((matrix<int>{{1, 2}, { 3, 4, 5 }}), std::invalid_argument);
}

TEST_F(MatrixTest, CopyConstructor) {
    matrix<int> original{ {1, 2}, {3, 4} };
    matrix<int> copy(original);

    EXPECT_EQ(copy.rows(), 2);
    EXPECT_EQ(copy.cols(), 2);
    EXPECT_EQ(copy[0][0], 1);
    EXPECT_EQ(copy[1][1], 4);

    original[0][0] = 100;
    EXPECT_EQ(copy[0][0], 1);
}

TEST_F(MatrixTest, AddScalar) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    matrix<int> result = mat.addScalar(5);

    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 7);
    EXPECT_EQ(result[1][0], 8);
    EXPECT_EQ(result[1][1], 9);
}

TEST_F(MatrixTest, SubScalar) {
    matrix<int> mat{ {10, 8}, {6, 4} };
    matrix<int> result = mat.subScalar(2);

    EXPECT_EQ(result[0][0], 8);
    EXPECT_EQ(result[0][1], 6);
    EXPECT_EQ(result[1][0], 4);
    EXPECT_EQ(result[1][1], 2);
}

TEST_F(MatrixTest, MultScalar) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    matrix<int> result = mat.multScalar(3);

    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[0][1], 6);
    EXPECT_EQ(result[1][0], 9);
    EXPECT_EQ(result[1][1], 12);
}

TEST_F(MatrixTest, DivScalar) {
    matrix<int> mat{ {10, 8}, {6, 4} };
    matrix<int> result = mat.divScalar(2);

    EXPECT_EQ(result[0][0], 5);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[1][1], 2);
}

TEST_F(MatrixTest, DivScalarThrowsOnZero) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    EXPECT_THROW(mat.divScalar(0), std::logic_error);
}

TEST_F(MatrixTest, VectorMult) {
    matrix<int> mat{ {1, 2, 3}, {4, 5, 6} };
    mathVector<int> vec{ 2, 1, 3 };

    mathVector<int> result = mat.vectorMult(vec);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 1 * 2 + 2 * 1 + 3 * 3);
    EXPECT_EQ(result[1], 4 * 2 + 5 * 1 + 6 * 3);
}

TEST_F(MatrixTest, VectorMultThrowsOnEmptyVector) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    mathVector<int> empty_vec;
    EXPECT_THROW(mat.vectorMult(empty_vec), std::logic_error);
}

TEST_F(MatrixTest, VectorMultThrowsOnSizeMismatch) {
    matrix<int> mat{ {1, 2, 3}, {4, 5, 6} };
    mathVector<int> vec{ 1, 2 };
    EXPECT_THROW(mat.vectorMult(vec), std::logic_error);
}

TEST_F(MatrixTest, MatrixAdd) {
    matrix<int> mat1{ {1, 2}, {3, 4} };
    matrix<int> mat2{ {5, 6}, {7, 8} };

    matrix<int> result = mat1.add(mat2);

    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[0][1], 8);
    EXPECT_EQ(result[1][0], 10);
    EXPECT_EQ(result[1][1], 12);
}

TEST_F(MatrixTest, MatrixAddThrowsOnSizeMismatch) {
    matrix<int> mat1{ {1, 2, 3} };
    matrix<int> mat2{ {4, 5} };
    EXPECT_THROW(mat1.add(mat2), std::logic_error);
}

TEST_F(MatrixTest, MatrixSub) {
    matrix<int> mat1{ {10, 8}, {6, 4} };
    matrix<int> mat2{ {1, 2}, {3, 4} };

    matrix<int> result = mat1.sub(mat2);

    EXPECT_EQ(result[0][0], 9);
    EXPECT_EQ(result[0][1], 6);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[1][1], 0);
}

TEST_F(MatrixTest, MatrixMult) {
    matrix<int> mat1{ {1, 2, 3}, {4, 5, 6} };
    matrix<int> mat2{ {7, 8}, {9, 10}, {11, 12} };

    matrix<int> result = mat1.matrixMult(mat2);

    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_EQ(result[0][0], 1 * 7 + 2 * 9 + 3 * 11);
    EXPECT_EQ(result[0][1], 1 * 8 + 2 * 10 + 3 * 12);
    EXPECT_EQ(result[1][0], 4 * 7 + 5 * 9 + 6 * 11);
    EXPECT_EQ(result[1][1], 4 * 8 + 5 * 10 + 6 * 12);
}

TEST_F(MatrixTest, MatrixMultThrowsOnIncompatible) {
    matrix<int> mat1{ {1, 2, 3} };
    matrix<int> mat2{ {4, 5} };
    EXPECT_THROW(mat1.matrixMult(mat2), std::logic_error);
}

// ƒругие методы
TEST_F(MatrixTest, Transpose) {
    matrix<int> mat{ {1, 2, 3}, {4, 5, 6} };
    matrix<int> result = mat.transpose();

    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[1][0], 2);
    EXPECT_EQ(result[1][1], 5);
    EXPECT_EQ(result[2][0], 3);
    EXPECT_EQ(result[2][1], 6);
}

TEST_F(MatrixTest, TransposeEmpty) {
    matrix<int> empty_mat;
    matrix<int> result = empty_mat.transpose();
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
}

TEST_F(MatrixTest, IsEqual) {
    matrix<int> mat1{ {1, 2}, {3, 4} };
    matrix<int> mat2{ {1, 2}, {3, 4} };
    matrix<int> mat3{ {1, 2}, {3, 5} };

    EXPECT_TRUE(mat1.isEqual(mat2));
    EXPECT_FALSE(mat1.isEqual(mat3));
}

// √еттеры
TEST_F(MatrixTest, RowsCols) {
    matrix<int> mat(4, 5);
    EXPECT_EQ(mat.rows(), 4);
    EXPECT_EQ(mat.cols(), 5);
}

TEST_F(MatrixTest, AtMethod) {
    matrix<int> mat{ {10, 20}, {30, 40} };

    EXPECT_EQ(mat.atMatrix(0, 0), 10);
    EXPECT_EQ(mat.atMatrix(1, 1), 40);

    mat.atMatrix(0, 1) = 25;
    EXPECT_EQ(mat.atMatrix(0, 1), 25);
}

TEST_F(MatrixTest, AtMethodThrowsOnOutOfRange) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    EXPECT_THROW(mat.atMatrix(-1, 0), std::out_of_range);
    EXPECT_THROW(mat.atMatrix(2, 0), std::out_of_range);
    EXPECT_THROW(mat.atMatrix(0, -1), std::out_of_range);
    EXPECT_THROW(mat.atMatrix(0, 2), std::out_of_range);
}

TEST_F(MatrixTest, SubscriptOperator) {
    matrix<int> mat{ {1, 2}, {3, 4} };

    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[1][1], 4);

    mat[0][1] = 10;
    EXPECT_EQ(mat[0][1], 10);
}

// ќператоры (не измен€ющие объект)
TEST_F(MatrixTest, ScalarAdditionOperator) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    matrix<int> result = mat + 5;

    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[1][1], 9);
}

TEST_F(MatrixTest, ScalarSubtractionOperator) {
    matrix<int> mat{ {10, 8}, {6, 4} };
    matrix<int> result = mat - 2;

    EXPECT_EQ(result[0][0], 8);
    EXPECT_EQ(result[1][1], 2);
}

TEST_F(MatrixTest, ScalarMultiplicationOperator) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    matrix<int> result = mat * 3;

    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[1][1], 12);
}

TEST_F(MatrixTest, ScalarDivisionOperator) {
    matrix<int> mat{ {10, 8}, {6, 4} };
    matrix<int> result = mat / 2;

    EXPECT_EQ(result[0][0], 5);
    EXPECT_EQ(result[1][1], 2);
}

TEST_F(MatrixTest, VectorMultiplicationOperator) {
    matrix<int> mat{ {1, 2, 3}, {4, 5, 6} };
    mathVector<int> vec{ 2, 1, 3 };

    mathVector<int> result = mat * vec;

    EXPECT_EQ(result[0], 13);
    EXPECT_EQ(result[1], 31);
}

TEST_F(MatrixTest, MatrixAdditionOperator) {
    matrix<int> mat1{ {1, 2}, {3, 4} };
    matrix<int> mat2{ {5, 6}, {7, 8} };

    matrix<int> result = mat1 + mat2;

    EXPECT_EQ(result[0][0], 6);
    EXPECT_EQ(result[1][1], 12);
}

TEST_F(MatrixTest, MatrixSubtractionOperator) {
    matrix<int> mat1{ {10, 8}, {6, 4} };
    matrix<int> mat2{ {1, 2}, {3, 4} };

    matrix<int> result = mat1 - mat2;

    EXPECT_EQ(result[0][0], 9);
    EXPECT_EQ(result[1][1], 0);
}

TEST_F(MatrixTest, MatrixMultiplicationOperator) {
    matrix<int> mat1{ {1, 2, 3}, {4, 5, 6} };
    matrix<int> mat2{ {7, 8}, {9, 10}, {11, 12} };

    matrix<int> result = mat1 * mat2;

    EXPECT_EQ(result[0][0], 58);
    EXPECT_EQ(result[1][1], 154);
}

TEST_F(MatrixTest, ScalarPlusEquals) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    mat += 5;

    EXPECT_EQ(mat[0][0], 6);
    EXPECT_EQ(mat[1][1], 9);
}

TEST_F(MatrixTest, ScalarMinusEquals) {
    matrix<int> mat{ {10, 8}, {6, 4} };
    mat -= 2;

    EXPECT_EQ(mat[0][0], 8);
    EXPECT_EQ(mat[1][1], 2);
}

TEST_F(MatrixTest, ScalarTimesEquals) {
    matrix<int> mat{ {1, 2}, {3, 4} };
    mat *= 3;

    EXPECT_EQ(mat[0][0], 3);
    EXPECT_EQ(mat[1][1], 12);
}

TEST_F(MatrixTest, ScalarDivideEquals) {
    matrix<int> mat{ {10, 8}, {6, 4} };
    mat /= 2;

    EXPECT_EQ(mat[0][0], 5);
    EXPECT_EQ(mat[1][1], 2);
}

TEST_F(MatrixTest, MatrixPlusEquals) {
    matrix<int> mat1{ {1, 2}, {3, 4} };
    matrix<int> mat2{ {5, 6}, {7, 8} };

    mat1 += mat2;

    EXPECT_EQ(mat1[0][0], 6);
    EXPECT_EQ(mat1[1][1], 12);
}

TEST_F(MatrixTest, MatrixMinusEquals) {
    matrix<int> mat1{ {10, 8}, {6, 4} };
    matrix<int> mat2{ {1, 2}, {3, 4} };

    mat1 -= mat2;

    EXPECT_EQ(mat1[0][0], 9);
    EXPECT_EQ(mat1[1][1], 0);
}

TEST_F(MatrixTest, MatrixTimesEquals) {
    matrix<int> mat1{ {1, 2, 3}, {4, 5, 6} };
    matrix<int> mat2{ {7, 8}, {9, 10}, {11, 12} };

    mat1 *= mat2;

    EXPECT_EQ(mat1.rows(), 2);
    EXPECT_EQ(mat1.cols(), 2);

    EXPECT_EQ(mat1[0][0], 58);
    EXPECT_EQ(mat1[0][1], 64);
    EXPECT_EQ(mat1[1][0], 139);
    EXPECT_EQ(mat1[1][1], 154);
}

TEST_F(MatrixTest, MatrixTimesEqualsModifiesOriginal) {
    matrix<int> mat{ {1, 2, 3}, {4, 5, 6} };
    matrix<int> other{ {7, 8}, {9, 10}, {11, 12} };

    matrix<int>& result_ref = (mat *= other);

    EXPECT_EQ(&result_ref, &mat);

    EXPECT_EQ(mat.rows(), 2);
    EXPECT_EQ(mat.cols(), 2);
}

TEST_F(MatrixTest, AssignmentOperator) {
    matrix<int> mat1{ {1, 2}, {3, 4} };
    matrix<int> mat2{ {5, 6, 7}, {8, 9, 10}, {11, 12, 13} };

    mat1 = mat2;

    EXPECT_EQ(mat1.rows(), 3);
    EXPECT_EQ(mat1.cols(), 3);
    EXPECT_EQ(mat1[0][0], 5);
    EXPECT_EQ(mat1[1][1], 9);
    EXPECT_EQ(mat1[2][2], 13);
}

TEST_F(MatrixTest, EqualityOperator) {
    matrix<int> mat1{ {1, 2}, {3, 4} };
    matrix<int> mat2{ {1, 2}, {3, 4} };
    matrix<int> mat3{ {1, 2}, {3, 5} };

    EXPECT_TRUE(mat1 == mat2);
    EXPECT_FALSE(mat1 == mat3);
}

TEST_F(MatrixTest, InequalityOperator) {
    matrix<int> mat1{ {1, 2}, {3, 4} };
    matrix<int> mat2{ {1, 2}, {3, 4} };
    matrix<int> mat3{ {1, 2}, {3, 5} };

    EXPECT_FALSE(mat1 != mat2);
    EXPECT_TRUE(mat1 != mat3);
}

TEST_F(MatrixTest, ChainOperations) {
    matrix<int> A{ {1, 2}, {3, 4} };
    matrix<int> B{ {5, 6}, {7, 8} };
    matrix<int> C{ {2, 0}, {1, 3} };

    matrix<int> result = (A + B) * C - A;

    EXPECT_EQ(result[0][0], 19);
    EXPECT_EQ(result[0][1], 22);
    EXPECT_EQ(result[1][0], 29);
    EXPECT_EQ(result[1][1], 32);
}

TEST_F(MatrixTest, FloatingPointOperations) {
    matrix<double> mat{ {1.5, 2.5}, {3.5, 4.5} };
    matrix<double> result = mat * 2.0;

    EXPECT_DOUBLE_EQ(result[0][0], 3.0);
    EXPECT_DOUBLE_EQ(result[0][1], 5.0);
    EXPECT_DOUBLE_EQ(result[1][0], 7.0);
    EXPECT_DOUBLE_EQ(result[1][1], 9.0);
}

TEST_F(MatrixTest, EmptyMatrixOperations) {
    matrix<int> empty1;
    matrix<int> empty2;

    matrix<int> result = empty1 + empty2;
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);

    result = empty1 * 5;
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
}

TEST_F(MatrixTest, OriginalsUnaffected) {
    matrix<int> original1{ {1, 2}, {3, 4} };
    matrix<int> original2{ {5, 6}, {7, 8} };

    matrix<int> copy1 = original1;
    matrix<int> copy2 = original2;

    matrix<int> result = original1 + original2;

    EXPECT_EQ(original1[0][0], 1);
    EXPECT_EQ(original1[1][1], 4);
    EXPECT_EQ(original2[0][0], 5);
    EXPECT_EQ(original2[1][1], 8);
}