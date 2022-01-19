package lab4.main;

import lab4.annotations.Repeat;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class Main {

    public static void main(String[] args) {
        try {
            executeTask();
        } catch (Exception error) {
            error.printStackTrace();
            System.exit(2);
        }
    }

    public static void executeTask() throws InvocationTargetException, IllegalAccessException {
        Animal animal = new Animal();
        int counter = 0;
        for (Method animalMethod : animal.getClass().getDeclaredMethods()) {
            animalMethod.setAccessible(true);
            if (animalMethod.isAnnotationPresent(Repeat.class)) {
                counter = animalMethod.getAnnotation(Repeat.class).value();
                for (int i = 0; i < counter; i++) {
                    animalMethod.invoke(animal);
                }
            }
        }
    }
}
