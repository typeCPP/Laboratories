package com.test;

import com.errors.MatrixSizeError;
import com.main.*;
import org.junit.Test;

import java.io.File;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

import static org.junit.jupiter.api.Assertions.*;

public class MainTest {

    final int TEST_MATRIX_SIZE = 5;

    @Test
    public void testBuildMatrix() throws Exception {
        double[][] testMatrix = MatrixOperations.buildMatrix(TEST_MATRIX_SIZE);

        assertEquals(TEST_MATRIX_SIZE, testMatrix.length);
        assertThrows(MatrixSizeError.class, () -> MatrixOperations.buildMatrix(1000000));
        assertThrows(MatrixSizeError.class, () -> MatrixOperations.buildMatrix(1));
        assertThrows(OutOfMemoryError.class, () -> MatrixOperations.buildMatrix(999000));
    }

    @Test
    public void testRotateMatrix90() throws Exception {
        double[][] testMatrix = MatrixOperations.buildMatrix(TEST_MATRIX_SIZE);
        double[][] unrotatedMatrix = new double[TEST_MATRIX_SIZE][TEST_MATRIX_SIZE];
        MatrixOperations.copyMatrix(testMatrix, unrotatedMatrix);
        MatrixOperations.rotateMatrix90(testMatrix);
        for (int i = 0; i < testMatrix.length; i++) {
            for (int j = 0; j < testMatrix.length; j++) {
                assertEquals(unrotatedMatrix[j][testMatrix.length - i - 1], testMatrix[i][j]);
            }
        }
    }

    @Test
    public void testDivideMatrixElements() throws Exception {
        double[][] testMatrix = {{10, 20}, {30, 40}};
        MatrixOperations.divideMatrixElements(testMatrix);
        assertEquals(10.0 / 50.0, testMatrix[0][0]);
        assertEquals(20.0 / 50.0, testMatrix[0][1]);
        assertEquals(30.0 / 50.0, testMatrix[1][0]);
        assertEquals(40.0 / 50.0, testMatrix[1][1]);
    }

    @Test
    public void testParsingFromFile() throws Exception {
        final String TEST_FILE_NAME = "text.txt";
        final String TEST_LINE = "5";

        //create file and fill it with sample text
        File testFile = new File(TEST_FILE_NAME);
        testFile.createNewFile();
        Path path = Path.of(TEST_FILE_NAME);
        OutputStream outputStream = Files.newOutputStream(path);
        outputStream.write(TEST_LINE.getBytes(StandardCharsets.UTF_8));
        outputStream.close();

        assertEquals(TEST_MATRIX_SIZE, Main.parseSizeFromInputFile(TEST_FILE_NAME));
        testFile.delete();
    }

    @Test
    public void testCleanFile() throws Exception {
        final String TEST_FILE_NAME = "text.txt";
        final String TEST_LINE = "TEST TEST TEST\n";

        //create file and fill it with sample text
        File testFile = new File(TEST_FILE_NAME);
        testFile.createNewFile();
        Path path = Path.of(TEST_FILE_NAME);
        OutputStream outputStream = Files.newOutputStream(path);
        outputStream.write(TEST_LINE.getBytes(StandardCharsets.UTF_8));
        outputStream.close();
        //execute cleaning
        Main.cleanFile(TEST_FILE_NAME);
        //check if it's clean
        InputStream inputStream = Files.newInputStream(path);
        assertEquals(-1, inputStream.read());
        inputStream.close();
        testFile.delete();
    }

} 
