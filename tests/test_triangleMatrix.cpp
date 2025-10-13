#include <gtest/gtest.h>
#include "../lib_triangleMatrix/triangleMatrix.h"

class TriangleMatrixTest : public ::testing::Test {
protected:
    void SetUp() override {
        upper_3x3 = triangleMatrix<int>({ {1, 2, 3},
                                         {0, 4, 5},
                                         {0, 0, 6} }, true);
        lower_3x3 = triangleMatrix<int>({ {1, 0, 0},
                                         {2, 3, 0},
                                         {4, 5, 6} }, false);
    }

    triangleMatrix<int> upper_3x3;
    triangleMatrix<int> lower_3x3;
};

TEST_F(TriangleMatrixTest, DefaultConstructor) {
    triangleMatrix<int> mat;
    EXPECT_EQ(mat.size(), 0);
    EXPECT_TRUE(mat.isUpper());
    EXPECT_TRUE(mat.is_empty());
}

TEST_F(TriangleMatrixTest, SizeConstructorUpper) {
    triangleMatrix<int> mat(3, true);
    EXPECT_EQ(mat.size(), 3);
    EXPECT_TRUE(mat.isUpper());

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i > j) {
                EXPECT_EQ(mat[i][j], 0);
            }
        }
    }
}

TEST_F(TriangleMatrixTest, SizeConstructorLower) {
    triangleMatrix<int> mat(3, false);
    EXPECT_EQ(mat.size(), 3);
    EXPECT_FALSE(mat.isUpper());

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i < j) {
                EXPECT_EQ(mat[i][j], 0);
            }
        }
    }
}

TEST_F(TriangleMatrixTest, CopyConstructor) {
    triangleMatrix<int> original({ {1, 2}, {0, 3} }, true);
    triangleMatrix<int> copy(original);

    EXPECT_EQ(copy.size(), 2);
    EXPECT_TRUE(copy.isUpper());
    EXPECT_EQ(copy[0][0], 1);
    EXPECT_EQ(copy[0][1], 2);
    EXPECT_EQ(copy[1][1], 3);

    original[0][0] = 100;
    EXPECT_EQ(copy[0][0], 1);
}

TEST_F(TriangleMatrixTest, MatrixConstructorUpper) {
    matrix<int> regular_mat({ {1, 2, 3},
                             {0, 4, 5},
                             {0, 0, 6} });
    triangleMatrix<int> tri_mat(regular_mat, true);

    EXPECT_EQ(tri_mat.size(), 3);
    EXPECT_TRUE(tri_mat.isUpper());
    EXPECT_EQ(tri_mat[0][0], 1);
    EXPECT_EQ(tri_mat[1][1], 4);
    EXPECT_EQ(tri_mat[2][2], 6);
}

TEST_F(TriangleMatrixTest, MatrixConstructorLower) {
    matrix<int> regular_mat({ {1, 0, 0},
                             {2, 3, 0},
                             {4, 5, 6} });
    triangleMatrix<int> tri_mat(regular_mat, false);

    EXPECT_EQ(tri_mat.size(), 3);
    EXPECT_FALSE(tri_mat.isUpper());
    EXPECT_EQ(tri_mat[0][0], 1);
    EXPECT_EQ(tri_mat[1][1], 3);
    EXPECT_EQ(tri_mat[2][2], 6);
}

TEST_F(TriangleMatrixTest, MatrixConstructorThrowsOnNonTriangular) {
    matrix<int> non_tri_mat({ {1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 9} });

    EXPECT_THROW(triangleMatrix<int>(non_tri_mat, true), std::invalid_argument);
}

TEST_F(TriangleMatrixTest, MatrixConstructorThrowsOnNonSquare) {
    matrix<int> non_square_mat({ {1, 2}, {3, 4}, {5, 6} });
    EXPECT_THROW(triangleMatrix<int>(non_square_mat, true), std::invalid_argument);
}

