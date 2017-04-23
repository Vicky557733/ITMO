package com.webdriver;

import org.junit.Assert;
import org.junit.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;

/**
 * Created by Vika-PC on 08.04.2017.
 */
public class FirstTest {
    //We should add @Test annotation that JUnit will run below method
    @Test
    //Start to write our test method. It should ends with "Test"
    public void chromeTest(){

        System.setProperty("webdriver.chrome.driver", "C:\\Users\\Vika-PC\\Documents\\chrome\\chromedriver.exe");

        WebDriver chromeDriver = new ChromeDriver();
        chromeDriver.get("http://de.ifmo.ru");
        chromeDriver.findElement(By.className("p-right")).click();
        chromeDriver.findElement(By.id("login")).sendKeys("");
        chromeDriver.findElement(By.id("password")).sendKeys("");
        //chromeDriver.findElement(By.xpath("//input[@type='submit']")).click();
        chromeDriver.findElement(By.cssSelector("input[type='submit']")).click();
        //  chromeDriver.quit();
    }
}