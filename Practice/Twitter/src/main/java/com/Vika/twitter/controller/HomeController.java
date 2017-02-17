package com.Vika.twitter.controller;

import com.Vika.twitter.models.Note;
import com.Vika.twitter.models.User;
import com.Vika.twitter.service.impl.NoteServiceImpl;
import com.Vika.twitter.service.impl.UserServiceImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.security.core.*;
import org.springframework.web.servlet.ModelAndView;

import java.security.Principal;
import java.util.*;

import static com.Vika.twitter.utils.Constants.PRELOAD_NOTE_COUNT;

@Controller
public class HomeController {

    @Autowired
    private UserServiceImpl userService;

    @Autowired
    private NoteServiceImpl noteService;

    @GetMapping(value={"/home", "/"})
    static String home() {return "home";}

    @GetMapping("/login")
    static String login(Model model) {System.out.println("get login !!!"); return "login";}

    @GetMapping("/secret")
    static String secret() {return "secret";}

    @GetMapping("/logged_user")
    public String logged_user(Model model, Principal principal) {
        System.out.println("get logged_user !!!");
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        System.out.println("username: " + auth.getName());
        HashMap<Long, Long> countNotes = new HashMap<>();

        Iterable<User> userRepositoryAll = userService.getAllUsers();

        Iterator<User> user_iterator = userRepositoryAll.iterator();
        User user;
        while(user_iterator.hasNext()) {
            user = user_iterator.next();
            if (user.getUsername().equals(principal.getName()))
                user_iterator.remove();
            else
                countNotes.put(user.getId(), noteService.countNotesByUser(user));
        }
        System.out.println(countNotes);

        int preloadNotesCounter = PRELOAD_NOTE_COUNT;

        List<Note> preloadNotes = new ArrayList<>();
        for(Note note : noteService.getAllNotes()) {
            preloadNotesCounter--;
            if (preloadNotesCounter < 0) {
                break;
            }
            preloadNotes.add(note);
        }

        model.addAttribute("users", userRepositoryAll);
        model.addAttribute("notes", preloadNotes);
        model.addAttribute("countNotes", countNotes);
        return "logged_user";
    }

    @RequestMapping(value = "/admin**", method = RequestMethod.GET)
    public ModelAndView adminPage() {

        ModelAndView model = new ModelAndView();
        model.addObject("title", "Spring Security Hello World");
        model.addObject("message", "This is protected page - Admin Page!");
        model.setViewName("admin");

        return model;
    }

    @RequestMapping(value = "/dba**", method = RequestMethod.GET)
    public ModelAndView dbaPage() {

        ModelAndView model = new ModelAndView();
        model.addObject("title", "Spring Security Hello World");
        model.addObject("message", "This is protected page - Database Page!");
        model.setViewName("admin");

        return model;
    }

    @RequestMapping(value = "/registration", params = {"name", "surname", "username", "password"}, method = RequestMethod.POST)
    public String showRegistrationForm(@ModelAttribute("user") User user,
                                       @RequestParam("confirmPassword") String confirmPassword,
                                       Model model) {
        System.out.println(user);

        if (!user.getPassword().equals(confirmPassword))
            return "redirect:/login?register_error=passwords not equal";

        if (userService.findUserByUsername(user.getUsername()) != null)
            return "redirect:/login?register_error=login already exists";

        userService.save(user);

        return "redirect:/login?register_success=register success";
    }

    @RequestMapping(value="/new_post", method=RequestMethod.GET)
    public String newPost() {
        System.out.println("get new_post !!!");
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        System.out.println("username: " + auth.getName());

        return "new_post";
    }

    @RequestMapping(value = "/addPost", params = {"body"}, method = RequestMethod.POST)
    public String addPost(
            @RequestParam("body") String body,
            Model model,
            Principal principal) {
        System.out.println("post addPost !!!");
        Authentication auth = SecurityContextHolder.getContext().getAuthentication();
        System.out.println(principal.getName());
        System.out.println("username: " + auth.getName() + " \nbody: " + body);
        Note note = new Note(userService.findUserByUsername(principal.getName()), body);
        noteService.addNote(note);

        return "redirect:/logged_user";
    }
}