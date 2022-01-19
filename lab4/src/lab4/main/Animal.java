package lab4.main;

import lab4.annotations.Repeat;

public class Animal {

    @Repeat(3)
    private void makeSound() {
        System.out.println("Animal makes sound.");
    }

    @Repeat(2)
    private void jump() {
        System.out.println("Animal jumps.");
    }

    @Repeat
    private void drink() {
        System.out.println("Animal drinks.");
    }
}
