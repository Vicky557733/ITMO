package com.webdriver;

import com.yandex.*;
import org.junit.Assert;
import org.junit.Test;
import org.junit.After;
import org.junit.Before;

/**
 * Created by Vika-PC on 08.04.2017.
 */
public class MailTest {

    @Before
    public void beforeTest() {
        WebDriverFactory.startBrowser();
    }

    @Test
    public void checkLoginError() {
        String textForLogin = "error";
        String textForPassword = "error";
        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        MailLettersPage mailLettersPage = mailPage.clickLogin();
        Assert.assertEquals(null, mailLettersPage);
        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());
    }

    @Test
    public void checkLogin() {
        String textForLogin = " ";
        String textForPassword = " ";
        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        //mailPage.clickLogin();
        MailLettersPage mailLettersPage = mailPage.clickLogin();
        Assert.assertNotEquals(null, mailLettersPage);
        mailLettersPage.logout();
        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());
    }

    @Test
    public void checkWriteLetter() {
        String textForLogin = " ";
        String textForToInput = " @yandex.ru";
        String textForPassword = " ";
        String textForSubject = "Ку-ку";
        String textForTextLetter = "Привет!";
        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        MailLettersPage mailLettersPage = mailPage.clickLogin();

        //write letter
        MailWriteLetterPage mailWriteLetterPage = mailLettersPage.clickWriteToLetter();
        mailWriteLetterPage.insertTo(textForToInput);
        mailWriteLetterPage.insertSubject(textForSubject);
        mailWriteLetterPage.insertTextLetter(textForTextLetter);
        mailLettersPage = mailWriteLetterPage.clickWriteLetter();
       // mailLettersPage.insertSearchLetter(textForSubject);
        mailLettersPage.logout();
        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());
    }

    @Test
    public void checkSearchLetter() {
        String textForLogin = " ";
        String textForToInput = " @yandex.ru";
        String textForPassword = " ";
        String textForSubject = "Ку-ку";
        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        //mailPage.clickLogin();
        MailLettersPage mailLettersPage = mailPage.clickLogin();
        mailLettersPage.insertSearchLetter(textForSubject);
        mailLettersPage.logout();

        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());
    }


    @Test
    public void checkChangeInformation() {
        String textForLogin = " ";
        String textForPassword = " ";
        String textForNewName = "Виктория";

        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        MailLettersPage mailLettersPage = mailPage.clickLogin();
        //write letter
        mailLettersPage.clickGoToInbox();
        MailChangeData mailChangeData = mailLettersPage.changePassword();
        mailChangeData.clickChangePersonalInformation();
        mailChangeData.clickInsertNewName(textForNewName);
        //mailLettersPage.logout();

        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());
    }

    // проверить

/*
    @Test
    public void checkLogin() {
        String textForLogin = " ";
        String textForPassword = " ";
        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        //mailPage.clickLogin();
        MailLettersPage mailLettersPage = mailPage.clickLogin();
        //write letter
        mailLettersPage.clickGoToInbox();
        mailLettersPage.clickCheckLetters();
        mailLettersPage.clickGoToDelete();
        mailLettersPage.clickCheckLettersForDelete();


        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());

        // mailLettersPage.logout();
    }
*/

    @Test
    public void checkDeleteLetters() {
        String textForLogin = " ";
        String textForPassword = " ";
        String textForSubject = "Ку-ку";


        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        MailLettersPage mailLettersPage = mailPage.clickLogin();

        mailLettersPage.clickGoToInbox();
        mailLettersPage.insertSearchLetter(textForSubject);
        mailLettersPage.clickSearchLetter();
        mailLettersPage.selectCheckbox();
        mailLettersPage.clickDeleteLetter();
        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());

        mailLettersPage.logout();
    }

    //создание шаблона
    @Test
    public void checkCreateTemplate() {
        String textForLogin = " ";
        String textForToInput = " @yandex.ru";
        String textForPassword = " ";
        String textForSubject = "Ку-ку";
        String textForTextLetter = "Привет!";

        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        MailLettersPage mailLettersPage = mailPage.clickLogin();

        mailLettersPage.clickGoToDraft();
        MailWriteLetterPage mailWriteLetterPage = mailLettersPage.clickCreateTemplate();
        mailWriteLetterPage.insertTo(textForToInput);
        mailWriteLetterPage.insertSubject(textForSubject);
        mailWriteLetterPage.insertTextLetter(textForTextLetter);
        mailLettersPage = mailWriteLetterPage.clickButtonSubmitSaveTemplate();
        mailLettersPage.clickGoToInbox();

        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());

        mailLettersPage.logout();
    }

    @Test
    public void checkDeleteLetter() {
        String textForLogin = " ";
        String textForPassword = " ";

        MailPage mailPage = new MailPage();
        mailPage.insertLogin(textForLogin);
        mailPage.insertPassword(textForPassword);
        MailLettersPage mailLettersPage = mailPage.clickLogin();

        mailLettersPage.selectCheckbox();
        mailLettersPage.clickDeleteLetter();
        System.out.println("Ending test " + new Object(){}.getClass().getEnclosingMethod().getName());

        mailLettersPage.logout();
    }


    @After
    public void afterTest() {
        WebDriverFactory.finishBrowser();
    }
}