TEST_F(TriangleMatrixTest, InitializerListConstructorUpper) {
    triangleMatrix<int> mat({ {1, 2, 3},
                             {0, 4, 5},
                             {0, 0, 6} }, true);

    EXPECT_EQ(mat.size(), 3);
    EXPECT_TRUE(mat.isUpper());
    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[0][1], 2);
    EXPECT_EQ(mat[0][2], 3);
    EXPECT_EQ(mat[1][1], 4);
    EXPECT_EQ(mat[1][2], 5);
    EXPECT_EQ(mat[2][2], 6);
}

TEST_F(TriangleMatrixTest, InitializerListConstructorLower) {
    triangleMatrix<int> mat({ {1, 0, 0},
                             {2, 3, 0},
                             {4, 5, 6} }, false);

    EXPECT_EQ(mat.size(), 3);
    EXPECT_FALSE(mat.isUpper());
    EXPECT_EQ(mat[0][0], 1);
    EXPECT_EQ(mat[1][0], 2);
    EXPECT_EQ(mat[1][1], 3);
    EXPECT_EQ(mat[2][0], 4);
    EXPECT_EQ(mat[2][1], 5);
    EXPECT_EQ(mat[2][2], 6);
}

TEST_F(TriangleMatrixTest, InitializerListConstructorThrowsOnNonTriangular) {
    EXPECT_THROW((triangleMatrix<int>{{1, 2}, { 3, 4 }}, true), std::invalid_argument);
}

TEST_F(TriangleMatrixTest, AddScalarUpper) {
    triangleMatrix<int> result = upper_3x3.addScalar(2);

    EXPECT_TRUE(result.isUpper());
    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[0][2], 5);
    EXPECT_EQ(result[1][1], 6);
    EXPECT_EQ(result[1][2], 7);
    EXPECT_EQ(result[2][2], 8);

    EXPECT_EQ(result[1][0], 0);
    EXPECT_EQ(result[2][0], 0);
    EXPECT_EQ(result[2][1], 0);
}

TEST_F(TriangleMatrixTest, SubScalarUpper) {
    triangleMatrix<int> result = upper_3x3.subScalar(1);

    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[0][1], 1);
    EXPECT_EQ(result[0][2], 2);
    EXPECT_EQ(result[1][1], 3);
    EXPECT_EQ(result[1][2], 4);
    EXPECT_EQ(result[2][2], 5);
}

TEST_F(TriangleMatrixTest, MultScalarUpper) {
    triangleMatrix<int> result = upper_3x3.multScalar(2);

    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[0][2], 6);
    EXPECT_EQ(result[1][1], 8);
    EXPECT_EQ(result[1][2], 10);
    EXPECT_EQ(result[2][2], 12);
}

TEST_F(TriangleMatrixTest, DivScalar) {
    triangleMatrix<int> mat({ {4, 6}, {0, 8} }, true);
    triangleMatrix<int> result = mat.divScalar(2);

    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[0][1], 3);
    EXPECT_EQ(result[1][1], 4);
}

TEST_F(TriangleMatrixTest, DivScalarThrowsOnZero) {
    EXPECT_THROW(upper_3x3.divScalar(0), std::logic_error);
}

TEST_F(TriangleMatrixTest, AddUpperMatrices) {
    triangleMatrix<int> other({ {2, 3, 4},
                               {0, 5, 6},
                               {0, 0, 7} }, true);
    triangleMatrix<int> result = upper_3x3.add(other);

    EXPECT_TRUE(result.isUpper());
    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[0][1], 5);
    EXPECT_EQ(result[0][2], 7);
    EXPECT_EQ(result[1][1], 9);
    EXPECT_EQ(result[1][2], 11);
    EXPECT_EQ(result[2][2], 13);
}

TEST_F(TriangleMatrixTest, AddLowerMatrices) {
    triangleMatrix<int> mat1({ {1, 0, 0},
                              {2, 3, 0},
                              {4, 5, 6} }, false);
    triangleMatrix<int> mat2({ {2, 0, 0},
                              {3, 4, 0},
                              {5, 6, 7} }, false);
    triangleMatrix<int> result = mat1.add(mat2);

    EXPECT_FALSE(result.isUpper());
    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[1][0], 5);
    EXPECT_EQ(result[1][1], 7);
    EXPECT_EQ(result[2][0], 9);
    EXPECT_EQ(result[2][1], 11);
    EXPECT_EQ(result[2][2], 13);
}

