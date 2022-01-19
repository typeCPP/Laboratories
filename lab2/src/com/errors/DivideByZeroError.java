package com.errors;

public class DivideByZeroError extends RuntimeException {
    public DivideByZeroError(String message) {
        super(message);
    }
}
