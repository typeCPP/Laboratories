package com.company;

public class Main {

    public static void main(String[] args) {
        Hero hero = new Hero();
        System.out.println("Setting current strategy as walking.");
        hero.setMovingStrategy(new WalkingStrategy());
        hero.move();

        System.out.println("\nSetting current strategy as horse riding.");
        hero.setMovingStrategy(new HorseStrategy());
        hero.move();

        System.out.println("\nSetting current strategy as flying.");
        hero.setMovingStrategy(new FlyingStrategy());
        hero.move();
    }
}
