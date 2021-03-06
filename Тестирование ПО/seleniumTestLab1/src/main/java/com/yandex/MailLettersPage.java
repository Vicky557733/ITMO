package com.yandex;

import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.interactions.Actions;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.PageFactory;

import static java.lang.Thread.sleep;

public class MailLettersPage {

    @FindBy(className = "mail-User-Name")
    private WebElement mailUserName;

    @FindBy(xpath = "//a[@data-metric=\"Меню сервисов:Выход\"]")
    private WebElement tabExit;

    @FindBy(xpath = "//a[@data-metric=\"Меню сервисов:Сменить пароль\"]")
    private WebElement tabChangePassword;

    @FindBy(className = "ns-view-toolbar-button-compose-go")
    private WebElement tabWrite;

    @FindBy(className = "mail-Toolbar-Item_check-mail")
    private WebElement tabCheck;

    @FindBy(className = "mail-Toolbar-Item_delete")
    private WebElement tabDelete;

    @FindBy(className = "mail-Layout-Panes")
    private static WebElement searchLetter;

    @FindBy(className = "mail-Search-Input")
    private static WebElement searchFocus;

    @FindBy(className = "ns-view-messages-list-box")
    private static WebElement letters;

    @FindBy(className = "mail-Search-Button")
    private static WebElement buttonSearchLetter;

    @FindBy(className = "mail-Toolbar-Item-Checkbox")
    private static WebElement checkLettersForDelete;

//    @FindBy(className = "mail-NestedList-Item_current")
    @FindBy(css = ".ns-view-folder:nth-child(5)")
    private static WebElement goToDraft;

    @FindBy(css = ".ns-view-folder:nth-child(1)")
    private static WebElement goToInbox;

    @FindBy(css = ".ns-view-folder:nth-child(3)")
    private static WebElement goToDelete;

//    @FindBy(className = "_nb-checkbox-input")
   // @FindBy(css=".mail-MessageList > div:nth-child(2) input[type=checkbox]")
    @FindBy(className = "mail-MessageSnippet-Checkbox-Nb")
    private WebElement checkboxForMarkLetter;

    @FindBy(className = "ns-view-toolbar-button-delete")
    private WebElement deleteLetter;

    @FindBy(className = "mail-Toolbar-Item_add-template")
    private WebElement createTemplate;

    public MailLettersPage() {
        PageFactory.initElements(WebDriverFactory.getDriver(), this);
        waitForPageToLoad();
    }

    public void clickGoToDraft(){
        goToDraft.click();
        waitForCreateTemplateToLoad();
    }

    public void clickGoToInbox(){
        goToInbox.click();
        waitForPageToLoad();
    }

    public void clickGoToDelete(){
        goToDelete.click();
        waitForPageToLoad();
        try {
            sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void clickCheckLetters(){
        tabCheck.click();
        waitForPageToLoad();
    }

    public void clickCheckLettersForDelete(){
        checkLettersForDelete.click();
        tabDelete.click();
    }

    public MailWriteLetterPage clickCreateTemplate(){
        createTemplate.click();
        return new MailWriteLetterPage();
    }

    public void clickSearchLetter(){
        buttonSearchLetter.click();
        waitForTabWriteToLoad();
    }

    public void clickDeleteLetter(){
        deleteLetter.click();
        try {
            sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void selectCheckbox() {
/*        WebElement e = WebDriverFactory.getDriver().findElement(By.cssSelector(".mail-MessageList > div:nth-child(2) input[type=checkbox]"));
        System.out.println(e);
        e.click();*/

        checkboxForMarkLetter.click();

        //if (checkboxForMarkLetter.getAttribute("checked") != null)
          //  checkboxForMarkLetter.click();
    }

    public static void insertSearchLetter(String text) {
        Actions actions = new Actions(WebDriverFactory.getDriver());
        actions.moveToElement(searchFocus);
        actions.click();
        actions.sendKeys(text);
        actions.build().perform();
        buttonSearchLetter.click();
        try {
            sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

/*        searchFocus.click();
        searchFocus.sendKeys(text);*/
    }

    public void clickMailUserName(){
        mailUserName.click();
        waitForTabExitToLoad();
    }

    public MailChangeData changePassword() {
        clickMailUserName();
        tabChangePassword.click();
        return new MailChangeData();
    }

    public void logout(){
        clickMailUserName();
        tabExit.click();
        //dropdown.click();
        //mailExit.click();
    }

    protected void waitForTabExitToLoad() {
        int secondsCount = 0;
        boolean isPageOpenedIndicator = isTabExitDisplayed();
        while (!isPageOpenedIndicator && secondsCount < 10) {
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            secondsCount++;
            isPageOpenedIndicator = isTabExitDisplayed();
        }
        if (!isPageOpenedIndicator) {
            throw new AssertionError("tab exit was not opened");
        }
    }

    private boolean isCreateTemplateDisplayed(){
        try {
            return createTemplate.isDisplayed();
        } catch (NoSuchElementException e){
            return false;
        }
    }

    protected void waitForCreateTemplateToLoad() {
        int secondsCount = 0;
        boolean isPageOpenedIndicator = isCreateTemplateDisplayed();
        while (!isPageOpenedIndicator && secondsCount < 10) {
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            secondsCount++;
            isPageOpenedIndicator = isCreateTemplateDisplayed();
        }
        if (!isPageOpenedIndicator) {
            throw new AssertionError("Create template was not opened");
        }
    }

    private boolean isTabExitDisplayed(){
        try {
            return tabExit.isDisplayed();
        } catch (NoSuchElementException e){
            return false;
        }
    }

    protected void waitForPageToLoad() {
        int secondsCount = 0;
        boolean isPageOpenedIndicator = isLettersDisplayed();
        while (!isPageOpenedIndicator && secondsCount < 40) {
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            secondsCount++;
            isPageOpenedIndicator = isLettersDisplayed();
        }
        if (!isPageOpenedIndicator) {
            throw new AssertionError("Page was not opened");
        }
    }

    private boolean isLettersDisplayed(){
        try {
            return letters.isDisplayed();
        } catch (NoSuchElementException e){
            return false;
        }
    }

    private boolean isTabWriteDisplayed(){
        try {
            return tabWrite.isDisplayed();
        } catch (NoSuchElementException e){
            return false;
        }
    }

    protected void waitForTabWriteToLoad() {
        int secondsCount = 0;
        boolean isPageOpenedIndicator = isTabWriteDisplayed();
        while (!isPageOpenedIndicator && secondsCount < 20) {
            try {
                sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            secondsCount++;
            isPageOpenedIndicator = isTabWriteDisplayed();
        }
        if (!isPageOpenedIndicator) {
            throw new AssertionError("tab write was not opened");
        }
    }


    private boolean isMailUserDisplayed(){
        try {
            return mailUserName.isDisplayed();
        } catch (NoSuchElementException e){
            return false;
        }
    }

    public MailWriteLetterPage clickWriteToLetter(){
        tabWrite.click();
        return new MailWriteLetterPage();
    }
}
