package com.Vika.twitter.service.impl;

import com.Vika.twitter.models.Note;
import com.Vika.twitter.models.repositories.NoteRepository;
import com.Vika.twitter.service.NoteService;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.Date;

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
    public Iterable<Note> findAllNotesByDate(Date date) {
        return noteRepository.findAllByDate(date);
    }
}
