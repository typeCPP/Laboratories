package lab5;

import java.util.ArrayList;
import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        try {
            executeTask();
        } catch (Exception error) {
            error.printStackTrace();
            System.exit(2);
        }
    }

    public static void executeTask() {
        ArrayList<Integer> integerArrayList = new ArrayList<>();
        integerArrayList.add(1);
        integerArrayList.add(5);
        integerArrayList.add(6);
        System.out.println("Integer array list is: " + integerArrayList);
        System.out.println("Average from integer array list: " + StreamMethods.getAverageFromList(integerArrayList));

        ArrayList<String> stringArrayList = new ArrayList<>();
        stringArrayList.add("qwe");
        stringArrayList.add("drt");
        stringArrayList.add("asd");
        stringArrayList.add("zxc");
        System.out.println("\nString array list is: " + stringArrayList);
        System.out.println("String array list after prefix addition: "
                + StreamMethods.addPrefixToStringList(stringArrayList));

        ArrayList<Double> doubleArrayList = new ArrayList<>();
        doubleArrayList.add(5.0);
        doubleArrayList.add(5.0);
        doubleArrayList.add(5.0);
        doubleArrayList.add(6.0);
        System.out.println("\nDouble array list is: " + doubleArrayList);
        System.out.println("Double array list after squaring unique elements: "
                + StreamMethods.getSquaredArrayListOfUniqueElements(doubleArrayList));

        final char START_LETTER = 'q';
        System.out.println("\nString array list is: " + stringArrayList);
        System.out.print("Sorted string array list with words starting with letter " + START_LETTER + ": ");
        System.out.println(StreamMethods.getSortedStringList(stringArrayList, START_LETTER));

        System.out.println("\nInteger array list: " + integerArrayList);
        System.out.println("Getting last element from the collection: " + StreamMethods.getLastElement(integerArrayList));

        int[] integerArray = new int[]{1, 2, 3, 4, 5, 6};
        System.out.println("\nInteger array is: " + Arrays.toString(integerArray));
        System.out.println("Sum of even numbers in this array: " + StreamMethods.getSumOfEvenNumbers(integerArray));

        System.out.println("\nString array list is: " + stringArrayList);
        System.out.println("Map from the list is: " + StreamMethods.convertListToMap(stringArrayList));
    }
}
