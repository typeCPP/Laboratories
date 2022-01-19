package com.errors;

import java.io.IOException;

public class FileNotExistError extends IOException {
    public FileNotExistError(String message) {
        super(message);
    }
}
