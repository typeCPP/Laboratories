package lab5;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Map;
import java.util.stream.Collectors;

public class StreamMethods {
    public static double getAverageFromList(ArrayList<Integer> list) {
        if (list.isEmpty()) {
            return 0;
        }
        return list.stream().mapToDouble(n -> n).sum() / list.size();
    }

    public static ArrayList<String> addPrefixToStringList(ArrayList<String> list) {
        if (list.isEmpty()) {
            throw new IllegalArgumentException("List is empty");
        }
        return (ArrayList<String>) list.stream().map(String::toUpperCase).map(n -> "_new_" + n)
                .collect(Collectors.toList());
    }

    public static ArrayList<Double> getSquaredArrayListOfUniqueElements(ArrayList<Double> list) {
        if (list.isEmpty()) {
            throw new IllegalArgumentException("List is empty");
        }
        return (ArrayList<Double>) list.stream().distinct().map(n -> n * n).collect(Collectors.toList());
    }

    public static ArrayList<String> getSortedStringList(ArrayList<String> list, char startingLetter) {
        if (list.isEmpty()) {
            throw new IllegalArgumentException("List is empty");
        }
        return (ArrayList<String>) list.stream().filter(n -> n.charAt(0) == startingLetter).sorted()
                .collect(Collectors.toList());
    }

    public static Object getLastElement(Collection collection) throws IllegalArgumentException {
        if (collection.isEmpty()) {
            throw new IllegalArgumentException("Collection is empty");
        }
        return collection.stream().toArray()[collection.size() - 1];
    }

    public static int getSumOfEvenNumbers(int[] array) {
        return Arrays.stream(array).filter(n -> n % 2 == 0).sum();
    }

    public static Map<String, String> convertListToMap(ArrayList<String> list) {
        return list.stream().collect(Collectors.toMap(n -> n.substring(0, 1), n -> n.substring(1)));
    }
}
