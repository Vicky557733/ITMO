package com.Vika.twitter.controller;

import com.Vika.twitter.models.Note;
import com.Vika.twitter.service.NoteService;
import com.Vika.twitter.service.impl.NoteServiceImpl;
import com.Vika.twitter.utils.Constants;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
@RequestMapping("/ajax")
public class AjaxController {

    @Autowired
    private NoteServiceImpl noteService;

    @GetMapping("/get_notes")
    @ResponseBody
    public  Iterable<Note> getNotes(
            @RequestParam("page") int page
    ) {
        return noteService.getAllNotes(new PageRequest(page, Constants.PRELOAD_NOTE_COUNT));
    }
}
