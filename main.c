#include <stddef.h>
#include <stdint.h>

typedef struct {
    size_t rows;
    size_t cols;
    float *data;
} Matrix;

void mat_fill(Matrix *m, float value) {
    for (size_t i = 0; i < m->rows * m->cols; ++i) {
        m->data[i] = value;
    }
}

void mat_add(const Matrix *a, const Matrix *b, Matrix *out) {
    for (size_t i = 0; i < a->rows * a->cols; ++i) {
        out->data[i] = a->data[i] + b->data[i];
    }
}

void mat_mul(const Matrix *a, const Matrix *b, Matrix *out) {
    for (size_t i = 0; i < out->rows * out->cols; ++i) {
        out->data[i] = 0.0f;
    }

    for (size_t i = 0; i < a->rows; ++i) {
        for (size_t k = 0; k < a->cols; ++k) {
            for (size_t j = 0; j < b->cols; ++j) {
                out->data[i * b->cols + j] += 
                    a->data[i * a->cols + k] * b->data[k * b->cols + j];
            }
        }
    }
}
