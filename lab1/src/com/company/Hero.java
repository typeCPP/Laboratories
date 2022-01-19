package com.company;

public class Hero {
    private float speed = 0.0f;
    private MovingStrategy strategy = new WalkingStrategy();

    void setMovingStrategy(MovingStrategy strategy) {
        this.strategy = strategy;
    }

    void move() {
        speed = strategy.moveHero();
        System.out.println("Current hero speed is " + speed + "f");
    }
}