TEST_F(TriangleMatrixTest, AddThrowsOnDifferentSizes) {
    triangleMatrix<int> small({ {1, 2}, {0, 3} }, true);
    EXPECT_THROW(upper_3x3.add(small), std::logic_error);
}

TEST_F(TriangleMatrixTest, AddThrowsOnDifferentTypes) {
    EXPECT_THROW(upper_3x3.add(lower_3x3), std::logic_error);
}

TEST_F(TriangleMatrixTest, SubUpperMatrices) {
    triangleMatrix<int> other({ {2, 3, 4},
                               {0, 5, 6},
                               {0, 0, 7} }, true);
    triangleMatrix<int> result = other.sub(upper_3x3);

    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 1);
    EXPECT_EQ(result[0][2], 1);
    EXPECT_EQ(result[1][1], 1);
    EXPECT_EQ(result[1][2], 1);
    EXPECT_EQ(result[2][2], 1);
}

TEST_F(TriangleMatrixTest, MultUpperMatrices) {
    triangleMatrix<int> mat1({ {1, 2}, {0, 3} }, true);
    triangleMatrix<int> mat2({ {4, 5}, {0, 6} }, true);
    triangleMatrix<int> result = mat1.mult(mat2);

    EXPECT_TRUE(result.isUpper());
    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[0][1], 17);
    EXPECT_EQ(result[1][1], 18);
}

TEST_F(TriangleMatrixTest, MultLowerMatrices) {
    triangleMatrix<int> mat1({ {1, 0}, {2, 3} }, false);
    triangleMatrix<int> mat2({ {4, 0}, {5, 6} }, false);
    triangleMatrix<int> result = mat1.mult(mat2);

    EXPECT_FALSE(result.isUpper());
    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[1][0], 23);
    EXPECT_EQ(result[1][1], 18);
}

TEST_F(TriangleMatrixTest, MultThrowsOnDifferentSizes) {
    triangleMatrix<int> small({ {1, 2}, {0, 3} }, true);
    EXPECT_THROW(upper_3x3.mult(small), std::logic_error);
}

TEST_F(TriangleMatrixTest, MultThrowsOnDifferentTypes) {
    EXPECT_THROW(upper_3x3.mult(lower_3x3), std::logic_error);
}

// Другие методы
TEST_F(TriangleMatrixTest, TransposeUpper) {
    triangleMatrix<int> result = upper_3x3.transpose();

    EXPECT_FALSE(result.isUpper());
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[1][0], 2);
    EXPECT_EQ(result[1][1], 4);
    EXPECT_EQ(result[2][0], 3);
    EXPECT_EQ(result[2][1], 5);
    EXPECT_EQ(result[2][2], 6);
}

TEST_F(TriangleMatrixTest, TransposeLower) {
    triangleMatrix<int> result = lower_3x3.transpose();

    EXPECT_TRUE(result.isUpper());
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 2);
    EXPECT_EQ(result[0][2], 4);
    EXPECT_EQ(result[1][1], 3);
    EXPECT_EQ(result[1][2], 5);
    EXPECT_EQ(result[2][2], 6);
}

TEST_F(TriangleMatrixTest, SizeMethod) {
    EXPECT_EQ(upper_3x3.size(), 3);

    triangleMatrix<int> empty;
    EXPECT_EQ(empty.size(), 0);
}

TEST_F(TriangleMatrixTest, IsUpperMethod) {
    EXPECT_TRUE(upper_3x3.isUpper());
    EXPECT_FALSE(lower_3x3.isUpper());
}

// Операторы
TEST_F(TriangleMatrixTest, ScalarAdditionOperator) {
    triangleMatrix<int> result = upper_3x3 + 2;

    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[1][1], 6);
}

TEST_F(TriangleMatrixTest, ScalarSubtractionOperator) {
    triangleMatrix<int> result = upper_3x3 - 1;

    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[0][1], 1);
    EXPECT_EQ(result[1][1], 3);
}

