package com.main;

import com.errors.DivideByZeroError;
import com.errors.FileNotExistError;
import com.errors.MatrixSizeError;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;

public class Main {
    public static void main(String[] args) {
        try {
            executeTask();
        } catch (FileNotExistError | DivideByZeroError | MatrixSizeError error) {
            error.printStackTrace();
            System.exit(1);
        } catch (OutOfMemoryError | NumberFormatException | IOException error) {
            error.printStackTrace();
            System.exit(2);
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(3);
        }
    }

    public static void executeTask() throws Exception {
        int size = parseSizeFromInputFile("input.txt");

        double[][] firstMatrix = MatrixOperations.buildMatrix(size);
        double[][] secondMatrix = new double[firstMatrix.length][firstMatrix.length];
        double[][] thirdMatrix = new double[firstMatrix.length][firstMatrix.length];
        MatrixOperations.copyMatrix(firstMatrix, secondMatrix);
        MatrixOperations.copyMatrix(firstMatrix, thirdMatrix);

        cleanFile("out.txt");
        MatrixOperations.rotateMatrix90(firstMatrix); //rotate by 90 from start
        MatrixOperations.divideMatrixElements(firstMatrix);
        MatrixOperations.writeMatrixInOutputFile(firstMatrix);

        MatrixOperations.rotateMatrix90(secondMatrix); //rotate by 180 from start
        MatrixOperations.rotateMatrix90(secondMatrix);
        MatrixOperations.divideMatrixElements(secondMatrix);
        MatrixOperations.writeMatrixInOutputFile(secondMatrix);

        MatrixOperations.rotateMatrix90(thirdMatrix); //rotate by 270 from start
        MatrixOperations.rotateMatrix90(thirdMatrix);
        MatrixOperations.rotateMatrix90(thirdMatrix);
        MatrixOperations.divideMatrixElements(thirdMatrix);
        MatrixOperations.writeMatrixInOutputFile(thirdMatrix);
    }

    public static int parseSizeFromInputFile(String fileName) throws FileNotExistError, IOException, NumberFormatException {
        final int ASCII_CODE_OF_1 = 48;
        final int ASCII_CODE_OF_9 = 57;
        StringBuilder sb = new StringBuilder();
        File input = new File(fileName);
        if (!input.exists()) {
            throw new FileNotExistError("Input file does not exist");
        }
        Path path = Path.of(fileName);
        try (InputStream inputStream = Files.newInputStream(path)) {

            int symbol = ASCII_CODE_OF_1 - 1;
            while ((symbol = inputStream.read()) != -1 && symbol >= ASCII_CODE_OF_1 && symbol <= ASCII_CODE_OF_9) {
                sb.append((char) symbol);
            }
            if (inputStream.read() != -1) {
                throw new IllegalArgumentException("File contains wrong data");
            }
        }
        return Integer.parseInt(sb.toString());
    }


    public static void cleanFile(String name) throws IOException {
        Path outPath = Path.of(name);
        OutputStream outputStream = Files.newOutputStream(outPath);
        outputStream.close();
    }

}
