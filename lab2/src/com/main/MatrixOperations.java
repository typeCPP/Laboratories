package com.main;

import com.errors.DivideByZeroError;
import com.errors.MatrixSizeError;

import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.text.DecimalFormat;

public class MatrixOperations {
    public static double[][] buildMatrix(int n) throws MatrixSizeError, OutOfMemoryError {
        if (n >= 1000000 || n < 2) {
            throw new MatrixSizeError("Wrong matrix size");
        }
        double[][] matrix = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = Math.random() * (n + 1);
                if (Math.random() < 0.5) {
                    matrix[i][j] = matrix[i][j] * -1; //choose positive or negative
                }
            }
        }
        return matrix;
    }

    public static void rotateMatrix90(double[][] matrix) {
        double[][] tempMatrix = new double[matrix.length][matrix.length];
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length; j++) {
                tempMatrix[i][j] = matrix[j][matrix.length - i - 1];
            }
        }
        copyMatrix(tempMatrix, matrix);
    }

    public static void divideMatrixElements(double[][] matrix) throws DivideByZeroError {
        double[][] tempMatrix = new double[matrix.length][matrix.length];

        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix.length; j++) {
                double sumOfNearest = 0;
                if (i > 0) sumOfNearest += matrix[i - 1][j];
                if (i < matrix.length - 1) sumOfNearest += matrix[i + 1][j];
                if (j > 0) sumOfNearest += matrix[i][j - 1];
                if (j < matrix.length - 1) sumOfNearest += matrix[i][j + 1];

                if (sumOfNearest != 0) {
                    tempMatrix[i][j] = matrix[i][j] / sumOfNearest;
                } else {
                    throw new DivideByZeroError("Dividing by zero");
                }
            }
        }
        copyMatrix(tempMatrix, matrix);
    }

    public static void copyMatrix(double[][] source, double[][] copyTo) {
        if (source.length != copyTo.length) {
            return;
        }
        for (int i = 0; i < source.length; i++) {
            for (int j = 0; j < source.length; j++) {
                copyTo[i][j] = source[i][j];
            }
        }
    }

    public static void writeMatrixInOutputFile(double[][] matrix) throws IOException {
        File output = new File("out.txt");
        output.createNewFile();

        Path outPath = Path.of("out.txt");
        try (OutputStream outputStream = Files.newOutputStream(outPath, StandardOpenOption.APPEND)) {
            StringBuilder line = new StringBuilder();
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix.length; j++) {
                    String formattedNumber = new DecimalFormat("#0.00").format(matrix[i][j]);
                    line.append(formattedNumber);
                    line.append(' ');
                    if (j == matrix.length - 1) {
                        line.append('\n');
                    }
                }
            }
            line.append('\n');
            outputStream.write(line.toString().getBytes(StandardCharsets.UTF_8));
        }
    }
}
