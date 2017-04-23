package com.yandex;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeOptions;
import org.openqa.selenium.remote.DesiredCapabilities;

import java.util.Arrays;

/**
 * Created by Vika-PC on 08.04.2017.
 */
public class WebDriverFactory {

    private static WebDriver driver;

/*    public static void startBrowser() {
        System.setProperty("webdriver.chrome.driver", "C:\\Users\\Vika-PC\\Documents\\chrome\\chromedriver.exe");
        driver = new ChromeDriver(DesiredCapabilities.chrome());
    }*/

    public static void startBrowser() {
        System.setProperty("webdriver.chrome.driver", "C:\\Users\\Vika-PC\\Documents\\chrome\\chromedriver.exe");
        ChromeOptions options = new ChromeOptions();
        options.addArguments("-incognito");
        options.addArguments("--start-maximized");
        DesiredCapabilities capabilities = DesiredCapabilities.chrome();
        capabilities.setCapability(ChromeOptions.CAPABILITY, options);
        driver=new ChromeDriver(capabilities);
    }

    public  static  void finishBrowser() {
        driver.quit();
    }

    public static WebDriver getDriver() {
        return driver;
    }
}
