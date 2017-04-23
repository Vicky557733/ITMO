package com.yandex;


import org.junit.Assert;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import java.util.concurrent.TimeUnit;

/**
 * Created by Vika-PC on 08.04.2017.
 */
public class MailPage {
    @FindBy(className = "domik2__link")
    private WebElement tabMail;

    @FindBy(className = "domik2__auth-button")
    private WebElement submitButton;

    @FindBy(className = "domik2__mail-promo")
    private static WebElement goToRegister;

    @FindBy(name = "login")
    private static WebElement loginField;

    @FindBy(name = "passwd")
    private static WebElement passwordField;


    public MailPage() {
        WebDriverFactory.getDriver().get("http://yandex.ru");
        PageFactory.initElements(WebDriverFactory.getDriver(), this);
        waitForPageToLoad();
        //tabMail.click();
    }

    protected void waitForPageToLoad() {
        int secondsCount = 0;
        boolean isPageOpenedIndicator = isSearchStringDisplayed();
        while (!isPageOpenedIndicator && secondsCount < 5) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            secondsCount++;
            isPageOpenedIndicator = isSearchStringDisplayed();
        }
        if (!isPageOpenedIndicator) {
            throw new AssertionError("Page was not opened");
        }
    }

    private boolean isSearchStringDisplayed(){
        try {
            return tabMail.isDisplayed();
        } catch (NoSuchElementException e){
            return false;
        }
    }

    public static void insertLogin(String text) {
        loginField.sendKeys(text);
    }

    public static void insertPassword(String text) {
        passwordField.sendKeys(text);
    }


/*    public void clickLogin(){
        submitButton.click();
    }*/
public MailLettersPage clickLogin(){
    submitButton.click();
    WebDriverFactory.getDriver().manage().timeouts().pageLoadTimeout(10, TimeUnit.SECONDS);
    if (WebDriverFactory.getDriver().getTitle().toLowerCase().contains("авторизация"))
        return null;
    return new MailLettersPage();
}
}

