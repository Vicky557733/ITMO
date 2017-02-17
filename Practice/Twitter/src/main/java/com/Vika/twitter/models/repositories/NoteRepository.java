package com.Vika.twitter.models.repositories;

import com.Vika.twitter.models.Note;
import com.Vika.twitter.models.User;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import java.util.Date;

public interface NoteRepository extends CrudRepository<Note, Long> {
    @Query("select b from Note b where b.user = :id")
    Iterable<Note> findAllByUserId(@Param("id") Long id);

    Long countNotesByUser(User user);

    Page<Note> findAll(Pageable pageable);
}
