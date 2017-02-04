package com.Vika.twitter.service;

import com.Vika.twitter.models.Note;

import java.util.Date;

public interface NoteService {
    Note addNote(Note Note);
    Note updateNote(Note Note);
    void deleteNoteById(Long id);
    Iterable<Note> findAllNotesByUserId(Long id);
    Iterable<Note> findAllNotesByDate(Date date);
}
