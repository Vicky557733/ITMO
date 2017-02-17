package com.Vika.twitter.service;

import com.Vika.twitter.models.Note;
import com.Vika.twitter.models.User;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;

public interface NoteService {
    Note addNote(Note Note);
    Note updateNote(Note Note);
    void deleteNoteById(Long id);
    Iterable<Note> findAllNotesByUserId(Long id);
    Long countNotesByUser(User user);
    Iterable<Note> getAllNotes();
    Page<Note> getAllNotes(Pageable pageable);
}