TEST_F(TriangleMatrixTest, ScalarMultiplicationOperator) {
    triangleMatrix<int> result = upper_3x3 * 2;

    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[0][1], 4);
    EXPECT_EQ(result[1][1], 8);
}

TEST_F(TriangleMatrixTest, ScalarDivisionOperator) {
    triangleMatrix<int> mat({ {4, 6}, {0, 8} }, true);
    triangleMatrix<int> result = mat / 2;

    EXPECT_EQ(result[0][0], 2);
    EXPECT_EQ(result[0][1], 3);
    EXPECT_EQ(result[1][1], 4);
}

TEST_F(TriangleMatrixTest, MatrixAdditionOperator) {
    triangleMatrix<int> other({ {2, 3, 4},
                               {0, 5, 6},
                               {0, 0, 7} }, true);
    triangleMatrix<int> result = upper_3x3 + other;

    EXPECT_EQ(result[0][0], 3);
    EXPECT_EQ(result[0][1], 5);
    EXPECT_EQ(result[1][1], 9);
}

TEST_F(TriangleMatrixTest, MatrixSubtractionOperator) {
    triangleMatrix<int> other({ {2, 3, 4},
                               {0, 5, 6},
                               {0, 0, 7} }, true);
    triangleMatrix<int> result = other - upper_3x3;

    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 1);
    EXPECT_EQ(result[1][1], 1);
}

TEST_F(TriangleMatrixTest, MatrixMultiplicationOperator) {
    triangleMatrix<int> mat1({ {1, 2}, {0, 3} }, true);
    triangleMatrix<int> mat2({ {4, 5}, {0, 6} }, true);
    triangleMatrix<int> result = mat1 * mat2;

    EXPECT_EQ(result[0][0], 4);
    EXPECT_EQ(result[0][1], 17);
    EXPECT_EQ(result[1][1], 18);
}

TEST_F(TriangleMatrixTest, ChainOperations) {
    triangleMatrix<int> A({ {1, 2}, {0, 3} }, true);
    triangleMatrix<int> B({ {4, 5}, {0, 6} }, true);

    triangleMatrix<int> result = (A + B) * 2 - A;

    EXPECT_EQ(result[0][0], 9);
    EXPECT_EQ(result[0][1], 12);
    EXPECT_EQ(result[1][1], 15);
}

TEST_F(TriangleMatrixTest, TransposeChain) {
    triangleMatrix<int> result = upper_3x3.transpose().transpose();

    EXPECT_TRUE(result.isUpper());
    EXPECT_EQ(result[0][0], upper_3x3[0][0]);
    EXPECT_EQ(result[0][1], upper_3x3[0][1]);
    EXPECT_EQ(result[1][1], upper_3x3[1][1]);
}

TEST_F(TriangleMatrixTest, FloatingPointOperations) {
    triangleMatrix<double> mat({ {1.5, 2.5}, {0.0, 3.5} }, true);
    triangleMatrix<double> result = mat * 2.0;

    EXPECT_DOUBLE_EQ(result[0][0], 3.0);
    EXPECT_DOUBLE_EQ(result[0][1], 5.0);
    EXPECT_DOUBLE_EQ(result[1][1], 7.0);
}

TEST_F(TriangleMatrixTest, EmptyMatrixOperations) {
    triangleMatrix<int> empty1;
    triangleMatrix<int> empty2;

    triangleMatrix<int> result = empty1 + empty2;
    EXPECT_EQ(result.size(), 0);

    result = empty1 * 5;
    EXPECT_EQ(result.size(), 0);
}

TEST_F(TriangleMatrixTest, OriginalsUnaffected) {
    triangleMatrix<int> original1({ {1, 2}, {0, 3} }, true);
    triangleMatrix<int> original2({ {4, 5}, {0, 6} }, true);

    triangleMatrix<int> copy1 = original1;
    triangleMatrix<int> copy2 = original2;

    triangleMatrix<int> result = original1 + original2;

    EXPECT_EQ(original1[0][0], 1);
    EXPECT_EQ(original1[1][1], 3);
    EXPECT_EQ(original2[0][0], 4);
    EXPECT_EQ(original2[1][1], 6);
}