#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

Matrix *matrix_create(size_t rows, size_t cols) {
    Matrix *m = malloc(sizeof(Matrix));
    if (!m) return NULL;
    m->rows = rows;
    m->cols = cols;
    m->data = calloc(rows * cols, sizeof(double));
    if (!m->data) {
        free(m);
        return NULL;
    }
    return m;
}

void matrix_free(Matrix *m) {
    if (!m) return;
    free(m->data);
    free(m);
}

double matrix_get(const Matrix *m, size_t i, size_t j) {
    return m->data[i * m->cols + j];
}

void matrix_set(Matrix *m, size_t i, size_t j, double val) {
    m->data[i * m->cols + j] = val;
}

Matrix *matrix_add(const Matrix *a, const Matrix *b) {
    if (!a || !b || a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *r = matrix_create(a->rows, a->cols);
    if (!r) return NULL;
    for (size_t i = 0; i < a->rows * a->cols; i++) r->data[i] = a->data[i] + b->data[i];
    return r;
}

Matrix *matrix_sub(const Matrix *a, const Matrix *b) {
    if (!a || !b || a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *r = matrix_create(a->rows, a->cols);
    if (!r) return NULL;
    for (size_t i = 0; i < a->rows * a->cols; i++) r->data[i] = a->data[i] - b->data[i];
    return r;
}

Matrix *matrix_mul(const Matrix *a, const Matrix *b) {
    if (!a || !b || a->cols != b->rows) return NULL;
    Matrix *r = matrix_create(a->rows, b->cols);
    if (!r) return NULL;
    for (size_t i = 0; i < a->rows; i++) {
        for (size_t j = 0; j < b->cols; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < a->cols; k++) sum += matrix_get(a, i, k) * matrix_get(b, k, j);
            matrix_set(r, i, j, sum);
        }
    }
    return r;
}

Matrix *matrix_transpose(const Matrix *a) {
    if (!a) return NULL;
    Matrix *r = matrix_create(a->cols, a->rows);
    if (!r) return NULL;
    for (size_t i = 0; i < a->rows; i++) for (size_t j = 0; j < a->cols; j++) matrix_set(r, j, i, matrix_get(a, i, j));
    return r;
}

Matrix *matrix_identity(size_t n) {
    Matrix *m = matrix_create(n, n);
    if (!m) return NULL;
    for (size_t i = 0; i < n; i++) matrix_set(m, i, i, 1.0);
    return m;
}

double matrix_det(const Matrix *a) {
    if (!a || a->rows != a->cols) return 0.0;
    size_t n = a->rows;
    Matrix *t = matrix_create(n, n);
    if (!t) return 0.0;
    for (size_t i = 0; i < n * n; i++) t->data[i] = a->data[i];
    double det = 1.0;
    for (size_t i = 0; i < n; i++) {
        if (matrix_get(t, i, i) == 0.0) { matrix_free(t); return 0.0; }
        for (size_t j = i + 1; j < n; j++) {
            double r = matrix_get(t, j, i) / matrix_get(t, i, i);
            for (size_t k = 0; k < n; k++) matrix_set(t, j, k, matrix_get(t, j, k) - r * matrix_get(t, i, k));
        }
        det *= matrix_get(t, i, i);
    }
    matrix_free(t);
    return det;
}

void matrix_print(const Matrix *m) {
    if (!m) return;
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) printf("%.2f ", matrix_get(m, i, j));
        printf("\n");
    }
}


