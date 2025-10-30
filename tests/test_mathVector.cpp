#include <gtest/gtest.h>
#include "../lib_math_vector/mathVector.h"

class MathVectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        int_data = new int[3] {1, 2, 3};
        double_data = new double[3] {1.5, 2.5, 3.5};
    }

    void TearDown() override {
        delete[] int_data;
        delete[] double_data;
    }

    int* int_data;
    double* double_data;
};


TEST_F(MathVectorTest, DefaultConstructor) {
    mathVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_GE(vec.capacity(), 15);
    EXPECT_TRUE(vec.is_empty());
}

TEST_F(MathVectorTest, SizeConstructor) {
    mathVector<int> vec(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_FALSE(vec.is_empty());
}

TEST_F(MathVectorTest, SizeDataConstructor) {
    mathVector<int> vec(3, int_data);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST_F(MathVectorTest, InitializerListConstructor) {
    mathVector<int> vec{ 10, 20, 30, 40 };
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
    EXPECT_EQ(vec[3], 40);
}

TEST_F(MathVectorTest, SizeInitializerListConstructor) {
    mathVector<int> vec(3, { 100, 200, 300 });
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 100);
    EXPECT_EQ(vec[1], 200);
    EXPECT_EQ(vec[2], 300);
}

TEST_F(MathVectorTest, CopyConstructor) {
    mathVector<int> original{ 1, 2, 3 };
    mathVector<int> copy(original);

    EXPECT_EQ(copy.size(), original.size());
    for (int i = 0; i < original.size(); i++) {
        EXPECT_EQ(copy[i], original[i]);
    }
}

TEST_F(MathVectorTest, TVectorCopyConstructor) {
    TVector<int> tvec(3, int_data);
    mathVector<int> mvec(tvec);

    EXPECT_EQ(mvec.size(), 3);
    EXPECT_EQ(mvec[0], 1);
    EXPECT_EQ(mvec[1], 2);
    EXPECT_EQ(mvec[2], 3);
}

TEST_F(MathVectorTest, AddMethod) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5, 6 };

    mathVector<int> result = vec1.add(vec2);

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

TEST_F(MathVectorTest, AddMethodDifferentSizesThrows) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5 };

    EXPECT_THROW(vec1.add(vec2), std::logic_error);
}

TEST_F(MathVectorTest, SubMethod) {
    mathVector<int> vec1{ 10, 8, 6 };
    mathVector<int> vec2{ 4, 3, 2 };

    mathVector<int> result = vec1.sub(vec2);

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 6);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 4);
}

TEST_F(MathVectorTest, MultMethodInt) {
    mathVector<int> vec{ 2, 4, 6 };
    mathVector<int> result = vec.mult(3);

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 6);
    EXPECT_EQ(result[1], 12);
    EXPECT_EQ(result[2], 18);
}

TEST_F(MathVectorTest, MultMethodDouble) {
    mathVector<double> vec{ 1.0, 2.0, 3.0 };
    mathVector<double> result = vec.mult(2.5);

    EXPECT_DOUBLE_EQ(result[0], 2.5);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
    EXPECT_DOUBLE_EQ(result[2], 7.5);
}

TEST_F(MathVectorTest, DivMethodInt) {
    mathVector<int> vec{ 10, 20, 30 };
    mathVector<int> result = vec.div(2);

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 10);
    EXPECT_EQ(result[2], 15);
}

TEST_F(MathVectorTest, DivMethodDouble) {
    mathVector<double> vec{ 10.0, 20.0, 30.0 };
    mathVector<double> result = vec.div(4.0);

    EXPECT_DOUBLE_EQ(result[0], 2.5);
    EXPECT_DOUBLE_EQ(result[1], 5.0);
    EXPECT_DOUBLE_EQ(result[2], 7.5);
}

TEST_F(MathVectorTest, DivByZeroThrows) {
    mathVector<int> vec{ 1, 2, 3 };
    EXPECT_THROW(vec.div(0), std::logic_error);
}

TEST_F(MathVectorTest, ScalarMultMethod) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5, 6 };

    int result = vec1.scalarMult(vec2);
    EXPECT_EQ(result, 32);
}

TEST_F(MathVectorTest, ScalarMultDifferentSizesThrows) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5 };

    EXPECT_THROW(vec1.scalarMult(vec2), std::logic_error);
}

TEST_F(MathVectorTest, AdditionOperator) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5, 6 };

    mathVector<int> result = vec1 + vec2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 7);
    EXPECT_EQ(result[2], 9);
}

TEST_F(MathVectorTest, SubtractionOperator) {
    mathVector<int> vec1{ 10, 8, 6 };
    mathVector<int> vec2{ 4, 3, 2 };

    mathVector<int> result = vec1 - vec2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 6);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 4);
}

