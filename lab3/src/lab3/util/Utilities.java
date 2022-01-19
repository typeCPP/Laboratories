package lab3.util;

import lab3.animalClasses.*;

import java.util.Scanner;

public class Utilities {
    public static Class getClassByNumber(int number) {
        return switch (number) {
            case 1 -> Animals.class;
            case 2 -> Chordal.class;
            case 3 -> Mammals.class;
            case 4 -> Predatory.class;
            case 5 -> Feline.class;
            case 6 -> Cat.class;
            default -> Animals.class;
        };
    }

    public static int getUpperBoundFromUser() {
        System.out.println("Which class would you like to set as upper bound?\n" +
                "1. Animals\n" +
                "2. Chordal\n" +
                "3. Mammals\n" +
                "4. Predatory\n" +
                "5. Feline\n" +
                "6. Cat");
        return getNumberFromUser();
    }

    public static int getLowerBoundFromUser() {
        System.out.println("Which class would you like to set as lower bound?\n" +
                "1. Animals\n" +
                "2. Chordal\n" +
                "3. Mammals\n" +
                "4. Predatory\n" +
                "5. Feline\n" +
                "6. Cat");
        return getNumberFromUser();
    }

    public static int getNumberFromUser() {
        System.out.print("Enter your number: ");
        int input = 0;
        try {
            Scanner scanner = new Scanner(System.in);
            input = scanner.nextInt();
        } catch (Exception error) {
            return 0;
        }
        if (input < 1 || input > 6) {
            return 0;
        } else {
            return input;
        }
    }
}
