package com.yandex;

import org.junit.Assert;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;
import org.openqa.selenium.support.ui.ExpectedCondition;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.util.concurrent.TimeUnit;

/**
 * Created by Vika-PC on 09.04.2017.
 */
public class MailWriteLetterPage {
    @FindBy(className = "_nb-large-action-button")
    private WebElement buttonSubmitLetter;

    @FindBy(className = "ns-view-compose-save-link")
    private WebElement buttonSubmitSaveTemplate;

    @FindBy(name = "subj")
    private static WebElement inputSubject;

    @FindBy(className = "cke_enable_context_menu")
    private static WebElement inputTextLetter;

    @FindBy(name = "to")
    private static WebElement inputTo;

    @FindBy(className = "mail-Done-Title")
    private WebElement mailDoneLetter;

    public MailWriteLetterPage() {
        PageFactory.initElements(WebDriverFactory.getDriver(), this);
        waitForButtonSubmitLetterToLoad();
    }

    public MailLettersPage clickButtonSubmitSaveTemplate(){
        buttonSubmitSaveTemplate.click();
        return new MailLettersPage();
    }


    public static void insertTo(String text) {
        inputTo.sendKeys(text);
    }

    public static void insertSubject(String text) {
        inputSubject.sendKeys(text);
    }

    public static void insertTextLetter(String text) {
        inputTextLetter.sendKeys(text);
    }



    protected void waitForButtonSubmitLetterToLoad() {
        int secondsCount = 0;
        boolean isPageOpenedIndicator = isButtonSubmitLetterDisplayed();
        while (!isPageOpenedIndicator && secondsCount < 5) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            secondsCount++;
            isPageOpenedIndicator = isButtonSubmitLetterDisplayed();
        }
        if (!isPageOpenedIndicator) {
            throw new AssertionError("Button was not loaded");
        }
    }

    private boolean isButtonSubmitLetterDisplayed(){
        try {
            return buttonSubmitLetter.isDisplayed();
        } catch (NoSuchElementException e){
            return false;
        }
    }

    public MailLettersPage clickWriteLetter(){
        buttonSubmitLetter.click();
        //WebDriverFactory.getDriver().manage().timeouts().pageLoadTimeout(15, TimeUnit.SECONDS);
        Assert.assertTrue(letterIsDone());
        //WebDriverFactory.getDriver().manage().timeouts().implicitlyWait(15, TimeUnit.SECONDS);
        //WebDriverFactory.getDriver().manage().timeouts().pageLoadTimeout(15, TimeUnit.SECONDS);
        return new MailLettersPage();
    }

    public boolean letterIsDone(){
        WebDriverWait webDriverWait = new WebDriverWait(WebDriverFactory.getDriver(), 5);
        webDriverWait.until(ExpectedConditions.visibilityOf(mailDoneLetter));
        return mailDoneLetter.isDisplayed();
    }
}
