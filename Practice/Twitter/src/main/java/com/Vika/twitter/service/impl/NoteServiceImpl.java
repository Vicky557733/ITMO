package com.Vika.twitter.service.impl;

import com.Vika.twitter.models.Note;
import com.Vika.twitter.models.User;
import com.Vika.twitter.models.repositories.NoteRepository;
import com.Vika.twitter.service.NoteService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Component;

import java.util.Date;

@Component
public class NoteServiceImpl implements NoteService{
    @Autowired
    private NoteRepository noteRepository;

    @Override
    public Note addNote(Note note) {
        return noteRepository.save(note);
    }

    @Override
    public Note updateNote(Note note) {
        return noteRepository.save(note);
    }

    @Override
    public void deleteNoteById(Long id) {
        noteRepository.delete(id);
    }

    @Override
    public Iterable<Note> findAllNotesByUserId(Long id) {
        return noteRepository.findAllByUserId(id);
    }

    @Override
    public Long countNotesByUser(User user){
        return noteRepository.countNotesByUser(user);
    }

    @Override
    public Iterable<Note> getAllNotes() {
        return noteRepository.findAll() ;
    }

    @Override
    public Page<Note> getAllNotes(Pageable pageable) {
        return noteRepository.findAll(pageable);
    }
}
