#include <iostream>
#include <array>
#include <stdexcept>

template <size_t R, size_t C, typename T = float>
class DroneMatrix {
private:
    std::array<T, R * C> data;

public:
    DroneMatrix() {
        data.fill(static_cast<T>(0));
    }

    T& operator()(size_t row, size_t col) {
        return data[row * C + col];
    }

    const T& operator()(size_t row, size_t col) const {
        return data[row * C + col];
    }

    DroneMatrix<R, C, T> operator+(const DroneMatrix<R, C, T>& other) const {
        DroneMatrix<R, C, T> result;
        for (size_t i = 0; i < R * C; ++i) {
            result.data[i] = this->data[i] + other.data[i];
        }
        return result;
    }

    template <size_t P>
    DroneMatrix<R, P, T> operator*(const DroneMatrix<C, P, T>& other) const {
        DroneMatrix<R, P, T> result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < P; ++j) {
                T sum = 0;
                for (size_t k = 0; k < C; ++k) {
                    sum += (*this)(i, k) * other(k, j);
                }
                result(i, j) = sum;
            }
        }
        return result;
    }

    DroneMatrix<C, R, T> transpose() const {
        DroneMatrix<C, R, T> result;
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < C; ++j) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    void print() const {
        for (size_t i = 0; i < R; ++i) {
            for (size_t j = 0; j < C; ++j) {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    DroneMatrix<3, 3, float> A;
    A(0, 0) = 1.0f; A(0, 1) = 0.01f; A(0, 2) = 0.0f;
    A(1, 0) = 0.0f; A(1, 1) = 1.0f;  A(1, 2) = 0.01f;
    A(2, 0) = 0.0f; A(2, 1) = 0.0f;  A(2, 2) = 1.0f;

    DroneMatrix<3, 1, float> x_k;
    x_k(0, 0) = 10.0f;
    x_k(1, 0) = 2.0f;
    x_k(2, 0) = 0.1f;

    DroneMatrix<3, 1, float> x_next = A * x_k;

    x_next.print();

    return 0;
}
        }
    }
}