TEST_F(MathVectorTest, ScalarMultiplicationOperator) {
    mathVector<int> vec{ 2, 4, 6 };
    mathVector<int> result = vec * 3;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 6);
    EXPECT_EQ(result[1], 12);
    EXPECT_EQ(result[2], 18);
}

TEST_F(MathVectorTest, ScalarDivisionOperator) {
    mathVector<int> vec{ 10, 20, 30 };
    mathVector<int> result = vec / 2;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 10);
    EXPECT_EQ(result[2], 15);
}

TEST_F(MathVectorTest, DotProductOperator) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5, 6 };

    int result = vec1 * vec2;
    EXPECT_EQ(result, 32);
}

TEST_F(MathVectorTest, PlusEqualsOperator) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5, 6 };

    vec1 += vec2;

    EXPECT_EQ(vec1.size(), 3);
    EXPECT_EQ(vec1[0], 5);
    EXPECT_EQ(vec1[1], 7);
    EXPECT_EQ(vec1[2], 9);
}

TEST_F(MathVectorTest, MinusEqualsOperator) {
    mathVector<int> vec1{ 10, 8, 6 };
    mathVector<int> vec2{ 4, 3, 2 };

    vec1 -= vec2;

    EXPECT_EQ(vec1.size(), 3);
    EXPECT_EQ(vec1[0], 6);
    EXPECT_EQ(vec1[1], 5);
    EXPECT_EQ(vec1[2], 4);
}

TEST_F(MathVectorTest, TimesEqualsOperator) {
    mathVector<int> vec{ 2, 4, 6 };

    vec *= 3;

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 6);
    EXPECT_EQ(vec[1], 12);
    EXPECT_EQ(vec[2], 18);
}

TEST_F(MathVectorTest, DivideEqualsOperator) {
    mathVector<int> vec{ 10, 20, 30 };

    vec /= 2;

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 10);
    EXPECT_EQ(vec[2], 15);
}

TEST_F(MathVectorTest, FloatingPointPrecision) {
    mathVector<double> vec1{ 0.1, 0.2, 0.3 };
    mathVector<double> vec2{ 0.4, 0.5, 0.6 };

    mathVector<double> result = vec1 + vec2;

    EXPECT_DOUBLE_EQ(result[0], 0.5);
    EXPECT_DOUBLE_EQ(result[1], 0.7);
    EXPECT_DOUBLE_EQ(result[2], 0.9);
}

TEST_F(MathVectorTest, OperationChaining) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5, 6 };
    mathVector<int> vec3{ 7, 8, 9 };

    mathVector<int> result = (vec1 + vec2) * 2 - vec3;

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], (1 + 4) * 2 - 7);
    EXPECT_EQ(result[1], (2 + 5) * 2 - 8);
    EXPECT_EQ(result[2], (3 + 6) * 2 - 9);
}

TEST_F(MathVectorTest, AssignmentChaining) {
    mathVector<int> vec{ 10, 20, 30 };

    (vec *= 2) += mathVector<int>{1, 1, 1};

    EXPECT_EQ(vec[0], 21);
    EXPECT_EQ(vec[1], 41);
    EXPECT_EQ(vec[2], 61);
}

TEST_F(MathVectorTest, EmptyVectorOperations) {
    mathVector<int> empty1;
    mathVector<int> empty2;

    mathVector<int> result = empty1 + empty2;
    EXPECT_EQ(result.size(), 0);
    EXPECT_TRUE(result.is_empty());
}

TEST_F(MathVectorTest, SizeMismatchThrowsInOperators) {
    mathVector<int> vec1{ 1, 2, 3 };
    mathVector<int> vec2{ 4, 5 };

    EXPECT_THROW(vec1 + vec2, std::logic_error);
    EXPECT_THROW(vec1 - vec2, std::logic_error);
    EXPECT_THROW(vec1 += vec2, std::logic_error);
    EXPECT_THROW(vec1 -= vec2, std::logic_error);
    EXPECT_THROW(vec1 * vec2, std::logic_error);
}

TEST_F(MathVectorTest, OriginalVectorsUnaffected) {
    mathVector<int> original1{ 1, 2, 3 };
    mathVector<int> original2{ 4, 5, 6 };

    mathVector<int> copy1 = original1;
    mathVector<int> copy2 = original2;

    mathVector<int> result = original1 + original2;

    EXPECT_EQ(original1.size(), 3);
    EXPECT_EQ(original1[0], 1);
    EXPECT_EQ(original1[1], 2);
    EXPECT_EQ(original1[2], 3);

    EXPECT_EQ(original2.size(), 3);
    EXPECT_EQ(original2[0], 4);
    EXPECT_EQ(original2[1], 5);
    EXPECT_EQ(original2[2], 6);
}