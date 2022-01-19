package lab5.test;

import lab5.StreamMethods;
import org.junit.jupiter.api.Assertions;

import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class StreamMethodsTest {

    @org.junit.jupiter.api.Test
    void getAverageFromList() {
        ArrayList<Integer> list = new ArrayList<>();
        Assertions.assertEquals(0, StreamMethods.getAverageFromList(list));
        list.add(1);
        list.add(5);
        list.add(6);
        assertEquals(4, StreamMethods.getAverageFromList(list));
    }

    @org.junit.jupiter.api.Test
    void addPrefixToStringList() {
        ArrayList<String> list = new ArrayList<>();
        assertThrows(IllegalArgumentException.class, () -> StreamMethods.addPrefixToStringList(list));
        list.add("firstString");
        list.add("secondString");
        list.add("thirdString");
        ArrayList<String> expectedList = new ArrayList<>();
        expectedList.add("_new_" + "FIRSTSTRING");
        expectedList.add("_new_" + "SECONDSTRING");
        expectedList.add("_new_" + "THIRDSTRING");

        assertEquals(expectedList, StreamMethods.addPrefixToStringList(list));
    }

    @org.junit.jupiter.api.Test
    void getSquaredArrayListOfUniqueElements() {
        ArrayList<Double> list = new ArrayList<>();
        assertThrows(IllegalArgumentException.class, () -> StreamMethods.getSquaredArrayListOfUniqueElements(list));
        list.add(5.0);
        list.add(5.0);
        list.add(4.0);
        ArrayList<Double> expectedList = new ArrayList<>();
        expectedList.add(25.0);
        expectedList.add(16.0);

        assertEquals(expectedList, StreamMethods.getSquaredArrayListOfUniqueElements(list));
    }

    @org.junit.jupiter.api.Test
    void getSortedStringList() {
        ArrayList<String> list = new ArrayList<>();
        assertThrows(IllegalArgumentException.class, () -> StreamMethods.getSortedStringList(list, 'q'));
        list.add("qwerty");
        list.add("qasdfg");
        list.add("zxczxc");
        ArrayList<String> expectedList = new ArrayList<>();
        expectedList.add("qasdfg");
        expectedList.add("qwerty");

        assertEquals(expectedList, StreamMethods.getSortedStringList(list, 'q'));
    }

    @org.junit.jupiter.api.Test
    void getLastElement() {
        ArrayList<Integer> list = new ArrayList<>();
        assertThrows(IllegalArgumentException.class, () -> StreamMethods.getLastElement(list));
        list.add(5);
        list.add(6);
        list.add(7);

        assertEquals(7, StreamMethods.getLastElement(list));
    }

    @org.junit.jupiter.api.Test
    void getSumOfEvenNumbers() {
        int[] emptyArray = new int[5];
        assertEquals(0, StreamMethods.getSumOfEvenNumbers(emptyArray));

        int[] filledArray = new int[]{1, 2, 3, 4, 5};
        assertEquals(6, StreamMethods.getSumOfEvenNumbers(filledArray));

        int[] arrayWithoutEvenNumbers = new int[]{1,3,5,7,9};
        assertEquals(0, StreamMethods.getSumOfEvenNumbers(arrayWithoutEvenNumbers));
    }

    @org.junit.jupiter.api.Test
    void convertListToMap() {
        ArrayList<String> list = new ArrayList<>();
        Map<String, String> expectedMap = new TreeMap<String, String>();
        assertEquals(expectedMap, StreamMethods.convertListToMap(list));

        list.add("qwe");
        list.add("asd");
        list.add("zxc");

        expectedMap.put("q", "we");
        expectedMap.put("a", "sd");
        expectedMap.put("z", "xc");

        assertEquals(expectedMap, StreamMethods.convertListToMap(list));
    }
}