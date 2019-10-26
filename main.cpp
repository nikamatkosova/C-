#define CATCH_CONFIG_MAIN
#include "catch.h"
#include "Vector.h"
#include "Matrix.h"

using namespace mat_vec;
using namespace std;

TEST_CASE("sizeVector", "[vector]"){
    Vector a(10, 2);
    REQUIRE( a.size() == 10);
}


TEST_CASE("copyVector", "[vector]"){
    Vector a(10, 2);
    Vector b = a;
    bool check = b == a;
    a = b;
    bool check2 = a == b;
    REQUIRE(check);
    REQUIRE(check2);
}

TEST_CASE("L2norm", "[vector]"){
    Vector a(9, 3);
    REQUIRE(a.norm() == 9);
}

TEST_CASE("operator+", "[vector]"){
    Vector a(10, 1);
    Vector b(10, 2);
    Vector d(10, 3);

    REQUIRE(d == a + b);
    a += b;
    REQUIRE(d == a);
}

TEST_CASE("operator-", "[vector]"){
    Vector a(10, 5);
    Vector b(10, 3);
    Vector d(10, 2);

    REQUIRE(d == a - b);
    a -= b;
    REQUIRE(d == a);
}

TEST_CASE("operator^", "[vector]"){
    Vector a(10, 5);
    Vector b(10, 3);
    Vector d(10, 15);

    REQUIRE(d == (a ^ b));
    a ^= b;
    REQUIRE(d == a);
}

TEST_CASE("operator*", "[vector]"){
    Vector a(3, 2);
    Vector b(3, 3);

    REQUIRE(a * b == 18);
}

TEST_CASE("operator*k", "[vector]"){
    Vector a(3, 2);
    Vector b(3, 6);

    REQUIRE(a * 3 == b);
    REQUIRE(3 * a == b);
    a *= 3;
    REQUIRE(a == b);
}

TEST_CASE("operator/k", "[vector]"){
    Vector a(3, 12);
    Vector b(3, 4);

    REQUIRE(a / 3 == b);
    a /= 3;
    REQUIRE(a == b);
}

TEST_CASE("operator==&!=", "[vector]"){
    Vector a(3, 12);
    Vector b(3, 4);
    Vector c(5, 4);
    Vector d(3, 4);


    bool check = a == b;

    REQUIRE(a != b);
    REQUIRE(not(check));

    check = b != d;
    REQUIRE(not(check));

    check = b == c;
    REQUIRE(not(check));

    check = b != c;
    REQUIRE(not(check));
}

TEST_CASE("normalizedL2", "[vector]"){
    Vector a(4, 3);
    Vector b(4, 0.5);
    Vector c(4, 0);

    REQUIRE(a.normalized() == b);
    a.normalize();
    REQUIRE(a == b);
}

TEST_CASE("operator[]", "[vector]"){
     const Vector a(4, 3);
     Vector b(5, 7);

     double check = a[1];
     REQUIRE(check == 3);

     check = b[3];
     REQUIRE(check == 7);
}

TEST_CASE("vec*mat", "[vector]"){
    Matrix mat(2, 3, 1);
    Vector vec(3, 2);
    Vector out(2, 6);
    Vector tmp(2, 0);

    tmp = vec * mat;
    REQUIRE(tmp == out);

    tmp = mat * vec;
    REQUIRE(tmp == out);

    vec *= mat;
    tmp = vec;
    REQUIRE(tmp == out);
}

TEST_CASE("consMatrix", "[matrix]"){
    Matrix a(3);
    Matrix c(3);
    Matrix b = a;

    REQUIRE(a == b);

    c.eye(3);
    b.eye(3);

    REQUIRE(c == b);
    REQUIRE(c.get(1, 1) == 0);
}

TEST_CASE("operator+Matrix", "[matrix]"){
    Matrix a(2, 3, 3);
    Matrix b(2, 3, 1);
    Matrix d(2, 3, 4);

    REQUIRE(a + b == d);

    a += b;
    REQUIRE(a == d);
}

TEST_CASE("operator-Matrix", "[matrix]"){
    Matrix a(3, 2, 9);
    Matrix b(3, 2, 7);
    Matrix d(3, 2, 2);

    REQUIRE(a - b == d);

    a -= b;
    REQUIRE(a == d);
}

TEST_CASE("operator*Matrix", "[matrix]"){
    Matrix a(2, 3, 2);
    Matrix b(3, 2, 1);
    Matrix d(2, 2, 6);

    REQUIRE(a * b == d);

    a *= b;
    REQUIRE(a == d);
}

TEST_CASE("operator*K_Matrix", "[matrix]"){
    Matrix a(2, 3, 5);
    Matrix b(2, 3, 15);

    REQUIRE(a * 3 == b);

    a *= 3;
    REQUIRE(a == b);
}

TEST_CASE("operator/K_Matrix", "[matrix]"){
    Matrix a(2, 3, 36);
    Matrix b(2, 3, 6);

    REQUIRE(a / 6 == b);

    a /= 6;
    REQUIRE(a == b);
}

TEST_CASE("operator=_Matrix", "[matrix]"){
    Matrix a(4, 3, 5);
    Matrix b(4, 3, 1);
    Matrix c(4, 3, 1);

    a = b;
    REQUIRE(a == c);
}

TEST_CASE("shapeMatrix", "[matrix]"){
    Matrix a(4, 3, 5);

    auto mShape = a.shape();
    REQUIRE(mShape.first == 4);
    REQUIRE(mShape.second == 3);
}

TEST_CASE("transpose", "[matrix]"){
    Matrix a(4, 3, 7);
    Matrix b(3, 4, 7);
    Matrix c(3, 4, 0);

    REQUIRE(a.transposed() == b);

    a.transpose();
    REQUIRE(a == b);
}

TEST_CASE("operator==&!=M", "[matrix]"){
    Matrix a(5, 3, 7);
    Matrix b(3, 2, 5);
    Matrix c(3, 2, 7);
    Matrix d(5, 3, 7);

    bool flag = a == b;
    REQUIRE(not(flag));

    flag = b == c;
    REQUIRE(not(flag));

    flag = a != b;
    REQUIRE(not(flag));

    flag = a != b;
    REQUIRE(not(flag));

    flag = b != c;
    REQUIRE(flag);

    flag = a != d;
    REQUIRE(not(flag));
}

TEST_CASE("reshapeM", "[matrix]"){
    Matrix a(6, 2, 3);
    Matrix b(2, 6, 3);

    a.reshape(2, 6);
    REQUIRE(a == b);
}

TEST_CASE("detMatrix", "[matrix]" ){
    Matrix a(2, 2, 3);
    Matrix c(5, 5, 8);

    REQUIRE(a.det() == 0);
    REQUIRE(c.det() == 0);
}