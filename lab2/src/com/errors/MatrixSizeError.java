package com.errors;

public class MatrixSizeError extends RuntimeException {
    public MatrixSizeError(String message) {
        super(message);
    }
}
